/* Original Author: Walter Lucetti
   source: https://github.com/Myzhar/simple-opencv-kalman-tracker
           http://www.robot-home.it/blog/en/software/ball-tracker-con-filtro-di-kalman/

 * OpenCV code for tracking a colored ball (or whatever) through a video
 * tracks the object through a recorded video using a self-written kalman filter

 * Modified by Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff
 * this code is based heavily on a version by Hayk Martirosyan
 *    https://github.com/hmartiro/kalman-cpp

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.
*/


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

#include <iostream>
#include <vector>
#include <ctime>

#include "../basic-c/kalman_filter.h"
#include "../basic-c/linear_algebra.h"

using namespace std;

// Color to be tracked
#define MIN_H_R 230
#define MAX_H_R 300
#define MIN_H_G 230
#define MAX_H_G 300
#define MIN_H_B 0
#define MAX_H_B 50

void init_kalman(TYPE** A, TYPE** C, TYPE** Q, TYPE** R, TYPE** P, TYPE** K, 
                TYPE** x, TYPE** y, TYPE** x_hat,
                TYPE dt, int n, int m);
bool init_video_output(cv::VideoWriter &vid, string name, cv::Size new_size, bool is_color);

int main() {

    // Kalman Filter
    int stateSize = 6;
    int measSize = 4;
    int contrSize = 0;

    unsigned int type = CV_32F;
    cv::KalmanFilter kf;

    //cv::Mat procNoise(stateSize, 1, type)
    // [E_x,E_y,E_v_x,E_v_y,E_w,E_h]

    /*
    A - system dynamics nxn
    C - H matrix - the measurement one, also output? mxn
    Q - process noise covariance nxn
    R - measurement noise covariance mxm
    P - error covariance nxn
    K - kalman gain nxm

    x     - estimated state n x m
    x_hat - the next prediction n x m
    y     - measurements m
    */
    TYPE *A, *C, *Q, *R, *P, *K, *x, *y, *x_hat;

    bool success = allocate_matrices(&A, &C, &Q, &R, &P, &K, stateSize, measSize);
    success = success && allocate_vectors(&x, &y, &x_hat, stateSize, measSize);
    success = success && allocate_temp_matrices(stateSize, measSize);
    if( !success ) {
        printf("ERROR allocating matrices\n");
        exit(1);
    }

    // video filename
    string in_name = "tennis_ball.mp4";
    // string in_name = "on-screen.h264";

    // Camera Capture
    cv::VideoCapture cap;
    if (!cap.open(in_name))
    {
        cout << "file '" << in_name << "' not found." << endl;
        return 1;
    }

    cv::VideoWriter out_thres; string thres_name = "thres_mod";
    cv::VideoWriter out_track; string track_name = "track_mod";

    cv::Size S =  cv::Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH), (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    init_video_output(out_thres, thres_name, S, false);
    init_video_output(out_track, track_name, S, true);

    char ch = 0;

    double ticks = 0;
    bool found = false;

    int notFoundCount = 0;

    clock_t predict_clock; 
    double tot_predict_time = 0.0;
    int    num_predictions = 0;
    clock_t correct_clock; 
    double tot_correct_time = 0.0;
    int    num_corrections = 0;


    cv::Mat res;

    // >>>>> Main loop
    while (cap.read(res))
    {
        double precTick = ticks;
        ticks = (double) cv::getTickCount();

        //double dT = (ticks - precTick) / cv::getTickFrequency(); //seconds
        double dT = 1.0 / 30.0; // 30 fps for video
        // Frame acquisition

        if (found) //TODO Kalman update?
        {
            //set dT for this round
            A[2] = dT;
            A[9] = dT;

            cout << "dT:" << endl << dT << endl;

            predict_clock = clock();
            predict(x_hat, stateSize, measSize, A, Q, P);
            tot_predict_time += double(clock() - predict_clock) / CLOCKS_PER_SEC;
            num_predictions++;
            cout << "x_hat (predicted):" << endl; 
            print_matrix(x_hat, stateSize, 1);
            cout << endl;

            cv::Rect predRect;
            predRect.width = x_hat[4];
            predRect.height = x_hat[5];
            predRect.x = x_hat[0] - predRect.width / 2;
            predRect.y = x_hat[1] - predRect.height / 2;

            cv::Point center;
            center.x = x_hat[0];
            center.y = x_hat[1];
            cv::circle(res, center, 2, CV_RGB(255,0,0), -1);

            cv::rectangle(res, predRect, CV_RGB(255,0,0), 2);
        }

        // >>>>> Noise smoothing
        cv::Mat blur;
        cv::GaussianBlur(res, blur, cv::Size(5, 5), 3.0, 3.0);
        // <<<<< Noise smoothing

        // >>>>> HSV conversion
        cv::Mat frmHsv;
        cv::cvtColor(blur, frmHsv, CV_BGR2HSV);
        // <<<<< HSV conversion

        // >>>>> Color Thresholding
        // Note: change parameters for different colors
        cv::Mat rangeRes = cv::Mat::zeros(res.size(), CV_8UC1);
        cv::inRange(frmHsv, cv::Scalar(MIN_H_B, MIN_H_G, MIN_H_R),
                    cv::Scalar(MAX_H_B, MAX_H_G, MAX_H_R), rangeRes);
        // <<<<< Color Thresholding

        // >>>>> Improving the result
        cv::erode(rangeRes, rangeRes, cv::Mat(), cv::Point(-1, -1), 2);
        cv::dilate(rangeRes, rangeRes, cv::Mat(), cv::Point(-1, -1), 2);
        // <<<<< Improving the result

        // Thresholding viewing
        out_thres.set(cv::CAP_PROP_FRAME_WIDTH, rangeRes.size().width);
        out_thres.set(cv::CAP_PROP_FRAME_HEIGHT, rangeRes.size().height);
        out_thres.write(rangeRes);

        // >>>>> Contours detection
        vector<vector<cv::Point> > contours;
        cv::findContours(rangeRes, contours, CV_RETR_EXTERNAL,
                         CV_CHAIN_APPROX_NONE);
        // <<<<< Contours detection

        // >>>>> Filtering
        vector<vector<cv::Point> > balls;
        vector<cv::Rect> ballsBox;
        for (size_t i = 0; i < contours.size(); i++)
        {
            cv::Rect bBox;
            bBox = cv::boundingRect(contours[i]);

            float ratio = (float) bBox.width / (float) bBox.height;
            if (ratio > 1.0f)
                ratio = 1.0f / ratio;

            // Searching for a bBox almost square
            if (ratio > 0.75 && bBox.area() >= 400)
            {
                balls.push_back(contours[i]);
                ballsBox.push_back(bBox);
            }
        }
        // <<<<< Filtering

        cout << "Balls found:" << ballsBox.size() << endl;

        // >>>>> Detection result
        for (size_t i = 0; i < balls.size(); i++)
        {
            cv::drawContours(res, balls, i, CV_RGB(20,150,20), 1);
            cv::rectangle(res, ballsBox[i], CV_RGB(0,255,0), 2);

            cv::Point center;
            center.x = ballsBox[i].x + ballsBox[i].width / 2;
            center.y = ballsBox[i].y + ballsBox[i].height / 2;
            cv::circle(res, center, 2, CV_RGB(20,150,20), -1);

            stringstream sstr;
            sstr << "(" << center.x << "," << center.y << ")";
            cv::putText(res, sstr.str(),
                        cv::Point(center.x + 3, center.y - 3),
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(20,150,20), 2);
        }
        // <<<<< Detection result

        // >>>>> Kalman Update
        if (balls.size() == 0)
        {
            notFoundCount++;
            cout << "notFoundCount:" << notFoundCount << endl;
            if( notFoundCount >= 100 )
            {
                found = false;
            }
        }
        else
        {
            notFoundCount = 0;

            //measurement vector
            y[0] = ballsBox[0].x + ballsBox[0].width / 2;
            y[1] = ballsBox[0].y + ballsBox[0].height / 2;
            y[2] = (float)ballsBox[0].width;
            y[3] = (float)ballsBox[0].height;

            if (!found) // First detection! 
            {
                init_kalman(&A, &C, &Q, &R, &P, &K, &x, &y, &x_hat, dT, stateSize, measSize); 

                found = true;
            }
            else {
                correct_clock = clock();
                correct(y, x_hat, stateSize, measSize, C, R, P, K);
                tot_correct_time += double(clock() - correct_clock) / CLOCKS_PER_SEC;
                num_corrections++;
                // cout << "x_hat (corrected):" << endl; 
                // print_matrix(x_hat, stateSize, 1);
            }

            cout << "Measure matrix:" << endl;
            print_matrix(y, measSize, 1);
            cout << endl;

            // cout << "K:" << endl;
            // print_matrix(K, stateSize, measSize);
            // cout << endl;

            // cout << "P:" << endl;
            // print_matrix(P, stateSize, stateSize);
            // cout << endl;

            // cout << "H/ C:" << endl;
            // print_matrix(C, measSize, stateSize);
            // cout << endl;
        }
        // <<<<< Kalman Update

        // Final result
        out_track.set(cv::CAP_PROP_FRAME_WIDTH, res.size().width);
        out_track.set(cv::CAP_PROP_FRAME_HEIGHT, res.size().height);
        out_track.write(res);

    }
    // <<<<< Main loop

    cout << endl;
    cout << "total time for predict:   " << tot_predict_time << endl;
    cout << "number of predictions:    " << num_predictions << endl;
    cout << "average time per predict: " << tot_predict_time / num_predictions << endl;
    cout << endl;
    cout << "total time for correct:   " << tot_correct_time << endl;
    cout << "number of corrections:    " << num_corrections << endl;
    cout << "average time per correct: " << tot_correct_time / num_corrections << endl;
    cout << endl;


    destroy_matrices(A, C, Q, R, P, K);
    destroy_vectors(x, y, x_hat);
    destroy_temp_matrices();
    cap.release();

    return 0;
}


bool init_video_output(cv::VideoWriter &vid, string name, cv::Size new_size, bool is_color){
    cv::Size frame_size  = cv::Size(new_size);
    char* file_ext = (char*)".h264";
    bool success = true;

    int ex = cv::VideoWriter::fourcc('X','2','6','4');    //TODO make more general?

    stringstream ss;
    ss << name << file_ext;

    vid.open(ss.str(),  ex, 4.0, frame_size, is_color);  
    if(!vid.isOpened()) {
        cout << "ERROR: video writer didn't open for video " << name << file_ext << endl;
        cout << "Press enter to continue..." << endl;
        getchar();
        success  = false;
    }

    return success;
}

void init_kalman(TYPE** A, TYPE** C, TYPE** Q, TYPE** R, TYPE** P, TYPE** K, 
                TYPE** x, TYPE** y, TYPE** x_hat,
                TYPE dt, int n, int m) {

    // User set params
    // TODO maybe make this easier to change
    int stateSize = 6;
    int measSize = 4;
    int contrSize = 0;
    unsigned int type = CV_32F;

    // Transition State Matrix A
    // Note: set dT at each processing step!
    // [ 1 0 dT 0  0 0 ]
    // [ 0 1 0  dT 0 0 ]
    // [ 0 0 1  0  0 0 ]
    // [ 0 0 0  1  0 0 ]
    // [ 0 0 0  0  1 0 ]
    // [ 0 0 0  0  0 1 ]
    TYPE A_init[] = {1, 0, dt, 0, 0, 0, 
                     0, 1, 0, dt, 0, 0,
                     0, 0, 1, 0,  0, 0,
                     0, 0, 0, 1,  0, 0,
                     0, 0, 0, 0,  1, 0,
                     0, 0, 0, 0,  0, 1};

    // Measure Matrix H
    // [ 1 0 0 0 0 0 ]
    // [ 0 1 0 0 0 0 ]
    // [ 0 0 0 0 1 0 ]
    // [ 0 0 0 0 0 1 ]
    TYPE C_init[] = {1, 0, 0, 0, 0, 0, 
                     0, 1, 0, 0, 0, 0,
                     0, 0, 0, 0, 1, 0,
                     0, 0, 0, 0, 0, 1};

    // Measure Matrix K
    // Should not matter
    TYPE K_init[] = {1, 0, 0, 0, 
                     0, 1, 0, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1};

    // Process Noise Covariance Matrix Q
    // [ Ex   0   0     0     0    0  ]
    // [ 0    Ey  0     0     0    0  ]
    // [ 0    0   Ev_x  0     0    0  ]
    // [ 0    0   0     Ev_y  0    0  ]
    // [ 0    0   0     0     Ew   0  ]
    // [ 0    0   0     0     0    Eh ]
    //cv::setIdentity(kf.processNoiseCov, cv::Scalar(1e-2));
    TYPE Q_init[] = {1e-2, 0,    0,   0,   0,    0, 
                     0,    1e-2, 0,   0,   0,    0,
                     0,    0,    5.0, 0,   0,    0,
                     0,    0,    0,   5.0, 0,    0,
                     0,    0,    0,   0,   1e-2, 0,
                     0,    0,    0,   0,   0,    1e-2};

    // Reasonable covariance matrices
    TYPE R_init[] = {1e-1, 0,    0,    0, 
                     0,    1e-1, 0,    0,
                     0,    0,    1e-1, 0,
                     0,    0,    0,    1e-1};

    TYPE P_init[] = {1, 0, 0, 0, 0, 0, 
                     0, 1, 0, 0, 0, 0,
                     0, 0, 1, 0, 0, 0,
                     0, 0, 0, 1, 0, 0,
                     0, 0, 0, 0, 1, 0,
                     0, 0, 0, 0, 0, 1};

    copy_mat(A_init, *A, n * n);
    copy_mat(C_init, *C, n * m);
    copy_mat(Q_init, *Q, n * n);
    copy_mat(R_init, *R, m * m);
    copy_mat(P_init, *P, n * n);
    copy_mat(K_init, *K, n * m);

    (*x_hat)[0] = (*y)[0];
    (*x_hat)[1] = (*y)[1];
    (*x_hat)[2] = 0;
    (*x_hat)[3] = 0;
    (*x_hat)[4] = (*y)[2];
    (*x_hat)[5] = (*y)[3];
    
}