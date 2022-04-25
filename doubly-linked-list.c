/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- 2021041018  장예서 -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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

/**
 * 헤드 노드를 변경해야 하므로 이중 포인터 사용
 */
int initialize(headNode** h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제한다.
	 */
	listNode* p = h->first;
	while (p != NULL) {
		free(p->llink);
		if (p->rlink == NULL)
			free(p);
			break;
		p = p->rlink;
	}
	free(h);

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	/* 리스트가 정의되지 않은 경우 */
	if (h == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = NULL;
	node->rlink = NULL;
	node->key = key;

	/* 리스트가 빈 경우 */
	if (h->first == NULL) {
		printf("빈 리스트에 처음으로 추가됩니다.\n");
		h->first = node;
	}
	/* 리스트가 비지 않은 경우 */
	else {
		listNode* p = h->first;
		while (p->rlink != NULL) {
			p = p->rlink;
		}
		p->rlink = node;
		node->llink = p;
	}

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	/* 리스트가 빈 경우 */
	if (h->first == NULL) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	listNode* p = h->first;
	listNode* trail = NULL;

	/* 마지막 노드 = 첫번째 노드인 경우 first에 NULL 대입하고 삭제 */
	if (p->rlink == NULL) {
		h->first = NULL;
	}
	/** 그렇지 않은 경우 마지막 노드까지 이동
	 * 이전 노드의 rlink에 NULL 대입하고 삭제 */
	else {
		while (p->rlink != NULL) {
			trail = p;
			p = p->rlink;
		}
		trail->rlink = NULL;
	}
	free(p);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	/* 리스트가 정의되지 않은 경우 */
	if (h == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = NULL;
	node->rlink = NULL;
	node->key = key;
	
	/* 리스트가 빈 경우 */
	if (h->first == NULL) {
		h->first = node;
	}
	/** 리스트가 비지 않은 경우
	 * first, 기존 첫 번째 노드 llink에 노드 주소 대입
	 * 노드의 rlink에 기존 첫 번째 노드 주소 대입 */
	else {
		listNode* p = h->first;
		h->first = node;
		p->llink = node;
		node->rlink = p;
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/* 리스트가 빈 경우 */
	if (h->first == NULL) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	listNode* p = h->first;
	/* 처음이자 마지막 노드일 경우 first에 NULL 대입하고 삭제 */
	if (p->rlink == NULL)
		h->first = NULL;
	/** 그렇지 않은 경우 first에 다음 노드의 주소 대입
	 * 다음 노드의 llink에 NULL 대입하고 삭제 */
	else {
		h->first = p->rlink;
		p->rlink->llink = NULL;
	}
	free(p);

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	/* 리스트가 정의되지 않은 경우 */
	if (h == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}
	/* 리스트가 빈 경우 */
	if (h->first == NULL) {
		printf("리스트가 비었습니다.\n");
		return 1;
	}

	listNode* p = h->first;
	listNode* temp = NULL;
	/** p가 NULL이 될 때까지 아래 과정 반복
	 * 마지막에는 first에 기존 마지막 노드 주소 대입 */
	while (p != NULL) {
		temp = p->llink;
		p->llink = p->rlink;
		p->rlink = temp;
		temp = p;
		p = p->llink;
	}
	h->first = temp;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	/* 정의되지 않은 경우 */
	if (h == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = NULL;
	node->rlink = NULL;
	node->key = key;

	/* 리스트가 빈 경우 */
	if (h->first == NULL) {
		printf("빈 리스트에 처음으로 추가됩니다.\n");
		h->first = node;
		return 0;
	}

	listNode* p = h->first;
	listNode* trail = NULL;

	/** 첫 번째 노드 앞쪽에 삽입될 경우
	 * first와 기존 첫 번째 노드의 llink에 노드 주소를 대입
	 * 노드의 rlink에 기존 첫 번째 노드의 주소 대입 */
	if (p->key >= key) {
		h->first = node;
		node->rlink = p;
		p->llink = node;
	}
	/** 중간이나 마지막에 삽입될 경우
	 * 이전 노드의 rlink, 다음 노드의 llink에 노드 주소를 대입
	 * 노드의 llink에 이전 노드, rlink에 다음 노드 주소를 대입 */
	else {
		do {
			trail = p;
			p = p->rlink;
			/** 마지막까지 더 큰 key 값을 가진 노드가 없을 경우 
			 * 마지막 노드의 rlink에 노드 주소를, 노드의 llink에 마지막 노드 주소를 대입 */
			if (p == NULL) {
				printf("노드가 리스트의 마지막에 추가됩니다.\n");
				trail->rlink = node;
				node->llink = trail;
			}
			else if (p->key >= key) {
				trail->rlink = node;
				node->llink = trail;
				node->rlink = p;
				p->llink = node;
				break;
			}
		} while (p != NULL);
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	/* 리스트가 빈 경우 */
	if (h->first == NULL) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	listNode* p = h->first;

	/** 해당 노드가 첫 번째 노드일 경우 first에 다음 노드 주소 대입
	 * 다음 노드의 llink에 NULL 대입하고 노드 삭제 */
	if (p->key == key) {
		h->first = p->rlink;
		/* 첫 번째이자 마지막 노드일 경우 그냥 노드 삭제 */
		if (p->rlink == NULL) {
			free(p);
			return 1;
		}
		p->rlink->llink = NULL;
		free(p);
	}
	/** 해당 노드가 중간이나 마지막 노드일 경우 
	 * 해당 노드를 발견할 때까지 이동
	 * 발견하면 이전 노드의 rlink에 다음 노드 주소 대입,
	 * 다음 노드의 llink에 이전 노드 주소 대입하고 삭제 */
	else {
		while (p != NULL) {
			if (p->key == key) {
				p->llink->rlink = p->rlink;
				/* 해당 노드가 마지막 노드일 경우 그냥 노드 삭제 */
				if (p->rlink == NULL) {
					free(p);
					return 1;
				}
				p->rlink->llink = p->llink;
				free(p);
				return 1;
			}
			p = p->rlink;
		}
		/* 해당 노드가 없을 경우 */
		printf("해당하는 노드가 없습니다.\n");
	}

	return 1;
}


