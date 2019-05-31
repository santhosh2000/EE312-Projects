#ifndef EXPRESSION_NODE_TABLE_H
#define EXPRESSION_NODE_TABLE_H
#include "SharnushString.h"
#include "TypeToken.h"

/*
	UT EID: sks3648
	Name: Santhosh Saravanan
	Class: Spring 2019 section EE 312
	Professor: Dr. Gligoric
	Special shoutout to Stack Overflow, GeeksforGeeks, the undergraduate TAS, and Umar Burney for helping me with this project....

	Thank you so much for your help!

*/
struct ExpressionNodeTable
{
	struct ExpressionNode
	{
		TYPE_TOKEN value_type;
		SharnushString name;
		void* value;
		ExpressionNode* LeftNode;
		ExpressionNode* RightNode;
		ExpressionNode* ParentNode;

	public:

		~ExpressionNode()
		{
			if (value != nullptr)
			{
				if (value_type == NUM_VALUE)
				{
					delete (int*)value;
				}
				else if (value_type == FUNC_VALUE)
				{
					delete (process*)value;
				}
			}
			value = nullptr;// setting pointer to null if none of the types match up
			if (this->LeftNode != nullptr && this->RightNode != nullptr)
			{
				delete LeftNode;
				delete RightNode;

			}
			this->LeftNode = nullptr;
			this->RightNode = nullptr;
		}
		template<typename Shar>
		ExpressionNode(TYPE_TOKEN tokenType, const SharnushString& other, Shar value)
		{
			this->value = new Shar(value);
			this->RightNode = this->LeftNode = nullptr;
			this->value_type = tokenType;
			this->name = other;
		}
		ExpressionNode()
		{
			this->name = "";
			this->value = 0;
			this->value_type = NUM_VALUE;
		}
	};

	ExpressionNode* head;

public:

	~ExpressionNodeTable()
	{
		if (head != nullptr)
		{
			delete head;
			head = nullptr;
		}
	}
	ExpressionNodeTable()
	{
		this->head = nullptr;
	}
	
	template<typename Shar>void insert(const Shar & value, const SharnushString & otherName, TYPE_TOKEN value_type = NUM_VALUE);
	template<typename Shar = int>Shar* get(const SharnushString & otherName);

};
template<typename Shar>
Shar* ExpressionNodeTable::get(const SharnushString& otherName)
{
	ExpressionNode* current = head;
	while (current != nullptr)
	{
		if (current->name < otherName)
		{
			current = current->RightNode;
		}
		else if (current->name > otherName)
		{
			current = current->LeftNode;
		}
		else if (current->name == otherName)
		{
			return (Shar*)current->value;
		}

	}
	return nullptr;
}
template<typename Shar>
// cited from Gligorc's Parent Node Example in class!
void ExpressionNodeTable::insert(const Shar& value, const SharnushString& otherName, TYPE_TOKEN value_type)
{
	if (this->head == nullptr)
	{
		this->head = new ExpressionNode(NUM_VALUE, otherName, value);
		return;
	}
	ExpressionNode* parent = nullptr;
	ExpressionNode* current = head;
	while (current != nullptr)
	{
		parent = current;
		if (otherName < current->name)
		{
			current = current->LeftNode;
		}
		else if (otherName > current->name)
		{
			current = current->RightNode;
		}
	}
	if (otherName < parent->name)
	{
		parent->LeftNode = new ExpressionNode(NUM_VALUE, otherName, value);
	}
	else
	{
		parent->RightNode = new ExpressionNode(NUM_VALUE, otherName, value);
	}


}



#endif