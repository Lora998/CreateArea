/*
 * Area.h
 *
 *  Created on: Jun 8, 2018
 *      Author: l.hofer
 */

#ifndef AREA_H_
#define AREA_H_

#include <vector>
#include "Droplets.h"

class Area {
  public:
   Area();										// default constructor
   Area(unsigned int, double, double, double, double, double, double,
		   double, double, double, double);		// general constructor
   inline double getWidth() const {return width;}
   inline double getHeight() const {return height;}
   inline std::vector<Droplets> getDroplets() const {return droplets;}
  private:
   unsigned int n;								// number of points
   double width;
   double height;
   double angle_min;							// parameters for normal distribution of angles
   double angle_max;
   double angle_mean;
   double angle_stddev;
   double d_area_min;							// parameters for normal distribution of the area of the droplets
   double d_area_max;
   double d_area_mean;
   double d_area_stddev;
   std::vector<Droplets> droplets;

   void distributeDroplets();
   bool isValidDroplet(const Droplets &);
};


#endif /* AREA_H_ */
