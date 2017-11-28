#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "helpers.c"

#undef calculate
#undef getrusage


/* PROTOTYPE */

/**
 * Returns number of seconds between b and a.
 */
double calculate(const struct rusage* b, const struct rusage* a);



int main(int argc, char* argv[])
{
    // check for correct number of arguments
    if (argc != 2)
    {
        // clarify usage
        printf("Usage: timed-main [letters (up to 8 lowercase)] \n");
        return 1;
    }
    
    // TODO
    // check length of argv[1]
    
    // use this as base (root) of trie
    node* root = NULL;
    
    // structs for timing data
    struct rusage before, after;

    // benchmarks
    double time_load = 0.0, time_check = 0.0, time_unload = 0.0;
    
    // the dictionary to use
    char* dictionary = "scrabble.txt";
    
    // load dictionary into memory
    getrusage(RUSAGE_SELF, &before);
    node* loaded = load(dictionary, root);
    getrusage(RUSAGE_SELF, &after);

    // abort program if dictionary not loaded
    if (loaded == NULL)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }
    
    // calculate time to load dictionary
    time_load = calculate(&before, &after);
    
    // prepare to report possible words
    printf("\nPOSSIBLE WORDS\n\n");
    
    // find words
    getrusage(RUSAGE_SELF, &before);
    check(argv[1], "", loaded);
    getrusage(RUSAGE_SELF, &after);
    
    // update benchmark
    time_check += calculate(&before, &after);
    
    // unload dictionary from memory
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload(root);
    getrusage(RUSAGE_SELF, &after);
    
    // abort program if dictionary not unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }
    
    // calculate time to unload dictionary
    time_unload = calculate(&before, &after);
    
    // report benchmarks
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n", 
     time_load + time_check + time_unload);
    
    return 0;
}



/**
 * Returns number of seconds between b and a.
 */
double calculate(const struct rusage* b, const struct rusage* a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
