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
#include <limits>
#include "textread.h"
#include <string.h>
using namespace std;

/*
 * returns the distance from a point(x/y) to the center of a given droplet
 */
double getDistanceToDroplet(double x, double y, Droplets d){
	return (sqrt(pow(d.getX()-x, 2) + pow(d.getY()-y, 2)));
}

/*
 * generates a filename, which depends on the current date and time 
 */
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

/*
 * parses the given arguments
 */
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

/*
 * writes every Droplet of the area in the given file
 */
void writeBasicOutput(Area a, string outputFile){
	ofstream fos(outputFile+".txt");
	if(!fos || ! fos.is_open()){
		cerr << "There was a problem opening the output file " << outputFile <<".txt" << endl;
		exit(0);
	}
	for(Droplets d : a.getDroplets() ){
		fos << d << "\n";
	}
	fos.close();
}

/*
 * creates a vtk file for paraview used
 */
void writeVTKFiles(Area a, string outputFilePrefix){
	ofstream fos(outputFilePrefix+"_pore_dist.vtk");
	if(!fos|| ! fos.is_open() ){
		cerr << "There occured a problem opening the output file." << endl;
		exit(0);
	}
	cout << "Output files successfully opened." << endl;
	fos << "# vtk DataFile Version 3.0\n" ;
    fos << "vtk output\n";
	fos << "ASCII\n";
	fos << "DATASET POLYDATA\n";
	fos << "POINTS " << a.getN() << " float\n";
    for(Droplets d : a.getDroplets() ){
        fos << "0.0 " << d.getX() << " " << d.getY() << "\n";
    }
    fos << "POINT_DATA " << a.getN() << "\n";
    fos << "FIELD droplets 2\n";
    fos << "angle 1 " << a.getN() << " float\n";
    for(Droplets d : a.getDroplets() ){
        fos << d.getAngle() << " " ;
    }
    fos <<"\n";
    fos << "area 1 " << a.getN() << " float\n";
    for(Droplets d : a.getDroplets() ){
        fos << d.getA() << " " ;
    }
    fos << "\n";
    fos.close();
	cout << "Output file successfully closed." << endl;
}

void writeOutputFiles(Area a, string outputFilePrefix){
	writeBasicOutput(a, outputFilePrefix);
    writeVTKFiles(a, outputFilePrefix);
}

int main(int argc, char *argv[]){
	string inputFile("");
    string outputFile("");
    bool createOutputFile = false;
	parseArgs(argc, argv, inputFile, outputFile, createOutputFile);
	
	if(inputFile != string("")){
        double paras[11];
		char *cstr = new char[inputFile.length() + 1];
		strcpy(cstr, inputFile.c_str());
		int state = textread(cstr, paras, 11);
		if(state < 0){
			cerr << "There was a problem opening the input file." << endl;
			exit(0);
		}
		delete [] cstr;
		/* read the parameters for the constructor of the area */
		
		cout << "n = " << paras[0] << endl;
		cout << "width = " << paras[1] << "\theight = " << paras[2] << endl;
		cout << "Angle Minimum = " << paras[3] << "\tAngle Maximum = " << paras[4] << 
			"\tAngle Mean = " << paras[5] << "\tAngle Standard Deviation = " << paras[6] << endl;
		cout << "Droplet Size Minimum = " << paras[7] << "\tDroplet size Maximum = " << paras[8] << 
			"\tDroplet Size Mean = " << paras[9] << "\tDroplet Size Standard Deviation = " << paras[10] << endl;

		
		Area a((int)(paras[0]), paras[1], paras[2], paras[3], paras[4], paras[5], paras[6],
			paras[7], paras[8], paras[9], paras[10]);

		if(createOutputFile){
			
			if( outputFile == string("")){
				
				outputFile = generateFilenamePrefix();
				cout << "The data will be stored in "<< outputFile << endl;
			}
			writeOutputFiles(a, outputFile);
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
			writeOutputFiles(a, outputFile);
		}
		else{
			for(Droplets d : a.getDroplets() ){
				cout << d << endl;
			}
		}
	}
	cout << "Process successful" << endl;
	return 0;
}
