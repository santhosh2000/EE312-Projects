#include "MasterParser.h"
#include "ProcessNode.h"
#include "Parse.h"
#include "SharnushString.h"
#include "SharnushVector.h"

/*
	UT EID: sks3648
	Name: Santhosh Saravanan
	Class: Spring 2019 section EE 312
	Professor: Dr. Gligoric
	Special shoutout to Stack Overflow, GeeksforGeeks, the undergraduate TAS, and gradute TAs for helping me with this project....

	Thank you so much for your help!

*/
/* Unfinished main **/
int main()
{
	ExpressionNodeTable NodeTable;
	Process_Node_Tree tree;
	set_input("test_grader.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	/*
	set_input("test8.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	set_input("test7.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	set_input("test6.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	set_input("test5.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	set_input("test4.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	set_input("test3.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	set_input("test2.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	set_input("test1.blip");
	parse(&tree);
	run(tree.start(), NodeTable, NodeTable);
	*/
	//system("pause");

	return 0;
}