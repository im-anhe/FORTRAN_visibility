#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

double diffTime(struct timespec t0, struct timespec t1)
{
   // This function calculates the difference between two
   // timespec's in seconds.
   return ((t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9);
}

int main()
{
    char *keywords[] = {"assign", "backspace", "block data", "call", "close", "common",
    "continue", "data", "dimension", "do", "else", "else if", "end", "endfile", "endif",
    "entry", "equivalence", "external", "format", "function", "goto", "if", "implicit",
    "inquire", "intrinsic", "open", "parameter", "pause", "print", "program", "read",
    "return", "rewind", "rewrite", "save", "stop", "subroutine", "then", "write"};

    struct timespec t0; // pronounced "T ZERO"
    struct timespec t1; //            "T 1"

    clock_gettime(CLOCK_REALTIME, &t0);

    int size = sizeof(keywords)/sizeof(keywords[0]);

    for(int i = 0; i<size; i++)
    {
        printf("\n%s", keywords[i]);
    }
    clock_gettime(CLOCK_REALTIME, &t1);

    printf("Program took %f seconds\n", diffTime(t0, t1));
    return 0;
}
