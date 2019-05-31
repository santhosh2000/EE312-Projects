#ifndef PROJECT8_EXPRESSIONNODE_H
#define PROJECT8_EXPRESSIONNODE_H
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "ExpressionNodeTree.h"
#include "Construction.h"
#include "Runner.h"
#include "Literals.h"
using namespace std;

/* Special Note:
	Some of these functions are cited from academic tutors at the UT ECE tutoring session and the website
	http://www.geeksforgeeks.com for maps and vector ( online coding resource) and my brain.
	https://stackoverflow.com/questions/53687363/c-creating-a-map-with-a-string-as-key-and-vector-of-string-as-value
	// copyright to Milos Gligoric's exptree in class
	*/
class ExpressionNode {
private:
	// operator string
	string optr;
	// type of operator string
	string type_operand;
	// says if the node is operator or not
	bool is_operand;
	// value of the operand if this is an operand node
	int operand;
	// says if the node is symbol or not
	bool is_symbol;
	// left subtree
	ExpressionNode* left;
	// right subree
	ExpressionNode* right;



public:
	ExpressionNode();
	ExpressionNode(string optr, string type_operand, bool is_operand, bool is_symbol, int operand);
	void copyNodes(const ExpressionNode& other);
	ExpressionNode(const ExpressionNode& other);
	~ExpressionNode();
	ExpressionNode& operator=(const ExpressionNode &other);
	bool getIs_Operand();
	int getOperand();
	bool getIs_Symbol();
	string getOperator();
	void setOperator(string);
	void setOperatorType(string);
	void setRightNode(ExpressionNode*);
	void setLeftNode(ExpressionNode*);
	string getOperatorType();
	ExpressionNode* getLeft();
	ExpressionNode* getRight();
};
#endif