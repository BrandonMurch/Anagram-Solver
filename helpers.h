#ifndef HELPERS_H_
#define HELPERS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

char *getInput(void);
bool containsDigits(size_t size, char *string);
void removePunc(size_t size, char *string);
char *getSubstring(char *string, int start, int end, int reverse);
void swap(char *a, char *b);
void quicksort(char arr[], int low, int high);
int partition(char arr[], int low, int high);
char *get_remaining_letters(char *string, char *already_used);
void lowercase_string(size_t size, char *string);
char *handle_string(char *string);

#endif /* HELPERS_H_ */
