/*
 * Target.cpp
 * wrapper to manage data going in and out of Kalman filter
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#include "Target.hpp"

Target::Target(int _n, int _m, TYPE* A_init, TYPE* C_init, TYPE* Q_init, TYPE* R_init, TYPE* P_init, TYPE* x_hat_init) {
  n = _n;
  m = _m;

  num_steps = 0;
  num_empty_steps = 0;

  radius = 1000;

  bool success;

  success = allocate_matrices(&A, &C, &Q, &R, &P, &K, n, m);
  success = success && allocate_vectors(&x, &y, &x_hat, n, m);
  success = success && allocate_temp_matrices(&x_hat_new, &A_T, &C_T, &id,
                                              &temp_1, &temp_2, &temp_3, &temp_4, n, m);

  if( !success ) {
    printf("\n\nERROR allocating matrices in Target class\n\n");
    exit(1);
  }

  copy_mat(A_init, A, n * n);
  copy_mat(C_init, C, n * m);
  copy_mat(Q_init, Q, n * n);
  copy_mat(R_init, R, m * m);
  copy_mat(P_init, P, n * n);
  copy_mat(x_hat_init, x_hat, n);
}

Target::~Target() {
  destroy_matrices(A, C, Q, R, P, K);
  destroy_vectors(x, y, x_hat);
  destroy_temp_matrices(x_hat_new, A_T, C_T, id, temp_1, temp_2, temp_3, temp_4);
}


void Target::update(int* ind_list, Points measurements, int num_points, double dt) {

  bool found;

  predict();
  found = choose_next_point(ind_list, measurements, num_points);
  correct(found);

  num_steps++;
}

void Target::predict() {
  ::predict(x_hat, n, m, A, Q, P, x_hat_new, A_T, temp_1, temp_2);
}

void Target::correct(bool found) {
  if(found) {
    ::correct(y, x_hat, n, m, C, R, P, K, x_hat_new, C_T, id, temp_1, temp_2, temp_3, temp_4);
  } else {
    num_empty_steps++;
  }
}

bool Target::choose_next_point(int* ind_list, Points measurements, int num_points) {
  bool found = false;

  double dist, min_dist = -1;
  double dx, dy;
  int min_ind;

  for (int i = 0; i < num_points; i++) {
    dx = x_hat_new[0] - measurements.x[ind_list[i]];
    dy = x_hat_new[3] - measurements.y[ind_list[i]];
    dist = dx*dx + dy*dy;

    // if( ((dist < min_dist) || (min_dist == -1)) ){
    if( (dist < radius) && ((dist < min_dist) || (min_dist == -1)) ){
      min_ind = i;
      found = true;
    } 
  }

  if (found){
    y[0] = measurements.x[ind_list[min_ind]];
    y[1] = measurements.y[ind_list[min_ind]];
    measurements.found[ind_list[min_ind]] = true;
  }

  return found;
}





/************************ Getters and Setters *************************/


int  Target::get_num_steps() {
  return num_steps;
}

void Target::set_num_steps(int steps) {
  num_steps = steps;  
}


int  Target::get_num_empty_steps() {
  return num_empty_steps;
}

void Target::set_num_empty_steps(int steps) {
  num_empty_steps = steps;
}


double Target::get_radius() {
  return radius;
}

void Target::set_radius(double r) {
  radius = r;
}


