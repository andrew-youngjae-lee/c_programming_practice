#include <stdio.h>
#include <stdlib.h>

 typedef struct Node{
	 int data;
	 struct Node *leftChild;
	 struct Node *rightChild;
 } Node;

Node* insertTree(Node *root, int data){ //insert + add
	if(root == NULL){
		root = (Node*)malloc(sizeof(Node));
		root->data = data;
		root->leftChild = NULL;
		root->rightChild = NULL;
		return root;
	}
	else if(root->data > data){
		root->leftChild = insertTree(root->leftChild, data);
	}
	else root->rightChild = insertTree(root->rightChild, data);
	return root;
}

Node* searchTree(Node* root, int data){
	if(root == NULL) return NULL;
	if(root->data == data) return root;
	else if(root->data > data) return searchTree(root->leftChild, data);
	else return searchTree(root->rightChild, data);
}

void preorder(Node *root){
	if(root == NULL) return;
	printf("%d ", root->data);
	preorder(root->leftChild);
	preorder(root->rightChild);
}

/*이진탐색트리의 삭제
1)삭제할 노드의 자식이 없는 경우 = 해당 노드를 단순히 제거
2)삭제할 노드의 자식이 하나만 있는 경우 = 삭제할 노드 자리에 자식노드 넣기
3)삭제할 노드의 자식이 둘 다 존재하는 경우 = 삭제할 노드 자리에 자기 다음으로 큰 노드 넣기
-> 자기보다 작은 노드 넣으면 root 왼쪽 배열에서 오류, 자기보다 두 단계 이상 큰 노드 넣으면 오른쪽 배열에서 오류
*/

Node* findNextMin(Node *root){
	Node* node = root;
	while(node->leftChild != NULL){
		node = node->leftChild;
	}
	return node;
} //자기 다음으로 큰 노드는 자기 오른쪽 자식의 왼쪽 트리 최하단에 존재함!

Node* deleteNode(Node *root, int data){
	Node* replace = NULL;
	if(root == NULL) return NULL;
	if(root->data > data) root->leftChild = deleteNode(root->leftChild, data);
	else if (root->data < data) root->rightChild = deleteNode(root->rightChild, data);
	else { //(root->data == data)
		if(root->leftChild != NULL && root->rightChild != NULL){ // 3) case
			replace = findNextMin(root->rightChild);
			root->data = replace->data;
			root->rightChild = deleteNode(root->rightChild, replace->data);
		}
		else { // 1), 2) case
			replace = (root->leftChild != NULL) ? root->leftChild : root->rightChild;
			//자식노드가 한개뿐인 case라 왼쪽이거나 오른쪽 중에 있는 자식을 골라 대체 노드로 지정하여 자기 자신이 삭제된 뒤 대체되도록 해줌
			free(root);
			return replace;
		}
	}
	return root;
}

int main(void)
{
	Node *root = NULL;
	root = insertTree(root, 30);
	root = insertTree(root, 17);
	root = insertTree(root, 48);
	root = insertTree(root, 5);
	root = insertTree(root, 23);
	root = insertTree(root, 37);
	root = insertTree(root, 50);
	root = deleteNode(root, 30);
	preorder(root);
	printf("\n");
	return 0;
}
