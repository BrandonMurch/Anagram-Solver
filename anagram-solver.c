#include "dictionary.h"
#include "helpers.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	if (argc == 2)
	{
		if (strcmp(argv[1], "--help") == 0)
		{
			printf("Anagram Solver \n\n"
					"./anagram-solver \n"
					"\n"
					"Dictionary types:\n"
					"words\n"
					"movies\n"
					"famous people\n");
			return 0;
		}
		else if (strcmp(argv[1], "--test-people") == 0)
		{
			char *input ="Keanu Reeves";
			char *string = malloc(sizeof(char) * strlen(input) + 1);
			strcpy(string, input);
			search_people(string);
			//int exitCode = search(string, dict);
			//unload();
			free(string);
		}
		else if (strcmp(argv[1], "--test-movies") == 0)
		{
			char dict[] = "movies";
			load("dictionaries/movies.txt");
			char *input ="yot yrots";
			char *string = malloc(sizeof(char) * strlen(input) + 1);
			strcpy(string, input);
			int exitCode = search(string, dict);
			unload();
			free(string);
			exit(exitCode);
		}
		else if (strcmp(argv[1], "--test-words") == 0)
		{
			char dict[] = "words";
			load("dictionaries/words.txt");
			char *input ="hello world";
			char *string = malloc(sizeof(char) * strlen(input) + 1);
			strcpy(string, input);
			int exitCode = search(string, dict);
			unload();
			free(string);
			exit(exitCode);
		}
		else if (strcmp(argv[1], "--test_remaining_letters") == 0)
		{
			char *input ="aaeeelmrssrt";
			char *string = malloc(sizeof(char) * strlen(input) + 1);
			strcpy(string, input);
			char *input2 ="aaeeelssrt";
			char *string2 = malloc(sizeof(char) * strlen(input) + 1);
			strcpy(string2, input2);
			char* string3 = get_remaining_letters(string, string2);
			printf("string input: %s already used letters: %s  letters remaining: %s \n", string, string2, string3);
			if (strcmp(string3, "") == 0)
				printf("nothing left");
			free(string3);
		}
	}
	else if (argc == 1)
	{
		printf("Please select your dictionary: \n words \n movies \n people \n");
		char options[3][10] = {"words", "movies", "people"};
		char *dict = NULL;
		char *dict_input;
		do
		{
			dict_input = getInput();
			if (strcmp(dict_input, "Input entered was too long") == 0)
				printf("%s \n", dict_input);
			else
			{
				int dict_input_len = strlen(dict_input);
				removePunc(dict_input_len, dict_input);
				lowercase_string(dict_input_len, dict_input);
				for(int i = 0; i < 3; i++)
				{
					if (strcmp(dict_input, options[i]) == 0)
					{
						dict = malloc(sizeof(char) * 25);
						if (!dict)
							return 6;
						sprintf(dict, "dictionaries/%s.txt", dict_input);

					}
				}
				if (!dict)
					printf("Incorrect dictionary selected\n");
			}
		}
		while(!dict);
		if (strcmp(dict_input, "people") != 0)
			load(dict);
		printf("input a string: \n");
		char *input;
		do
		{
			input = getInput();
				if (strcmp(input, "Input entered was too long") == 0)
				{
					printf("Input entered was too long\n");
					input = NULL;
				}
		}
		while(!input);
		//char *input ="yot yrots";
		char *string = malloc(sizeof(char) * strlen(input) + 1);
		strcpy(string, input);
		int exitCode;
		if (strcmp(dict_input, "people") == 0)
			exitCode = search_people(string);
		else
		{
			exitCode = search(string, dict_input);
			unload();
		}
		free(dict);
		free(input);
		free(string);
		exit(exitCode);
	}
	else
	{
		printf("./anagram-solver --help for more information\n");
		return 1;
	}
}
