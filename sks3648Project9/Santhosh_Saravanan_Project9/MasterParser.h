#ifndef MASTERPARSER_H
#define MASTERPARSER_H

#include "ProcessNode.h"
#include "ExpressionNodeTable.h"

struct return_value
{
	bool is_void;
	int value;
};

void parse(Process_Node_Tree * out);
return_value run(Process_Node*, ExpressionNodeTable&, ExpressionNodeTable&);
#endif