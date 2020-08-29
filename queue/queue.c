#include <stdio.h>
#include <stdlib.h>

#define INF 99999999

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *front;
	Node *rear;
	int count;
} Queue;

void insert(Queue *queue, int data){
	Node* inserted = (Node*)malloc(sizeof(Node));
	inserted->data = data;
	inserted->next = NULL;
	if(queue->count == 0){
		queue->front = inserted;		
	}
	else {
		queue->rear->next = inserted;
	}
	queue->rear = inserted;
	queue->count++;
}

int pop(Queue *queue){
	if(queue->count == 0){
		printf("Queue is already Empty!\n");
		return -INF;
	}
	else {
		Node* popped = queue->front;
		int data = popped->data;
		queue->front = popped->next;
		free(popped);
		queue->count--;
		return data;
	}
}

void showAll(Queue *queue){
	if(queue->count==0){
		printf("Queue is already Empty!\n");
	}
	else {
		Node* curr = queue->front;
		printf("--- Top of the Queue ---\n");
		while(curr != NULL){
			printf("%d\n", curr->data);
			curr = curr->next;
		}
		printf("--- Bottom of the Queue ---\n");	
	}
}

int main(void)
{
	Queue q;
	q.front = q.rear = NULL;
	q.count = 0;
	insert(&q,10);
	insert(&q,20);
	insert(&q,30);
	int pop1 = pop(&q);
	printf("Popped Node : %d\n",pop1);
	showAll(&q);
	return 0;
}
