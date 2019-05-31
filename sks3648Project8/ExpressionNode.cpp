#include "ExpressionNode.h"
/*
UT EID: sks3648
Name: Santhosh Saravanan
Spring 2019 section
Milos Gligoric
*/

	void ExpressionNode::setOperator(string oper)
	{
		this->optr = oper;
	}
	void ExpressionNode::setLeftNode(ExpressionNode* leftNode)
	{
		this->left = leftNode;
	}
	void ExpressionNode::setRightNode(ExpressionNode* setRightNode)
	{
		this->right = setRightNode;
	}
	void ExpressionNode::setOperatorType(string operatorType)
	{
		this->type_operand = operatorType;
	}

	bool ExpressionNode::getIs_Operand()
	{
		return this->is_operand;
	}
	int ExpressionNode::getOperand()
	{
		return this->operand;
	}
	bool ExpressionNode::getIs_Symbol()
	{
		return this->is_symbol;
	}
	string ExpressionNode::getOperator()
	{
		return this->optr;
	}
	string ExpressionNode::getOperatorType()
	{
		return this->type_operand;
	}
	ExpressionNode* ExpressionNode::getLeft()
	{
		return this->left;
	}
	ExpressionNode* ExpressionNode::getRight()
	{
		return this->right;
	}

	ExpressionNode::ExpressionNode()
	{
		this->optr = "";
		this->type_operand = "";
		this->is_operand = false;
		this->is_symbol = false;
		this->operand = 0;
		this->left = this->right = nullptr;

	}
	ExpressionNode::ExpressionNode(string optr, string type_operand, bool is_operand, bool is_symbol, int operand)
	{
		this->optr = optr;
		this->type_operand = type_operand;
		this->is_operand = is_operand;
		this->is_symbol = is_symbol;
		this->operand = operand;
		this->left = this->right = nullptr;
	}
	void ExpressionNode::copyNodes(const ExpressionNode& other)
	{
		this->optr = other.optr;
		this->type_operand = other.type_operand;
		this->operand = other.operand;
		this->is_operand = other.is_operand;
		this->is_symbol = other.is_symbol;
		this->left = other.left ? new ExpressionNode(*other.left) : nullptr;
		this->right = other.right ? new ExpressionNode(*other.right) : nullptr;
	}
	ExpressionNode::ExpressionNode(const ExpressionNode& other)
	{
		copyNodes(other);
	}
	ExpressionNode::~ExpressionNode()
	{
		delete this->right;
		delete this->left;
	}
	ExpressionNode& ExpressionNode::operator=(const ExpressionNode &other)
	{
		if (this == &other)
		{
			return *this;
		}
		delete this->right;
		delete this->left;
		copyNodes(other);
		return *this;
	}
	







