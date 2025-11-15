//Jordan Liu - definition of ParamMatrix class

#include "ParamMatrix.h"


ParamMatrix::ParamMatrix() : m_matrix() {}  //default constructor 
ParamMatrix::ParamMatrix(const vector<vector<pair<string, double>>>& hard_coded) : m_matrix(hard_coded) {} //constructor with hard-coded parameter matrix
ParamMatrix::~ParamMatrix() {}

void ParamMatrix::loadMesh(const vector<double>& mesh, const string& order) { //takes a mesh of doubles and a string to indicate which double gets assigned to which parameter
	//e.g. the string "SKs" indicates the first double is an S, the second is a K, and the third is a sig
	vector<pair<string, double>> row;
	for (int i = 0; i < order.length(); ++i) { //creates the pairs, pushes them into the row, pushes row into matrix
		if (order[i] == 'S') {
			row.push_back(make_pair("S", mesh[i]));
		}
		else if (order[i] == 'K') {
			row.push_back(make_pair("K", mesh[i]));
		}
		else if (order[i] == 'T') {
			row.push_back(make_pair("T", mesh[i]));
		}
		else if (order[i] == 'r') {
			row.push_back(make_pair("r", mesh[i]));
		}
		else if (order[i] == 's') {
			row.push_back(make_pair("sig", mesh[i]));
		}
		else if (order[i] == 'b') {
			row.push_back(make_pair("b", mesh[i]));
		}
		else {
			cout << "Error - invalid parameter input" << endl;
		}
	}
	m_matrix.push_back(row);
}

//S1, K1, T1, r1, sig1, b1
void ParamMatrix::loadBatch(const BlackScholes& batch) { //load a BlackScholes class object into the parameter matrix
	vector<pair<string, double>> row;
	row.push_back(make_pair("S", batch.getS()));
	row.push_back(make_pair("K", batch.getK()));
	row.push_back(make_pair("T", batch.getT()));
	row.push_back(make_pair("r", batch.getR()));
	row.push_back(make_pair("sig", batch.getSig()));
	row.push_back(make_pair("b", batch.getB()));
	m_matrix.push_back(row);
}
	


void ParamMatrix::loadMeshConsole() { //for loadConsole
	string order;
	double value;
	vector<double> mesh_doubles;
	cout << "Input the preferred order of option parameters as a string (e.g. 'SKTsrb'; 'Ks' means input the K-value first and sig second): ";
	cin >> order; //get string indicating order of parameters
    for (int i = 0; i < order.length(); ++i) {
        cout << "Input the value of option parameter " << i+1 << ": ";
        cin >> value;
		mesh_doubles.push_back(value); //build mesh of values corresponding to the string parameter order
    }
	loadMesh(mesh_doubles, order); //call loadMesh
}

//example of a parameter matrix:
//Row 1: {{(S, 5), (T, 3), (r, 0.12)},
//Row 2: {(sig, 4), (S, 50), (T, 1), (K, 20)},
//Row 3: {(S, 100)}}

void ParamMatrix::loadConsole() { //creates a matrix from vectors of doubles inputted through the console
	cout << "What is the number of options? I.e., how many rows are in the matrix? ";
	int row_num;
	cin >> row_num;
	for (int i = 0; i < row_num; ++i) {
		loadMeshConsole(); //call loadMeshConsole
	}
}


void ParamMatrix::print() { //prints the parameter matrix
	for (vector<vector<pair<string, double>>>::const_iterator pair_row = m_matrix.begin(); pair_row != m_matrix.end(); ++pair_row) {
		for (vector<pair<string, double>>::const_iterator pair = pair_row->begin(); pair != pair_row->end(); ++pair) {
			cout << setw(10) << pair->first << ": " << setw(6) << pair->second; //print each parameter followed by its value in every row 
		}
		cout << endl;
	}
}

//prices the parameter matrix according to the string operation (e.g. "price", "delta", "gamma") and returns a vector of prices
vector<double> ParamMatrix::callMatrix(BlackScholes& option, const string& output_type) {
	const double save_S = option.getS(), save_K = option.getK(), save_sig = option.getSig(), save_r = option.getR(), save_T = option.getT(), save_b = option.getB();
	vector<double> price_mesh; //vector of prices to be returned
	price_mesh.reserve(m_matrix.size()); //reserve same size as the parameter matrix
	//iterate through each row of paired doubles and strings (parameter and value)
	for (vector<vector<pair<string, double>>>::const_iterator pair_row = m_matrix.begin(); pair_row != m_matrix.end(); ++pair_row) {
		//iterate through each pair in a row, e.g. {(S, 5), (T, 1), (K, 3)}
		for (vector<pair<string, double>>::const_iterator pair = pair_row->begin(); pair != pair_row->end(); ++pair) {
			//now we use the checkParam() function on the pair of a string and double, so we assign the value to the right parameter
			option.checkParam(pair->first, pair->second); //assign value to the parameter data member specified by the string
			//keep assigning values to parameters until we complete a full option
		}
		//check what type of output is wanted - gamma, delta, or price (default
		if (output_type == "gamma") price_mesh.push_back(option.gamma());
		else if (output_type == "delta") price_mesh.push_back(option.callDelta());
		else price_mesh.push_back(option.callPrice()); //assume price is wanted by default
		//if option is a US_Perpetual, then it should use the callPrice function for US_Perpetual
		//restore original values for parameters
		option.setS(save_S), option.setK(save_K), option.setSig(save_sig), option.setR(save_r), option.setT(save_T), option.setB(save_b);
	}
	return price_mesh;
}

//identical to callMatrix but we use putDelta and putPrice instead
vector<double> ParamMatrix::putMatrix(BlackScholes& option, const string& output_type) {
	const double save_S = option.getS(), save_K = option.getK(), save_sig = option.getSig(), save_r = option.getR(), save_T = option.getT(), save_b = option.getB();
	vector<double> price_mesh; //vector of prices to be returned
	price_mesh.reserve(m_matrix.size()); //reserve same size as the parameter matrix
	//iterate through each row of paired doubles and strings (parameter and value)
	for (vector<vector<pair<string, double>>>::const_iterator pair_row = m_matrix.begin(); pair_row != m_matrix.end(); ++pair_row) {
		//iterate through each pair in a row, e.g. {(S, 5), (T, 1), (K, 3)}
		for (vector<pair<string, double>>::const_iterator pair = pair_row->begin(); pair != pair_row->end(); ++pair) {
			//now we use the checkParam() function on the pair of a string and double, so we assign the value to the right parameter
			option.checkParam(pair->first, pair->second); //assign value to the parameter data member specified by the string
			//keep assigning values to parameters until we complete a full option
		}
		//check what type of output is wanted - gamma, delta, or price (default)
		if (output_type == "gamma") price_mesh.push_back(option.gamma());
		else if (output_type == "delta") price_mesh.push_back(option.putDelta());
		else price_mesh.push_back(option.putPrice()); //assume price is wanted by default
		//if option is a US_Perpetual, then it should use the putPrice function for US_Perpetual
		//restore original values for parameters
		option.setS(save_S), option.setK(save_K), option.setSig(save_sig), option.setR(save_r), option.setT(save_T), option.setB(save_b);
	}
	return price_mesh;
}