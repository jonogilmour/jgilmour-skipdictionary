
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "stringlib.h"

/*
 Returns a new, empty dictionary
*/
dict* newDict()
{
	dict* theDict = (dict*)malloc(sizeof(dict));
	theDict->size = 0;
	theDict->head = NULL;
	return theDict;
}

/*
 Returns a new dict entry filled with the information given (key, value, next node, previous node)
*/
dictEntry* newEntry(char* key, char* value, dictEntry* next, dictEntry* prev)
{
	dictEntry* theEntry = (dictEntry*)malloc(sizeof(dictEntry));
	theEntry->key = cpystr(key, lengthof(key));
	theEntry->value = cpystr(value, lengthof(value));
	theEntry->next = next;
	theEntry->prev = prev;
	return theEntry;
}

/*
 Prints the contents of an entire dictionary in the format
 "KEY: VALUE", one pair per line.
 
 If the dictionary is empty it prints "Empty Dictionary"
 only.
*/
void printDict(dict* theDict)
{
	int x;
	dictEntry* curNode = theDict->head;
	
	printf("Printing dict of size: %d\n", theDict->size);
	
	if (curNode == NULL) {
		printf("Empty dictionary\n");
	}
	
	else {
		for(x = 0; x < theDict->size; x++) {
			printf("%s: %s\n", curNode->key, curNode->value);
			curNode = curNode->next;
		}
	}
}


/*
 Adds a new dictionary entry into the dictionary provided
 Returns the number of key comparisons made
 Takes a pointer, "added", which is set to 1 if the entry was successfully added
*/
int addEntry(dict* theDict, char* key, char* value, int* added, int (*keycmp)(char*, char*))
{
	int comparisons = 0;
	if(theDict->size)
	{
		dictEntry* curNode = theDict->head;
		int x;
		int cmpr;
		for(x = 0; x < theDict->size; x++) {
			
			comparisons++;
			cmpr = keycmp(key, curNode->key);
			
			if(cmpr == -1) { // If this node should be before the current node...
				
				if(curNode == theDict->head) { // If the current node is head, replace it and rearrange...
					theDict->head = newEntry(key, value, curNode, NULL);
					curNode->prev = theDict->head;
				}
				
				else { // If the node isn't the head, do a standard insertion...
					curNode->prev->next = newEntry(key, value, curNode, curNode->prev);
					curNode->prev = curNode->prev->next;
				}
				(theDict->size)++;
				*added = 1;
				return comparisons;
			}
			
			if(cmpr == 0) { // Key is already in the dictionary.
				*added = 0;
				return comparisons;
			}
			
			if(curNode->next != NULL) curNode = curNode->next;
		}
		
		// If control reaches here we have reached the end of the list, so place the new node at the end.
		curNode->next = newEntry(key, value, NULL, curNode);
		(theDict->size)++;
		*added = 1;
		return comparisons;
	}

	// Size is zero, so there is no head node. Make it!
	theDict->head = newEntry(key, value, NULL, NULL);
	(theDict->size)++;
	*added = 1;
	return comparisons;
}

/*
 Searches (brute force) for a key in the given dictionary
 Returns the node if the key is found, otherwise it returns NULL if the key isn't in the dictionary
*/
dictEntry* dictSearch(dict* theDict, char* queryKey, int* comparisons, int (*keycmp)(char*, char*))
{
	if(theDict->size == 0) return NULL; // Cannot search an empty list.

	int x;
	int rposition;
	dictEntry* curNode = theDict->head;
	
	(*comparisons) = 0;
	
	for(x = 0; x < theDict->size; x++) {
		(*comparisons)++;
		if(!(rposition = keycmp(queryKey, curNode->key))) {
			return curNode;
		}
		if(rposition < 0) {
			return NULL; // The key isn't present.
		}
		curNode = curNode->next;
	}
	
	return NULL;
}

/*
 Does a faster, binary search for a key in a dictionary.
 Returns the node if the key is found, otherwise it returns NULL if the key isn't in the dictionary
 ****Added for experimentation purposes only****
*/
dictEntry* dictBSearch(dict* theDict, char* queryKey, int* comparisons, int (*keycmp)(char*, char*))
{
	// If the list is really small, it benefits nothing by binary search. Just do a normal search instead.
	if(theDict->size <= 2) return dictSearch(theDict, queryKey, comparisons, keycmp);
	
	int halfway = (theDict->size/2);
	int y;
	dictEntry* curNode = theDict->head;
	int place;
	(*comparisons) = 0;
	
	while(halfway) {
		(*comparisons)++;
		place = keycmp(queryKey, curNode->key);
		
		if(!place) {
			return curNode;
		}
		
		halfway /= 2;
		
		if(place < 0) { // The key is before.
			for (y = 0; y < halfway; y++) {
				curNode = curNode->prev;
			}
		}
		
		else if(place > 0) { // The key is after.
			for (y = 0; y < halfway; y++) {
				curNode = curNode->next;
			}
		}
	}
	
	return NULL;
}

/*
 Deletes the given entry from the dictionary
 This function assumes that the entry is in the dictionary
*/
void dictDelete(dict* theDict, dictEntry* theEntry)
{
	if(theEntry->next == NULL) {
		if(theEntry->prev == NULL) { // Last node in the list, and list size = 1 (a.k.a. lone head node).
			freeEntry(theEntry);
		}
		else { // Last node in the list, and list size > 1.
			theEntry->prev->next = NULL;
			freeEntry(theEntry);
		}
	}
	else if(theEntry == theDict->head) { // Head node in list , and list size > 1.
		theDict->head = theEntry->next;
		theEntry->next->prev = NULL;
		freeEntry(theEntry);
	}
	else { // Node is somewhere in the middle.
		theEntry->prev->next = theEntry->next;
		theEntry->next->prev = theEntry->prev;
		freeEntry(theEntry);
	}
}

/*
 Frees an entry and its assets
*/
void freeEntry(dictEntry* theEntry)
{
	free(theEntry->key);
	free(theEntry->value);
	theEntry->next = NULL;
	theEntry->prev = NULL;
	free(theEntry);
}

/*
 Deletes everything in a dictionary, but not the dictionary itself
*/
void purgeDict(dict* theDict)
{
	dictEntry* curNode = theDict->head;
	dictEntry* nextNode;
	
	while(curNode != NULL) {
		nextNode = curNode->next;
		dictDelete(theDict, curNode);
		curNode = nextNode;
	}
}
