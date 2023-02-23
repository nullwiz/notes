#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_NAME 256
#define TABLE_SIZE 20

// Quick note dynamically resizable arrays
// http://www.cplusplus.com/doc/tutorial/dynamic/
// in some languages arrays are automatically resizable, it will grow as needed
// as we append items. In Java, the array sze can't change after it's creation
// (much like C).
// A typical implementation would be to just duplicate the size
// when it's full. In C, we can use a pointer to a function to dynamically
// resize the array. The function should take the current size of the array
// and return a pointer to a new array of the new size (we can use calloc() and realloc() to do this).
// The function should also free the old array.
// Example:
int* resize(int* arr, int size) {
    int* new_arr = calloc(size * 2, sizeof(int)); 
    if (new_arr == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }
    // realloc() will copy the contents of the old array to the new one
    // and free the old one.
    new_arr = realloc(arr, size * 2);
    if (new_arr == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }
    return new_arr;
}

struct Node {
    char *value;
    struct Node *next;
};

typedef struct Node Node;

Node * hash_table[TABLE_SIZE];


unsigned int hash_function(char *str) {
    int length = strnlen(str, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i= 0; i < length; i++){
        hash_value += str[i];
        hash_value = (hash_value * str[i]) % TABLE_SIZE;
    }
    return hash_value;

}

void init_hash_table(){
    for(int i=0; i < TABLE_SIZE; i++){
        hash_table[i] = malloc(sizeof(Node));
        if (hash_table[i] == NULL){
            // memory not allocated
            printf("memory not allocated\n");
            break;
        }
        // init to zero 
        hash_table[i]->value = NULL;
        hash_table[i]->next = NULL;
    }
}

void print_linked_list(Node *head){
    Node *current = head;
    // Dont print last null char
    while(current->next!= NULL){
        printf("%s -> ", current->value);
        current = current->next;
    }
}

void print_table(){
    printf("Start\n");
    for(int i=0; i < TABLE_SIZE; i++){
        while (hash_table[i]!= NULL){
            if (hash_table[i]->value == NULL){
                printf("\t%i\t 0\n", i);
            }
            else{
                // print linked list
                printf("\t%i\t", i);
                print_linked_list(hash_table[i]);
                printf("\n");
            }
           break; 
        }
    }
    printf("End\n");
    }

//insert node to hash table at the head of the linked list
void insert_node_at_head(char *value){
    unsigned int hash_value = hash_function(value);
    printf("hash value: %i\n", hash_value);
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = hash_table[hash_value];
    hash_table[hash_value] = new_node;
}

// hash table insert function
int insert_node(Node *node){
    if( node == NULL) return 0;
    unsigned int hash_value = hash_function(node->value);
    printf("hash value: %i\n", hash_value);
    node->next = hash_table[hash_value];
    hash_table[hash_value] = node;
    return 1;
}

// Create new node
Node *create_new_node(char *value){
    Node *result = malloc(sizeof(Node));
    result->value = value;
    result->next = NULL;
    return result;
}
// O(n)
Node *find_value(Node *head, char value){
    Node *current = head;  
    while(current != NULL){
        if(current->value == value){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int main(){
    init_hash_table();
    insert_node_at_head("hello");
    insert_node_at_head("world");
    Node *tmp; 
    tmp = create_new_node("asd");
    unsigned int hash_value = hash_function("asd");
    printf("hash value: %i\n", hash_value);
    tmp->next = hash_table[hash_value];
    hash_table[hash_value] = tmp;
    
    print_table();
}


