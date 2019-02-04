/*----------------------------------------------------------------
file: knapsackdp.h
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
This file has knapsackdp class declaration
-----------------------------------------------------------------*/

/*----------------------------------------------------------------
All includes here
-----------------------------------------------------------------*/
#ifndef knapsackdp_H
#define knapsackdp_H

#include "knapsackbase.h"

/*----------------------------------------------------------------
class knapsackdp concrete class
-----------------------------------------------------------------*/
class knapsackdp :public knapsackbase {
public:
  knapsackdp() {
    //YOU CANNOT ADD ANYTHING HERE
    testbed();
  }
  ~knapsackdp() {}
  knapsackdp(const knapsackdp& m) = delete;
  knapsackdp& operator = (const knapsackdp& m) = delete;
protected:
  void knapsack(const char* t, int bagsize, int numitem, const int* w, const int* v, int& ans) {
    //WRITE YOUR CODE. Populate ans
	  cout << "--------------------------" << t << "------------------------" << endl;
	  int _row = numitem + 1;
	  int _col = bagsize + 1;

	  vector<vector<int>> _value(_row);
	  vector<vector<int>> _steal(_row);

	  _createNullMatrix(_value, _row, _col);
	  _createNullMatrix(_steal, _row, _col);
	  _updateMatrix(_value, _steal, _row, _col, w, v);
	  cout << "------------ V matrix ----------------" << endl;
	  _displayMatrix(_value, _row, _col);
	  cout << "------------ k matrix ----------------" << endl;
	  _displayMatrix(_steal, _row, _col);
	  ans = _value[numitem][bagsize];
	  _displayFinal(_steal, w, v, ans, numitem, bagsize);
  }
private:
  //You can have any number of private variables
  //You can have any number of private functions
	void _createNullMatrix(vector<vector<int>>& vec, int& _row, int& _col);
	void _displayMatrix(vector<vector<int>>& vec, int& _row, int& _col);
	void _updateMatrix(vector<vector<int>>& vecValue, vector<vector<int>>& vecSteal, int& _row, int& _col, const int* _w, const int* _v);
	int _buildWVMatrix(vector<vector<int>>& vecValue, vector<vector<int>>& vecSteal, int& weight, int& value, int& currRow, int& currCol);
	int _steal(vector<vector<int>>& vecValue, int& weight, int& value, int& currRow, int& currCol);
	int _notSteal(vector<vector<int>>& vecValue, int& weight, int& value, int& currRow, int& currCol);
	void _displayWVI(const int* _w, const int* _v, int& numItem);
	void _displayFinal(vector<vector<int>>& vecSteal, const int* _w, const int* _v, int& _ans, int& numItem, int& bagSize);
};



#endif

//EOF
