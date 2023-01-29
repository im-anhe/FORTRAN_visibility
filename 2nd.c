//In this experiment, the keywords are going to be in a file and read into the code

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
    struct timespec t0; // pronounced "T ZERO"
    struct timespec t1; //            "T 1"
    clock_gettime(CLOCK_REALTIME, &t0);

    //will rewind to look at the file keywords
    char filename[] = "keywords.txt";

    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Could not open file %s. Exit", "keywords.txt");
        return 0;
    }
    
    char string[30];

    
    while(fgets(string,30,fp))
    {
        printf("%s", string);
    }

    rewind(fp);

    fclose(fp);

    clock_gettime(CLOCK_REALTIME, &t1);
    
    printf("Program took %f seconds\n", diffTime(t0, t1));

    return 0;
}
