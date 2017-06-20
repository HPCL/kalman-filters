/*
 * projectile_tester.cpp
 * code to test and compare various kalman implementaions
 * uses projetile motion data
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff
 * this code is based heavily on a version by Hayk Martirosyan
 *    https://github.com/hmartiro/kalman-cpp

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

 * Things that need to be established
    n - num states
    m - num measurements

    A - system dynamics nxn
    C - H matrix - the measurement one, also output? mxn
    Q - process noise covariance nxn
    R - measurement noise covariance mxm
    P - error covariance nxn
    K - kalman gain nxm

    x     - estimated state n x 1
    x_hat - the next prediction n x 1
    y     - measurements m x 1

    t  - time
    dt - time step
*/

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

// IO
#include <iostream>
#include <fstream> 

// my Kalman stuff
// 
#include "../basic-c/kalman_filter.h"
#include "../basic-c/linear_algebra.h"
#include "Points.h"
#include "Target.hpp"

// generic c++ things
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>

//TODO make these params or something
// #define IN_FILE_NAME "../data_generator/projectile_motion.csv"
#define IN_FILE_NAME "../data_generator/multiple.csv"
#define OUT_FILE_CV  "projectile_motion_out_cv.csv"
#define OUT_FILE_BC  "projectile_motion_out_bc.csv"
#define MAX_TARGETS  100 //TODO only for now
#define EMPTY_LIMIT  10

using namespace std;

//void test_lapack(Points measurements); //TODO
//void test_autotuned(Points measurements); //TODO
void test_basic_c(Points measurements);
void test_basic_c_MTT(Points measurements);
void test_opencv(Points measurements);
void init_cv_kalman(cv::KalmanFilter &kf, int stateSize, int measSize, double dT);

void get_projectile_measurements(FILE *file, Points &data_in);
void write_output_line(ofstream &file, double data[], int length);

int main(int argc, char* argv[]) {

  FILE* file = fopen(IN_FILE_NAME, "r");
  Points measurements;

  get_projectile_measurements(file, measurements);
  
  cout << "Starting tests..." << endl;
  // test_opencv(measurements);
  // test_basic_c(measurements);
  test_basic_c_MTT(measurements);

  cout << "Freeing memory..." << endl;

  free(measurements.x);
  free(measurements.y);
  free(measurements.t);
  free(measurements.found);

  cout << "done." << endl;

  return 0;
}


void test_basic_c(Points measurements) {

  char success = 0;
  int i = 0;

  int n = 6; // Number of states
  int m = 2; // Number of measurements

  double dt = 0.01; // Time step TODO this should probably come from the file
  double t  = 0;

  ofstream file;
  file.open(OUT_FILE_BC);
  double out_buffer[n+1];

  // system dynamics matrix A (nxn)
  // 1  dt 0  0  0  0
  // 0  1  dt 0  0  0
  // 0  0  1  0  0  0
  // 0  0  0  1  dt 0
  // 0  0  0  0  1  dt
  // 0  0  0  0  0  1
  TYPE A_init[] = {1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1};

  // measurement matrix H
  // 1  0  0  0  0  0
  // 0  0  0  1  0  0
  TYPE C_init[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};

  // Reasonable covariance matrices
  // process noise covariance Q
  // 1e-2  0     0     0     0      0
  // 0     5.0   0     0     0      0
  // 0     0     1e-2  0     0      0
  // 0     0     0     1e-2  0      0
  // 0     0     0     0     5.0    0
  // 0     0     0     0     0      1e-2
  TYPE Q_init[] = {1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2};

  // measurement noise covariance R
  // 5 0
  // 0 5
  TYPE R_init[] = {5.0, 0, 0, 5.0};

  // error covariance P
  // 1     0     0     0     0      0
  // 0     1     0     0     0      0
  // 0     0     1     0     0      0
  // 0     0     0     1     0      0
  // 0     0     0     0     1      0
  // 0     0     0     0     0      1   
  TYPE P_init[] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1};


  TYPE x_hat_init[] = {0, 0, 0, 0, 0, -9.81};


  TYPE *A, *C, *Q, *R, *P, *K, *x, *y, *x_hat,
       *x_hat_new, *A_T, *C_T, *id,
       *temp_1, *temp_2, *temp_3, *temp_4;

  success = allocate_matrices(&A, &C, &Q, &R, &P, &K, n, m);
  success = success && allocate_vectors(&x, &y, &x_hat, n, m);
  success = success && allocate_temp_matrices(&x_hat_new, &A_T, &C_T, &id,
                                              &temp_1, &temp_2, &temp_3, &temp_4, n, m);

  if( !success ) {
    printf("ERROR allocating matrices\n");
    exit(1);
  }


  x_hat_init[0] = measurements.x[0];
  x_hat_init[3] = measurements.y[0];

  copy_mat(A_init, A, n * n);
  copy_mat(C_init, C, n * m);
  copy_mat(Q_init, Q, n * n);
  copy_mat(R_init, R, m * m);
  copy_mat(P_init, P, n * n);
  copy_mat(x_hat_init, x_hat, n);

  // printf("n: %d\n", measurements.size);
  // printf("\nA:\n");
  // print_matrix(A, n, n);
  // printf("\nC:\n");
  // print_matrix(C, m, n);
  // printf("\nQ:\n");
  // print_matrix(Q, n, n);
  // printf("\nR:\n");
  // print_matrix(R, m, m);
  // printf("\nP:\n");
  // print_matrix(P, n, n);

  // printf("t     = %f\n", t);
  // printf("x_hat = ");
  // print_matrix(x_hat, 1, n);
  // printf("\n");

  for(i = 0; i < measurements.size; i++) {
    y[0] = measurements.x[i];
    y[1] = measurements.y[i];

    update(y, x_hat, &t, dt, n, m, A,  C,  Q,  R,  P,  K,
           x_hat_new, A_T, C_T, id, temp_1, temp_2, temp_3, temp_4);

    out_buffer[0] = t;
    for (int j = 0; j < n; j++) out_buffer[j+1] = x_hat[j];
    write_output_line(file, out_buffer, n+1);
    // printf("t     = %f\n", t);
    // printf("y = ");
    // print_matrix(y, 1, m);
    // printf("x_hat = ");
    // print_matrix(x_hat, 1, n);
    // printf("\n");

    t += dt;

  }

  destroy_matrices(A, C, Q, R, P, K);
  destroy_vectors(x, y, x_hat);
  destroy_temp_matrices(x_hat_new, A_T, C_T, id,
                        temp_1, temp_2, temp_3, temp_4);

  file.close();

} // test_basic_c




void test_basic_c_MTT(Points measurements) {

  char success = 0;
  int i = 0;

  int n = 6; // Number of states
  int m = 2; // Number of measurements

  double dt = 0.01; // Time step TODO this should probably come from the file
  double t  = 0;

  // ofstream file;
  // file.open(OUT_FILE_BC);
  double out_buffer[n+1];

  TYPE A_init[] = {1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1};
  TYPE C_init[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
  TYPE Q_init[] = {1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2};
  TYPE R_init[] = {5.0, 0, 0, 5.0};
  TYPE P_init[] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1};

  TYPE x_hat_init[] = {0, 0, 0, 0, 0, 0};

  vector<Target*> targets; 

  int ind_list[MAX_TARGETS];
  int list_count = 0;

  Target* temp_target;

  x_hat_init[0] = measurements.x[0];
  x_hat_init[3] = measurements.y[0];

  for(i = 0; i < measurements.size; ) {
    list_count = 0;
    ind_list[list_count] = i;
    t = measurements.t[i];
    i++;
    list_count++;
    while( (i < measurements.size) && (measurements.t[i] == t) ) {
      ind_list[list_count] = i;
      i++;
      list_count++;
    }

    for (vector<Target*>::iterator it = targets.begin(); it != targets.end(); it++) {
      (*it)->update((int*)ind_list, measurements, list_count, dt);
    }

    for (int j = 0; j < list_count; j++) {
      if(!measurements.found[ind_list[j]]) {
        if (targets.size() == MAX_TARGETS) {
          printf("\n\nERROR too many targets testing MTT\n\n");
          exit(1);
        }
        x_hat_init[0] = measurements.x[ind_list[j]];
        x_hat_init[3] = measurements.y[ind_list[j]];

        temp_target = new Target(n, m, A_init, C_init, Q_init, R_init, P_init, x_hat_init);
        targets.push_back(temp_target);
      }
    }

    out_buffer[0] = t;
    // for (int j = 0; j < n; j++) out_buffer[j+1] = x_hat[j];
    // write_output_line(file, out_buffer, n+1);

    for (vector<Target*>::iterator it = targets.begin(); it != targets.end(); it++) {
      if((*it)->get_num_empty_steps() > EMPTY_LIMIT) {
        (*it)->~Target();
        targets.erase(it);
      }
    }

    // t += dt;
    cout << "t: " << t << "    target count: " << targets.size() << endl;

  } // measurement loop

  // TODO destroy targets
  for (vector<Target*>::iterator it = targets.begin(); it != targets.end(); it++) {
    (*it)->~Target();
  }
  // file.close();

} // test_basic_c_MTT



void test_opencv(Points measurements) {

  // Kalman Filter
  int stateSize = 6;
  int measSize  = 2;
  int i = 0, j = 0;
  double dT = 0.01;
  double T  = 0.0;

  ofstream file;
  file.open(OUT_FILE_CV);
  double out_buffer[stateSize+1];

  unsigned int type = CV_32F;
  cv::KalmanFilter kf;

  cv::Mat state(stateSize, 1, type); 
  cv::Mat meas(measSize, 1, type);  

  init_cv_kalman(kf, stateSize, measSize, dT);

  kf.statePre.at<float>(0)  = measurements.x[0];
  kf.statePost.at<float>(0) = measurements.x[0];
  kf.statePre.at<float>(3)  = measurements.y[0];
  kf.statePost.at<float>(3) = measurements.y[0];
  kf.statePre.at<float>(5)  = -9.81f;
  kf.statePost.at<float>(5) = -9.81f;

  // clock_t predict_clock; 
  // double tot_predict_time = 0.0;
  // int    num_predictions = 0;
  // clock_t correct_clock; 
  // double tot_correct_time = 0.0;
  // int    num_corrections = 0;

  // first measurement

  meas.at<float>(0) = measurements.x[0];
  meas.at<float>(1) = measurements.y[0];

  state.at<float>(0) = measurements.x[0];
  state.at<float>(1) = 0;
  state.at<float>(2) = 0;
  state.at<float>(3) = measurements.y[0];
  state.at<float>(4) = 0;
  state.at<float>(5) = -9.81f;

  // TODO for loop
  for(i = 0; i < measurements.size; i++) {

    // predict_clock = clock();
    state = kf.predict();
    // tot_predict_time += double(clock() - predict_clock) / CLOCKS_PER_SEC;
    // num_predictions++;
    // cout << "State post:" << endl << state << endl;
    out_buffer[0] = T;
    for (int j = 0; j < stateSize; j++) out_buffer[j+1] = state.at<float>(j);
    write_output_line(file, out_buffer, stateSize+1);

    meas.at<float>(0) = measurements.x[i];
    meas.at<float>(1) = measurements.y[i];

    // correct_clock = clock();
    kf.correct(meas); // Kalman Correction
    // tot_correct_time += double(clock() - correct_clock) / CLOCKS_PER_SEC;
    // num_corrections++;

    // cout << "Measure matrix:" << endl << meas << endl;
    T += dT;
  }

  // cout << endl;
  // cout << "total time for predict:   " << tot_predict_time << endl;
  // cout << "number of predictions:    " << num_predictions << endl;
  // cout << "average time per predict: " << tot_predict_time / num_predictions << endl;
  // cout << endl;
  // cout << "total time for correct:   " << tot_correct_time << endl;
  // cout << "number of corrections:    " << num_corrections << endl;
  // cout << "average time per correct: " << tot_correct_time / num_corrections << endl;
  // cout << endl;
  file.close();
    
}

void init_cv_kalman(cv::KalmanFilter &kf, int stateSize, int measSize, double dT) {
    
  // User set params
  // TODO maybe make this easier to change

  int contrSize = 0;
  unsigned int type = CV_32F;

  kf.init(stateSize, measSize, contrSize, type);

  // Transition State Matrix A
  // system dynamics matrix A (nxn)
  // 1  dt 0  0  0  0
  // 0  1  dt 0  0  0
  // 0  0  1  0  0  0
  // 0  0  0  1  dt 0
  // 0  0  0  0  1  dt
  // 0  0  0  0  0  1
  cv::setIdentity(kf.transitionMatrix);
  kf.transitionMatrix.at<float>(1) = dT; 
  kf.transitionMatrix.at<float>(8) = dT;
  kf.transitionMatrix.at<float>(22) = dT;
  kf.transitionMatrix.at<float>(29) = dT;

  // Measure Matrix H
  // 1  0  0  0  0  0
  // 0  0  0  1  0  0
  kf.measurementMatrix = cv::Mat::zeros(measSize, stateSize, type);
  kf.measurementMatrix.at<float>(0) = 1.0f;
  kf.measurementMatrix.at<float>(9) = 1.0f;

  // Process Noise Covariance Matrix Q
  // 1e-2  0     0     0     0      0
  // 0     5.0   0     0     0      0
  // 0     0     1e-2  0     0      0
  // 0     0     0     1e-2  0      0
  // 0     0     0     0     5.0    0
  // 0     0     0     0     0      1e-2
  kf.processNoiseCov = cv::Mat::zeros(stateSize, stateSize, type);
  kf.processNoiseCov.at<float>(0)  = 1e-2;
  kf.processNoiseCov.at<float>(7)  = 5.0f;
  kf.processNoiseCov.at<float>(14) = 1e-2;
  kf.processNoiseCov.at<float>(21) = 1e-2;
  kf.processNoiseCov.at<float>(28) = 5.0f;
  kf.processNoiseCov.at<float>(35) = 1e-2;

  // Measures Noise Covariance Matrix R
  // 5 0
  // 0 5
  cv::setIdentity(kf.measurementNoiseCov, cv::Scalar(5.0f));


  // error covariance P
  // 1     0     0     0     0      0
  // 0     1     0     0     0      0
  // 0     0     1     0     0      0
  // 0     0     0     1     0      0
  // 0     0     0     0     1      0
  // 0     0     0     0     0      1    
  cv::setIdentity(kf.errorCovPre); 

}


void get_projectile_measurements(FILE *file, Points &data_in) {

  int n, i, j;
  char* tok;
  double t;
  int line_size = 5120;

  char line[line_size];

  fgets(line, line_size, file); // header
  fgets(line, line_size, file); 
  n = atoi(line);

  data_in.size = n;
  data_in.x = (TYPE*)malloc(n * sizeof(TYPE));
  data_in.y = (TYPE*)malloc(n * sizeof(TYPE));
  data_in.t = (TYPE*)malloc(n * sizeof(TYPE));
  data_in.found = (bool*)malloc(n * sizeof(bool));

  if( (data_in.x == NULL) || (data_in.y == NULL) || (data_in.t == NULL) || (data_in.found == NULL) ) {
    printf("\n\nERROR allocating matrices in get_projectile_measurements\n\n");
    exit(1);
  }

  i = 0;
  while (fgets(line, line_size, file)) { 

    tok = strtok(line, ",");
    j = 0;
    t = atof(tok);
    while (tok != NULL) {

      if(j%12 == 2) {
        data_in.x[i] = atof(tok);

      } else if(j%12 == 8) {
        data_in.y[i] = atof(tok);
        data_in.t[i] = t;
        data_in.found[i] = false;
        i++;

      } 

      tok = strtok(NULL, ",");
      j++;

    }
  }
}

void write_output_line(ofstream &file, double data[], int length) {
  for (int i = 0; i < length-1; i++) {
    file << data[i] << ",";
  }
  file << data[length-1] << "\n";
}
