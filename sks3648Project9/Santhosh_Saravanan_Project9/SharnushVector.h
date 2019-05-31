

#ifndef _Sharnush_Vector_h
#define _Sharnush_Vector_h 


#include <assert.h>
#include <map>
#include <vector>
//using templates from Gligoric's lecture

template <typename Shar>
struct SharnushVector {
private:
	Shar* entity;
	int length;
	int capacity;

public:
	~SharnushVector(void) { delete[] entity; }

	SharnushVector(void) {
		this->entity = new Shar[1];
		this->length = 0;
		this->capacity = 1;
	}


	Shar& operator[](uint32_t var) {
		assert(var < this->length);

		return this->entity[var];
	}
	SharnushVector(const SharnushVector& other) : SharnushVector(other.size()) {
		for (int i = 0; i < length; i++) {
			this->entity[i] = other.entity[i];
		}
	}
	int size(void) const { return length; }

	SharnushVector(uint32_t len) {
		this->length = len;
		this->capacity = len;
		if (this->capacity == 0) {
			this->capacity = 1;
		}
		this->entity = new Shar[capacity];
	}


	/*
	Project 7 stuff
	*/

	void push_back(Shar var)
	{
		if (this->capacity == this->length) {
			this->capacity *=2 ; // Gligoric lol
			Shar* new_database = new Shar[capacity];
			for (uint32_t index = 0; index < this->length; index++) {
				new_database[index] = this->entity[index];
			}
			delete[] this->entity;
			this->entity = new_database;
		}

		this->entity[this->length] = var;
		this->length++;
	}
};

#endif 