/*
 * Name:Santhosh Saravanan
 * EID: sks3648
 * Project 7, CRM part 2
 * EE 312, Spring 2019
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
	for (int i = 0; i < this->length; i++)
	{
		if (this->data[i].name == name)
		{
			return this->data[i];
		}
	}
	if (this->length == this->capacity)
	{
		this->capacity *= 2;
		Customer* spaciousData = new Customer[this->capacity];
		for (int index = 0;index < this->length; index++)
		{
			spaciousData[index] = this->data[index];
		}
		delete[] this->data;
		this->data = spaciousData;
	}
	this->data[this->length++] = Customer(name);
	return this->data[this->length - 1];

}

bool CustomerDB::isMember(String name) { // not done, your effort goes here
	for (int i = 0; i < this->length; i++)
	{
		if (this->data[i].name == name)
		{
			return true;
		}
	}
	return false;
}
