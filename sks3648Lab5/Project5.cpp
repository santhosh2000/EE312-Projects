/*
 * Set ADT
 * Project5.c
 *
 * Santhosh Saravanan
 * EE 312 Project 5 -( Shirley Liu from 2-3 p.m. on Mondays
 * Spring 2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

 /*
  * Several of the required functions have been written already
  * You may use these functions as-is or you may modify them in any way.
  * Please NOTE, you are responsible for ensuring that the functions work correctly in
  * your project solution. Just because the function works correctly in my solution does
  * NOT mean that the function will work correctly in yours.
  */

  /*
   * Design NOTES:
   *
   * The design provided in this starter kit assumes
   * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
   * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
   * the amount of storage available in the elements[] array is equal to length
   */



   /* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*)malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*)malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }

	destroySet(self);
	createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
	int low = 0;
	int high = self->len;
	int mid = 0;
	while (low < high)
	{
		mid = (low + high) / 2;
		if (self->elements[mid] > x)
		{
			high = mid;
		}
		else if (self->elements[mid] < x)
		{
			low = mid + 1;
		}
		else
		{
			return true;
		}
	}
	return false;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
	int* newElements = (int*)malloc(sizeof(int)* (self->len + 1));
	if (self->len == 0)
	{
		newElements[0] = x;
	}
	else
	{
		bool avoidDuplicates = false;
		int j = 0;
		for (int i = 0; i < self->len; i++)
		{
			if (x == self->elements[i])
			{
				free(newElements);
				return;
			}
			if (x < self->elements[i] && !avoidDuplicates)
			{
				avoidDuplicates = true;
				newElements[j] = x;
				j++;

			}
			newElements[j] = self->elements[i];
			j++;
			if (self->len == i + 1 && !avoidDuplicates)
			{
				newElements[j] = x;
				avoidDuplicates = true;
			}
		}

	}
	free(self->elements);
	self->elements = newElements;
	self->len++;
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
	int* elements = (int*)malloc(self->len * sizeof(int));
	int len = self->len;
	int j = 0;
	for (int i = 0; i < len; i++) {
		if (x != self->elements[i]) {
			elements[j++] = self->elements[i];
		}
		else {
			self->len--;
		}
	}

	free(self->elements);
	self->elements = elements;
}
/* done for you already */
void displaySet(const Set* self) {
	int k;

	printf("{");

	if (self->len == 0) {
		printf("}");
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			}
			else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
	if (self->len != other->len)
	{
		return false;
	}
	for (int i = 0; i < self->len; i++)
	{
		if (self->elements[i] != other->elements[i])
		{
			return false;
		}
	}
	return true;
}


/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
	int index = 0;
	for (int i = 0; i < other->len; i++) {
		if (index == self->len) {
			return true;
		}
		else if (self->elements[index] == other->elements[i]) {
			index++;
		}
	}

	return index == self->len;
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
	int* newElements = (int*)malloc(self->len * sizeof(int));
	int numElements = 0;
	int a = 0; // index of newElements
	int b = 0; // index of other Elements
	for (int i = 0; i < self->len; i++)
	{
		if (b == other->len)
		{
			break;
		}
		else if (self->elements[i] == other->elements[b])
		{
			newElements[a++] = self->elements[i];
			b++;
			numElements++;
		}
		else if (self->elements[i] > other->elements[b])
		{
			b++;
			i--;
		}
	}
	free(self->elements);
	self->elements = newElements;
	self->len = numElements;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
	if (other->len == 0) {
		return;
	}

	int* elements = (int*)malloc(self->len * sizeof(int));
	int count = 0;

	int k = 0;
	int j = 0;
	for (int i = 0; i < self->len; i++) {
		if (j >= other->len) {
			elements[k++] = self->elements[i];
			count++;
		}
		else if (self->elements[i] < other->elements[j]) {
			elements[k++] = self->elements[i];
			count++;
		}
		else if (self->elements[i] > other->elements[j]) {
			j++;
			i--;
		}
		else {
			j++;
		}
	}
	free(self->elements);
	self->elements = elements;
	self->len = count;
}


/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
	int* completeSet = (int*)malloc(sizeof(int)*(other->len + self->len));
	int numElements = 0;
	int selfIndex = 0;
	int otherIndex = 0;
	for (int i = 0; i < other->len + self->len; i++)
	{
		if (otherIndex >= other->len)
		{
			while (selfIndex < self->len)
			{
				completeSet[i++] = self->elements[selfIndex++];
				numElements++;
			}
			break;
		}


		if (selfIndex >= self->len)
		{
			while (otherIndex < other->len)
			{
				completeSet[i++] = other->elements[otherIndex++];
				numElements++;
			}
			break;
		}


		if (self->elements[selfIndex] > other->elements[otherIndex])
		{
			completeSet[i] = other->elements[otherIndex++];
			numElements++;
		}

		else if (self->elements[selfIndex] < other->elements[otherIndex])
		{
			completeSet[i] = self->elements[selfIndex++];
			numElements++;
		}
		// even case
		else
		{
			completeSet[i] = self->elements[selfIndex];
			otherIndex++;
			selfIndex++;
			numElements++;
		}
	}
	free(self->elements);
	self->elements = completeSet;
	self->len = numElements;
}

