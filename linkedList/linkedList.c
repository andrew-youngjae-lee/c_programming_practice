#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

void addFirst(Node* target, int data){
	Node *addedNode = (Node*)malloc(sizeof(Node));
	addedNode->next = target->next;
	addedNode->data = data;
	target->next = addedNode;
}

void discardFirst(Node* target){
	Node *discarded = (Node*)malloc(sizeof(Node));
	discarded = target->next;
	target->next = discarded->next;
	free(discarded);
}

void showAll(Node* target){
	Node *curr = (Node*)malloc(sizeof(Node));
	//Node *next = (Node*)malloc(sizeof(Node));
	curr = target->next;
	//next = curr->next;
	while(curr != NULL){
		printf("%d ",curr->data);
		curr = curr->next;
		//free(curr);
		//curr = next;
	}
}

void freeAll(Node* start){
	Node* curr = (Node*)malloc(sizeof(Node));
	curr = start->next;
	//Node* next = curr->next;
	while(curr != NULL){
		Node* next = curr->next;
		free(curr);
		curr = next;
	}
}

int main(void)
{
	Node *head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	
	addFirst(head,10);
	addFirst(head,20);
	addFirst(head,30);
	addFirst(head,40);
	addFirst(head,50);
	discardFirst(head);
	showAll(head);
	free(head);
	return 0;
}