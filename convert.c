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

int firstOccurance(char line[], char ch, int startIndex)
{
    for(int i = startIndex; i<(int)(strlen(line)); i++)
    {
        if(line[i]==ch)
        {
            return i;
        }
    }
    return -1;
}

int detectQuotes(char Line[])
{
   int single = 0;
   int doubleQuotes = 0;

   for(int i = 0; i<(int)strlen(Line); i++)
   {
      if(Line[i] == 39)
      {
         doubleQuotes++;
      }
      else if (Line[i] == 34)
      {
         single++;
      }
   }
   if(single==2)
   {
      return 34;
   }
   else if (doubleQuotes==2)
   {
      return 39;
   }
   return 0;
}


int main()
{
   char *keywords[] = {"assign", "backspace", "block data", "call", "close", "common",
   "continue", "data", "dimension", "do", "else", "else if", "end", "endfile", "endif",
   "entry", "equivalence", "external", "format", "function", "goto", "if", "implicit",
   "inquire", "intrinsic", "open", "parameter", "pause", "print", "program", "read",
   "return", "rewind", "rewrite", "save", "stop", "subroutine", "then", "write"};

   //struct timespec t0; // pronounced "T ZERO"
   //struct timespec t1; //            "T 1"

   // using clock_gettime() on small segments of code will
   // give highly variable answers.  suggest doing it many times
   // in a loop and taking the average.

   //clock_gettime(CLOCK_REALTIME, &t0);

   int size = sizeof(keywords)/sizeof(keywords[0]);

   char eachLine[82];
   while(fgets(eachLine, 82, stdin))
   {
      if(eachLine[strlen(eachLine)-1] != 10)
      {
         strcat(eachLine, "\n");
      }
      //printf("%s",eachLine);
      if (eachLine[0] == 'C')
      {
         //ignore and just print it
      }
      else
      {
         //replace keywords to uppercase
         for(int p = 0; p<size; p++)
         {
            char s1[20];
            strcpy(s1,keywords[p]);
            char strupper[20] = " ";
            for (int i = 0; i<(int)strlen(s1); i++)
            {
               if(keywords[p][i]<65 || keywords[p][i]>90)
               {
                  strupper[i]= toupper(keywords[p][i]);
               }
               else
               {
                  strupper[i]= keywords[p][i];
               }
            }

            int M = strlen(strupper);
            int N = strlen(eachLine);
            int noChangeIndex = firstOccurance(eachLine, '!', 0);
            char haveQuotes = detectQuotes(eachLine);
            int quotesIndex = 0;
            int quotesEnd = 0;

            if(haveQuotes != 0)
            {
               //get the first occurance of the quotes
               quotesIndex = firstOccurance(eachLine, haveQuotes,0);
               quotesEnd = firstOccurance(eachLine, haveQuotes, quotesIndex+1);
            }

            for(int i=0; i<N-M;i++)
            {
               int j;
               for(j=0;j<M;j++)
               {
                  if(eachLine[i+j]!=strupper[j])
                  {
                     break;
                  }
               }
               if (j==M)
               {
                  if(eachLine[(i)-1]==' ')
                  {

                     for(int f=0;f<M;f++)
                     {
                        
                        if (noChangeIndex == -1 && haveQuotes == 0)
                        {
                           eachLine[i+f] = keywords[p][f];
                        }
                        else if(noChangeIndex != -1 && haveQuotes != 0)
                        {
                           if((i+f)<noChangeIndex && noChangeIndex<quotesIndex)
                           {
                              eachLine[i+f] = keywords[p][f];
                           }
                           else if((i+f)<quotesIndex && quotesIndex<noChangeIndex)
                           {
                              eachLine[i+f] = keywords[p][f];
                           }
                           else if(quotesEnd<(i+f) && (i+f)<noChangeIndex)
                           {
                              eachLine[i+f] = keywords[p][f];
                           }
                        }
                        else if (noChangeIndex == -1)
                        {
                           if((i+f)<quotesIndex || quotesEnd<(i+f))
                           {
                              eachLine[i+f] = keywords[p][f];
                           }
                        }
                        else if (haveQuotes == 0)
                        {
                           if((i+f) < noChangeIndex)
                           {
                              eachLine[i+f] = keywords[p][f];
                           }
                        }
                     }
                  }
               }
            }
         }
      }
      printf("%s",eachLine);
   }
   
   //clock_gettime(CLOCK_REALTIME, &t1);

   //printf("Program took %f seconds\n", diffTime(t0, t1));
   return 0;
}