#ifndef _Literals_h
#define _Literals_h
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
struct Literal
{
private:
	uint32_t len;
	char* ptrString;
	void create(const char* other);
	void copy(const char* other);
	void copy(const Literal& other);
	void destroy(); 
public:
	Literal& operator=(const Literal& other){};
	Literal& operator= (const char* other){};
	Literal(void) {};
	~Literal(void) {};
	Literal(const char* other) {};
	Literal(const Literal& other) {};
	uint32_t getLen(void);
	const char* getStr(void);
	/*
	   checking for string equality
	*/
	bool operator==(Literal q);
	bool operator<(Literal q);
	bool operator<=(Literal q);
	bool operator>=(Literal q);
	bool operator>(Literal q);
	bool operator!=(Literal q);

};
	
#endif
