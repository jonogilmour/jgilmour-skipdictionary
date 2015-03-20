
#ifndef skipdict_h
#define skipdict_h

typedef struct sde skipDictEntry;
typedef struct sdict skipDict;

struct sde
{
	char* key;
	char* value;
	struct sde** next;
};

struct sdict
{
	skipDictEntry* head;
	int level;
};

float newrand();
int level();
skipDict* newSkipDict();
skipDictEntry* newSkipEntry(char* key, char* value, int level);
void printSkipDict(skipDict* theSkipDict);
int addSkipEntry(skipDict* theSkipDict, char* key, char* value, int* added, int (*keycmp)(char*, char*));
skipDictEntry* skipDictSearch(skipDict* theSkipDict, char* queryKey, int* comparisons, int (*keycmp)(char*, char*));
void skipDictDelete(skipDict* theSkipDict, char* key, int (*keycmp)(char*, char*));
void purgeSkipDict(skipDict* theSkipDict, int (*keycmp)(char*, char*));

#endif
