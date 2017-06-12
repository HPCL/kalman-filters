/*
 * test_data_generator.cpp
 * test the data generation
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * See LICENSE file for licensing information and boring legal stuff

 * If by some miricale you find this software useful, thanks are accepted in
 * the form of chocolate, coffee, or introductions to potential employers.

*/


#include "data_generator.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <math.h>

using namespace std;

void test_projectile();
void test_sin_wave();
void test_straight_line();

int main(int argc, char const *argv[])
{
  // test_projectile();
  // test_sin_wave();
  test_straight_line();
  return 0;
}


void test_projectile() {

  char* fname = (char*)"projectile_motion.csv";

  DataGenerator gen(fname, 1000);

  gen.generate_projectile_motion();

}


void test_sin_wave() {

  char* fname = (char*)"sine_wave.csv";

  DataGenerator gen(fname, 1000);

  gen.generate_sin_wave(50);

}


void test_straight_line() {

  char* fname = (char*)"straight_line.csv";

  DataGenerator gen(fname, 1000);

  gen.generate_straight_line(50, 10);

}