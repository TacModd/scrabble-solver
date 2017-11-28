#include <ctype.h>
#include <stdio.h>

#include "helpers.c"



int main(int argc, char* argv[])
{
    // check for correct number of arguments
    if (argc != 2)
    {
        // clarify usage
        printf("Usage: main [letters (up to 8 lowercase)] \n");
        return 1;
    }
    
    // TODO
    // check length of argv[1]
    
    // use this as base (root) of trie
    node* root = NULL;
    
    // the dictionary to use
    char* dictionary = "scrabble.txt";
    
    // load dictionary into memory
    node* loaded = load(dictionary, root);

    // abort program if dictionary not loaded
    if (loaded == NULL)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }
    
    // prepare to report possible words
    printf("\nPOSSIBLE WORDS\n\n");
    
    // find words
    check(argv[1], "", loaded);
    
    // unload dictionary from memory
    bool unloaded = unload(root);
    
    // abort program if dictionary not unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }
    
    return 0;
}
