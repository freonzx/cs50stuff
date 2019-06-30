#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>

#define WORD_S 45
typedef struct node
    {
        struct node *child[27];
        
        int isWord;
    }node;
    
    
void insert(node * root, char *key);
struct node *getNode(void);
int search(struct node *root, const char *key);

int main () {
    
    
    node *root = getNode();
    
    FILE *fp = fopen("dictionaries/large","r");
    if (fp == NULL){
        puts("Error opening dictionary");
        return 1;
    }
    
    FILE *wfp = fopen("texts/cat.txt","r");
    if (wfp == NULL){
        puts("Error opening words");
        return 2;
    }
    
    char buffer[45];
    
    /*if (fp){
        while (fgets(buffer, WORD_S, fp) != NULL){
            insert(root,buffer);
        }
    }*/
    
    
    fclose(fp);
    
    return 0;
}

void insert(node * root, char * key){
    node *current_node = root;

    for(int i=0, len = strlen(key)-1; i<len ; i++){
        int index = key[i]-97;
        
        if(index < 0 || index > 26){
            continue;
        }
        
        //eprintf("the key is %c the root is at %p",key[i],root);
            if (current_node->child[key[i]-97] == NULL) {
                //eprintf("Key-97 %d \n",key[i]-97);
                current_node->child[key[i]-97] = getNode();
                //eprintf(" NEW NODE ADDR: %p",current_node->child[key[i]-97]);
            }
        current_node = current_node->child[key[i]-97];
    }
    current_node->isWord = 1;
}


struct node *getNode(void)
{
    struct node *pNode = NULL;
 
    pNode = (struct node *)malloc(sizeof(struct node));
 
    if (pNode)
    {
        int i;
 
        pNode->isWord = 0;
 
        for (i = 0; i < 27; i++)
            pNode->child[i] = NULL;
    }
 
    return pNode;
}

int search(struct node *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct node *Crawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = key[level]-97;
 
        if (!Crawl->child[index])
            return 0;
 
        Crawl = Crawl->child[index];
    }
 
    return (Crawl != NULL && Crawl->isWord);
}