#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001

typedef struct Node {
	int index;
	struct Node *next;
} Node;

int n,m;
int check[MAX_SIZE];
Node** graph; //Point!

void addFront(Node *root, int index){
	Node *addedNode = (Node*)malloc(sizeof(Node));
	addedNode->index = index;
	addedNode->next = root->next;
	root->next = addedNode;
}

void showAll(Node *root){
	Node *curr = root->next;
	while(curr != NULL){
		printf("[%d]", curr->index);
		curr = curr->next;
	}
}

void dfs(int x){
	if(check[x]) return;
	check[x] = 1;
	printf("%d ", x);
	Node* curr = graph[x]->next;
	while(curr != NULL){
		int next = curr->index;
		dfs(next);
		curr = curr->next;
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
	
	dfs(1);
	return 0;
}
