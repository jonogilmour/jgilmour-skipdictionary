
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "stringlib.h"
#include <string.h>

#define ARGUMENT_ERROR 2
#define LINE_MAX 100

int main(int argc, const char * argv[])
{
	if(argc == 1) {
		printf("Usage: path_to_file\n");
		exit(ARGUMENT_ERROR);
	}
	
	FILE* kvpairs = fopen(argv[1], "r");
	
	if(kvpairs == NULL) {
		printf("File \"%s\" not found\n", argv[1]);
		exit(ARGUMENT_ERROR);
	}
	
	int (*compareFunction)(char*, char*);
	
	if(argc < 3) {
		compareFunction = &intkeycmp;
	}
	
	else {
		
		switch (argv[2][0]) {
			case 'i':
				compareFunction = &intkeycmp;
				break;
			case 's':
				compareFunction = &strkeycmp;
				break;
			default:
				compareFunction = &intkeycmp;
				break;
		}
	}
	
	char buffer[LINE_MAX];
	char* key;
	char* value;
	
	char* firstvalue;
	char* appendvalue;
	char* space = " ";
	
	dict* dict = newDict();
	int inserted = 0;
	
	int comparisons = 0;
	int duplicates = 0;
	int* added = (int*)malloc(sizeof(int));
	
	
	
	////////////////////
	//BUILD DICTIONARY//
	////////////////////
	
	// Keep reading the file until EOF.
	while(fgets(buffer, LINE_MAX, kvpairs) != NULL) {
		
		if( buffer[0] == '\n') { // Skip any empty lines.
			printf("Warning: Line \"%s\" is too short to be a valid key-value string. Skipping...\n", buffer);
			continue;
		}
		
		/*
		 Begin splitting the buffer string into keys and tokens
		 Start by getting the key; the first word in the buffer
		 Then get the first word of the value and store it in "firstvalue"
		 If there is any data after that (ie the key is a sentence) then grab that
		 and store it in "appendvalue".
		 Then concatenate the firstvalue and the appendvalue and store it as "value",
		 placing a space in between (as the space would have been skipped by strtok)
		 If the value is just a single word, nothing will be appended and the size of
		 "value" won't be bigger than needed too.
		*/
		key = strtok(buffer," \t");
		firstvalue = strtok (NULL, " \t\n");
		appendvalue = strtok(NULL, "\n");
		
		// If the line is only one word without any separation, skip it.
		if(firstvalue == NULL) {
			printf("Warning: Line \"%s\" is not a valid key-value string (format 'key *whitespace* value'). Skipping...\n", buffer);
			continue;
		}
		
		// If there is nothing left, set everything to null string.
		if(appendvalue == NULL) {
			appendvalue = "";
			space = "";
		}
		
		// Allocate space for the value and concatenate everything into it.
		value = (char*)calloc(lengthof(firstvalue) + lengthof(appendvalue) + lengthof(space) + 1, sizeof(char));
		strcpy(value, firstvalue);
		strcat(value, space);
		strcat(value, appendvalue);
		
		// Add the entry to the dictionary.
		comparisons += addEntry(dict, key, value, added, compareFunction);
		if(!*added) duplicates++;
		else inserted += *added;
		free(value);
		
	}
	
	
	
	/////////////////
	//TESTING PHASE//
	/////////////////
	
	printf("%6d\tINSERTIONS\t%6d\n", inserted, comparisons);
	
	// Perform searches by reading in terms from stdin and searching for those words in the dictionary.
	
	int* cmpr = (int*)malloc(sizeof(int));
	char* querykey;
	dictEntry* searchresult;
	printf("Please enter a search key (or '!exit' to quit): ");
	while(fgets(buffer, LINE_MAX, stdin) != NULL && strcmp(buffer, "!exit\n")) {
		fseek(stdin, 0L, SEEK_END); // Flush stdin.
		if(!strcmp(buffer, "\n")) {
			printf("Please enter a search key (or '!exit' to quit): ");
			continue;
		}
		
		querykey = strtok(buffer,"\n");
		
		searchresult = dictSearch(dict, querykey, cmpr, compareFunction); //change to dictBSearch to perform binary search
		if(searchresult == NULL) printf("%6s\tNOT_FOUND\t%6d\n", querykey, (*cmpr));
		else printf("%6s\t%-9s\t%6d\n", querykey, (searchresult->value), (*cmpr));
		
		printf("Please enter a search key (or '!exit' to quit): ");
	}
	
	printf("Quitting...\n");
	
	///////////////
	//CLEANING UP//
	///////////////
	
	purgeDict(dict);
	free(dict);
	dict = NULL;
	free(added);
	added = NULL;
	free(cmpr);
	cmpr = NULL;
	
	
	
    return 0;
}

