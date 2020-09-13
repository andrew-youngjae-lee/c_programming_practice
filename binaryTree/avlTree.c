#include <stdio.h>
#include <stdlib.h>

int getMax(int a, int b){
	if(a>b) return a;
	return b;
}

typedef struct Node {
	int data;
	int height;
	struct Node* leftChild;
	struct Node* rightChild;
} Node;

int getHeight(Node *node) {
	if(node == NULL) return 0;
	return node->height;
}

//회전을 수행한 이후에 높이를 다시 계산해주는 함수
//왼쪽 자식과 오른쪽 자식의 높이 중 큰 값에 1를 더한게 자기 자신의 높이!
void setHeight(Node *node){
	node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

//균형인수를 구하는 함수 : |왼쪽자식 높이 - 오른쪽자식 높이|
int getBalanceFactor(Node *node){
	if(node == NULL) return 0;
	Node* leftChild = node->leftChild;
	Node* rightChild = node->rightChild;
	return getHeight(leftChild) - getHeight(rightChild);
}

Node* rotateLL(Node* node){ //균형인수의 절댓값이 2이상인 노드를 기준노드로 잡고 함수에 입력
	Node* leftChild = node->leftChild;
	node->leftChild = leftChild->rightChild;
	leftChild->rightChild = node;
	setHeight(node); //회전 이후에 높이가 바뀐 기준노드의 높이를 다시 계산
	return leftChild; //역시 높이가 바뀐 leftChild는 이후에 setHeight() 수행
}

Node* rotateRR(Node* node){ 
	Node* rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild;
	rightChild->leftChild = node;
	setHeight(node); 
	return rightChild; 
}

 Node *rotateLR(Node* node){
	 Node *leftChild = node->leftChild;
	 node->leftChild = rotateRR(leftChild);
	 setHeight(node->leftChild);
	 return rotateLL(node);
 }

Node *rotateRL(Node* node){
	 Node *rightChild = node->rightChild;
	 node->rightChild = rotateLL(rightChild);
	 setHeight(node->rightChild);
	 return rotateRR(node);
 }

//균형잡기
Node* balanceTree(Node* node){
	int balanceFactor = getBalanceFactor(node);
	if(balanceFactor >= 2) {
		if (getBalanceFactor(node->leftChild) >= 1) {
			node = rotateLL(node);
		}
		else {
			node = rotateLR(node);
		}
	}
	else if (balanceFactor <= -2) {
		if(getBalanceFactor(node->rightChild) <= -1){
			node = rotateRR(node);
		}
		else {
			node = rotateRL(node);
		}
	}
	setHeight(node);
	return node;
}

//삽입 함수 : 삽입 시에 거치는 모든 노드에 대하여 균형 잡기를 수행해주어야함
Node *insertNode(Node* node, int data){
	if (!node) {
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		node->height = 1;
		node->leftChild = NULL;
		node->rightChild = NULL;
	}
	else if(node->data > data){
		node->leftChild = insertNode(node->leftChild, data);
		node = balanceTree(node);
		//삽입할때마다 가장 아래 노드에서 위 노드로 올라오며 균형잡기 수행
	}
	else if(node->data < data){
		node->rightChild = insertNode(node->rightChild, data);
		node = balanceTree(node);
	}
	else {
		printf("데이터 중복이 발생했습니다.\n");
	}
	return node;
}

Node* root = NULL;
//출력 함수 : 일반적으로 트리의 너비가 높이보다 크므로 세로 방향으로 출력하는 함수로 구현
void showTree(Node* node, int level){
	if(node != NULL){
		showTree(node->rightChild, level + 1); //가장 오른쪽에 있는 노드로 이동, 가장 오른쪽부터 출력
		printf("\n");
		if (node == root) {
			printf("Root: ");
		}
		for(int i=0; i < level && node != root; i++){
			printf("	"); //가장 깊은 노드가 가장 오른쪽에 출력되도록 해줌
		}
		printf("%d(%d)", node->data, getHeight(node));
		showTree(node->leftChild, level + 1);
	}
}

int main(void) 
{
	root = insertNode(root, 7);
	root = insertNode(root, 6);
	root = insertNode(root, 5);
	root = insertNode(root, 3);
	root = insertNode(root, 1);
	root = insertNode(root, 9);
	root = insertNode(root, 8);
	root = insertNode(root, 12);
	root = insertNode(root, 16);
	root = insertNode(root, 18);
	root = insertNode(root, 23);
	root = insertNode(root, 21);
	root = insertNode(root, 14);
	root = insertNode(root, 15);
	root = insertNode(root, 19);
	root = insertNode(root, 20);
	showTree(root, 1); printf("\n");
	return 0;
}