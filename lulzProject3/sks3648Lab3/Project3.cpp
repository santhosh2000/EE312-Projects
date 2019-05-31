/*
// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Santhosh Saravanan
// sks3648
// Slip days used: 0
// Spring 2019
*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UTString.h"

#define SIGNATURE (~0xdeadbeef)

 /*
  * Helper macro to find the signature of a UTString
  * Treat this like a function that takes a UTString*
  * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))
uint32_t lenstr(const char* src);
void copyToHeap(const char* src, char* dest);
void addSignature(uint32_t index, char* src);
/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
	if (CHECK(s) == SIGNATURE) { return true; }
	else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
	uint32_t srcLength = lenstr(src);
	char* InitString = (char*)(malloc(srcLength * sizeof(char) + sizeof(SIGNATURE) + 1));
	UTString* InitUTString = (UTString*)malloc(sizeof(UTString));
	copyToHeap(src, InitString);
	InitUTString->capacity = srcLength * sizeof(char) + sizeof(SIGNATURE) + 1 - 5;
	InitUTString->length = srcLength;
	InitUTString->string = InitString;
	return InitUTString;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
	assert(isOurs(s));
	return s->length;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
	assert(isOurs(s));
	uint32_t suffixLen = lenstr(suffix);
	uint32_t counter = 0;
	unsigned int  firstLen = s->length;
	while (firstLen < s->capacity && firstLen < s->length + suffixLen)
	{
		s->string[firstLen] = suffix[counter];
		counter++;
		firstLen++;
	}
	s->length = firstLen;
	s->string[firstLen] = '\0';
	addSignature(firstLen + 1, s->string);
	return s;
}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
	assert(isOurs(dst));
	int suffixLen = lenstr(src);
	uint32_t i = 0;
	while (src[i] != '\0' && i < dst->capacity)
	{
		dst->string[i] = src[i];
		i++;
	}
	dst->length = i;
	dst->string[i] = '\0';
	addSignature(i + 1, dst->string);
	return dst;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
	assert(isOurs(self));
	free((char*)self->string);
	free(self);



}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
	assert(isOurs(s));
	if (s->capacity >= new_capacity)
	{
		return s;
	}
	else
	{
		char* prevString = s->string;
		char* newBoyz = (char*)malloc(new_capacity * sizeof(char) + 1 + sizeof(SIGNATURE));
		s->capacity = new_capacity;
		s->string = newBoyz;
		uint32_t j = 0;
		while (prevString[j] != '\0' &&  j < s->capacity)
		{
			s->string[j] = prevString[j];
			j++;
		}
		s->length = j;
		s->string[j] = '\0';
		addSignature(j + 1, s->string);
		free(prevString);
		return s;
	}

}

/*
   Intuitive method which just counts the total number of non-Null characters pointed to by char pointer
   returns length after counting
 */
uint32_t lenstr(const char* src)
{
	uint32_t i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	return i;
}
/*
  Intuitive method which just copies the characters in the source into the destination, assuming length and
  capacity have been initialized correctly....
*/
void copyToHeap(const char* src, char* dest)
{
	uint32_t i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	addSignature(i + 1, dest);
}
/*
Intuitive method which appends the signature (~0xdeadbeef) after the null-termination character present
in char array
*/
void addSignature(uint32_t index, char* src)
{
	src[index] = (char)~0xef;
	src[index + 1] = (char)~0xbe;
	src[index + 2] = (char)~0xad;
	src[index + 3] = (char)~0xde;
}