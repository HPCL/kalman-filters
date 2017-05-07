/**
 * Test for the KalmanFilter class with 1D projectile motion.
 *
 * @author: Hayk Martirosyan
 * @date: 2014.11.15
 */

#include <iostream>
#include <vector>
#include <fstream>
#include </usr/local/include/eigen3/Eigen/Dense>
#include "kalman.hpp"

using namespace std;

#define FILE_NAME "../../data_generator/projectile_motion.csv"

typedef struct Points {
  double* x;
  double* y;
  int size;
} Points;

void test_original();
void test_projectile();
Points get_projectile_measurements(ifstream &file);

int main(int argc, char* argv[]) {
  // test_original();
  test_projectile();
  return 0;
}

void test_projectile() {

  int n = 6; // Number of states
  int m = 2; // Number of measurements

  double dt = 0.01; // Time step TODO this should probably come from the file

  Eigen::MatrixXd A(n, n); // System dynamics matrix
  Eigen::MatrixXd C(m, n); // Output matrix
  Eigen::MatrixXd Q(n, n); // Process noise covariance
  Eigen::MatrixXd R(m, m); // Measurement noise covariance
  Eigen::MatrixXd P(n, n); // Estimate error covariance

  // system dynamics matrix A (nxn)
  // 1  dt 0  0  0  0
  // 0  1  dt 0  0  0
  // 0  0  1  0  0  0
  // 0  0  0  1  dt 0
  // 0  0  0  0  1  dt
  // 0  0  0  0  0  1
  A << 1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1;

  // measurement matrix H
  // 1  0  0  0  0  0
  // 0  0  0  1  0  0
  C << 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0;

  // Reasonable covariance matrices
  // process noise covariance Q
  // 1e-2  0     0     0     0      0
  // 0     5.0   0     0     0      0
  // 0     0     1e-2  0     0      0
  // 0     0     0     1e-2  0      0
  // 0     0     0     0     5.0    0
  // 0     0     0     0     0      1e-2
  Q << 1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2;

  // measurement noise covariance R
  // 5 0
  // 0 5
  R << 5.0, 0, 0, 5.0;

  // error covariance P
  // 1     0     0     0     0      0
  // 0     1     0     0     0      0
  // 0     0     1     0     0      0
  // 0     0     0     1     0      0
  // 0     0     0     0     1      0
  // 0     0     0     0     0      1   
  P << 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1;

  cout << "\nA: \n" << A << endl;
  cout << "\nC: \n" << C << endl;
  cout << "\nQ: \n" << Q << endl;
  cout << "\nR: \n" << R << endl;
  cout << "\nP: \n" << P << endl;

  // get data
  ifstream file;
  file.open(FILE_NAME);
  Points measurements = get_projectile_measurements(file);

  cout << "n: " << measurements.size << endl;

  // Construct the filter
  KalmanFilter kf(dt, A, C, Q, R, P);

  // Best guess of initial states
  Eigen::VectorXd x0(n);
  x0 << measurements.x[0], 0, 0, measurements.y[0], 0, -9.81;
  kf.init(dt, x0);

  // Feed measurements into filter, output estimated states
  double t = 0;
  Eigen::VectorXd y(m);
  std::cout << "t = " << t << ", " << "x_hat[0]: " << kf.state().transpose() << std::endl;
  for(int i = 0; i < measurements.size; i++) {
    t += dt;
    y << measurements.x[i], measurements.y[i];
    kf.update(y);
    std::cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose()
        << ", x_hat[" << i << "] = " << kf.state().transpose() << std::endl;
  }


  delete measurements.x;
  delete measurements.y;
}

Points get_projectile_measurements(ifstream &file) {

  string header, temp;
  int n, i;

  getline(file, header);
  file >> n;
  cout << "\nn: " << n << endl; 
  Points data_in;
  data_in.size = n;
  data_in.x = new double[n];
  data_in.y = new double[n];

  i = 0;
  while (getline(file, temp, ',') && i < n) { //t

    getline(file, temp, ','); //x
    getline(file, temp, ','); //x_n
    data_in.x[i] = atof(temp.c_str());
    getline(file, temp, ','); //v_x
    getline(file, temp, ','); //v_xn
    getline(file, temp, ','); //a_x
    getline(file, temp, ','); //a_xn

    getline(file, temp, ','); //y
    getline(file, temp, ','); //y_n
    data_in.y[i] = atoi(temp.c_str());
    getline(file, temp, ','); //v_y
    getline(file, temp, ','); //v_yn
    getline(file, temp, ','); //a_y
    getline(file, temp); //a_yn

    i++;
  }

  return data_in;
}

void test_original() {

  int n = 3; // Number of states
  int m = 1; // Number of measurements

  double dt = 1.0/30; // Time step

  Eigen::MatrixXd A(n, n); // System dynamics matrix
  Eigen::MatrixXd C(m, n); // Output matrix
  Eigen::MatrixXd Q(n, n); // Process noise covariance
  Eigen::MatrixXd R(m, m); // Measurement noise covariance
  Eigen::MatrixXd P(n, n); // Estimate error covariance

  // Discrete LTI projectile motion, measuring position only
  A << 1, dt, 0, 0, 1, dt, 0, 0, 1;
  C << 1, 0, 0;

  // Reasonable covariance matrices
  Q << .05, .05, .0, .05, .05, .0, .0, .0, .0;
  R << 5;
  P << .1, .1, .1, .1, 10000, 10, .1, 10, 100;

  std::cout << "A: \n" << A << std::endl;
  std::cout << "C: \n" << C << std::endl;
  std::cout << "Q: \n" << Q << std::endl;
  std::cout << "R: \n" << R << std::endl;
  std::cout << "P: \n" << P << std::endl;

  // Construct the filter
  KalmanFilter kf(dt, A, C, Q, R, P);

  // List of noisy position measurements (y)
  std::vector<double> measurements = {
      1.04202710058, 1.10726790452, 1.2913511148, 1.48485250951, 1.72825901034,
      1.74216489744, 2.11672039768, 2.14529225112, 2.16029641405, 2.21269371128,
      2.57709350237, 2.6682215744, 2.51641839428, 2.76034056782, 2.88131780617,
      2.88373786518, 2.9448468727, 2.82866600131, 3.0006601946, 3.12920591669,
      2.858361783, 2.83808170354, 2.68975330958, 2.66533185589, 2.81613499531,
      2.81003612051, 2.88321849354, 2.69789264832, 2.4342229249, 2.23464791825,
      2.30278776224, 2.02069770395, 1.94393985809, 1.82498398739, 1.52526230354,
      1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913, 0.678547664519,
      0.562381751596, 0.355468474885, -0.155607486619, -0.287198661013, -0.602973173813
  };

  // Best guess of initial states
  Eigen::VectorXd x0(n);
  x0 << measurements[0], 0, -9.81;
  kf.init(dt, x0);

  // Feed measurements into filter, output estimated states
  double t = 0;
  Eigen::VectorXd y(m);
  std::cout << "t = " << t << ", " << "x_hat[0]: " << kf.state().transpose() << std::endl;
  for(int i = 0; i < measurements.size(); i++) {
    t += dt;
    y << measurements[i];
    kf.update(y);
    std::cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose()
        << ", x_hat[" << i << "] = " << kf.state().transpose() << std::endl;
  }

}
