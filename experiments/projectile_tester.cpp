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

// IO
#include <iostream>
#include <fstream> 

// my Kalman stuff
// extern "C" {
#include "../basic-c/kalman_filter.h"
#include "../basic-c/linear_algebra.h"
// }
#include "Points.h"
#include "Target.hpp"

// generic c++ things
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <vector>

#ifdef USE_CALI
#include <caliper/cali.h>
#endif

//TODO make these params or something
// #define IN_FILE_NAME "../data_generator/projectile_motion.csv"
// #define IN_FILE_NAME "../data_generator/multiple.csv"
#define IN_FILE_NAME "../data_generator/many.csv"

#define OUT_FILE_BC  "projectile_motion_out_bc.csv"
#define MAX_TARGETS  1000 //TODO only for now
#define EMPTY_LIMIT  5

using namespace std;

//void test_lapack(Points measurements); //TODO
//void test_autotuned(Points measurements); //TODO
void test_basic_c(Points measurements);
void test_basic_c_MTT(Points measurements);

void get_projectile_measurements(FILE *file, Points &data_in);
void write_output_line(ofstream &file, double data[], int length);

int main(int argc, char* argv[]) {

#ifdef USE_CALI
CALI_CXX_MARK_FUNCTION;
#endif

  FILE* file = fopen(IN_FILE_NAME, "r");
  Points measurements;
  
  get_projectile_measurements(file, measurements);
  
  cout << "Starting tests..." << endl;
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
  KALMAN_TYPE A_init[] = {1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1};

  // measurement matrix H
  // 1  0  0  0  0  0
  // 0  0  0  1  0  0
  KALMAN_TYPE C_init[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};

  // Reasonable covariance matrices
  // process noise covariance Q
  // 1e-2  0     0     0     0      0
  // 0     5.0   0     0     0      0
  // 0     0     1e-2  0     0      0
  // 0     0     0     1e-2  0      0
  // 0     0     0     0     5.0    0
  // 0     0     0     0     0      1e-2
  KALMAN_TYPE Q_init[] = {1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2};

  // measurement noise covariance R
  // 5 0
  // 0 5
  KALMAN_TYPE R_init[] = {5.0, 0, 0, 5.0};

  // error covariance P
  // 1     0     0     0     0      0
  // 0     1     0     0     0      0
  // 0     0     1     0     0      0
  // 0     0     0     1     0      0
  // 0     0     0     0     1      0
  // 0     0     0     0     0      1   
  KALMAN_TYPE P_init[] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1};


  KALMAN_TYPE x_hat_init[] = {0, 0, 0, 0, 0, -9.81};


  KALMAN_TYPE *A, *C, *Q, *R, *P, *K, *x, *y, *x_hat,
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
  double wall_t = 0.0;
  clock_t start;
  long num_updates = 0;

  // ofstream file;
  // file.open(OUT_FILE_BC);
  double out_buffer[n+1];

  KALMAN_TYPE A_init[] = {1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1, dt, 0, 0, 0, 0, 0, 1};
  KALMAN_TYPE C_init[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
  KALMAN_TYPE Q_init[] = {1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 1e-2, 0, 0, 0, 0, 0, 0, 5.0, 0, 0, 0, 0, 0, 0, 1e-2};
  KALMAN_TYPE R_init[] = {5.0, 0, 0, 5.0};
  KALMAN_TYPE P_init[] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1};

  KALMAN_TYPE x_hat_init[] = {0, 0, 0, 0, 0, 0};

  vector<Target*> targets; 

  int ind_list[MAX_TARGETS];
  int list_count = 0;
  int new_count = 0;

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
      start = clock();
      (*it)->update((int*)ind_list, measurements, list_count, dt);
      wall_t += clock() - start;
      num_updates++;
    }

    new_count = 0;
    for (int j = 0; j < list_count; j++) {
      if(!measurements.found[ind_list[j]]) {
        if (targets.size() == MAX_TARGETS) {
          printf("\n\nERROR too many targets testing MTT\n");
          exit(1);
        }
        x_hat_init[0] = measurements.x[ind_list[j]];
        x_hat_init[3] = measurements.y[ind_list[j]];

        temp_target = new Target(n, m, A_init, C_init, Q_init, R_init, P_init, x_hat_init);
        targets.push_back(temp_target);
        new_count++;
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
    // cout << "t: " << t << "    target count: " << targets.size() << "    new target count: " << new_count << endl;

  } // measurement loop

  // TODO destroy targets
  for (vector<Target*>::iterator it = targets.begin(); it != targets.end(); it++) {
    (*it)->~Target();
  }
  // file.close();

  cout << "testing basic c MTT" << endl;
  cout << "total update time    = " << (wall_t/CLOCKS_PER_SEC) << endl;
  cout << "total num updates    = " << num_updates << endl;
  cout << "avgerage update time = " << (wall_t/CLOCKS_PER_SEC)/num_updates << endl;

} // test_basic_c_MTT



void get_projectile_measurements(FILE *file, Points &data_in) {

  int n, i, j;
  char* tok;
  double t;
  int line_size = 312*MAX_TARGETS;

  char line[line_size];

  fgets(line, line_size, file); // header
  fgets(line, line_size, file); 
  n = atoi(line);

  data_in.size = n;
  data_in.x = (KALMAN_TYPE*)malloc(n * sizeof(KALMAN_TYPE));
  data_in.y = (KALMAN_TYPE*)malloc(n * sizeof(KALMAN_TYPE));
  data_in.t = (KALMAN_TYPE*)malloc(n * sizeof(KALMAN_TYPE));
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
