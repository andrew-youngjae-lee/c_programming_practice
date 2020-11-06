#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 20001
#define EDGE_MAX 600001 // 양방향 간선이므로 간선 300,000개

typedef struct {
	int cost;
	int node;
} Edge;

void swap(Edge *a, Edge *b) { //우선순위 큐 구현 위해 edge끼리 swap하는 기능 구현
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

void push(priorityQueue *pq, Edge *edge) {
	if(pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge; //count = 가장 마지막 원소의 다음 index에 새 원소 넣어줌
	int now = pq->count; //now = 가장 마지막 원소(=아직 우선순위큐 배열 안된, 새로 추가된 원소)의 index
	int parent = (pq->count - 1) / 2; //새로 추가된 원소의 부모노드
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost){
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;//now에 이제는 부모노드의 index를 차지한 새 원소의 위치를 찍어줌
		parent = (parent - 1) / 2;//새 원소의 바뀐 위치를 기준으로 다시 부모노드 지정
	}
	pq->count++; //새 원소가 제 위치를 찾으면 count 갱신 : 배열 내 원소 개수를 추가해줌과 동시에 다음 추가될 원소의 최초위치를 찍어주는 역할
}

Edge* pop(priorityQueue *pq) {
	if(pq->count <= 0) return NULL; //edge가 배열안에 없으면 종료
	Edge *poppedNode = pq->heap[0]; //트리 내 최솟값인 노드가 맨 위이자 맨 앞에 위치
	pq->count--; //맨 마지막 노드를 메모리해제로 삭제하는것이 아니므로 count값을 줄여 맨 마지막 노드를 연산의 최대범위에서 제외(맨 마지막 노드는 맨 앞 index로 이동함)
	pq->heap[0] = pq->heap[pq->count]; //비어버린 맨 앞자리에 맨 뒤에 있던 노드 넣어줌
	int now = 0, leftChild = 1, rightChild = 2; //now = 위치가 갑자기 이동되어 위치조정이 필요한 노드 
	int target = now; //target : 현재 가리키는 노드보다 작은 값의 노드로 이동하여 swap의 대상이 누군지 찍어주는 역할
	//맨 앞 원소를 추출한 이후에 하향식으로 힙을 구성
	while(leftChild < pq->count) { //count는 맨 마지막 원소의 다음 index를 가리키고 있으므로 lfC나 rfC가 배열 범위 내에 있다면 반드시 count보다 작아야함!
		if(pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;
		if(pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count) target = rightChild;
		if (target == now) break; //더 이상 내려가지 않아도 될 때 종료
		else {
			swap(pq->heap[now], pq->heap[target]);
			now = target; //정상위치에서 갑자기 위치가 바뀌어버린 target을 다음 조정대상으로 지목
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2; //위치가 비뀐 노드를 기준으로 자식노드를 재지정하여 다시 재배열 실행(leftChild 값이 연산 최대범위를 벗어날 때 까지)-lfC값이 벗어나면 rfC값은 당연히 벗어남
		}	
	}
	return poppedNode;
}

//**그래프 정의**
typedef struct Node {
	Edge *data; //data = 간선에 대한 정보
	struct Node *next; //next = 다음 노드에 대한 정보
} Node;

Node** graph; //graph : 다익스트라 알고리즘을 적용할 현실세계의 그래프
int answer[NODE_MAX]; //특정 노드까지의 최단거리값

void addNode(Node** targetGraph, int index, Edge* edge){
	if(targetGraph[index]==NULL){ //Node포인터 배열의 index번째 Node포인터가 가리키는 값이 NULL 이면(그래프의 해당 위치에 노드가 없으면)
		targetGraph[index] = (Node*)malloc(sizeof(Node));
		targetGraph[index]->data = edge;
		targetGraph[index]->next = NULL;
	}
	else {
		Node *addedNode = (Node*)malloc(sizeof(Node));
		addedNode->data = edge;
		addedNode->next = targetGraph[index];
		targetGraph[index] = addedNode;
	}
}

int main(void) {
	int n,m,k; //n:정점의 개수(만들어지는 Node* 개수) m:간선의 개수(입력값 개수)
	scanf("%d %d %d", &n, &m, &k); //k:다익스트라 알고리즘을 시작하는 최초 노드 번호, 출발하는 노드
	graph = (Node**)malloc(sizeof(Node*) * (n+1));
	for(int i = 1; i <= n; i++){
		graph[i] = NULL;
		answer[i] = INT_MAX;
	}
	priorityQueue *pq;
	pq = (priorityQueue*)malloc(sizeof(priorityQueue));
	pq->count = 0;
	for(int i = 0; i < m; i++){
		int from, to, cost; // from, to:서로 연결되는 정점 cost:해당 간선의 가중치
		scanf("%d %d %d", &from, &to, &cost);
		Edge *edge = (Edge*)malloc(sizeof(Edge));
		edge->node = to;
		edge->cost = cost;
		addNode(graph, from, edge); //유방향 그래프 생성
	}
	//여기서부터 다익스트라 알고리즘 시작
	answer[k] = 0;
	Edge *start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; start->node = k; push(pq, start); //알고리즘 시동 위한 초기값 넣어줌
	while(1){
		Edge* now = pop(pq);
		if(now == NULL) break; //원소가 바닥날때까지 pop = 모든 간선에 대한 정보를 전부 queue에 담았다가 뺄것
		int currNode = now->node; //처음 시작할때 : currNode = k. *node = next node
		int currCost = now->cost;//처음 시작할때 : currCost = 0;
		if(answer[currNode] < currCost) continue; //현재 보고 있는 비용이 현재까지 answer테이블에 담은 비용보다 크다면 볼 필요 없이 무시하겠다는것 => 더 작을때만 갱신해줌.
		Node *curr = graph[currNode]; //currNode와 연결된 인접 노드들의 정보를 순회하며 담는 노드 포인터 변수 선언
		while (curr != NULL){
			Edge *temp = curr->data;
			temp->cost += currCost;
			if(temp->cost < answer[temp->node]){
				answer[temp->node] = temp->cost;
				push(pq, temp);
			}
			curr = curr->next;
		}
	}
	//priorityQueue에는 지금까지 노드들을 방문하는데 든 최소비용에 다음 노드를 방문하는데 들어가는 비용을 합산한 값이 들어감 => 그 중 가장 작은 값이 계속 트리 최상단에 위치하여 pop되며 cost합산값을 최소값으로 갱신함. 해당 최소값이 answer배열의 해당 위치값과 비교하여 더 작으면 갱신되는 방식으로 answer배열에 노드별 최소 방문비용이 입력됨 => answer 배열의 값이 더 이상 갱신되지 않는 위치의 노드는 이미 최소비용으로 방문이 끝났다는 뜻
	for(int i = 1; i <= n; i++) {
		if(answer[i] == INT_MAX) printf("INF\n");
		else printf("%d\n", answer[i]);
	}
}