#ifndef TYPE_TOKEN_H
#define TYPE_TOKEN_H
/*
	UT EID: sks3648
	Name: Santhosh Saravanan
	Class: Spring 2019 section EE 312
	Professor: Dr. Gligoric
	Special shoutout to Stack Overflow, GeeksforGeeks, the undergraduate TAS, and Umar Burney for helping me with this project....

	Thank you so much for your help!

*/
#include "SharnushString.h"
#include "SharnushVector.h"


enum TYPE_TOKEN
{
	FUNC_VALUE,
	NUM_VALUE,
	STRING_VALUE
};

struct Process_Node;

struct process {
	SharnushVector<SharnushString> arguments;
	Process_Node* treePtr;

	/*
	~process()
	{
	}
	*/
	process(const process &other) : arguments(other.arguments)
	{
		treePtr = other.treePtr;
	}
	process() : arguments{}
	{
		treePtr = nullptr;
	}



};

#endif