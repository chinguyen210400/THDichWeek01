#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char* word, *linesAppear;
    int count;
} index;

typedef struct LinkedList{
    index data;
    struct LinkedList *next;
 } *node;

char* numtostring(int a)
{
    char* temp = (char*) malloc(sizeof(char));
    sprintf(temp,"%d", a);
    return temp;
}
node createNode(char* value, int line){
    node temp;
    char* str;
    temp = (node) malloc(sizeof(struct LinkedList));
    str  = (char*) malloc(50*sizeof(char));
    strcpy(str, strlwr(value));
    temp->next = NULL;
    temp->data.word = str;
    temp->data.linesAppear = numtostring(line);
    temp->data.count = 1;
    return temp;
}

void printResult(node head)
{
    for(node p = head; p != NULL; p = p->next){
        printf("%s %d,%s\n", p->data.word, 
                p->data.count, p->data.linesAppear);
    }
}
