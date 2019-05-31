/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
vector<int> twoSum(vector<int>& nums, int target) {
	unordered_map<int, int> hash; //Number, Index

	for (int i = 0; i < nums.size(); i++)
	{
		int numberToFind = target - nums[i];

		if (hash.find(numberToFind) != hash.end())
			return  { hash[numberToFind] ,i };

		hash[nums[i]] = i;
	}
	return {};
}
int main()
{
	printf("Hello World");
	std::vector<int> nums = { 2,7,8,11 };
	twoSum(nums, 9);
	system("pause");
	return 0;
}


