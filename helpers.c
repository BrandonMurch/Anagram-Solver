#include "helpers.h"

//Get user input block by block
//Modified from a response on Stackoverflow from "Mr Lister"
char *getInput(void)
{
	#define READSIZE 200
	char *input = NULL;
	char tempbuff[READSIZE];
	size_t inputlen = 0, templen = 0;
	do
	{
		if (inputlen > 200)
			return "Input entered was too long";
		fgets(tempbuff, READSIZE, stdin);
		templen = strlen(tempbuff);
		input = realloc(input, inputlen+templen+1);
		if (!input)
			return "Reading input failed";
		// concatenate strings
		strcpy(input+inputlen, tempbuff);
		inputlen += templen;
	}
	while(templen==READSIZE-1 && tempbuff[READSIZE-2] != '\n');
	return input;
}


// function to handle string manipulation (removing non-letters, turning all letters lowercase and sorting)
char *handle_string(char *string)
{
	int string_length = strlen(string);
	char *modified_string = malloc(sizeof(char) * (string_length + 1));
	strcpy(modified_string, string);
    removePunc(string_length, modified_string);
    int modified_string_length = strlen(modified_string);
    lowercase_string(modified_string_length, modified_string);
    quicksort(modified_string, 0, modified_string_length - 1);
    return modified_string;
}

// remove non letters from a string
void removePunc(size_t size, char *string)
{
	for (size_t i = 0; i < size; i++)
	{
		if (!isalpha(string[i]))
		{
			for(size_t j = i; j < size; j++)
			{
				if (j == size - 1)
					string[j] = '\0';
				else
					string[j] = string[j + 1];
			}
			size--;
			i--;
		}
	}
}

// turn a string all lowercase
void lowercase_string(size_t size, char *string)
{
	for (size_t i = 0; i < size; i++)
	       {
	           if (!islower(string[i]))
	               string[i] = tolower(string[i]);
	       }
}

// return letters in the first argument that aren't in the second
// result must be free'd
char *get_remaining_letters(char *string, char *already_used)
{
	int string_length = strlen(string);
	int used_length = strlen(already_used);
	char *tempstr = malloc(sizeof(char) * (string_length + 1));
	strcpy(tempstr, string);

	// iterate through already used letters
	for(int i = 0; i < used_length; i++)
	{
		// iterate through string
		for (int j = 0; j < string_length; j++)
		{
			if (already_used[i] == tempstr[j])
			{
				// remove letter and shift remaining letters 1 space left
				for(int k = j; k < string_length; k++)
				{
					if (k == string_length - 1)
						tempstr[k] = '\0';
					else
						tempstr[k] = tempstr[k + 1];
				}
				string_length -= 1;
				break;
			}
			// since letters are alphabetical, if we have passed it, it cannot possibly be in the string
			else if (already_used[i] < tempstr[j])
				break;
		}
	}
	return tempstr;
}

// QUICKSORT FUNCTIONS

// swap two characters
void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;

}

//implement quicksort algorithm with an array of characters,
void quicksort(char arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// setting partition index for quicksort, then sorting can occur on
// either side of the partition recursively.
int partition(char arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j ++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


