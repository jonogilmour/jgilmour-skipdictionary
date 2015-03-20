
#ifndef dict_h
#define dict_h

typedef struct de dictEntry;
typedef struct dict dict;

struct de
{
	char* key;
	char* value;
	struct de* next;
	struct de* prev;
};

struct dict
{
	dictEntry* head;
	int size;
};

dict* newDict();
dictEntry* newEntry(char*, char*, dictEntry*, dictEntry*);
void printDict(dict* theDict);
int addEntry(dict* dict, char* key, char* value, int* added, int (*keycmp)(char*, char*));
dictEntry* dictSearch(dict* theDict, char* queryKey, int* comparisons, int (*keycmp)(char*, char*));
dictEntry* dictBSearch(dict* theDict, char* queryKey, int* comparisons, int (*keycmp)(char*, char*));
void dictDelete(dict* theDict, dictEntry* theEntry);
void freeEntry(dictEntry* theEntry);
void purgeDict(dict* theDict);

#endif
