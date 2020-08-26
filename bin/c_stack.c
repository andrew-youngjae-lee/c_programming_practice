#include <stdio.h>
#include <stdlib.h>

#define INF 99999999

typedef struct {
	int data;
	struct Node *next;
} Node;

typedef struct{
	Node *top;
} Stack;

//Stack Insert Fuction
void push(Stack *stack, int data){
	Node *addedNode = (Node*)malloc(sizeof(Node));
	addedNode->data = data;
	addedNode->next = stack->top;
	stack->top = addedNode;
	//항상 제일 마지막에 들어온 최상단 노드가 top이기 때문
}

int pop(Stack *stack){
	if(stack->top == NULL){
		printf("Stack Underflow is occured.\n");
		return -INF;
	}
	//데이터 추출을 위해 최상단 노드를 poppedNode에 따로 할당해줌
	Node *poppedNode = stack->top;
	int data = poppedNode->data;
	stack->top = poppedNode->next;
	free(poppedNode);
	return data;
}

void show(Stack *stack){
	Node *cur = stack->top;
	if(cur == NULL) printf("Theres no data in Stack.\n");
	else{
		printf("--- Top of the Stack ---\n");
		while(cur != NULL){
			printf("%d\n", cur->data);
			cur = cur->next;
		}
		printf("--- Bottom of the Stack ---\n");
	}
		
}

int main(void){
	Stack s;
	s.top = NULL; //반드시 NULL로 초기화해줘야 언더플로우나 순회포인터를 사용할 수 있음
	show(&s);
	push(&s,7);
	push(&s,5);
	push(&s,4);
	pop(&s);
	push(&s,6);
	pop(&s);
	show(&s);
	return 0;
}