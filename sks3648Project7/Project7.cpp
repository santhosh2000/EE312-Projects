/*
 * Name: Santhosh Saravanan
 * EID: sks3648
 * Project 7, CRM part 2
 * EE 312, Spring 2019
 */

#include <stdio.h>
#include <iostream>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	}
	else if (word == "Diapers") {
		return &num_diapers;
	}
	else if (word == "Rattles") {
		return &num_rattles;
	}

	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	}
	else if (word == "Diapers") {
		return &cust.diapers;
	}
	else if (word == "Rattles") {
		return &cust.rattles;
	}

	/* NOT REACHED */
	return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust);
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}

	return result;
}

void processPurchase() {
	String personName;
	String itemPurchased;
	int amountPurchased;
	int amountInInventory;
	readString(personName);
	readString(itemPurchased);
	readNum(amountPurchased);
	if (amountPurchased > 0)
	{
		amountInInventory = *(selectInventItem(itemPurchased));
		if (amountPurchased > amountInInventory)
		{
			std::cout << "Sorry " << personName.c_str() << ", we only have " << *selectInventItem(itemPurchased) << " " << itemPurchased.c_str() << std::endl;
		}
		else
		{
			*(selectInventItem(itemPurchased)) -= amountPurchased;
			*(selectInventItem(itemPurchased, database[personName])) += amountPurchased;
		}
	}
}

void processSummarize() {
	std::cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << std::endl;
	std::cout << "we have had a total of " << database.size() << " different customers" << std::endl;
	Customer* mostBottles = findMax("Bottles");
	Customer* mostRattles = findMax("Rattles");
	Customer* mostDiapers = findMax("Diapers");
	if (mostBottles == 0) {
		std::cout << "no one has purchased any Bottles" << std::endl;
	}
	else {
		std::cout << mostBottles->name.c_str() << " has purchased the most Bottles (" << mostBottles->bottles << ")" << std::endl;
	}
	if (mostDiapers == 0) {
		std::cout << "no one has purchased any Diapers" << std::endl;
	}
	else {
		std::cout << mostDiapers->name.c_str() << " has purchased the most Diapers (" << mostDiapers->diapers << ")" << std::endl;
	}
	if (mostRattles == 0) {
		std::cout << "no one has purchased any Rattles" << std::endl;
	}
	else {
		std::cout << mostRattles->name.c_str() << " has purchased the most Rattles (" << mostRattles->rattles << ")" << std::endl;
	}

	

}

void processInventory() {
	String itemName;
	int itemAmount;
	readString(itemName);
	readNum(itemAmount);
	if (itemAmount > 0)
	{
		*selectInventItem(itemName) += itemAmount;
	}
}