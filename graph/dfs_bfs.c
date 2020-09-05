#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001

typedef struct Node {
	int index;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *front;
	Node *rear;
	int count;
} Queue;

int n,m;
int checkDfs[MAX_SIZE];
int checkBfs[MAX_SIZE];
Node** graph; //Point!

void addFront(Node *root, int index){
	Node *addedNode = (Node*)malloc(sizeof(Node));
	addedNode->index = index;
	addedNode->next = root->next;
	root->next = addedNode;
}

void queuePush(Queue *queue, int index){
	Node* addedNode = (Node*)malloc(sizeof(Node));
	addedNode->index = index;
	addedNode->next = NULL;
	if(queue->count == 0){
		queue->front = addedNode;
	}
	else {
		queue->rear->next = addedNode;
	}
	queue->rear = addedNode;
	queue->count++;
}

int queuePop(Queue* queue){
	if(queue->count == 0) {
		printf("There's no data in the file.\n");
		return -9999;
	}
	Node* poppedNode = queue->front;
	int index = poppedNode->index;
	queue->front = poppedNode->next;
	free(poppedNode);
	queue->count--;
	return index;	
}

void showAll(Node *root){
	Node *curr = root->next;
	while(curr != NULL){
		printf("[%d]", curr->index);
		curr = curr->next;
	}
}

void dfs(int x){
	if(checkDfs[x]) return;
	checkDfs[x] = 1;
	printf("%d ", x);
	Node* curr = graph[x]->next;
	while(curr != NULL){
		int next = curr->index;
		dfs(next);
		curr = curr->next;
	}
}

void bfs(int x){
	Queue q;
	q.front = q.rear = NULL;
	q.count = 0;
	queuePush(&q,x);
	checkBfs[x]=1;
	while(q.count != 0){
		int root = queuePop(&q);
		printf("%d ", root);
		Node* curr = graph[root]->next;
		while (curr != NULL) {
			int next = curr->index;
			if(!checkBfs[next]){
				queuePush(&q,next);
				checkBfs[next] = 1;
			}
			curr = curr->next;
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);
	graph = (Node**)malloc(sizeof(Node*)*n+1); //Point!
	for(int i=1; i<=n; i++){
		graph[i] = (Node*)malloc(sizeof(Node));
		graph[i]->next = NULL;
	}
	for(int i=0; i<m; i++){
		int x,y;
		scanf("%d %d", &x, &y);
		addFront(graph[x],y);
		addFront(graph[y],x);
	}
	for(int i=1; i<=n; i++){
		printf("[%d] : ",i);
		showAll(graph[i]);
		printf("\n");
	}
	printf("[DFS] : ");
	dfs(1);
	printf("\n");
	printf("[BFS] : ");
	bfs(1);
	return 0;
}
