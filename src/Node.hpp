#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <cmath>
using namespace std;

class NumObject{
public:
	int rank;
	vector<int> dimentions;
	vector<double> values;

	NumObject();
	NumObject(double val);
	NumObject(vector<double> val, vector<int> dimentionsList);
	NumObject(vector<int> dimentionsList, double fill);
	NumObject(vector<int> dimentionsList);

	string describe();
	NumObject getIndex(vector<int> idx);
	void setIndex(vector<int> idx, vector<double> val);
	void setIndex(vector<int> idx, double val);
};

class Node{
public:
	vector<Node*> inputs;
	string name;
	NumObject derivativeMemo;

	virtual NumObject getValue() = 0;
	virtual string describe();
	virtual void derive(NumObject& seed) = 0;
	NumObject& memoize(NumObject& val);

	// Node* operator+(Node& param);
	// Node* operator-(Node& param);
	// Node* operator/(Node& param);
	// Node* operator*(Node& param);
};

class Constant: public Node{
public:
	NumObject value;
	Constant(NumObject val, string placeHolder = "");
	NumObject getValue();
	string describe();
	void derive(NumObject& seed);
};

class Variable: public Constant{
public:
	NumObject derivative;
	Variable(NumObject val, string placeHolder = "");
	void derive(NumObject& seed);
	double deriveOperation(vector<double>& a);
};

NumObject reduceSumByDimention(NumObject& nums, int byDimention);

class BasicOperator: public Node{
public:
	BasicOperator(Node* a, Node* b);
	NumObject getValue();
	virtual double operation(vector<double>& a) = 0;
	virtual string describe();
};

class BasicFunction: public Node{
public:
	BasicFunction(Node* a);
	NumObject getValue();
	virtual double operation(vector<double>& a) = 0;
};



#endif

