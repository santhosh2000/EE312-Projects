/*
 * EE312 Simple CRM Project
 *
 * YOUR INFO HERE!
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
int num_diapers = 0;
int num_bottles = 0;
int num_rattles = 0;
String diapers;
String bottles;
String rattles;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	/* your code here */
	for (int i = 0; i <= num_customers; i++) {
		String name = customers[i].name;
		customers[i].bottles = 0;
		customers[i].diapers = 0;
		customers[i].rattles = 0;
		StringDestroy(&name);
		//free(&customers[i]);
	}
	num_customers = 0;
	num_diapers = 0;
	num_bottles = 0;
	num_rattles = 0;



}
int checkExists(String s) {
	for (int i = 0; i <= num_customers; i++) {
		if (StringIsEqualTo(&customers[i].name, &s))
			return i;
	}
	return -1;
}
int MostBottles(Customer list[]) {
	int max = 0;
	int a = 0;
	for (int i = 0; i <= num_customers; i++) {
		if (list[i].bottles > max) {
			max = list[i].bottles;
			a = i;
		}
	}
	if (max == 0) {
		a = -1;
	}
	return a;
}
int MostDiapers(Customer list[]) {
	int max = 0;
	int a = 0;
	for (int i = 0; i <= num_customers; i++) {
		if (list[i].diapers > max) {
			max = list[i].diapers;
			a = i;
		}
	}
	if (max == 0) {
		a = -1;
	}
	return a;
}
int MostRattles(Customer list[]) {
	int max = 0;
	int a = 0;
	for (int i = 0; i <= num_customers; i++) {
		if (list[i].rattles > max) {
			max = list[i].rattles;
			a = i;
		}
	}
	if (max == 0) {
		a = -1;
	}
	return a;
}

void UpdateCustomer(int index, String type, int num) {
	if (StringIsEqualTo(&type, &diapers)) {
		if (num_diapers >= num) {
			customers[index].diapers += num;
			num_diapers -= num;
		}
		else {
			printf("Sorry ");
			StringPrint(&customers[index].name);
			printf(", we only have %d diapers\n", num_diapers);
		}
	}
	else if (StringIsEqualTo(&type, &bottles)) {
		if (num_bottles >= num) {
			customers[index].bottles += num;
			num_bottles -= num;
		}
		else {
			printf("Sorry ");
			StringPrint(&customers[index].name);
			printf(", we only have %d bottles\n", num_bottles);
		}
	}
	else if (StringIsEqualTo(&type, &rattles)) {
		if (num_rattles >= num) {
			customers[index].rattles += num;
			num_rattles -= num;
		}
		else {
			printf("Sorry ");
			StringPrint(&customers[index].name);
			printf(", we only have %d rattles\n", num_rattles);
		}
	}
}

void processSummarize() {
	printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", num_bottles, num_diapers, num_rattles);
	printf("we have a total of %d different customers\n", num_customers);
	int b = MostBottles(customers);
	int d = MostDiapers(customers);
	int r = MostRattles(customers);
	if (b != -1) {
		String bname = customers[b].name;
		int bot = customers[b].bottles;
		StringPrint(&bname);
		printf(" has purchased the most Bottles (%d)\n", bot);
	}
	else {
		printf("no one has purchased any Bottles\n");
	}
	if (d != -1) {
		String dname = customers[d].name;
		int dia = customers[d].diapers;
		StringPrint(&dname);
		printf(" has purchased the most Diapers (%d)\n", dia);
	}
	else {
		printf("no one has purchased any Diapers\n");
	}
	if (r != -1) {
		String rname = customers[r].name;
		int rat = customers[r].rattles;
		StringPrint(&rname);
		printf(" has purchased the most Rattles (%d)", rat);
	}
	else {
		printf("no one has purchased any Rattles");
	}

}

void processPurchase() {
	diapers = StringCreate("Diapers");
	bottles = StringCreate("Bottles");
	rattles = StringCreate("Rattles");
	String name;
	readString(&name);
	String this_word;
	readString(&this_word);
	int quantity;
	readNum(&quantity);
	int a = checkExists(name);
	if (a != -1) {
		UpdateCustomer(a, this_word, quantity);
	}
	else {
		num_customers += 1;
		Customer temp;
		temp.name = name;
		temp.diapers = 0;
		temp.bottles = 0;
		temp.rattles = 0;
		customers[num_customers] = temp;
		UpdateCustomer(num_customers, this_word, quantity);
		if (customers[num_customers].bottles == 0 && customers[num_customers].diapers == 0 && customers[num_customers].rattles == 0) {
			StringDestroy(&customers[num_customers].name);
			//free(&customers[num_customers]);
			num_customers -= 1;
		}
	}
	StringDestroy(&diapers);
	StringDestroy(&bottles);
	StringDestroy(&rattles);

}

void processInventory() {
	diapers = StringCreate("Diapers");
	bottles = StringCreate("Bottles");
	rattles = StringCreate("Rattles");
	String this_word;
	readString(&this_word);
	int quantity;
	readNum(&quantity);
	if (StringIsEqualTo(&this_word, &diapers)) {
		num_diapers += quantity;
	}
	else if (StringIsEqualTo(&this_word, &bottles)) {
		num_bottles += quantity;
	}
	else if (StringIsEqualTo(&this_word, &rattles)) {
		num_rattles += quantity;
	}

	StringDestroy(&diapers);
	StringDestroy(&bottles);
	StringDestroy(&rattles);


}