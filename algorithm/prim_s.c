#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NODE_MAX 1001
#define EDGE_MAX 200001 //양방향 간선이므로 간선 10만개 정의

typedef struct { //간선 구조체 정의
	int cost;
	int node; //연결되는 상대방 노드
} Edge;

void swap(Edge *a, Edge *b){
	Edge temp;
	temp.cost = a->cost;
	temp.node = a->node;
	a->cost = b->cost;
	a->node = b->node;
	b->cost = temp.cost;
	b->node = temp.node;
}

typedef struct {
	Edge *heap[EDGE_MAX];
	int count;
} priorityQueue;

//최소 가중치의 간선을 선택할 것이므로 cost값을 기준으로 우선순위큐 구성
void pushPQ(priorityQueue *pq, Edge *edge){
	if(pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge; //Edge 구조체
	int now = pq->count; //인덱스값
	int parent = (pq->count - 1)/2; //인덱스값
	while(now>0 && pq->heap[now]->cost < pq->heap[parent]->cost){
		swap(pq->heap[now], pq->heap[parent]);
		now = parent; //인덱스값
		parent = (parent - 1)/2;
	}
	pq->count++;
}

Edge* pop(priorityQueue *pq){
	if(pq->count <= 0) return NULL;
	Edge *popped = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, leftchild = 1, rightchild = 2;
	int swapTarget = now;
	//lf나 rf가 count와 같다는건 그것이 이미 복사되어 popped 값과 교체된 맨 마지막 값이라는 뜻이므로 해당 값을 다룰 필요가 없음
	//while문이 한번 돌때마다 자기 바로 한단계 아래 노드들만 검사하여 교체 수행
	while(leftchild < pq->count){
		if(pq->heap[swapTarget]->cost > pq->heap[leftchild]->cost) swapTarget = leftchild;
		if(pq->heap[swapTarget]->cost > pq->heap[rightchild]->cost && rightchild < pq->count) swapTarget = rightchild;
		if(now == swapTarget) break;//now값보다 작은 자식노드가 존재하지 않아 내려가지 않아도 되면 종료
		else{
			swap(pq->heap[swapTarget], pq->heap[now]);
			now = swapTarget;
			leftchild = now * 2 + 1;
			rightchild = now * 2 + 2;
		}
	}
	return popped;
}

typedef struct Node {
	Edge *data; //다음 노드로 연결되는 간선
	struct Node *next;
} Node;

Node** graph;
int check[NODE_MAX]; //프림 알고리즘 동작 시 노드 방문여부 체크

void addNode(Node** targetGraph, int index, Edge* edge){
	if(targetGraph[index]==NULL){
		targetGraph[index] = (Node*)malloc(sizeof(Node));
		targetGraph[index]->data = edge;
		targetGraph[index]->next = NULL;
	}
	else{
		Node* addedNode = (Node*)malloc(sizeof(Node));
		addedNode->data = edge;
		addedNode->next = targetGraph[index];
		targetGraph[index] = addedNode;
	}
}

int main(void)
{
	int n, m; //n:정점의 개수(만들어지는 Node* 개수) m:간선의 개수(입력값 개수)
	scanf("%d %d", &n, &m);
	graph = (Node**)malloc(sizeof(Node*)*(n+1));
	for(int i=1; i<=n; i++){
		graph[i] = NULL;
	}
	priorityQueue *pq = (priorityQueue*)malloc(sizeof(priorityQueue));
	pq->count = 0;
	for(int i=0; i<m; i++){
		int a, b, c; // a,b:서로 연결되는 정점 c:해당 간선의 가중치
		scanf("%d %d %d", &a, &b, &c);
		Edge *edge1 = (Edge*)malloc(sizeof(Edge));
		edge1->cost = c;
		edge1->node = b;
		addNode(graph, a, edge1);
		Edge *edge2 = (Edge*)malloc(sizeof(Edge));
		edge2->cost = c;
		edge2->node = a;
		addNode(graph, b, edge2);
	}//무방향 그래프
	
	//프림 알고리즘 시작
	long long minCost = 0;//최소신장트리로 모든 노드를 연결할때 간선 가중치의 합(최소 비용)
	Edge *start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; start->node = 1; pushPQ(pq, start);//동작 위한 초기 입력값
    for(int i=1; i<=n; i++){ //i=0부터 반복문 돌리면 오류발생
		int nextNode = -1, nextCost = INT_MAX;//nextNode=인덱스값(참조 위해) nextCost=INT_MAX : nextCost값이 INT_MAX에서 변경되지 않았다는건 now==NULL이라는 뜻
		while(1){
			Edge *now = pop(pq);
			//printf("Test_nextCost1 : %d\n", nextCost);
			if(now == NULL) break; 
			//printf("Test_nextCost2 : %d\n", nextCost);
			nextNode = now->node;
			if(!check[nextNode]){
				nextCost = now->cost;
				//printf("Test_nextCost3 : %d\n", nextCost);
				break;
			}
		}
		if(nextCost == INT_MAX) printf("Graph is not connected.\n");
		minCost = minCost + nextCost;
		//printf("Test_minCost1 : %d\n", minCost);
		check[nextNode] = 1;
		Node* curr = graph[nextNode];
		while(curr != NULL){pushPQ(pq,curr->data); curr = curr->next;}
	}
	printf("%lld\n", minCost);
	return 0;	
}
