// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

typedef struct node
{
    struct node *child[27];
    int isWord;
} node;
// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
//Custom
void insert(node *root, char *key);
struct node *getNode(void);
bool search(struct node *rot, char *key);
bool free_all(node *rot);

#endif // DICTIONARY_H
