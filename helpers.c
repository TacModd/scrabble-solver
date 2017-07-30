#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* DEFINITIONS */

// trie definition
typedef struct node
{
    bool is_word;
    struct node* nextcharacter[27]; // child nodes
}
node;


/* PROTOTYPES */

/**
 * Generates, all subsets and permutations of given letters.
 * Prints current permutation if it's a word, returns nothing.
 */
void check(char* word, char* current, node* trielvl);

/**
 * Loads dictionary into memory.  Returns pointer to root if successful.
 */
node* load(const char* dictionary, node* root);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful.
 */
bool unload(node* trielvl);

/**
 * Unload function helper.  Returns true after freeing all nodes in subtree.
 */
bool empty(node* trielvl);


/* FUNCTIONS */

/**
 * Generates, all subsets and permutations of given letters.
 * Prints current permutation if it's a word, returns nothing.
 */
void check(char* word, char* current, node* trielvl)
{
    // if word is empty, check current and end
    if (word[0] == '\0')
    {
        // check current
        if (trielvl->is_word == true)
        {
            // return current word;
            printf("%s\n", current);
        }
    }
    
    else
    {
        // check current
        if (trielvl->is_word == true)
        {
        // return current word;
            printf("%s\n", current);
        }
        
        // iteratively search through array
        for (int i = 0; i < strlen(word); i++)
        {
            char lowercasecharacter[2];
            sprintf(lowercasecharacter, "%c", word[i]);
            
            // if not NULL, current permutation of letters may lead to a word
            if (trielvl->nextcharacter[word[i] - 'a'] != NULL)
            {
                char nextchar[9];
                strcpy(nextchar, current);
                strcat(nextchar, lowercasecharacter);
                
                char remaining[9];
                strncpy(remaining, word, i);
                remaining[i] = '\0';
                strcat(remaining, word + i + 1);
                
                node* temp = trielvl->nextcharacter[word[i] - 'a'];
                
                check(remaining, nextchar, temp);
            }
        }
    }
}



/**
 * Loads dictionary into memory.  Returns pointer to root if successful.
 */
node* load(const char* dictionary, node* root)
{
    root = calloc(1, sizeof(node)); // use this to anchor the trie
    
    wordcount = 0; // use this to make sure all words are being entered correctly
    
    // open dictionary
    FILE* dictionptr = fopen(dictionary, "r");
    // check to make sure it opened correctly
    if (dictionptr == NULL)
    {
        fclose(dictionptr); 
        printf("unable to open dictionary\n");
        return false;
    }
    
    int c = 0;
    node* trielvl = NULL;
    
    while(EOF != (c = fgetc(dictionptr)))
    {
        // set the address to the root
        trielvl = root;

        for (; c != '\n'; c = fgetc(dictionptr))
        {
            if (c == '\'')
            {
                // remember 'a' - 'a' is 0, and z = a + 25, thus a to z forms array 0 to 25, and \' goes at nextcharacter[26]
                c = 'a' + 26; // or 'z' + 1
            }
            
            // each element in children corresponds to a different letter, or an apostrophe
            
            // check the value at children[i]
            if (trielvl->nextcharacter[c - 'a'] == NULL)
            {
                // if NULL, malloc a new node, have children[i] point to it
                trielvl->nextcharacter[c - 'a'] = calloc(1, sizeof(node));
            }
            
            // move to new node[i] and continue
            trielvl = trielvl->nextcharacter[c - 'a'];
        }

        // end of word is reached when loop ends, thus set is_word to true
        trielvl->is_word = true;
        // up word count for checking purposes
        wordcount++;
    }
    
    // once we've finished reading the dictionary we can close it
    fclose(dictionptr);
    // and return true per instructions
    return root;
    
}



bool empty(node* trielvl)
{
    // explore local tree
    if (trielvl != NULL)
    {
        for (int i = 0; i < 27; i++)
        {
            if (trielvl->nextcharacter[i] != NULL)
            {
                // if non-empty, empty children
                empty(trielvl->nextcharacter[i]);
            }
        }
    }
    
    // free local root
    free(trielvl);
    return true;
}



/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(node* root)
{
    // call empty
    empty(root);
    // once done, return true
    return true;
}
