//Functions that concern powerset (all subsets)

#include "powerset.h"

//initialize table
char ***init_table(int size)
{
	char ***table = NULL;
	table = malloc(sizeof(char *) * (size + 2));
	if (!table)
		return NULL;
	for(int i = 0; i < size; i++)
	{
		table[i] = NULL;
	}
	return table;
}

int *init_int_array(int size)
{
	int *arr = malloc(sizeof(int) * (size + 2));
	if (!arr)
		return NULL;
	for(int i = 0; i < size; i++)
	{
		arr[i] = 0;
	}
	return arr;
}

//https://www.geeksforgeeks.org/power-set/
int_char_ptr *getPowerSet(char *set, int set_size)
{
	/*set_size of power set of a set with set_size
	n is (2**n -1)*/
	unsigned int pow_set_size = pow(2, set_size);
	char ***table = init_table(set_size);
	int *array_size = init_int_array(set_size);
	int *max_size = init_int_array(set_size);
	/*Run from counter 000..0 to 111..1*/
	for(size_t counter = 0; counter < pow_set_size; counter++)
	{
		char *temp = malloc(sizeof(char) * (set_size + 1));
		if (!temp)
			return NULL;
		int temp_counter = 0;
		for(int j = 0; j < set_size; j++)
		{
			/* Check if jth bit in the counter is set
				If set then print jth element from set */
			if(counter & (1<<j))
			{
				temp[temp_counter] = set[j];
				temp_counter++;
			}
		}
		temp[temp_counter] = '\0';
		// ensure string is not empty
		// use if statement to restrict length of strings to larger words
		//if (strcmp(temp, "") != 0 && strlen(temp) > 5)
		if (strcmp(temp, "") != 0)
		{
			int temp_length = strlen(temp) - 1;
			// remove duplicates
			int exists = 0;
			for (int k = 0; k < array_size[temp_length]; k ++)
			{
				if (strcmp(temp, table[temp_length][k]) == 0)
				{
					exists = 1;
					free(temp);
					break;
				}
			}
			if (exists)
				continue;
			// malloc on first iteration through a particular size
			if (!table[temp_length])
			{
				table[temp_length] = malloc(sizeof(char *) * 10);
				if (!table[temp_length])
					return NULL;
				max_size[temp_length] += 10;
			}
			// expand array if more space is needed
			if (array_size[temp_length] >= max_size[temp_length])
			{
				max_size[temp_length] += 10;
				char ** temp_ptr = realloc(table[temp_length], (sizeof(char *) * (max_size[temp_length] + 1)));
				if (!temp_ptr)
					return NULL;
				table[temp_length] = temp_ptr;
			}
			// store word in tables array and increment array_size to keep track of how many
			//words of a particular length are stored
			table[temp_length][array_size[temp_length]] = malloc(sizeof(char) * (temp_length + 2));
			if (!table[temp_length][array_size[temp_length]])
				return NULL;
			strcpy(table[temp_length][array_size[temp_length]], temp);
			array_size[temp_length] += 1;
		}
		free(temp);
	}
	free(max_size);
	// store both the table and counts to return
	int_char_ptr *results = malloc(sizeof(int_char_ptr));
	results->table = table;
	results->count = array_size;
	return results;
}


/* EXAMPLE Driver program to test printPowerSet
	int main(void)
	{
		char *string = malloc(sizeof(char) * 4);
		strcpy(string, "abc");
		table_node **results = getPowerSet(string, strlen(string));
		for (int i = strlen(string); i >= 0; i--)
		{
			if (results[i])
			{
				print_linked_list(results[i]);
			}
		}

		return 0;
	}
*/
