/*
 * Area.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: l.hofer
 */


#include "Area.h"
#include <chrono>
#include <random>
/*
 * default constructor
 * used for testing
 */
Area::Area(){
	n = 5;
	width = 10.;
	height = 10.;
	angle_min = 0.1;
	angle_max = 89.9;
	angle_mean = 10.;
	angle_stddev = 5.;
	d_area_min = 0.001;
	d_area_max = 1.;
	d_area_mean = 0.2;
	d_area_stddev = 0.05;
	distributeDroplets();
}

Area::Area(unsigned int nW, double wW, double hW, double aMinW, double aMaxW, double aMeanW,
		double aSW, double dMinW, double dMaxW, double dMeanW, double dSW){
	n = nW;
	width = wW;
	height = hW;
	angle_min = aMinW;
	angle_max = aMaxW;
	angle_mean = aMeanW;
	angle_stddev = aSW;
	d_area_min = dMinW;
	d_area_max = dMaxW;
	d_area_mean = dMeanW;
	d_area_stddev = dSW;
	distributeDroplets();
}

void Area::distributeDroplets(){

	// construct a trivial random generator engine from a time-based seed
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	/*
	 * generate independent uniform distributions for
	 * x- and y-coordinates
	 * x-coordinate : width
	 * y-coordinate : height
	 */
	std::default_random_engine drpPosXGenerator (seed);
	std::uniform_real_distribution<double> dropletPositionDistrX(0., width);
	// set new seed
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine drpPosYGenerator (seed);
	std::uniform_real_distribution<double> dropletPositionDistrY(0., height);

	/*
	 * generate normal distribution for the size and the
	 * angles of the droplets
	 */
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine drpAngleGenerator (seed);
	std::normal_distribution<double> drpAngleDistr(angle_mean, angle_stddev);
	// set new seed
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine drpSizeGenerator (seed);
	std::normal_distribution<double> drpSizeDistr(d_area_mean, d_area_stddev);

	for(int i = 0; i < n; ++i){
		// generate a random droplet
		Droplets tmp(dropletPositionDistrX(drpPosXGenerator),
				dropletPositionDistrY(drpPosYGenerator),
				drpSizeDistr(drpSizeGenerator),
				drpAngleDistr(drpAngleGenerator), i);
		/*
		 * if the attributes of the droplet doe not conflict
		 * with the given parameters, the droplet gets added
		 * to the droplet list
		 */

		if(isValidDroplet(tmp) ){
			droplets.push_back(tmp);
		}
		else{
			--i;
		}
	}
}

bool Area::isValidDroplet(const Droplets& d){
	/*
	 * a valid droplet has to fulfil all the given arguments
	 */
	if(d.getX() < 0. || d.getY() < 0. || d.getX() > width ||
			d.getY() > height || d.getAngle() < angle_min ||
			d.getAngle() > angle_max || d.getA() > d_area_max ||
			d.getA() < d_area_min){
		return false;
	}
	for( Droplets ds : droplets){
		double distance = getDistance(d, ds);
		if( distance < d.getRadian() || distance < ds.getRadian()){
			return false;
		}
	}
	return true;
}

