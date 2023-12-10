#include <stdio.h>
#include <stdlib.h>
#define insert(x,y) push(x,y)
#define delete(x) pop_top(x)

typedef struct linkedlist {
    int data;
    struct linkedlist *next;
}lkdlist;

int isEmpty(lkdlist *head){
    if(!head){
        return 1;
    }
    return 0;
}

int len(lkdlist *head){
    lkdlist *temp = head;
    int count = 0;
    while(temp){
        temp = temp->next;
        count++;
    }
    return count;
}

int count(lkdlist *head, int key){
    lkdlist *temp = head;
    int count = 0;
    while(temp){
        if(temp->data == key){
            count++;
        }
        temp = temp->next;
    }
    return count;
}

int item_at(lkdlist *head,int index){
    if(index >= len(head)){
        printf("index out of range.\n");
        return -1;
    }
    int count = 1;
    lkdlist *temp = head;
    while(count <= index){
        temp = temp->next;
        count++;
    }
    return temp->data;
}

int top(lkdlist *head){
    item_at(head,0);
}

int bottom(lkdlist *head){
    item_at(head,len(head)-1);
}

void push(lkdlist **head, int new_data, int index){
    if(len(*head) < index || index < 0){
        printf("Index Out of Range %d\n",len(*head));
        return;
    }

    lkdlist *new_node = (lkdlist*)malloc(sizeof(lkdlist));
    new_node->data = new_data;

    if(index == 0){
        new_node->next = *head;
        *head = new_node;
        return;
    }
    int i = 0;
    lkdlist *temp = *head, *prev;
    do{
        prev = temp;
        temp = temp->next;
        i++;
    }while(i < index);
    prev->next = new_node;
    new_node->next = temp;
}

void push_top(lkdlist **head, int new_data) {
    push(head,new_data,0);
}

void push_bottom(lkdlist **head, int new_data){
    int l = len(*head);
    push(head,new_data,l);
}

void sort_push(lkdlist **head, int new_data){
    lkdlist *new_node = (lkdlist*)malloc(sizeof(lkdlist));
    new_node->data = new_data;
    if(!(*head) || (*head)->data > new_node->data){
        new_node->next = *head;
        *head = new_node;
        return;
    }
    lkdlist *temp = *head, *prev;
    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
        if(temp->data >= new_node->data){
            prev->next = new_node;
            new_node->next = temp;
            return;
        }
    }
    temp->next = new_node;
    new_node->next = NULL;
}

int pop_at(lkdlist **head, int index){
    if(isEmpty(*head)){
        printf("No Element Found.\n");
        return -1;
    }

    if(len(*head) < index || index < 0){
        printf("Index Out of Range %d\n",len(*head));
        return -1;
    }

    lkdlist *temp = *head, *prev;
    int i = 0;
    int data;
    if(i == index){
        data = temp->data;
        *head = temp->next;
        free(temp);
        return data;
    }

    while(i < index){
        prev = temp;
        temp = temp->next;
        i++;
    }
    prev->next = temp->next;
    data = temp->data;
    free(temp);
    return data;
}

void pop(lkdlist **head, int key) {
    lkdlist *temp = *head, *prev;

    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key not found\n");
        return;
    }

    prev->next = temp->next;
    printf("Removed %d\n",temp->data);
    free(temp);
}

int pop_top(lkdlist **head) {
    pop_at(head,0);
}

int pop_bottom(lkdlist **head){
    if(isEmpty(*head)){
        return -1;
    }

    if (!(*head)->next) {
        int data = (*head)->data;
        *head = NULL;
        return data;
    }

    lkdlist *current = *head;
    while (current->next->next) {
        current = current->next;
    }

    int data = current->next->data;
    free(current->next);
    current->next = NULL;
    return data;
}

void display(lkdlist *head) {
    lkdlist *temp = head;

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int isExist(lkdlist *head, int key){
    if(isEmpty(head)){
        return 0;
    }
    lkdlist *temp = head;
    while(temp){
        if(temp->data == key){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void del_List(lkdlist **head){
    lkdlist *temp = (*head)->next, *prev;
    while(temp){
        prev = temp;
        temp = temp->next;
        free(prev);
    }
    free(temp);
    (*head) = NULL;
}

void sort_list(lkdlist **head){
    if(isEmpty(*head)){
        printf("No Element Found.\n");
        return;
    }
    lkdlist *temp = *head, *prev, *new_head = NULL;
    while(temp){
        sort_push(&new_head,temp->data);
        prev = temp;
        temp = temp->next;
        free(prev);
    }
    *head = new_head;
    free(temp);
}

void reverse_list(lkdlist **head){
    if(!(*head)){
        printf("No Element to Reverse.\n");
        return;
    }
    lkdlist *temp = *head, *prev = NULL, *new_head = NULL;
    while(temp){
        new_head = temp;
        temp = temp->next;
        new_head->next = prev;
        prev = new_head;
    }
    *head = new_head;
}

/*void reverse_list(lkdlist **head){
    if(!(*head)){
        printf("No Element to Reverse.\n");
        return;
    }
    lkdlist *temp = *head, *prev, *new_head = NULL;
    while(temp){
        push_top(&new_head,temp->data);
        prev = temp;
        temp = temp->next;
        free(prev);
    }
    *head = new_head;
    free(temp);
}*/

lkdlist *merge(lkdlist *head1, lkdlist *head2){
    lkdlist *temp1 = head1, *temp2 = head2;
    lkdlist *head = NULL;
    while(temp1){
        push_bottom(&head,temp1->data);
        temp1 = temp1->next;
    }
    while(temp2){
        push_bottom(&head,temp2->data);
        temp2 = temp2->next;
    }
    return head;
}

lkdlist *sort_marge(lkdlist *head1, lkdlist *head2){
    lkdlist *temp1 = head1, *temp2 = head2;
    lkdlist *head = NULL;
    while(temp1){
        sort_push(&head,temp1->data);
        temp1 = temp1->next;
    }
    while(temp2){
        sort_push(&head,temp2->data);
        temp2 = temp2->next;
    }
    return head;
}

void replace(lkdlist *head, int old_data, int new_data){
    
}

void replace_at(lkdlist *head, int new_data, int index){

}

void replaceAll(lkdlist *head, int old_data, int new_data){
    
}