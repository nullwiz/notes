#include <stdio.h>
#include <stdlib.h>

// Doubly linked list implementation
struct node {
    struct node* last;
    int value; 
    struct node* next;
};


typedef struct node node_t;

// Create a node
node_t *create_new_node(int value){
    node_t *new_node= malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next  = NULL;
    new_node->last  = NULL;
    return new_node;
}
/// <null> -- v1 -- v2 -- <null>
node_t *insert_node_at_head(node_t **head, node_t *node){
    node->next = head;
    *head = node; 
}

void printlist(node_t *head){
    node_t *current = head;
    while(current != NULL){
        printf("(%p) %d  (%p)-> ",current->last, current->value, current->next);
        current = current->next;
    }
    free(current);
    printf("NULL\n");
}

int main(){
    node_t *node = NULL;
    node_t *tmp;

    for(int i=0; i<20; i++){
        tmp = create_new_node(i);
        insert_node_at_head(&node,tmp);
    }
    printlist(node);
    return 0;    
};
