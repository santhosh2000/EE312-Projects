/*
 * Project1.cpp
 *
 * Name: Santhosh Saravanan
 * EE312 Spring 2018
 * SpellCheck
 */
 // SpellCheck <Project1.cpp>
 // EE 312 Project 1 submission by
 // <Santhosh Saravanan>
 // <sks3648>
 // Slip days used: <0>
 // Spring 2018
#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <string.h> // provides declarations for the string class and methods
#include <iostream> // provides declarations to make character lowercase and for the character class
#define ONE_MB (1 << 20)
#define BUFFER_SIZE ONE_MB 
 /* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
   *
   * Many students find it helpful to declare global variables (often arrays). You are welcome to use
   * globals if you find them helfpul. Global variables are by no means necessary for this project.
   */

   /* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
	  * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
	  * You are expected to use reasonable programming style. I *insist* that you indent
	  * reasonably and consistently in your code. I strongly encourage you to avoid big functions
	  * So, plan on implementing spellCheck by writing two or three other "support functions" that
	  * help make the actual spell checking easier for you.
	  * There are no explicit restictions on using functions from the C standard library. However,
	  * for this project you should avoid using functionality from the C++ standard libary. You will
	  * almost certainly find it easiest to just write everything you need from scratch!
	  */

	  /***** Global variables - BEGIN *****/
bool isDictEmpty = false; // isDictEmpty is a boolean which stores the condition of whether the dictArray provide as input is empty or not.
bool isCharEmpty = false; // isCharEmpty is a boolean which stores the condition of whether the charArray provided as input is empty or not.
char main_Article[BUFFER_SIZE] = {}; // char array initialized to 0 and holds 1 megabyte of dictionary data
char main_Dictionary[BUFFER_SIZE] = {}; // char array initialized to 0 and holds 1 megabyte of article data
int Dictionary_Counter = 0; // counts number of elements in main_Dictionary array
int Article_Counter = 0; // counts number of elements in main_Article array
int resultTestOne = -1; // result of helper method testOne
int resultTestTwo = -1; // result of helper method testTwo
/***** Global variables - END *****/

/* checks if program contains a valid word with the following conditions as specified:
 1 . character preceding first word can't be a letter or must be the first character in article
 2 . length of the word must at least be two
 3 . character following last character in word can't be a letter, but can be the end
 4 .
*/

/*****************************************************************************
**
** @name replaceCharArray
** Converts and stores the content of article to be spell checked to global buffer.
**
** @param article pointer to char buffer
** @return void
** @@
******************************************************************************/
void replaceCharArray(char* article)
{

	char* letter = article;
	int i = 0;
	if (*letter == NULL) {
		isCharEmpty = true;
		return;
	}

	isCharEmpty = false;

	for (; i < BUFFER_SIZE && *letter != '\0'; i++, letter++) {

		if (*letter >= 'a' && *letter <= 'z' || *letter >= 'A' && *letter <= 'Z') {
			main_Article[i] = tolower(*letter);
		}

		else {
			main_Article[i] = ';';
		}
		Article_Counter++;
	}
	main_Article[i] = 0;
}

/*****************************************************************************
**
** @name replaceDictArray
** Converts and stores the content of dictionary to be spell checked to global buffer.
**
** @param article pointer to char buffer
** @return void
** @@
******************************************************************************/

void replaceDictArray(char* dictionary)
{
	char* dictChar = dictionary;
	if (*dictChar == NULL) {
		isDictEmpty = true;
		return;
	}

	isDictEmpty = false;
	int i = 0;
	main_Dictionary[i] = ';';
	for (i = 1; i < BUFFER_SIZE && *dictChar != '\0'; i++, dictChar++) {

		if (*dictChar >= 'a' && *dictChar <= 'z' || *dictChar >= 'A' && *dictChar <= 'Z') {
			main_Dictionary[i] = tolower(*dictChar);
		}

		else if (*dictChar == '\n') {
			main_Dictionary[i] = ';';
		}

		else {
			main_Dictionary[i] = *dictChar;
		}
		Dictionary_Counter++;
	}
	main_Dictionary[i] = 0;
}

/*****************************************************************************
**
** @name checkIfWordExists
** Checks for presence of input word in the global dictionary buffer.
**
** @param word, pointer to char buffer
** @return int, 1 if exists and -1 if not exists.
** @@
******************************************************************************/
int checkIfWordExists(char* word)
{
	size_t length = strlen(word);
	char* pointer = NULL;
	for (int i = 0; i < Dictionary_Counter + 1; i++) {
		if (main_Dictionary[i] == ';' && main_Dictionary[i] != NULL && main_Dictionary[i + length + 1] == ';'
			&& main_Dictionary[i + length + 1] != NULL) {
			pointer = &(main_Dictionary[i + 1]);
			if (strncmp(pointer, word, length) == 0) {
				return 1;
			}
		}
	}
	return -1;
}

/*****************************************************************************
**
** @name spellCheck
** Perform spell check operation on the given article referencing given dictionary.
** Prints spell check needed words to the console.
**
** @param article, char buffer
** @param dictionary, char buffer
** @return void.
** @@
******************************************************************************/
void spellCheck(char article[], char dictionary[])
{
	replaceCharArray(article);
	replaceDictArray(dictionary);
	int selectStringCounter = 0;
	char selectString[255];
	int j = 0;
	/*
	Condition if the user has inputted a correct dictionary and article
	*/

	if (isDictEmpty != true && isCharEmpty != true) {
		for (int i = 0; i < Article_Counter + 1; i++) {
			if (main_Article[i] != '\0' && main_Article[i] != ';') {
				selectString[j++] = main_Article[i];
			}
			else {
				selectString[j] = 0;
				if (j >= 2 && checkIfWordExists(selectString) == -1) {
					printf("%s \n", selectString);
				}
				j = 0;
			}
		}
	}
	/*
	Condition if the user has inputted an empty dictionary and article
	*/
	else if (isCharEmpty != true && isDictEmpty != false) {
		char* pointer = article;
		while (*pointer != '\0') {

			printf("%c", *pointer);
			pointer++;
		}
		printf("\n");
	}

	/*
	Condition if the user has inputted an empty dictionary and article
	*/
	else {
		printf("You have an empty dictionary and article. Please try again!\n");
	}
	/* Sanity check 101 -> reset all global varaibles and delete dynamically allocated space
	*/
	Article_Counter = 0;
	Dictionary_Counter = 0;
	return;
}
