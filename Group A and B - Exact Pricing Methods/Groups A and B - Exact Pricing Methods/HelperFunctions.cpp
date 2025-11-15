///Jordan Liu - definitions of various helper functions e.g. printBatch, makeMesh

#include "HelperFunctions.h"
#include <iomanip> //for formatting
using namespace std;


//simple print functions to make things easier when printing results
void printBatch(int batch_num, double call, double put) {
	cout << "Batch " << batch_num << ": C = " << call << ", P = " << put << endl;
}
void printParity(double call, double put, bool verify) { 
	cout << "The call price " << call << " and put price " << put << (verify ? " do" : " do not") << " satisfy put-call parity" << endl;
}

vector<double> makeMesh(double start, double end, double h) { //for making a mesh of S values 
    vector<double> mesh;
    for (double S = start; S <= end; S += h) {
        mesh.push_back(S);
    }
    return mesh; 
}

vector<pair<string, double>> makeMeshPair(double start, double end, double h, string param) { //for making a mesh of paired doubles and strings
    vector<pair<string, double>> mesh;
    for (double S = start; S <= end; S += h) {
        mesh.push_back(make_pair(param, S));
    }
    return mesh;
}

//function to print vectors of S values and corresponding call and put prices
void printMesh(const vector<double>& S_values, const vector<double>& call_prices, const vector<double>& put_prices) { 
    cout << "S\tCall prices\tPut prices" << endl;
    cout << "--------------------------------" << endl;
    for (int i = 0; i < S_values.size(); ++i) {
        cout << S_values[i] << "\t" << setw(10) << call_prices[i] << "\t" << put_prices[i] << endl;
    }
}

void printMeshPrice(const vector<double>& prices) {
    for (int i = 0; i < prices.size(); ++i) {
        cout << "Option " << i+1 << ": " << prices[i] << endl;
    }
}


//function to print matrix
void printMatrix(const vector<vector<double>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        cout << setw(3) << " "; //for formatting purposes
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << setw(10) << matrix[i][j];
        }
        cout << endl;
    }
}

void printMatrixPair(const vector<vector<pair<string, double>>>& matrix) { //adjusted version of printMatrix specifically for printing matrices of pairs
    for (vector<vector<pair<string, double>>>::const_iterator pair_row = matrix.begin(); pair_row != matrix.end(); ++pair_row) {
        cout << setw(3) << pair_row->begin()->first; //print the string (i.e. parameter type)
        for (vector<pair<string, double>>::const_iterator pair = pair_row->begin(); pair != pair_row->end(); ++pair) {
            cout << setw(10) << pair->second; //print the values of that parameter
        }
        cout << endl;
    }
}

//function to print option sensitivities of a batch
void printGreeks(const Greek& batch, int batch_num) {
    cout << "Option sensitivites of Batch " << batch_num << ": " << endl;
    cout << "Call delta: " << batch.callDelta() << endl;
    cout << "Put delta: " << batch.putDelta() << endl;
    cout << "Gamma: " << batch.gamma() << endl;
    cout << "Vega: " << batch.vega() << endl;
    cout << "Call theta: " << batch.callTheta() << endl;
    cout << "Put theta: " << batch.putTheta() << endl;
}

//compare S-value vector, exact vector, and DD-approximated vector for call deltas, put deltas, and gammas
void printCompare(const vector<double>& S_values, Greek& batch, double h) {
    //get exact vectors (first line) and DD approx. vectors (second line)
    vector<double> call = batch.callDelta(S_values), put = batch.putDelta(S_values), gamma = batch.gamma(S_values),
    callDD = batch.callDelta(S_values, h), putDD = batch.putDelta(S_values, h), gammaDD = batch.gamma(S_values, h);

    cout << "Call deltas (h = " << h <<"): " << endl;
    cout << setw(3) << "S" << setw(15) << "Exact" << setw(15) << "Approx." << setw(15) << "Difference" << endl;
    cout << "----------------------------------------------------" << endl;
    for (int i = 0; i < S_values.size(); ++i) {
        cout << setw(3) << S_values[i] << setw(15) << call[i] << setw(15) << callDD[i] << setw(15) << (call[i] - callDD[i]) << endl;
    }

    cout << "\nPut deltas (h = " << h << "): " << endl;
    cout << setw(3) << "S" << setw(15) << "Exact" << setw(15) << "Approx." << setw(15) << "Difference" << endl;
    cout << "----------------------------------------------------" << endl;
    for (int i = 0; i < S_values.size(); ++i) {
        cout << setw(3) << S_values[i] << setw(15) << put[i] << setw(15) << putDD[i] << setw(15) << (put[i] - putDD[i]) << endl;
    }

    cout << "\nGammas (h = " << h << "): " << endl;
    cout << setw(3) << "S" << setw(15) << "Exact" << setw(15) << "Approx." << setw(15) << "Difference" << endl;
    cout << "----------------------------------------------------" << endl;
    for (int i = 0; i < S_values.size(); ++i) {
        cout << setw(3) << S_values[i] << setw(15) << gamma[i] << setw(15) << gammaDD[i] << setw(15) << (gamma[i] - gammaDD[i]) << endl;
    }

}