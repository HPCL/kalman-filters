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

#ifndef __POINTS__
#define __POINTS__

typedef struct Points {
  double* x;
  double* y;
  double* t;
  bool* found;
  int size;
} Points;


#endif