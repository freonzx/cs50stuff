// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
//Global pointer to root to be used by functions
node *rP = NULL;
//Global that stores the word count
unsigned int wordCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int word_size = strlen(word);
    //We create a copy of the string and set the characters to lower case
    char loword[word_size + 1];
    for (int i = 0; i < word_size; i++)
    {
        loword[i] = tolower(word[i]);
    }
    //Adding the terminator byte at the end
    loword[word_size] = '\0';
    bool result = search(rP, loword);
    if (result == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Using getNode() to generate a new struct with initialized NULL's
    node *root = getNode();
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        puts("Error opening dictionary");
        return false;
    }
    //Sets global variable rP to address of root so we can use it latter on other functions
    rP = root;
    char *buffer = calloc(sizeof(char) * LENGTH + 1, sizeof(char));
    if (fp)
    {
        while (fgets(buffer, LENGTH + 1, fp) != NULL)
        {
            //Since fgets will read last /n of the file this was my solution for it
            if (buffer[0] != '\n')
            {
                wordCount++;
            }
            insert(root, buffer);
        }
    }
    free(buffer);
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (!free_all(rP))
    {
        return false;
    }
    return true;
}
//Function that inserts words into the trie node
void insert(node *rot, char *key)
{
    node *current_node = rot;
    int index;
    for (int i = 0, len = strlen(key); i < len ; i++)
    {
        if (key[i] == '\'')
        {
            index = 26;
        }
        else
        {
            index = key[i] - (int)'a';
        }
        if (index < 0 || index > 26)
        {
            continue;
        }
        if (current_node->child[index] == NULL)
        {
            current_node->child[index] = getNode();
        }
        current_node = current_node->child[index];
    }
    current_node->isWord = 1;
}
//Function that creates a new node and sets all child's to NULL
struct node *getNode(void)
{
    struct node *pNode = NULL;

    pNode = (struct node *)malloc(sizeof(struct node));
    if (pNode)
    {
        int i;
        pNode->isWord = 0;
        for (i = 0; i < 27; i++)
        {
            pNode->child[i] = NULL;
        }
    }
    return pNode;
}

bool search(struct node *rot, char *key)
{
    int level;
    int length = strlen(key);
    int index = 0;
    struct node *Crawl = rot;

    for (level = 0; level < length; level++)
    {
        //Dealing with ' caracters or else just calculate the offset
        if (key[level] == '\'')
        {
            index = 26;
        }
        else
        {
            index = key[level] - (int)'a';
        }
        //to skip characters we don't want
        if (index < 0 || index > 26)
        {
            continue;
        }
        if (!Crawl->child[index])
        {
            return false;
        }
        Crawl = Crawl->child[index];
    }
    return (Crawl != NULL && Crawl->isWord);
}

bool free_all(node *rot)
{
    int i;
    if (!rot)
    {
        return false;
    }
    // go to end of trie
    for (i = 0; i < 27; i++)
    {
        free_all(rot->child[i]);
    }
    free(rot);
    return true;
}
