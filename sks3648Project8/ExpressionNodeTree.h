#ifndef PROJECT8_EXPRESSIONNODE_H
#define PROJECT8_EXPRESSIONNODETREE_H
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "ExpressionNode.h"
#include "Construction.h"
#include "Runner.h"
#include "DataStruct.h"
/* Special Note:
    Some of these functions are cited from academic tutors at the UT ECE tutoring session and the website 
	http://www.geeksforgeeks.com for maps and vector ( online coding resource) and my brain.
	https://stackoverflow.com/questions/53687363/c-creating-a-map-with-a-string-as-key-and-vector-of-string-as-value
	*/
using namespace std;
class ExpressionNodeTree
{
private:
	ExpressionNode* base;

public:
	// a way to process the vector database of map objects
	ExpressionNodeTree();
	ExpressionNodeTree(vector<map<string, int>>&processor);
	// checks Operand finally!!!!!!!
	static bool checkOperand(const string& input);
	// copy constructor
	ExpressionNodeTree(const ExpressionNodeTree& other);
	int process(ExpressionNode* base, vector<map<string, int>>& processor);
	ExpressionNode* addNode(vector<ExpressionNode*>& lit, ExpressionNode* newInput);
	ExpressionNodeTree& operator=(const ExpressionNodeTree& other);
	// default constructor

	// overloaded function   with just one parameter
	int process(vector<map<string, int>>& processor);
	// destructor
	~ExpressionNodeTree();
	// constructor with one parameter of ExpressionNode* pointers
	ExpressionNodeTree(vector<ExpressionNode*>&processor);
	// process Operand and calculates the operators of two operands
	int calculateResult(const string& input, const int& op1, const int& op2);

};










#endif
