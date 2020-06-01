#ifndef DICTIONARY_H_
#define DICTIONARY_H_

// Declares a dictionary's functionality
#include <stdbool.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Declare user created headers
#include "powerset.h"
#include "helpers.h"


// Represents number of children for each node in a trie
#define N 26

typedef struct word_array
{
	char **arr;
	size_t size;
}
word_array;

// nodes of a linked list that holds words at the end of the try
typedef struct wordNode
{
	char *stored_word;
	struct wordNode *next;
}
wordNode;

// Represents a node in a trie
typedef struct node
{
    struct wordNode *words;
    struct node *children[N];
}
node;


// Maximum length for a word
#define LENGTH 60

// block of elements to be malloc'd at one time
#define ARRAY_BLOCK 20


// Prototypes
bool load(const char *dictionary);
unsigned int size(void);
word_array *dictionary_check(char *word);
bool unload(void);
node *initNode(node *newNode);
word_array *initWords(void);
bool insert(node *nextNode, char *word, char *sorted, int length, int count);
unsigned int countTrie(node *nextNode, unsigned int count);
word_array *checkWord(word_array *words, node *nextNode, char *word, int length, int count);
int dictionary_selected(char original_string[], char string[], char found_so_far[], char dict[]);
void freeNodes(node *nextNode);
wordNode *insertWord(char *word, wordNode *ptr);
unsigned int countWords(wordNode *ptr);
void freeWords(wordNode *wordN);
int search(char *string, char dict[]);
word_array *storeWords(word_array * words, wordNode *ptr);
void freeWordsArr(word_array *words);
void get_matches(char original_string[], char string[], char word[], char found_so_far[], char dict[]);
int search_people(char *input);




#endif /* DICTIONARY_H_ */
