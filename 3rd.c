//keywords are in a linked list

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>


typedef struct node{
	char * data;
	struct node* next;
} nodess;

double diffTime(struct timespec t0, struct timespec t1)
{
   // This function calculates the difference between two
   // timespec's in seconds.
   return ((t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9);
}

void insert_end(nodess** head,char* value)
{
	nodess* new_node= (nodess *) malloc(sizeof (nodess));
	new_node->data=value;
	new_node->next=NULL;

	if(*head==NULL)
	{
		*head=new_node;
	}
	else{
		nodess* tmp=*head;

		while(tmp->next!=NULL)
		{
			tmp=tmp->next;
		}
		tmp->next=new_node;
	}
}

void print(nodess* head) 
{
	while(head->next!=NULL)
	{

		printf("%s\n",head->data);
		head=head->next;
	}
	printf("%s",head->data);
}

int main()
{
   
    struct timespec t0; // pronounced "T ZERO"
    struct timespec t1; //            "T 1"
    clock_gettime(CLOCK_REALTIME, &t0);

    char *arr[]={"assign", "backspace", "block data", "call", "close", "common",
   "continue", "data", "dimension", "do", "else", "else if", "end", "endfile", "endif",
   "entry", "equivalence", "external", "format", "function", "goto", "if", "implicit",
   "inquire", "intrinsic", "open", "parameter", "pause", "print", "program", "read",
   "return", "rewind", "rewrite", "save", "stop", "subroutine", "then", "write"};

	nodess* head=NULL;

	for(int i=0;i<39;i++)
	{
		insert_end(&head,arr[i]);
	}

	print(head);

    clock_gettime(CLOCK_REALTIME, &t1);
    printf("Program took %f seconds\n", diffTime(t0, t1));
    return 0;
}
