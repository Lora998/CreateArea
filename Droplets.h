/*
 * Droplets.h
 *
 *  Created on: Jun 8, 2018
 *      Author: l.hofer
 */

#ifndef DROPLETS_H_
#define DROPLETS_H_

#include<iostream>

class Droplets {
  public:
   Droplets();												// default constructor
   Droplets(double, double, double, double, unsigned int );	// general constructor
   Droplets(const Droplets&);								// copy constructor

   inline double getX() const {return x;}
   inline double getY() const {return y;}
   inline double getA() const {return a;}
   inline double getAngle() const {return angle;}
   inline double getRadian() const {return r;}
   inline unsigned int getID() const {return id;}
  private:
   double x;							// x-coord
   double y;							// y-coord
   double a;							// area
   double r;							// radian
   double angle;						// angle
   unsigned int id;					// unique id to identify the droplets

   /*
    * x, y and a have to be greater than 0
    */
};

std::ostream &operator<<(std::ostream &, const Droplets&);
double getDistance(const Droplets &, const Droplets &);



#endif /* DROPLETS_H_ */
