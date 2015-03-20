
#include <stdlib.h>
#include "stringlib.h"

/*
 Simple O(n) deep string copy
 Returns a copy of the input string
 */
char* cpystr(char* string, int length)
{
	char* returnString = (char*)calloc(sizeof(char),length+1);
	int x;
	for (x = 0; x < length; x++) {
		returnString[x] = string[x];
	}
	return returnString;
}

/*
 Returns the length of a null terminated string
 */
int lengthof(char* string)
{
	int x = 0;
	while(string[x] != '\0' && string[x] != '\n') {
		x++;
	}
	return x;
}

/*
 Compares two integer strings by numeric values
 Returns 1 if the key comes is larger than compare
 Returns 0 if the key is equal to the compare
 Returns -1 if the key is smaller compare
 */
int intkeycmp(char* theKey, char* toCompare)
{
	long theIntKey = strtol(theKey, NULL, 0);
	long theIntToCompare = strtol(toCompare, NULL, 0);
	
	if(theIntKey > theIntToCompare) return 1;
	if(theIntKey < theIntToCompare) return -1;
	
	return 0; //key is the same as compare
}

/*
 Compares two strings by alphanumeric order
 Returns 1 if the key comes after the compare
 Returns 0 if the key is equal to the compare
 Returns -1 if the key comes before the compare
 */
int strkeycmp(char* theKey, char* toCompare)
{
	int x = 0;
	while((theKey[x] != '\0' && theKey[x] != '\n') &&
		  (toCompare[x] != '\0' && toCompare[x] != '\n')) {
		
		if (theKey[x] < toCompare[x]) {
			return -1;
		}
		if (theKey[x] > toCompare[x]) {
			return 1;
		}
		x++;
	}
	
	int klen = lengthof(theKey);
	int clen = lengthof(toCompare);
	
	if (klen > clen) {
		return 1; //key is longer than compare
	}
	if (klen < clen) {
		return -1; //key is shorter than compare
	}
	return 0; //key is the same as compare
}
