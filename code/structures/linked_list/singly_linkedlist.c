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
    while(current->next!=NULL && next!=NULL){ //O(n)
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
void *remove_dups(node_t **head){
    node_t *current = *head; 
    node_t *tmp = NULL; 
    node_t *value;
    while (current!=NULL){ //O(n)
        value = find_value(tmp,current->value); //O(n)
        if(value!= NULL){
            //printf("skipping value %d\n", current->value);
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
        printf("%d -> ", current->value);
        current = current->next;
    }
    free(current);
    printf("NULL\n");
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


int main(){
    node_t *head = NULL;
    node_t *tmp;

    for (int i=0; i<20;i++){
        tmp = create_new_node(i);
        insert_node_at_head_pointer(&head,tmp);
    }
    // Previous head
    printlist(head);

    insert_node_at_head_pointer(&head, create_new_node(20));
    //New head
    printlist(head);

    // Try to find a non-existing value
    find_value(head, 21230);

    // Find pointer to value (can also be *int type)
    tmp = find_value(head, 20);
    // Print address value
    printf("%p\n", tmp);
    // Print actual value 
    printf("%d\n", *tmp);

    // Insert new node after node (we find it by value)
    insert_node_after_node(tmp, create_new_node(200));
    // Print full node after insert  
    printlist(head);

    
    tmp = find_value(head,200);
    // Delete node
    printf("Deleting 200 from node\n");
    delete_node(&head, tmp);
    printlist(head);
    tmp = find_value(head,20);
    printf("head address: %p - tmp address %p\n", head,tmp);
    printf("Deleting 20 from node\n");
    delete_node(&head, tmp);
    printlist(head);
    node_t *new_head = NULL;
    node_t *new_tmp;

    for (int i=0; i<20;i++){
        new_tmp = create_new_node(i);
        insert_node_at_head_pointer(&new_head,new_tmp);
    }
    
    printf("================\n");
    printlist(new_head); 
    insert_node_after_node(find_value(new_head,19), create_new_node(19));
    insert_node_after_node(find_value(new_head,19), create_new_node(19));
    insert_node_after_node(find_value(new_head,19), create_new_node(19));
    insert_node_after_node(find_value(new_head,19), create_new_node(19));
    insert_node_after_node(find_value(new_head,19), create_new_node(2));
    insert_node_after_node(find_value(new_head,19), create_new_node(6));
    insert_node_after_node(find_value(new_head,19), create_new_node(8));
    insert_node_after_node(find_value(new_head,19), create_new_node(0));
    insert_node_after_node(find_value(new_head,19), create_new_node(0));
    insert_node_after_node(find_value(new_head,19), create_new_node(0));



    printf("================\n");

    printlist(new_head); 
    remove_dups_runner(&new_head);
    printlist(new_head); 
    
    printf("================\n");
    printlist(k_to_last(new_head,3));
    return 0;

}