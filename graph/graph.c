//[1]2차원 행렬을 이용한 그래프 표현 - 무방향 비가중치 그래프와 인접행렬
/*#include <stdio.h>

int array[1001][1001];
int n, m; //n=정점의 개수, m=간선의 개수=입력할 data set 개수

int main(void)
{
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int x,y;
		scanf("%d %d",&x,&y);
		array[x][y]=1;
		array[y][x]=1;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			printf("%d ",array[i][j]);
		}
		printf("\n");
	}
	return 0;
}
*/

//[2]방향 가중치 그래프와 인접리스트 1)스택형 연결리스트
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int index;
	int distance;
	struct Node *next;
} Node;

void addFront(Node *root, int index, int distance){
	Node *addedNode = (Node*)malloc(sizeof(Node));
	addedNode->index = index;
	addedNode->distance = distance;
	addedNode->next = root->next;
	root->next = addedNode;
}

void showGraph(Node *root){
	Node* curr = root->next;
	while(curr != NULL){
		printf("[%d] (거리 : %d) ", curr->index, curr->distance);
		curr = curr->next;
	}
}

int main(void)
{
	int n,m;
	scanf("%d %d",&n, &m);
	Node** graph = (Node**)malloc(sizeof(Node*)*(n+1)); 
	for(int i=1; i<=n; i++){
		graph[i]=(Node*)malloc(sizeof(Node));
		graph[i]->next = NULL;
		//*(graph+i)->index = i;
	}
	for(int i=0; i<m; i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		addFront(*(graph+x),y,z);
	}
	for(int i=1; i<=n; i++){
		printf("원소[%d] : ", i);
		showGraph(*(graph+i));
		printf("\n");
	}
	return 0;
}