/*----------------------------------------------------------------
file: knapsackdp.cpp
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
knapsackdp class
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
All includes here
-----------------------------------------------------------------*/
#include "knapsackdp.h"

/*----------------------------------------------------------------
WRITE YOUR CODE BELOW
-----------------------------------------------------------------*/
void knapsackdp::_createNullMatrix(vector<vector<int>>& vec, int& _row, int& _col) {
	for (int i = 0; i < _row; i++) {
		vec[i] = vector<int>(_col);
		for (int j = 0; j < _col; j++) {
			vec[i][j] = 0;
		}
	}
}

void knapsackdp::_displayMatrix(vector<vector<int>>& vec, int& _row, int& _col) {
	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}

void knapsackdp::_displayWVI(const int* w, const int* v, int& numItem) {
	cout << "i = ";
	for (int i = 1; i <= numItem; i++) {
		cout << i << " ";
	}
	cout << endl;
	cout << "w = ";
	for (int i = 0; i < numItem; i++) {
		cout << w[i] << " ";
	}
	cout << endl;
	cout << "v = ";
	for (int i = 0; i < numItem; i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

void knapsackdp::_updateMatrix(vector<vector<int>>& vecValue, vector<vector<int>>& vecSteal, int& _row, int& _col, const int* w, const int* v) {
	for (int i = 1; i < _row; i++) {
		vecValue[i] = vector<int>(_col);
		int weight = w[i-1];
		int value = v[i-1];
		for (int j = 1; j < _col; j++) {
			//write here the function to build weight / value matrix
			int currCol = j;
			int currRow = i;
			vecValue[i][j] = _buildWVMatrix(vecValue, vecSteal, weight, value, currRow, currCol);
		}
	}
}

int knapsackdp::_buildWVMatrix(vector<vector<int>>& vecValue, vector<vector<int>>& vecSteal, int& weight, int& value, int& currRow, int& currCol) {
	if (currCol < weight) {
		//cout << currRow - 1 << " " << currCol;
		if ((currRow - 1) != 0) {
			return vecValue[currRow - 1][currCol];
		}
		else { return 0; }
		//return 0;
	}
	else {
		int _stealVal = _steal(vecValue, weight, value, currRow, currCol);
		int _notStealVal = _notSteal(vecValue, weight, value, currRow, currCol);
		if (_stealVal > _notStealVal) {
			vecSteal[currRow][currCol] = 1;
			return _stealVal;
		}
		else {
			return _notStealVal;
		}
	}
}

int knapsackdp::_steal(vector<vector<int>>& vecValue, int& weight, int& value, int& currRow, int& currCol) {
	//int val = value;
	//cout <<"currCOl " << currCol <<" weight " << weight << endl;
	int newWeight = currCol - weight;
	//cout <<"new weight "<< newWeight << endl;
	int finalValue = value + vecValue[currRow - 1][newWeight];
	return finalValue;
}

int knapsackdp::_notSteal(vector<vector<int>>& vecValue, int& weight, int& value, int& currRow, int& currCol) {
	int finalValue = vecValue[currRow - 1][currCol];
	return finalValue;
}

void knapsackdp::_displayFinal(vector<vector<int>>& vecSteal, const int* _w, const int* _v, int& _ans, int& numItem, int& bagSize) {
	int value = 0;
	int count = 0;
	int row = numItem;
	int col = bagSize;
	vector<int> sumValues;
	vector<int> indexValues;
	while (row >= 0 && col >= 0) {
		if (vecSteal[row][col] == 1) {
			//cout << _v[row - 1] << " " << row << endl; 
			sumValues.push_back(_v[row - 1]);
			indexValues.push_back(row);
			value = value + _v[row - 1];
			col = col - _w[row - 1];
			row = row - 1;
		}
		else {
			row = row - 1;
		}
	}
	cout << "i = ";
	for (int i = 1; i <= numItem; i++) {
		cout << i << " ";
	}
	cout << endl;
	cout << "w = ";
	for (int i = 0; i < numItem; i++) {
		cout << _w[i] << " ";
	}
	cout << endl;
	cout << "v = ";
	for (int i = 0; i < numItem; i++) {
		cout << _v[i] << " ";
	}
	cout << endl;
	cout << "Max Value of " << value << " can obtained from items {";
	for (int i = 0; i < indexValues.size(); i++) {
		cout << indexValues[i];
		if (i != indexValues.size() - 1) { cout << ","; }
	}
	cout << "} that has values {";
	for (int i = 0; i < sumValues.size(); i++) {
		cout << sumValues[i];
		if (i != sumValues.size() - 1) { cout << "+"; }
	}
	cout << "=" << value << "}" << endl;
 }

//EOF