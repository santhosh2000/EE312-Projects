#include "ExpressionNodeTree.h"
/*
UT EID: sks3648
Name: Santhosh Saravanan
Spring 2019 section 
Milos Gligoric
*/
ExpressionNodeTree::ExpressionNodeTree()
{
	this->base = nullptr;
}

ExpressionNodeTree& ExpressionNodeTree::operator=(const ExpressionNodeTree& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete this->base;
	this->base = new ExpressionNode(*other.base);
	return (*this);
}
ExpressionNodeTree::~ExpressionNodeTree()
{
	delete this->base;
}


ExpressionNode* ExpressionNodeTree::addNode(vector<ExpressionNode*> &lit, ExpressionNode* newInput)
{
	ExpressionNode* firstCommand = new ExpressionNode(*lit[0]);
	delete lit[0];
	newInput = firstCommand;
	lit.erase(lit.begin());
	if (firstCommand->getIs_Operand() == false)
	{
		// non-operand types go on the left;
		// non0leaf nodes have the operand types
		newInput->setLeftNode(addNode(lit, newInput->getLeft()));

		if (checkOperand(firstCommand->getOperatorType()) == true)
		{
			newInput->setRightNode(addNode(lit, newInput->getRight()));
			// operand types go on the right;
			// leaf node has operand
		}
		else
		{
			//ExpressionNode(string optr, string type_operand, bool is_operand, bool is_symbol, int operand)
			newInput->setRightNode(new ExpressionNode("", "", true, false, 0));

		}
	}
	return newInput;
}

ExpressionNodeTree::ExpressionNodeTree(vector<ExpressionNode*>&processor)
{
	this->base = addNode(processor, this->base);
}
 bool ExpressionNodeTree::checkOperand(const string & input)
{
	return(/*input == "!" ||*/ input == "+" || input == "-" || /*input == "~" || */input == "*" || input == "/" ||
		input == "%" || input == "&&" || input == "||" || input == ">" || input == "<" || input == ">=" || input ==
		"<=" || input == "==" || input == "!=");
}
int ExpressionNodeTree::calculateResult(const string & input, const int & op1, const int & op2)
{
	if (input == "+")
	{
		return op1 + op2;
	}
	else if (input == "-")
	{
		return op1 - op2;
	}
	else if (input == "!")
	{
		return !op1;
	}
	else if (input == "*")
	{
		return op1 * op2;
	}
	else if (input == "/")
	{
		return op1 / op2;
	}
	else if (input == "&&")
	{
		return op1 && op2;
	}
	else if (input == "||")
	{
		return op1 || op2;
	}
	else if (input == "%")
	{
		return op1 % op2;
	}
	else if (input == ">")
	{
		return op1 > op2;
	}
	else if (input == ">=")
	{
		return op1 >= op2;
	}
	else if (input == "!=")
	{
		return op1 != op2;
	}
	else if (input == "<")
	{
		return op1 < op2;
	}
	else if (input == "<=")
	{
		return op1 <= op2;
	}
	else if (input == "~")
	{
		return op1 * -1;
	}
	else if (input == "==")
	{
		return op1 == op2;
	}
	else
	{
		return -234234234; // making compiler happy
	}

}
int ExpressionNodeTree::process(ExpressionNode* base, vector<map<string, int>>& processor)
{
	
	if (base->getIs_Operand() == true && base->getIs_Symbol() == true)
	{
		return processor[0][base->getOperatorType()];
	}
	else if (base->getIs_Symbol() == false && base->getIs_Operand() != false)
	{
		return base->getOperand();
	}	

	int32_t op2 = process(base->getRight(), processor);
	int32_t op1 = process(base->getLeft(), processor);
	return (calculateResult(base->getOperatorType(), op1, op2));
}

int ExpressionNodeTree::process(vector<map<string, int>>& processor)
{
	return process(this->base, processor);
}

ExpressionNodeTree::ExpressionNodeTree(const ExpressionNodeTree & other)
{
	this->base = new ExpressionNode(*other.base);
}







