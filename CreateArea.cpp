//============================================================================
// Name        : CreateArea.cpp
// Author      : 
// Version     :

//============================================================================

#include "Area.h"
#include "Droplets.h"
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

double getDistanceToDroplet(double x, double y, Droplets d){
	return (sqrt(pow(d.getX()-x, 2) + pow(d.getY()-y, 2)));
}

void createAreaVTK(string dataname, double ***area, Area a){
	ofstream fos(dataname+"areaSize.vtk");
	if(!fos || ! fos.is_open()){
		cerr << "There was a problem opening the input file." << endl;
		exit(0);
	}
	fos << "# vtk DataFile Version 3.0" <<endl;
	fos << "vtk Output in ascii" <<endl;
	fos << "ASCII" << endl;
	fos << "DATASET STRUCTURED_POINTS" << endl;
	fos <<"DIMENSIONS " << a.getWidth() << " " << a.getHeight() <<endl;
	fos << "ORIGIN 0 0 0" << endl;
	fos << "SPACING 1 1 1" <<endl;
	fos << "POINT_DATA " << (a.getWidth()*a.getWidth()) << endl;
	fos << "\n";
	fos << "SCALARS Cells int 1" << endl;
	fos << "LOOKUP_TABLE default" << endl;
	for(int x = 0; x < a.getWidth(); x++){
		for(int y = 0; a.getHeight(); y++){
			fos << (int)(area[0][x][y]) << endl;
		}
	}
	fos.close();
}

void createAngleVTK(string dataname, Area a){
	
}

string generateFilenamePrefix(){
    time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,sizeof(buffer),"%d-%m-%Y-%I:%M:%S",timeinfo);
	std::string str(buffer);
    return str;
}

void parseArgs(int &argc, char **argv, string &inputFile, string &outputFile, bool &createOutputFile){
	string in("-i");
	string out("-o");
    for(int i = 1; i < argc; i++) {
        if(string(argv[i]) == in ){
			if(i+1 == argc || string(argv[i+1]) == out){
				inputFile = "";
				cerr << "Input file not specified. Process will be terminated." << endl;
				exit(0);
			}
			else{
				i++;
				inputFile = string(argv[i]);
				cout << "Input file: " << inputFile << endl;
				
			}
		} else if(string(argv[i]) == out){
			createOutputFile = true;
			if(i+1 == argc || argv[i+1] == in){
				outputFile = generateFilenamePrefix();
				cout << "No output file specified. The data will be stored in "<< outputFile << endl;
			}
			else{
				i++;
				outputFile = string(argv[i]);
				cout << "Output file: " << outputFile << endl;
			}
		}
		else{
			cout << "Option \""<< argv[i] << "\" was not recognized." << endl; 
		}
    }
}

void calculateArea( Area a,double ***area){
	for(int x = 0; x < a.getWidth(); x++){
		for(int y = 0; a.getHeight(); y++){
			area[0][x][y] = 0.;
			for(Droplets d : a.getDroplets() ){
				if(getDistanceToDroplet(x, y, d) <= d.getRadian()){
					area[0][x][y] = 1.;
					break;
				}
			}
		}
    }
}

int main(int argc, char *argv[]){
	string inputFile("");
    string outputFile("");
    bool createOutputFile = false;
	parseArgs(argc, argv, inputFile, outputFile, createOutputFile);
	
	if(inputFile != string("")){
		ifstream fis(string(inputFile), ifstream::in);
		if(!fis || ! fis.is_open()){
			cerr << "There was a problem opening the input file." << endl;
			exit(0);
		}
		unsigned int n;
		double width, height, angleMin, angleMax, angleMean, 
			angleStdDeviation, sizeMin, sizeMax, sizeMean, sizeStdDeviation;
		fis >> n >> width >> height >> angleMin >> angleMax >> angleMean >>
			angleStdDeviation >> sizeMin >> sizeMax >> sizeMean >> sizeStdDeviation;
		cout << "n = " << n << endl;
		cout << "width = " << width << "\theight = " << height << endl;
		cout << "Angle Minimum = " << angleMin << "\tAngle Maximum = " << angleMax << 
			"\tAngle Mean = " << angleMean << "\tAngle Standard Deviation = " << angleStdDeviation << endl;
		cout << "Droplet Size Minimum = " << sizeMin << "\tDroplet size Maximum = " << sizeMax << 
			"\tDroplet Size Mean = " << sizeMean << "\tDroplet Size Standard Deviation = " << sizeStdDeviation << endl;
		fis.close();
		Area a(n, width, height, angleMin, angleMax, angleMean, angleStdDeviation,
			sizeMin, sizeMax, sizeMean, sizeStdDeviation);
		if(createOutputFile){
			double area[2][(int)(width+0.5)][(int)(height)];
			
			if( outputFile == string("")){
				outputFile = generateFilenamePrefix();
				cout << "The data will be stored in "<< outputFile << endl;
			}
			calculateArea(a, area);
		//	createAreaVTK(outputFile, area, a);
		//	createAngleVTK(outputFile,area, a);
		}
		else{
			for(Droplets d : a.getDroplets() ){
				cout << d << endl;
			}
		}
		
	}
	
	if(inputFile == string("")){
		cout << "Default values are used." << endl;
		Area a;
		if(createOutputFile){
			if( outputFile == string("")){
				outputFile = generateFilenamePrefix();
				cout << "The data will be stored in "<< outputFile << endl;
			}
//			createAreaVTK(outputFile, a);
//			createAngleVTK(outputFile, a);
		}
		else{
			for(Droplets d : a.getDroplets() ){
				cout << d << endl;
			}
		}
	}

	return 0;
}
