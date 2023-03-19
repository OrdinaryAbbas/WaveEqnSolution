#ifndef SCHEME_H	//include guard
#define SCHEME_H

#include "Matrix.h"	//matrix class, inspired on c++ course
#include <cmath>	//numeric library for sin method
#include <iostream>	//generic IO
#include <string>	//for string objects and methods
#include <chrono>	//use for delay in printing method
#include <thread>	//use for dealy in printing method
#include <fstream>	//input/output file stream class
#include <iomanip>	//for precision of numbers

using namespace std;

#pragma once

/**
* The Scheme class is the parent class of the ExplicitScheme and ImplicitScheme classes.
* This class includes common methods for child classes (ExplicitScheme and ImplicitScheme)
* Additionally, Scheme class includes methods responsible for printing results to screen and saving them to an excel sheet
**/
class Scheme 
{
protected: 
	
	Matrix matrix;
	int sizeOfMatrix;
	int sizeT;
	int sizeX;
	double deltaT;
	double deltaX;
	const double PI = atan(1) * 4;
	const double u = 250; 

public: 
	// Empty Default Constructor
	Scheme();

protected:
	
	// Compute initial condition for each type of scheme.
	void InitialCondition();
	
	//Compute boundry condition for each type of scheme.
	void BoundryCondition();
	
	// Input timestep (deltaT)
	void InsertDeltaT();
	
	//Compute size of matrix depend of deltaT defined by user.
	void ComputeSizeOfMatrix(bool ifPrinted = 1);

public:

	//Save matrix into the text file.
	void SaveResultIntoFiles(double deltaT, string schemeName);
	
	//Solve analytical solution of given problem.
	string AnalyticalSolution(double defaultDeltaT = 0);
	
	//Compute Norms.
	void ComputeNorms(Matrix m1, Matrix m2);
	
	//Print result to screen (10 rows only)
	void PrintResult();

	//Accessor methods
	Matrix GetMatrix();
	double GetDeltaT();

	friend bool IsDouble(string input);

	~Scheme() {}
};

#endif
