/*
 * Droplets.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: l.hofer
 */


#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
#include<climits>
#include "Droplets.h"

/* constructors */

inline Droplets::Droplets()		: x(-1.), y(-1.), a(-1.), r(-1.), angle(0.), id(UINT_MAX) {}
Droplets::Droplets(double xW, double yW, double aW, double angleW, unsigned int i){
	x = xW;
	y = yW;
	a = aW;
	angle = angleW;
	r = std::sqrt(a/ (M_PI) );
    id = i;
}
Droplets::Droplets(const Droplets& c){
	x = c.x;
	y = c.y;
	a = c.a;
	angle = c.angle;
	r = c.r;
    id = c.id;
}

std::ostream &operator<<(std::ostream & os, const Droplets& d){
	return os << "( id = " << d.getID() << " ; x = " << d.getX() <<" ; y = " << d.getY() <<
			" ; area = " << d.getA() << " ; angle = " << d.getAngle() << " )" ;
}

double getDistance(const Droplets & a, const Droplets & b){
	return (std::sqrt(std::pow(a.getX()-b.getX(), 2) +
			std::pow(a.getY()-b.getY(), 2)));
}
