#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define _GNU_SOURCE

struct node{
    int value;
    struct node* next;
    struct node* prev;
};
typedef struct node node_t;

void arrayCopy(char* sourceArray, char* destArray, int start, int end);
void printlist(node_t* head);
node_t* push(int value, node_t* head);
node_t* delete(int value, node_t* head);
node_t* getNode(int value, node_t* head);
void uniqueNum(node_t* head);


int main(int argc, char *argv[]){
    //char ch, file_name[25];    
    FILE* fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // printf("Enter name of file\n");
    // gets(file_name);
    fp = fopen(argv[1], "r");

    if (fp == NULL){
      printf("error");
      exit(EXIT_FAILURE);
    }
    if (NULL != fp){
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        if(size == 0){ 
            printf("0\n");
            exit(EXIT_FAILURE);
        }
    }

    // reinitialize fp
    fp = fopen(argv[1], "r");
    node_t *head = NULL;
    while ((read = getline(&line, &len, fp)) != -1) {
        int size = sizeof(line)/sizeof(line[0]);
        int operation;
        if (line[0] == 'i') {
            operation = 1;
        } else if (line[0] == 'd'){
            operation = 0;
        } else {
            // invalid state
            operation = 2;
        }
        char number[size];
        
        // logic to get value
        arrayCopy(line, number, 2, size);
        // logic to insert/delete based on operation
        int num = atoi(number);

        if(operation == 1) {
            head = push(num, head);
        }
        else if(operation == 0) {
            head = delete(num, head);
        } else {
            // do nothing
        }
    }
    
    // printlist(head);
    // printf("\n");

    int numNodes = 0;
    node_t* temp = head;
    while(temp!= NULL){
        numNodes++;
        temp = temp->next; 
    }

    printf("%d\n", numNodes);
    uniqueNum(head);

    free(line);
    exit(EXIT_SUCCESS);
    //logic to handle blank file
    return 0;
}

void arrayCopy(char* sourceArray, char* destArray, int start, int end) { 
    int i = 0;
    while (start < end){
        destArray[i] = sourceArray[start];
        i++;
        start++;
    }
}

node_t* push(int value, node_t* head){

    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    result->prev = NULL;
    //blank value = 4
    //8      :   value - 8
    //1 6    :   1 - value - 6
    //1 3    :   1 - 3 - value
    //1 4 5  :   1 - value - 4 - 5

    // No linked list exists yet -> create & return head
    if(head==NULL){
        return result;
    }
    // replacing head 
    if (value <= head->value) {
        result->next = head;
        head->prev = result;
        return result;
    }
    // head is initialized
    node_t* temp = head;
    while(temp!= NULL) {
        // push stuff
        if(temp->value < value && temp->next== NULL){
            temp->next = result;
            result->prev = temp;
            return head;
        }
        if(temp->value < value && temp->next->value >= value){
            result->next = temp->next;
            temp->next = result;
            result->prev = temp;
            return head;
        }
        else {
            temp = temp->next; 
        }
    }
    return head;
    
}

node_t* delete(int value, node_t* head){
    // blank                : ignore
    // 1(value)             : blank
    // 1 - 2(value) - 3     : 1 - 3
    // 1 - 2(value) -2 - 3  : 1 - 2 - 3
    if(head==NULL){
        return head;
    }
    //node_t* temp = head;
    node_t* toBeDeleted = getNode(value, head);

    if (toBeDeleted==NULL) {
        return head;
    }
    
    if(toBeDeleted == head){
        head = head->next;
        return head;
    }
    if (toBeDeleted->next==NULL) {
        toBeDeleted->prev->next = NULL;
        return head;
    }
    toBeDeleted->prev->next = toBeDeleted->next;
     return head;
}

void printlist(node_t* head){
    node_t *temp = head;
    while(temp != NULL){
        printf("%d  ", temp->value);
        temp = temp->next;
    }
}

node_t* getNode(int value, node_t* head) {
    // find value in LL
    node_t* temp = head;
    while(temp!= NULL) {
        if (temp->value==value) {
            return temp;
        }
        temp = temp->next; 
    }
    return NULL;
}

void uniqueNum(node_t* head){
    //traverses the linked list and prints: if the previously printed number is the same as the current, skip
    int prev;
    node_t* temp = head;
    while(temp!= NULL) {
        if(prev != temp->value){
            if(temp->next==NULL)
                printf("%d", temp->value);
            else
                printf("%d\t", temp->value);
        }
        prev = temp->value;
        temp = temp->next; 
    }
}
 







 