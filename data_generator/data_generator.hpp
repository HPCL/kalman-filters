/*
 * data_generator.hpp
 * come function and stuff to make synthetic data for Kalman filters
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#ifndef __DATA_GENERATOR_HPP__
#define __DATA_GENERATOR_HPP__


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <math.h>

using namespace std;

class DataGenerator {

public:
  DataGenerator(char* _out_file_name, int _num_points = 100000, double _stdev = 5);
  ~DataGenerator();

  //generates some noisy projectile motion data

  void generate_projectile_motion();
  void generate_sin_wave(double offset);
  void generate_straight_line(double offset, double slope);

  // copied verbatium from wikipedia, please dont fire me
  // https://en.wikipedia.org/wiki/Marsaglia_polar_method
  static double get_gaussian_noise(const double& mean, const double &std_dev);

// private: // public becaue I'm too laxy to do getters and setters
  char* out_file_name;
  int num_points;
  double stdev;
  ofstream out_file;

};


#endif