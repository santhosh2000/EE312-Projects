#ifndef PROJECT8_INSTRUCTION_SET
#define PROJECT8_INSTRUCTION_SET
#include <string>
#include "ExpressionNodeTree.h"
#include "ExpressionNode.h"


// Advised by a EE 312 tutor to make ( so I oblidged lol)
using namespace std;
class InstructionSet
{
public:
	string textOutput;
	string currentInstruction;
	ExpressionNodeTree current;
};



#endif