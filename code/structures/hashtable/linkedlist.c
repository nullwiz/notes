#include <stdio.h>
#include <stdlib.h>

// Singlely linked list example : points only to next node. 
// This inits our node structure. 
struct node { 
    int value;
    struct node* next;
};

typedef struct node node_t;

node_t *create_new_node(int value){
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next  = NULL;
    return result;
}

// O(n)
node_t *find_value(node_t *head, int value){
    node_t *current = head;
    while(current != NULL){
        if (current->value == value){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// In here, I am assigning the head myself.
node_t *insert_node_at_head(node_t *head, node_t *node_to_insert){
    node_to_insert->next = head;
    return node_to_insert;
}
// In here, I pass a pointer to a pointer(reference) so I dont have to assign the head myself
// so it will modify the structure in head. O(1)!
node_t *insert_node_at_head_pointer(node_t **head, node_t *node_to_insert){
    node_to_insert->next = *head;
    *head = node_to_insert;
}

// Delete node/free memory. Contemplate empty head and that node to delete is the head.
void *delete_node(node_t **head, node_t *node_to_delete ){
    node_t *current = *head; 
    if (head == NULL) return NULL;
    if (node_to_delete == current){ // If node is head
        *head = current->next;
        free(current);
    }
    while (current != NULL){
        if (current->next == node_to_delete ){
            current->next = node_to_delete->next;
        }
        current = current->next;
    }
    free(current);
};

// Remove dups without a bufffer allowed. We have to implement a hash table? Or runner technique: second pointer = first pointer+1
void *remove_dups_runner(node_t **head){
    node_t *current = *head; 
    node_t *next = NULL;

    // Returned nodes
    node_t *node = NULL; 
    // If the next value equals null, we have just one value
    if (current->next != NULL)
        next = current->next;
    // When first pointer points to null, next pointer == first pointer
    while(current->next!=NULL && next!=NULL){ //O(n^2)
        // Remove next pointer if it equals current value
        if(current->value == next->value){
            delete_node(&current, next);
        }
        // Move to next index if we did/didnt find the value. 
        // If next reached it's end, move current pointer and re-assign next's pointer to current+1 pointer
        if (next->next == NULL){
            insert_node_at_head_pointer(&node, create_new_node(current->value)); // O(1)
            current = current->next; 
            next = current->next;
        }
        else{next = next->next;}
    }
    // If we are at the end of the loop, this value is unique. Insert it
    insert_node_at_head_pointer(&node, create_new_node(current->value));
    // Assign new head
    *head = node; 
    // Free memory
    free(current);
    free(next);
}

// Remove dups from unsorted linked list. Using a pointer buffer this is O(n^2) [while doing n, we do n].
// If I used a HashSet this would be O(n)code/structures/hashtable/linkedlist.c
void *remove_dups(node_t **head){
    node_t *current = *head; 
    node_t *tmp = NULL; 
    node_t *value;
    while (current!=NULL){ //O(n)
        value = find_value(tmp,current->value); //O(n)
        if(value!= NULL){
            current = current->next; 
            continue;
        }
        insert_node_at_head_pointer(&tmp, create_new_node(current->value)); //O(1)
        current = current->next; 
    }
    *head = tmp;
    free(current);
    free(value);
}


// Not constant since we had to find the previous node address
void *insert_node_after_node(node_t *node, node_t *node_to_insert){
    // After node should point to new node
    node_to_insert-> next = node->next;
    // New node should point to after node next address
    node->next = node_to_insert;
};


void printlist(node_t *head){
    node_t *current = head;
    while(current != NULL){
        printf("%d ->", current->value, current, current->next);
        current = current->next;
    }
    free(current);
    printf("\n");
}

void *partition_around_value(node_t *head, int value){
   node_t *current = head; 
   node_t *less = NULL; 
   node_t *more_or_equal = NULL;
   while (current!=NULL){
       if (current->value < value){
           insert_node_at_head_pointer(&less, create_new_node(current->value));
       }
       if (current->value >= value){
           insert_node_at_head_pointer(&more_or_equal, create_new_node(current->value));
       }
       current = current->next;
   }
   printlist(less);
   printf("  ->  ");
   printlist(more_or_equal);
   free(less);
   free(more_or_equal);
   free(current);
}

// O(n)
node_t *k_to_last(node_t *head, int k){
    node_t *current = head;
    // Loop until kth element, print until null.
    for(int counter=0; counter < k; counter++){
        if (current!=NULL){
            current = current->next;
        }
    }
    return current;
}

int *sum_two_lists(node_t *head, node_t *secondhead){
    // First translate to a string, then to int again
    node_t *digit_1 = head;
    node_t *digit_2 = secondhead;
    int first_sum = 0; 
    int value; 
    for(int i = 0; digit_1 !=NULL;i++){
        first_sum = first_sum + digit_1->value * 10^i; 
        digit_1 = digit_1->next;
    }
    printf("%d\t", first_sum);
    int second_sum = 0; 

    for(int i = 0; digit_2 !=NULL;i++){
       second_sum  = second_sum + digit_2->value * 10^i; 
        digit_2 = digit_2->next;
    }
    printf("%d\t", second_sum);

    int totalsum = first_sum + second_sum;
    
    printf("%d\t\n", totalsum);
    // Create a new node, add values to it 
    int n = log10(totalsum) + 1;
    int i; 
    node_t *new_node = NULL; 
    for(i = 0; i < n; ++i, totalsum /=10){
        insert_node_at_head_pointer(&new_node, create_new_node(totalsum % 10));
    }
    printlist(new_node);
    free(new_node);
}

node_t *create_from_list(int arr[],int len){
    node_t *node = NULL;
    for (int i=len-1;i!=-1;i--){
        printf("%d\n",i);
        insert_node_at_head_pointer(&node,create_new_node(arr[i]));
    }
    return node;
}
int is_palindrome(node_t *head){
    // Check if node is palindrome
    node_t *current = head;
    node_t *reverse = NULL;
    while(current != NULL){
        insert_node_at_head_pointer(&reverse, create_new_node(current->value));
        current = current->next;
    }
    current = head;
    node_t *reverse_current = reverse;
    while(current != NULL){
        if(current->value != reverse_current->value){
            return 0;
        }
        current = current->next;
        reverse_current = reverse_current->next;
    }
    return 1;
}