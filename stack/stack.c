#include <stdio.h>
#include <stdlib.h>

#define INF 99999999

typedef struct Node {
	struct Node *next;
	int data;
} Node;

typedef struct Stack{
	Node *top;
} Stack;

void push(Stack *stack, int data){
	Node *pushed = (Node*)malloc(sizeof(Node));
	pushed->data = data;
	pushed->next = stack->top;
	stack->top = pushed;
}

int pop(Stack *stack){
	if(stack->top == NULL) {
		printf("Stack is already Empty.\n");
		return -INF;
	}
	Node *popped = (Node*)malloc(sizeof(Node));
	popped = stack->top;
	int data;
	data = popped->data;
	stack->top = popped->next;
	free(popped);
	return data;	
}

void showStack(Stack *stack){
	Node* curr = (Node*)malloc(sizeof(Node));
	curr = stack->top;
	printf("---- Top of Stack ----\n");
	while(curr != NULL) {
		printf("%d\n",curr->data);
		curr = curr->next;
	}
	printf("--- Bottom of Stack ---\n");
}

int main(void)
{
	Stack s;
	s.top = NULL;
	push(&s,10);
	push(&s,20);
	push(&s,30);
	push(&s,40);
	push(&s,50);
	int stack1 = pop(&s);
	int stack2 = pop(&s);
	printf("Popped Data : %d %d\n",stack1, stack2);
	showStack(&s);
	return 0;
}