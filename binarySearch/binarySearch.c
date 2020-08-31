//문자열 순차 탐색(Sequential Search) 구현
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 1000

char **array; //이차원배열
int founded; //특정 원소를 발견했는지에 대한 정보

int main(void)
{
	int n;
	char *word;
	word = malloc(sizeof(char)*LENGTH);
	scanf("%d", &n);
	array = (char**)malloc(sizeof(char*)*n);
	//printf("Fine\n");
	for(int i=0; i<n; i++){
		array[i] = malloc(sizeof(char)*LENGTH);
		scanf("%s", array[i]);
	}
	printf("Enter the word you want to find : ");
	scanf("%s", word);
	for(int i=0; i<n; i++){
		if(!strcmp(array[i], word)){
			printf("Word is in the number %d file.\n",i+1);
			founded = 1;
		}
	}
	if(!founded) printf("There's no word you want to find.\n");
	return 0;
}
*/

//이진 탐색 (Binary Search) 구현
#include <stdio.h>
#define MAX_SIZE 100000

int array[MAX_SIZE];

int search(int start, int end, int target){
	if(start > end) return -99999;
	int mid = (start + end)/2;
	if(target == array[mid]) return mid;
	else if (target > array[mid]) return search(mid + 1, end, target);
	else if (target < array[mid]) return search(start, mid - 1, target);
}

int main(void)
{
	int n, target;
	printf("Input the number of numFile: ");
	scanf("%d",&n);
	printf("Input the number : \n");
	for(int i=0; i<n; i++){
		scanf("%d",&array[i]);
	}
	printf("Input the number you want to find : ");
	scanf("%d",&target);
	int result = search(0, n-1, target);
	printf("The number you want to find is in file number %d.\n", result + 1);
	return 0;	
}
