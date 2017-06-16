/*
 * Target.hpp
 * wrapper to manage data going in and out of Kalman filter
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#ifndef __TARGET_HPP__
#define __TARGET_HPP__

// my Kalman stuff

#include "../basic-c/kalman_filter.h"
#include "../basic-c/linear_algebra.h"
#include "Points.h"

// generic c++ things
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>

class Target {
public:
 Target(int _n, int _m, TYPE* A_init, TYPE* C_init, TYPE* Q_init, TYPE* R_init, TYPE* P_init, TYPE* x_hat_init);
  ~Target();

  void update(int* ind_list, Points measurements, int num_points, double dt);
  void predict();
  void correct(bool found);
  bool choose_next_point(int* ind_list, Points measurements, int num_points);

  int  get_num_steps();
  void set_num_steps(int steps);

  int  get_num_empty_steps();
  void set_num_empty_steps(int steps);

  double get_radius();
  void   set_radius(double r);

private:
  
  TYPE *A, *C, *Q, *R, *P, *K, *x, *y, *x_hat,
       *x_hat_new, *A_T, *C_T, *id,
       *temp_1, *temp_2, *temp_3, *temp_4;

  int num_steps, num_empty_steps;
  int n, m;
  double radius; //note this is radius squared
};

#endif