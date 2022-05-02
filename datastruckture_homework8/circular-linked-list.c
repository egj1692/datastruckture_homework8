/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("------------------[LeeJunGi]     [2017035135]-------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	/* 노드가 없는 경우 */
	if(h->rlink == h)
	{
		free(h);
		return 1;
	}
	/* 노드가 있는 경우 */
	listNode* p = h->rlink;
	listNode* prev = NULL;

	/* list를 탐색하여 하나씩 할당 해제 */
	while(p != NULL && p != h){
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	/* list초기화 되지 않으면 return -1 */
	if(h == NULL) return -1;

	/* 새로운 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/* 노드가 없는 경우 */
	if(h->rlink == h)
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}
	/* 노드가 있는 경우 마지막에 연결 */
	else
	{
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	/* list가 초기화되지 않거나 노드가 없는 경우 */
	if(h->llink == h || h==NULL)
	{
		printf("nothing to delete. \n");
		return 1;
	}
	/* 제허라 노드 설정 */
	listNode* nodetoremove = h->llink;
	/* link정리 후 노드 할당 해제 */
	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;
	free(nodetoremove);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	/* 새로운 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/* link 정리 */
	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	/* lisk가 초기화되지 않거나 노드가 없는 경우 */
	if(h == NULL || h->rlink == h)
	{
		printf("nothing to delete. \n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;

	/* link 정리 */
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;
	/* node wprj */
	free(nodetoremove);

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	/* list가 초기화되지 않거나 비어있는 경우 */
	if(h->rlink == h || h==NULL)
	{
		printf("nothing to invert..\n");
		return 0;
	}

	listNode* n = h->rlink;
	listNode* tail = h;
	listNode* middle = h;

	/* list link 역순으로 배치 */
	h->llink = h->rlink;
	while(n!=NULL && n != h){
		tail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = tail;
		middle->llink = n;
	}
	
	h->rlink = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	/* list가 초기화되지 않으면 */
	if(h==NULL)return -1;

	/* 새로운 노드 생성 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/* 초기화되고 노드가 없는 경우 */
	if(h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	/* 리스트를 검색하여, 입력받은 key보다 큰 값 탐색 */
	listNode* n = h->rlink;
	while(n != NULL && n != h){
		/* 입력한 key보다 큰 경우 */
		if(n->key >= key){
			/* 큰 노드가 첫 번째 노드인 경우 */
			if(n == h->rlink){
				insertFirst(h, key);
			}
			/* 중간이나 마지막인 경우 */
			else{
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}
		n = n->rlink;
	}
	insertLast(h,key);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	/* list가 초기화되지 않거나 노드가 없는 경우 */
	if(h->rlink == h || h==NULL){
		printf("nothing to delete.\n");
		return 0;
	}
	/* list에서 동일한 key를 탐색 */
	listNode* n = h->rlink;
	while(n != NULL && n !=h){
		if(n->key == key){
			/* 첫 번째 노드인 경우 */
			if(n == h->rlink){
				deleteFirst(h);
			}
			/* 마지막 노드인 경우 */
			else if(n->rlink == h){
				deleteLast(h);
			}
			/* 중간 노드인 경우 */
			else{
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}
		n = n->rlink;
	}
	/* 동일한 key를 가진 노드가 없는 경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


