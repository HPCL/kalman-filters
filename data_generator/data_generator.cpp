/*
 * data_generator.cpp
 * come function and stuff to make synthetic data for Kalman filters
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/

#include "data_generator.hpp"
using namespace std;

DataGenerator::DataGenerator(char* _out_file_name, int _num_points /* = 100000*/ ) {
  out_file_name = _out_file_name;
  out_file.open(out_file_name);
  num_points = _num_points;
}

DataGenerator::~DataGenerator() {
  out_file.close();
}

// generate data based on projectile motion
// prints data to out_file as csv with header
// output includes time,
//                 position, velocity, acceleration
//                 for x and y with and without noise 
void DataGenerator::generate_projectile_motion() {

  //TODO figure out if these values are useful
  // assumes m/s but whatever
  double dt  = 0.01, 
         t   = 0.0,
         x   = 0.0,
         y   = 0.0,
         v_x = 60.0,
         v_y = 50.0,
         a_x = 0.0,   // assumes constant acceleration
         a_y = -9.8;

  double mean    = 0.0,
         std_dev = 5.0,
         noise   = 0.0;

  out_file << "t,x,x_n,v_x,v_xn,a_x,a_xn,y,y_n,v_y,v_yn,a_y,a_yn" << endl;
  out_file << num_points << endl;

  for (int i = 0; i < num_points; ++i) {
    t += dt;

    x += v_x * dt;
    y += v_y * dt;

    v_x += a_x * dt;
    v_y += a_y * dt;

    out_file << t << ",";

    noise = get_gaussian_noise(mean, std_dev);
    out_file << x << "," << x+noise << ",";
    noise = get_gaussian_noise(mean, std_dev);
    out_file << v_x << "," << v_x+noise << ",";
    noise = get_gaussian_noise(mean, std_dev);
    out_file << a_x << "," << a_x+noise << ",";

    noise = get_gaussian_noise(mean, std_dev);
    out_file << y << "," << y+noise << ",";
    noise = get_gaussian_noise(mean, std_dev);
    out_file << v_y << "," << v_y+noise << ",";
    noise = get_gaussian_noise(mean, std_dev);
    out_file << a_y << "," << a_y+noise << endl;
  }


}

// copied verbatium from wikipedia, please dont fire me
// https://en.wikipedia.org/wiki/Marsaglia_polar_method
double DataGenerator::get_gaussian_noise(const double& mean, const double &std_dev) {
  static bool hasSpare = false;
  static double spare;

  if(hasSpare)
  {
    hasSpare = false;
    return mean + std_dev * spare;
  }

  hasSpare = true;
  static double u, v, s;
  do
  {
    u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
    v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
    s = u * u + v * v;
  }
  while( (s >= 1.0) || (s == 0.0) );

  s = sqrt(-2.0 * log(s) / s);
  spare = v * s;
  return mean + std_dev * u * s;
}
