#ifndef PROCESS_NODE_H
#define PROCESS_NODE_H
#include "SharnushString.h"
#include "SharnushVector.h"
#include "TypeToken.h"
enum ProcessNodeTypes
{
	NUM, STR, OPERATOR, LITERAL, VAR, FINALLY, SHIT
};



struct Process_Node
{
	~Process_Node();
	Process_Node();
	ProcessNodeTypes type;
	TYPE_TOKEN typeToken;
	SharnushVector<Process_Node*> allNodes;
	Process_Node* next;
	void* val;
};
struct Process_Node_Tree
{
private:
	Process_Node* head;
	Process_Node* tail;
public:
	~Process_Node_Tree();
	Process_Node_Tree();
	void push(Process_Node*);
	void clean();
	Process_Node* finish();
	Process_Node* start();
};
#endif