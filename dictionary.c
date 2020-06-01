#include "dictionary.h"

// Represents a trie
node *root;


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // initNodeialize trie
    root = initNode(root);
    if (!root)
        return false;

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        unload();
        fclose(file);
        return false;
    }

    // Buffer for a word, quite program if malloc fails
    char *word =  malloc(sizeof(char) * (LENGTH + 1));
    char *sorted = malloc(sizeof(char) * (LENGTH + 1));
    if (!word || !sorted)
    {
    	printf("malloc failed");
        unload();
        free(word);
        fclose(file);
        return false;
    }

    // Insert words into trie
    while (fgets(word, sizeof(char) * LENGTH, file))
    {
    	word[strcspn(word, "\n")] = 0;
        sorted = handle_string(word);
        insert(root, word, sorted, strlen(sorted), 0);
    }

    // Close dictionary
    free(sorted);
    free(word);
    fclose(file);

    // Indicate success
    return true;
}

int search_people(char *input)
{
    // Open dictionary
    FILE *file = fopen("dictionaries/people.txt", "r");
    if (!file)
    {
    	printf("file open failed");
        unload();
        fclose(file);
        return 1;
    }

    // Buffer for a word, quite program if malloc fails
    char *word =  malloc(sizeof(char) * (LENGTH + 1));
    char *sorted = malloc(sizeof(char) * (LENGTH + 1));
    if (!word || !sorted)
    {
    	printf("malloc failed");
        unload();
        free(word);
        fclose(file);
        return 2;
    }

    // handle input string
    input = handle_string(input);

    // get words on line at a time
    while (fgets(word, sizeof(char) * LENGTH, file))
    {
    	word[strcspn(word, "\n")] = 0;
        sorted = handle_string(word);
        if(strcmp(sorted, input) == 0)
        	printf("Match found: %s \n", word);
    }

    // Close dictionary
    free(sorted);
    free(word);
    fclose(file);

    // Indicate success
    return 0;
}


// Returns list of words found in dictionary
word_array *dictionary_check(char *word)
{
    word = handle_string(word);
    word_array *results = initWords();
    results = checkWord(results, root, word, strlen(word), 0);
    return results;
}


//recursively check if a word exists in a trie
word_array *checkWord(word_array *words, node *nextNode, char *word, int length, int count)
{
    //the next node or letter has not been initNodeialized, therefore the word doesn't exist
    if (!nextNode)
        return words;

    // the word was found in the trie
    else if (count == length && nextNode->words)
    	return storeWords(words, nextNode->words);

    // have reached the end of the word and it doesn't exist
    else if (count == length && !nextNode->words)
    	return words;

    //recursively check the rest of the word
    int letter = (int)word[count];
	letter = letter - 97;
    if (nextNode->children[letter])
    {
        count ++;
        return checkWord(words, nextNode->children[letter], word, length, count);
    }

    // word doesn't exist
    else
        return words;
}


// search dictionary for matching words
int search(char *string, char dict[]){
	// remove trailing newline
	string[strcspn(string, "\n")] = 0;
	char *sorted = handle_string(string);
	int strLength = strlen(string);

	// storage array to build matches
	char *storage = malloc(sizeof(char) * (strLength * 3));
	if (!storage)
		return 1;
	strcpy(storage, "");
	int result = dictionary_selected(string, sorted, "", dict);
	free(storage);
	if (result != 0)
		return result;
	else
		return 0;
}

//recursively find matches for each sub-word
int dictionary_selected(char original_string[], char string[], char found_so_far[], char dict[])
{
	// if words dictionary is selected, requiring the gathering of subsets
	if(strcmp(dict, "words") == 0)
	{
		int string_length = strlen(string);
		int_char_ptr *results = getPowerSet(string, string_length);
		if(!results)
			return 2;
		// selects length of subset, starting with the largest
		for (int i = string_length - 1; i >= 0; i--)
		{
			// iterates through all the subsets of a particular length
			for(int j = 0; j < results->count[i]; j++)
			{
				// search for matches with the subset
				get_matches(original_string, string, results->table[i][j], found_so_far, dict);
				free(results->table[i][j]);
			}
			free(results->table[i]);
		}
		free(results->table);
		free(results->count);
		free(results);
	}
	// other dictionary is selected that does not require subset
	else
	{
		get_matches(original_string, string, string, found_so_far, dict);
	}
	return 0;
}

void get_matches(char original_string[], char string[], char word[], char found_so_far[], char dict[])
{
	int string_length = strlen(string);
	word_array *matches = NULL;
	// check words against dictionary
	matches = dictionary_check(word);
	if (matches)
	{
		// iterate through matches
		for(size_t k = 0; k < matches->size; k++)
		{
			// length variables
			int found_so_far_length = strlen(found_so_far);
			int match_length = strlen(matches->arr[k]);
			int found_length;
			if (strcmp(found_so_far, "") == 0)
				found_length = match_length + 1;
			else
			{
				// stops longer words from reappearing after they have already been discovered
				if (found_so_far_length < match_length)
					break;
				found_length = strlen(found_so_far) + strlen(matches->arr[k]) + 2;
			}
			char found[found_length];

			// build match string in found_
			if (strcmp(found_so_far, "") == 0)
				strcpy(found, matches->arr[k]);
			else
				sprintf(found, "%s %s", found_so_far, matches->arr[k]);
			char tempstr[string_length];
			strcpy(tempstr, string);
			// get unused letters
			char *remain = get_remaining_letters(tempstr, word);
			// if there are no letters remaining, and the string isn't identical to the first, we have found an anagram
			if (strcmp(remain, "") == 0 && strcmp(found, original_string) != 0)
			{
				printf("MATCH FOUND: %s \n", found);
				// alternatively, could store strings to array

			}
			else
				// recursively search rest of the word
				dictionary_selected(original_string, remain, found, dict);
			free(remain);
		}
		freeWordsArr(matches);
	}
	else
		free(matches);
}

// store words in an array
word_array *storeWords(word_array * words, wordNode *ptr)
{
	// get words block by block, realloc-ing if more space is needed
	int size = words->size;
	if ((size % ARRAY_BLOCK) == ARRAY_BLOCK - 1)
	{
		void *temp_ptr = realloc(words->arr, size + ARRAY_BLOCK);
		if (!temp_ptr)
			return NULL;
		words->arr = temp_ptr;
	}
	if (!words->arr)
		return NULL;
	// store word in array
	words->arr[size] = malloc(sizeof(char) * (LENGTH + 1));
	strcpy(words->arr[size], ptr->stored_word);
	words->size++;
	if(ptr->next)
		return storeWords(words, ptr->next);
	else
		return words;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    freeNodes(root);
    return true;
}

//initNodeialise a node with malloc, then ensure all children are null
node *initNode(node *newNode)
{
    newNode = malloc(sizeof(node));
    if (!newNode)
        return NULL;
    newNode->words = NULL;
    for (int i = 0; i < N; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

word_array *initWords(void)
{
	word_array *words = malloc(sizeof(word_array));
	    words->arr = malloc(sizeof(char *) * 20);
	    words->size = 0;
	    return words;
}


//insert a word into the trie
bool insert(node *nextNode, char *word, char *sorted, int length, int count)
{
    //the end of the word has been reached.
    if (count == length)
    {
        nextNode->words = insertWord(word, nextNode->words);
        return true;
    }

    // adjust the letters to create positions in an array between 0-25 inclusively.
    int letter = (int)sorted[count];
	letter = letter - 97;
    //initNodeialise the next node, if it doesn't already exist.
	if ((letter < 0 || letter > 25))
	{
		count++;
		insert(nextNode, word, sorted, length, count);
		return true;
	}
    if (!nextNode->children[letter])
    {
        nextNode->children[letter] = initNode(nextNode->children[letter]);
        if (!nextNode)
            return false;
    }
    count++;
    // recursively add the rest of the word
    insert(nextNode->children[letter], word, sorted, length, count);
    return true;
}

wordNode *insertWord(char *input, wordNode *ptr)
{
	wordNode *temp = NULL;
	if (ptr)
	{
		temp = ptr;
		ptr = NULL;
	}
	ptr = malloc(sizeof(wordNode));
	if(!ptr)
	{
		printf("Malloc error");
		return false;
	}
	ptr->stored_word = malloc(sizeof(char) * (LENGTH + 1));
	strcpy(ptr->stored_word, input);
	if (temp)
		ptr->next = temp;
	else
		ptr->next = NULL;
	return ptr;
}

// free all word_array
void freeWordsArr(word_array *words)
{
	int size = words->size;
	for(int i = 0; i < size; i++)
	{
		free(words->arr[i]);
	}
	free(words->arr);
	free(words);
}

// recursively free all nodes in the trie
void freeNodes(node *nextNode)
{
    for (int i = 0; i < N; i++)
    {
        if (nextNode->children[i])
            freeNodes(nextNode->children[i]);
    }
    if (nextNode->words)
    	freeWords(nextNode->words);
    free(nextNode);
}

// free linked lists at the end of the trie
void freeWords(wordNode *wordN)
{
	// move to the next node if there is one
	if (wordN->next)
		freeWords(wordN->next);
	free(wordN->stored_word);
	free(wordN);
}

