#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "Parse.h"
#include "InstructionSet.h"
#include "ExpressionNode.h"
#include "ExpressionNodeTree.h"
using namespace std;


bool isValidToken(const string& token)
{
	
	return token != "text" && token != "output" && token != "var" && token != "set";
}
void initialize(int& indexInstructionSet, vector<InstructionSet*> &instructionSet)
{
	// make vector of expression Nodes
	vector<ExpressionNode*> bunchOfExpressions;
	string tokenizer;
	peek_next_token();
	while (isValidToken(next_token()) && next_token_type != END)
	{
		read_next_token();
		tokenizer = next_token();
		//explicit ExpressionNode(string optr, string type_operand, bool is_operand, bool is_symbol, int operand);
		if (next_token_type == SYMBOL)
		{
			bunchOfExpressions.push_back(new ExpressionNode("", next_token(), false, false, 0));
		}
		else if (next_token_type == NAME)
		{
			bunchOfExpressions.push_back(new ExpressionNode("", next_token(), true, true, 0));
		}
		else if (next_token_type == NUMBER)
		{
			bunchOfExpressions.push_back(new ExpressionNode("", "", true, false, token_number_value));
		}
		if (tokenizer == "//")
		{
			break;
		}
		peek_next_token();
	}
	instructionSet[indexInstructionSet]->current = ExpressionNodeTree(bunchOfExpressions);
}

void run() {
	int indexInstructionSet = 0;
	vector<map<string, int>> tokenInstructions;
	map<string, int> stringIntCombo;
	InstructionSet* instructPointer;
	string executeInstruction;
	tokenInstructions.push_back(stringIntCombo);
	vector<InstructionSet*> instructions;
	read_next_token();
	while (next_token_type != END)
	{
		if (next_token_type != NAME)
		{
			skip_line();
		}
		else
		{
			instructions.push_back(new InstructionSet());
			instructions[indexInstructionSet]->currentInstruction = next_token();
			if (instructions[indexInstructionSet]->currentInstruction == "output")
			{
				initialize(indexInstructionSet, instructions);
			}
			else if (instructions[indexInstructionSet]->currentInstruction == "set" || instructions[indexInstructionSet]->currentInstruction == "var")
			{
				read_next_token();
				instructions[indexInstructionSet]->textOutput = next_token();
				initialize(indexInstructionSet, instructions);
			}
			else if (instructions[indexInstructionSet]->currentInstruction == "text")
			{
				read_next_token();
				instructions[indexInstructionSet]->textOutput = next_token();
			}
			indexInstructionSet++;
		}
		if (string(next_token()) == "//")
		{
			skip_line();
		}
		read_next_token();

	}
	for (vector<InstructionSet*>::iterator index = instructions.begin(); index != instructions.end(); ++index)
	{
		instructPointer = *index;
		executeInstruction = instructPointer->currentInstruction;
		if (executeInstruction == "var")
		{
			if (tokenInstructions[0].count(instructPointer->textOutput) > 0)
			{
				cout << "variable" << instructPointer->textOutput << " incorrectly initialized" << endl;
			}
			tokenInstructions[0][instructPointer->textOutput] = instructPointer->current.process(tokenInstructions);

		}
		else if (executeInstruction == "set")
		{
			if (tokenInstructions[0].count(instructPointer->textOutput) < 1)
			{
				cout << "variable" << instructPointer->textOutput << " not declared" << endl;
			}
			tokenInstructions[0][instructPointer->textOutput] = instructPointer->current.process(tokenInstructions);
		}
		else if (executeInstruction == "text")
		{
			cout << instructPointer->textOutput; //<< endl;
		}
		else if (executeInstruction == "output")
		{
			cout << instructPointer->current.process(tokenInstructions);
		}
		delete instructPointer;

	}
}
		int main(void) {
			/*
			set_input("test_grader.blip");
			run();
			*/
			
			
			set_input("test1.blip");
			run();
			cout << endl;
			set_input("test2.blip");
			run();
			cout << endl;
			set_input("test3.blip");
			run();
			cout << endl;
			set_input("test4.blip");
			run();
			cout << endl;
			set_input("test5.blip");
			run();
			cout << endl;
			set_input("test7.blip");
			run();
			cout << endl;
			set_input("test2.blip");
			run();
			cout << endl;
			set_input("test8.blip");
			run();
			cout << endl;
			system("pause");
			
		}

	
