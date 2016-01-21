// PIE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataStructures.h"

// given two strings is one permutation of another? e.g abc == acb
bool Permutation(char str1[], char str2[])
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if (len1 != len2)
		return false;

	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < len1; i++)
	{
		sum1 += ('a' - str1[i]);
		sum2 += ('a' - str2[i]);
	}
	if (sum1 != sum2)
		return false;
	return true;
}

void RemoveCharFromString(char str[], char x)
{
	if (!str)
		return;

	int len = strlen(str);
	int r = 0;
	int w = 0;
	while (r < len)
	{
		if (str[r] == x)
		{
			r++;
		}
		else
		{
			str[w++] = str[r++];
		}
	}
	str[w] = '\0';
}


// given a string, can it be rearranged to a palindrome? e.g tat aa = taaat
bool CanItBePalindrome(char str[])
{
	int len = strlen(str);
	DataStructures::Hash<char, int> hashtable;

	int numOfChars = 0;

	for (int i = 0; i < len; i++)
	{
		if (str[i] != ' ')
		{
			int* pVal = hashtable.Find(str[i]);
			if (pVal)
				*pVal += 1;
			else
				hashtable.Insert(str[i], 1);

			numOfChars++;
		}
	}

	char oddChar = ' ';
	for (int i = 0; i < numOfChars; i++)
	{
		if (str[i] == ' ')
			continue;
		int* pVal = hashtable.Find(str[i]);
		if ((*pVal % 2) != 0)
		{
			if (numOfChars % 2 != 0) //odd length
			{
				if (oddChar == ' ')
				{
					oddChar = str[i];
				}
				else
				{
					if (oddChar != str[i])
						return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

bool CanItBePalindromeV2(char str[])
{
	int len = strlen(str);
	DataStructures::HeapSort<char>(str, len);

	RemoveCharFromString(str, ' ');
	len = strlen(str);
	if (len < 2)
		return true;

	int count = 0;
	int oddCharCount = 0;

	for (int i = 1; i < len; i++)
	{
		if (str[i] != str[i - 1])
		{
			if (((count + 1) % 2) == 1)
				oddCharCount++;
			count = 0;
		}
		else
		{
			count++;
		}
	}

	if (((count + 1) % 2) == 1)
		oddCharCount++;

	if ((len % 2) == 1)
	{
		if (oddCharCount > 1)
			return false;
	}
	else
	{
		if (oddCharCount > 0)
			return false;
	}

	return true;



	

}


int main()
{
	char str[] = "ab ab ab a ";
	bool result = CanItBePalindromeV2(str);

	return 0;
}

