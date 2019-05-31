#include "ProcessNode.h"
#define TYPE_TOKEN_H
/*
	UT EID: sks3648
	Name: Santhosh Saravanan
	Class: Spring 2019 section EE 312
	Professor: Dr. Gligoric
	Special shoutout to Stack Overflow, GeeksforGeeks, the undergraduate TAS, and Umar Burney for helping me with this project....

	Thank you so much for your help!

*/

void Process_Node_Tree::push(Process_Node* crap)
{
	this->tail->next = crap;
	this->tail = crap;
}
Process_Node_Tree::~Process_Node_Tree()
{
	while (this->head != nullptr)
	{
		delete head;
		this->head = nullptr;
	}
}
Process_Node* Process_Node_Tree::finish()
{
	return this->tail;
}
Process_Node* Process_Node_Tree::start()
{
	return this->head;
}
void Process_Node_Tree::clean()
{
	this->head = this->tail = nullptr;
}
Process_Node_Tree::Process_Node_Tree()
{
	this->head = new Process_Node();
	this->tail = this->head;
	this->head->type = SHIT;
}
Process_Node::~Process_Node()
{


	if (val != nullptr)
	{
		if (typeToken ==NUM_VALUE)
		{
			delete (int32_t*)val;
		}
		else if (typeToken == STRING_VALUE)
		{
			delete (SharnushString*)val;
		}
		else
		{
			delete (Process_Node*)val;
		}
		val = nullptr;// to prevent use-after-free error
	}
	for (int i = 0; i < allNodes.size(); i++)
	{
		if (allNodes[i] != nullptr)
		{
			delete allNodes[i];
			allNodes[i] = nullptr;// prevent use-after free error
		}

	}
	if (next != nullptr)
	{
		delete next;
		next = nullptr;
	}

}
Process_Node::Process_Node()
{
	this->val = nullptr;
	this->type = SHIT;
	this->next = nullptr;
}