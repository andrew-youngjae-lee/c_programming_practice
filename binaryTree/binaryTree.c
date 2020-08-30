#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *leftChild;
	struct Node *rightChild;
} Node;

Node* initNode(int data, Node* leftChild, Node* rightChild){
	Node* parentNode = (Node*)malloc(sizeof(Node));
	parentNode->data = data;
	parentNode->leftChild = leftChild;
	parentNode->rightChild = rightChild;
	return parentNode;
}

//이진트리의 전위순회(자기자신출력->왼쪽자식방문->오른쪽자식방문)
void preorder(Node* root){
	if(root){
		printf("%d ",root->data);
		preorder(root->leftChild);
		preorder(root->rightChild);
	}
}

//이진트리의 중위순회(왼쪽자식방문->자기자신출력->오른쪽자식방문)
void inorder(Node* root){
	if(root){
		inorder(root->leftChild);
		printf("%d ",root->data);
		inorder(root->rightChild);
	}
}

//이진트리의 후위순회(왼쪽자식방문->오른쪽자식방문->자기자신출력)
void postorder(Node* root){
	if(root){
		postorder(root->leftChild);
		postorder(root->rightChild);
		printf("%d ",root->data);
	}
}

int main(void)
{
	Node* n7 = initNode(50, NULL, NULL);
	Node* n6 = initNode(37, NULL, NULL);
	Node* n5 = initNode(23, NULL, NULL);
	Node* n4 = initNode(5, NULL, NULL);
	Node* n3 = initNode(48, n6, n7);
	Node* n2 = initNode(17, n4, n5);
	Node* n1 = initNode(30, n2, n3);
	preorder(n1);
	printf("\n");
	inorder(n1);
	printf("\n");
	postorder(n1);
	printf("\n");
	return 0;
}