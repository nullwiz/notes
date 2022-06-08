#include <stdlib.h>
#include <stdio.h>

struct Node {
    char *key;
    char *value;
    struct Node *next;
};

typedef struct Node Node;

struct hash_table {
    Node **table;
    int size;
    int (*hash_function)(char*);
    int (*compare_function)(char*, char*);
}; 

typedef struct hash_table HashTable;

// Create new node
Node *create_new_node(char *key, char *value){
    Node *result = malloc(sizeof(Node));
    result->key = key;
    result->value = value;
    result->next = NULL;
    return result;
}

Node *insert_node_at_head(Node **head, Node *node_to_insert){
    node_to_insert->next = *head;
    *head = node_to_insert;
}

Node *find_value(Node *head, char value){
    
}



int main(){


}


