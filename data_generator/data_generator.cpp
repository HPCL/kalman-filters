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

DataGenerator::DataGenerator(char* _out_file_name, int _num_points /* = 100000*/, double _stdev /* = 5*/ ) {
  out_file_name = _out_file_name;
  stdev = _stdev;
  out_file.open(out_file_name);
  num_points = _num_points;
}

DataGenerator::~DataGenerator() {
  out_file.close();
}





void DataGenerator::generate_projectile_motion_point(double &x,   double &y,
                                                double &v_x, double &v_y,
                                                double &a_x, double &a_y,
                                                double &dt ){

    x += v_x * dt;
    y += v_y * dt;

    v_x += a_x * dt;
    v_y += a_y * dt;
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
         std_dev = stdev,
         noise   = 0.0;

  out_file << "t,x,x_n,v_x,v_xn,a_x,a_xn,y,y_n,v_y,v_yn,a_y,a_yn" << endl;
  out_file << num_points << endl;

  for (int i = 0; i < num_points; ++i) {
    t += dt;

    generate_projectile_motion_point(x, y, v_x, v_y, a_x, a_y, dt);

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



void DataGenerator::generate_sin_wave_point(double &x,   double &y,
                                       double &v_x, double &v_y,
                                       double &a_x, double &a_y,
                                       double &dt ){

    x += v_x * dt;
    y += v_y * dt;

    v_x += a_x * dt;
    v_y  = 100*cos(x/20);

}


// generate data based on sin wave
// prints data to out_file as csv with header
// output includes time,
//                 position, velocity, acceleration
//                 for x and y with and without noise 
void DataGenerator::generate_sin_wave(double offset) {

  //TODO figure out if these values are useful
  // assumes m/s but whatever
  double dt  = 0.01, 
         t   = 0.0,
         x   = 0.0,
         y   = offset,
         v_x = 60.0,
         v_y = cos(x/20),
         a_x = 0.0,   // assumes constant acceleration
         a_y = 0;

  double mean    = 0.0,
         std_dev = stdev,
         noise   = 0.0;

  out_file << "t,x,x_n,v_x,v_xn,a_x,a_xn,y,y_n,v_y,v_yn,a_y,a_yn" << endl;
  out_file << num_points << endl;

  for (int i = 0; i < num_points; ++i) {
    t += dt;

    generate_sin_wave_point(x, y, v_x, v_y, a_x, a_y, dt);

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

void DataGenerator::generate_straight_line_point(double &x,   double &y,
                                            double &v_x, double &v_y,
                                            double &a_x, double &a_y,
                                            double &dt ){

    x += v_x * dt;
    y += v_y * dt;

    v_x += a_x * dt;
    v_y += a_y * dt;

}

// generate data based on sin wave
// prints data to out_file as csv with header
// output includes time,
//                 position, velocity, acceleration
//                 for x and y with and without noise 
void DataGenerator::generate_straight_line(double offset, double slope) {

  //TODO figure out if these values are useful
  // assumes m/s but whatever
  double dt  = 0.01, 
         t   = 0.0,
         x   = 0.0,
         y   = offset,
         v_x = 60.0,
         v_y = slope/dt,
         a_x = 0.0,   // assumes constant acceleration
         a_y = 0.0;

  double mean    = 0.0,
         std_dev = stdev,
         noise   = 0.0;

  out_file << "t,x,x_n,v_x,v_xn,a_x,a_xn,y,y_n,v_y,v_yn,a_y,a_yn" << endl;
  out_file << num_points << endl;

  for (int i = 0; i < num_points; ++i) {
    t += dt;

    generate_straight_line_point(x, y, v_x, v_y, a_x, a_y, dt);

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

void DataGenerator::init_multiple(int num_traces, int path_list[], 
                                  double x[], double y[], 
                                  double v_x[], double v_y[], 
                                  double a_x[], double a_y[],
                                  double dt) {

  for (int i = 0; i < num_traces; i++) {
    switch(path_list[i]) {
      case PROJECTILE:
        x[i]   = 0.0;
        y[i]   = 0.0;
        v_x[i] = rand()%30 + 50;
        v_y[i] = rand()%30 + 50;
        a_x[i] = 0.0;
        a_y[i] = -9.8;
        break;

      case SIN_WAVE:
        x[i]   = 0.0;
        y[i]   = rand()%1000;
        v_x[i] = rand()%30 + 50;
        v_y[i] = cos(x[i]/20);
        a_x[i] = 0.0;
        a_y[i] = 0;
        break;

      case LINE:
      default:
        x[i]   = 0.0;
        y[i]   = rand()%30 + 50;
        v_x[i] = rand()%30 + 50;
        v_y[i] = (rand()%1000)/dt;
        a_x[i] = 0.0;
        a_y[i] = 0.0;
    }
  }

}

// generate data for multiple paths
// prints data to out_file as csv with header
// output includes time,
//                 position, velocity, acceleration
//                 for x and y with and without noise 
void DataGenerator::generate_multiple(int num_traces, int path_list[]) {

  //TODO figure out if these values are useful
  // assumes m/s but whatever
  double dt  = 0.01, 
         t   = 0.0,
         x[num_traces],
         y[num_traces],
         v_x[num_traces],
         v_y[num_traces],
         a_x[num_traces],
         a_y[num_traces];

  double mean    = 0.0,
         std_dev = stdev,
         noise   = 0.0;

  init_multiple(num_traces, path_list, x, y, v_x, v_y, a_x, a_y, dt);

  out_file << "t,";
  for (int i = 0; i < num_traces; i++)
    out_file << "x" << i <<",x" << i <<"_n,v_x" << i <<",v_x" << i <<"n,a_x" << i <<",a_x" << i <<"n,y" << i <<",y" << i <<"_n,v_y" << i <<",v_y" << i <<"n,a_y" << i <<",a_y" << i <<"n,"; 
  out_file << endl;
  out_file << num_points << endl;

  for (int i = 0; i < num_points; ++i) {
    t += dt;
    out_file << t << ",";

    for (int j = 0; j < num_traces; j++) {

      switch(path_list[j]) {
      case PROJECTILE:
        generate_projectile_motion_point(x[j], y[j], v_x[j], v_y[j], a_x[j], a_y[j], dt);
        break;

      case SIN_WAVE:
        generate_sin_wave_point(x[j], y[j], v_x[j], v_y[j], a_x[j], a_y[j], dt);
        break;

      case LINE:
      default:
        generate_straight_line_point(x[j], y[j], v_x[j], v_y[j], a_x[j], a_y[j], dt);
      
      }


      noise = get_gaussian_noise(mean, std_dev);
      out_file << x[j] << "," << x[j]+noise << ",";
      noise = get_gaussian_noise(mean, std_dev);
      out_file << v_x[j] << "," << v_x[j]+noise << ",";
      noise = get_gaussian_noise(mean, std_dev);
      out_file << a_x[j] << "," << a_x[j]+noise << ",";

      noise = get_gaussian_noise(mean, std_dev);
      out_file << y[j] << "," << y[j]+noise << ",";
      noise = get_gaussian_noise(mean, std_dev);
      out_file << v_y[j] << "," << v_y[j]+noise << ",";
      noise = get_gaussian_noise(mean, std_dev);
      out_file << a_y[j] << "," << a_y[j]+noise << ",";
    }
    out_file << endl;
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
