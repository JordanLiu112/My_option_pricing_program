///Jordan Liu - declaration of ParamMatrix class derived from BlackScholes

#ifndef PARAM_MATRIX_H
#define PARAM_MATRIX_H

#include "HelperFunctions.h"

class ParamMatrix {
private:
	vector<vector<pair<string, double>>> m_matrix;
public:
	ParamMatrix(); //default constructor 
	ParamMatrix(const vector<vector<pair<string, double>>>& hard_coded); //constructor with hard-coded parameter matrix
	~ParamMatrix(); //destructor

	void loadMesh(const vector<double>& mesh, const string& order); //takes a mesh of doubles and a string to indicate which double gets assigned to which parameter
	//e.g. the string "SKs" indicates the first double is an S, the second is a K, and the third is a sig

	void loadBatch(const BlackScholes& batch); //load a BlackScholes class object into the parameter matrix

	void loadMeshConsole(); //for loadConsole

	void loadConsole(); //creates a matrix from vectors of doubles inputted through the console

	void print(); //prints the parameter matrix

	//prices the parameter matrix according to the string operation (e.g. "delta", "gamma", "price") and returns a vector of prices
	vector<double> callMatrix(BlackScholes& option, const string& output_type);
	vector<double> putMatrix(BlackScholes& option, const string& output_type); 

};



#endif