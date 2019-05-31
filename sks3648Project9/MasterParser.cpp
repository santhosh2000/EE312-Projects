#include <cstdio>
#include <cstdint>
#include "MasterParser.h"
#include "SharnushString.h"
#include "Parse.h"
#include "ProcessNode.h"

/*
	UT EID: sks3648
	Name: Santhosh Saravanan
	Class: Spring 2019 section EE 312	
	Professor: Dr. Gligoric
	Special shoutout to Stack Overflow, GeeksforGeeks, the undergraduate TAS, and Umar Burney for helping me with this project....

	Thank you so much for your help!

*/
/*
	Funcions to help create the distinct nodes in the tree classes
	John's recommendation from Stack Overflow
*/
Process_Node* CreateTreeNode();
Process_Node* CreateTreeNode_string(SharnushString);
Process_Node* CreateTreeNode_num(int);


template <typename Shar = int> const Shar& Evaluate_Value(Process_Node *);
template <typename Shar = int> Shar * Evaluate_Variable(Process_Node *, ExpressionNodeTable&, ExpressionNodeTable&);

return_value Evaluate_Void(Process_Node *, ExpressionNodeTable&, ExpressionNodeTable&);
int Evaluate_Operand(Process_Node *, ExpressionNodeTable&, ExpressionNodeTable&);
// Evaluates instructiions or functions with no specific return value
return_value Evaluate_Void(Process_Node*  node, ExpressionNodeTable& table, ExpressionNodeTable& mega_chungus)
{
	return_value result = { true };

	switch (node->type) {
	case LITERAL:
	{
		SharnushString stmnt_type{ Evaluate_Value<SharnushString>(node) };
		if (stmnt_type == "text") {
			printf("%s", Evaluate_Value<SharnushString>(node->allNodes[0]).c_str());
		}

		else if (stmnt_type == "output") {
			printf("%d", Evaluate_Operand(node->allNodes[0], table, mega_chungus));
		}

		else if (stmnt_type == "var") {
			SharnushString var_name = Evaluate_Value<SharnushString>(node->allNodes[0]);
			int var_value = Evaluate_Operand(node->allNodes[1], table, mega_chungus);
			if (table.get(var_name)) {
				printf("Bariable may not have been initialized properly dummy!", var_name.c_str());
				*(table.get(var_name)) = var_value;
				break;
			}

			table.insert(var_value, var_name);
		}

		else if (stmnt_type == "set") {
			SharnushString var_name = Evaluate_Value<SharnushString>(node->allNodes[0]);
			int32_t var_value = Evaluate_Operand(node->allNodes[1], table, mega_chungus);

			int32_t * local = table.get(var_name);
			int32_t * global = mega_chungus.get(var_name);

			if (!local && !global) {
				printf("variable %s not declared\n", var_name.c_str());
				table.insert(var_value, var_name);
			}
			else if (local)
				*local = var_value;
			else
				*global = var_value;
		}

		else if (stmnt_type == "if") {
			for (int i = 0; i < node->allNodes.size(); i += 2) {
				if (Evaluate_Operand(node->allNodes[i], table, mega_chungus)) {
					result = run(node->allNodes[i + 1], table, mega_chungus);

					break;
				}
			}
		}

		else if (stmnt_type == "do")
			while (Evaluate_Operand(node->allNodes[0], table, mega_chungus) && result.is_void)
				result = run(node->allNodes[1], table, mega_chungus);

		// for the defun call, functions are kept in the table as well to improve system design
		else if (stmnt_type == "defun") {
			SharnushString fun_name = Evaluate_Value<SharnushString>(node->allNodes[0]);
			process new_fun;

			int i = 1;
			for (; i < node->allNodes.size() - 1; i++)
				new_fun.arguments.push_back(Evaluate_Value<SharnushString>(node->allNodes[i]));

			new_fun.treePtr = node->allNodes[i];

			table.insert(new_fun, fun_name, FUNC_VALUE);
		}

		else if (stmnt_type == "return") {
			result.is_void = false;
			result.value = Evaluate_Operand(node->allNodes[0], table, mega_chungus);
		}
	}

	case SHIT: case FINALLY: case NUM: case STR: case OPERATOR:
		break;

	}

	return result;
}

// Returns the value of a calculation resulting from the use of an operator
int32_t Evaluate_Operand(Process_Node* node, ExpressionNodeTable& table, ExpressionNodeTable& mega_chungus)
{
	switch (node->type) {
	case NUM:
		return Evaluate_Value(node);

	case VAR:
		return *Evaluate_Variable(node, table, mega_chungus);

	case LITERAL:
	{
		// A function has been called
		process function{ *Evaluate_Variable<process>(node->allNodes[0], table, mega_chungus) };
		ExpressionNodeTable ominichungus;

		for (int i = 0; i < function.arguments.size(); i++)
		{
			ominichungus.insert(Evaluate_Operand(node->allNodes[i + 1], table, mega_chungus), function.arguments[i]);
		}

		return_value result = run(function.treePtr, ominichungus, mega_chungus);

		if (result.is_void)
			result.value = 0;

		return result.value;
	}

	case OPERATOR:
	{
		// an operator has been called
		SharnushString operationType{ Evaluate_Value<SharnushString>(node) };
		if (operationType == "&&") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus) && Evaluate_Operand(node->allNodes[1], table, mega_chungus))
				return 1;
			return 0;
		}
		if (operationType == "||") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus) || Evaluate_Operand(node->allNodes[1], table, mega_chungus))
				return 1;
			return 0;
		}
		if (operationType == "<") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus) < Evaluate_Operand(node->allNodes[1], table, mega_chungus))
				return 1;
			return 0;
		}
		if (operationType == ">") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus) > Evaluate_Operand(node->allNodes[1], table, mega_chungus))
				return 1;
			return 0;
		}
		if (operationType == "-")
			return Evaluate_Operand(node->allNodes[0], table, mega_chungus) - Evaluate_Operand(node->allNodes[1], table, mega_chungus);
		if (operationType == "*")
			return Evaluate_Operand(node->allNodes[0], table, mega_chungus) * Evaluate_Operand(node->allNodes[1], table, mega_chungus);
		if (operationType == "/")
			return Evaluate_Operand(node->allNodes[0], table, mega_chungus) / Evaluate_Operand(node->allNodes[1], table, mega_chungus);

		if (operationType == "+")
			return Evaluate_Operand(node->allNodes[0], table, mega_chungus) + Evaluate_Operand(node->allNodes[1], table, mega_chungus);
		if (operationType == "%")
			return Evaluate_Operand(node->allNodes[0], table, mega_chungus) % Evaluate_Operand(node->allNodes[1], table, mega_chungus);
		
		if (operationType == "==") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus) == Evaluate_Operand(node->allNodes[1], table, mega_chungus))
				return 1;
			return 0;
		}
		if (operationType == "!=") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus) != Evaluate_Operand(node->allNodes[1], table, mega_chungus))
				return 1;
			return 0;
		}
		if (operationType == "<=") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus) <= Evaluate_Operand(node->allNodes[1], table, mega_chungus))
				return 1;
			return 0;
		}
		if (operationType == ">=") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus) >= Evaluate_Operand(node->allNodes[1], table, mega_chungus))
				return 1;
			return 0;
		}
		if (operationType == "!") {
			if (Evaluate_Operand(node->allNodes[0], table, mega_chungus))
				return 0;
			return 1;
		}
		if (operationType == "~")
			return -Evaluate_Operand(node->allNodes[0], table, mega_chungus);


		return 0;
	}
	}
}

// my personla hell
// thanks to stack overflow and geeksforgeeks
return_value run(Process_Node * node, ExpressionNodeTable& local, ExpressionNodeTable& global)
{
	return_value result;

	while (node->type != FINALLY) {
		result = Evaluate_Void(node, local, global);

		if (!result.is_void)
			return result;

		node = node->next;
	}

	//result is NULLptr, must handle it to prevent after-use error
	return result;
}

// Constructs parse tree nodes and pushes them into the parse tree
void parse(Process_Node_Tree* out)
{
	while (out->finish()->type != FINALLY) {
		Process_Node * new_node = CreateTreeNode();
		out->push(new_node);
	}
}

// Creates a tree node of type MAGIC_STR
Process_Node * CreateTreeNode_string(SharnushString s)
{
	Process_Node * new_node = new Process_Node;
	new_node->type = STR;
	new_node->val = new SharnushString(s);
	new_node->typeToken = STRING_VALUE;

	return new_node;
}

// Make an Integer Tree Node
Process_Node* CreateTreeNode_num(int32_t n)
{
	Process_Node*  new_node = new Process_Node;
	new_node->type = NUM;
	new_node->val = new int32_t(n);
	new_node->typeToken =NUM_VALUE;

	return new_node;
}

// Make a string Tree Node
Process_Node* CreateTreeNode()
{
	read_next_token();

	Process_Node* new_node = new Process_Node;

	if (next_token_type == END) {
		new_node->type = FINALLY;
	}

	else if (next_token_type == NAME) {
		SharnushString name_type{ next_token() };

		new_node->type = LITERAL;
		new_node->val= new SharnushString(name_type);
		new_node->typeToken = STRING_VALUE;

		if (name_type == "text") {
			read_next_token();
			new_node->allNodes.push_back(CreateTreeNode_string(next_token()));
		}

		else if (name_type == "output" || name_type == "return") {
			new_node->allNodes.push_back(CreateTreeNode());
		}

		else if (name_type == "var" || name_type == "set") {
			read_next_token();
			new_node->allNodes.push_back(CreateTreeNode_string(next_token()));
			new_node->allNodes.push_back(CreateTreeNode());
		}

		else if (name_type == "if") {
			Process_Node* condition = CreateTreeNode();

			while (1) {
				new_node->allNodes.push_back(condition);

				Process_Node_Tree myDock;
				parse(&myDock);
				new_node->allNodes.push_back(myDock.start());

				if (*(SharnushString*)(myDock.finish()->val) == "fi") {
					myDock.clean();
					break;
				}

				if (*(SharnushString*)(myDock.finish()->val) == "else")
					condition = CreateTreeNode_num(1);
				else
					condition = CreateTreeNode();

				myDock.clean();
			}
		}

		else if (name_type == "do") {
			Process_Node*  condition = CreateTreeNode();
			new_node->allNodes.push_back(condition);

			Process_Node_Tree myDock;
			parse(&myDock);

			new_node->allNodes.push_back(myDock.start());
			myDock.clean();
		}

		else if (name_type == "defun") {
			read_next_token();
			Process_Node*  fun_name = CreateTreeNode_string(next_token());
			new_node->allNodes.push_back(fun_name);

			read_next_token(); 
			read_next_token();
			while (SharnushString{ next_token() } != "smarap") {
				new_node->allNodes.push_back(CreateTreeNode_string(next_token()));
				read_next_token();
			}

			Process_Node_Tree myDock;
			parse(&myDock);

			new_node->allNodes.push_back(myDock.start());
			myDock.clean();
		}

		else if (name_type == "call") {
			read_next_token();
			Process_Node* fun_name = CreateTreeNode_string(next_token());
			new_node->allNodes.push_back(fun_name);

			read_next_token(); 

			while (SharnushString{ peek_next_token() } != "sgra")
				new_node->allNodes.push_back(CreateTreeNode());

			read_next_token(); 
		}

		else if (name_type == "fi" || name_type == "else" || name_type == "od" || name_type == "nufed")
			new_node->type = FINALLY;

		else 
			new_node->type = VAR;
	}

	else if (next_token_type == NUMBER) {
		delete new_node;
		new_node = CreateTreeNode_num(token_number_value);
	}

	else if (next_token_type == SYMBOL) {
		SharnushString symtec{ next_token() };
		new_node->type = OPERATOR;
		new_node->val = new SharnushString(symtec);
		new_node->typeToken = STRING_VALUE;

		// Comment Alert
		if (symtec.size() >= 2 && symtec.c_str()[0] == '/' && symtec.c_str()[1] == '/') {
			skip_line();
			delete new_node;
			return CreateTreeNode();
		}

		new_node->allNodes.push_back(CreateTreeNode());

		if (symtec != "!" && symtec != "~")
			new_node->allNodes.push_back(CreateTreeNode());
	}

	return new_node;
}



// Returns the value subfield of a Process Node
template <typename Shar>
const Shar& Evaluate_Value(Process_Node* node)
{
	return *((Shar*)(node->val));
}

// Returns value of variable from Expression Node Tree
template <typename Shar>
Shar* Evaluate_Variable(Process_Node*  node, ExpressionNodeTable& ominichungus, ExpressionNodeTable& mega_chungus)
{
	Shar* local = ominichungus.get<Shar>(Evaluate_Value<SharnushString>(node));

	if (local)
		return local;

	return mega_chungus.get<Shar>(Evaluate_Value<SharnushString>(node));
}

