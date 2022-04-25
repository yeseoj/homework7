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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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

	printf("[----- 2021041018  �忹�� -----]\n");

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
 * ��� ��带 �����ؾ� �ϹǷ� ���� ������ ���
 */
int initialize(headNode** h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ� */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ѵ�.
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	/* ����Ʈ�� ���ǵ��� ���� ��� */
	if (h == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = NULL;
	node->rlink = NULL;
	node->key = key;

	/* ����Ʈ�� �� ��� */
	if (h->first == NULL) {
		printf("�� ����Ʈ�� ó������ �߰��˴ϴ�.\n");
		h->first = node;
	}
	/* ����Ʈ�� ���� ���� ��� */
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
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	/* ����Ʈ�� �� ��� */
	if (h->first == NULL) {
		printf("����Ʈ�� ������ϴ�.\n");
		return 0;
	}

	listNode* p = h->first;
	listNode* trail = NULL;

	/* ������ ��� = ù��° ����� ��� first�� NULL �����ϰ� ���� */
	if (p->rlink == NULL) {
		h->first = NULL;
	}
	/** �׷��� ���� ��� ������ ������ �̵�
	 * ���� ����� rlink�� NULL �����ϰ� ���� */
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
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	/* ����Ʈ�� ���ǵ��� ���� ��� */
	if (h == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = NULL;
	node->rlink = NULL;
	node->key = key;
	
	/* ����Ʈ�� �� ��� */
	if (h->first == NULL) {
		h->first = node;
	}
	/** ����Ʈ�� ���� ���� ���
	 * first, ���� ù ��° ��� llink�� ��� �ּ� ����
	 * ����� rlink�� ���� ù ��° ��� �ּ� ���� */
	else {
		listNode* p = h->first;
		h->first = node;
		p->llink = node;
		node->rlink = p;
	}
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	/* ����Ʈ�� �� ��� */
	if (h->first == NULL) {
		printf("����Ʈ�� ������ϴ�.\n");
		return 0;
	}

	listNode* p = h->first;
	/* ó������ ������ ����� ��� first�� NULL �����ϰ� ���� */
	if (p->rlink == NULL)
		h->first = NULL;
	/** �׷��� ���� ��� first�� ���� ����� �ּ� ����
	 * ���� ����� llink�� NULL �����ϰ� ���� */
	else {
		h->first = p->rlink;
		p->rlink->llink = NULL;
	}
	free(p);

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	/* ����Ʈ�� ���ǵ��� ���� ��� */
	if (h == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}
	/* ����Ʈ�� �� ��� */
	if (h->first == NULL) {
		printf("����Ʈ�� ������ϴ�.\n");
		return 1;
	}

	listNode* p = h->first;
	listNode* temp = NULL;
	/** p�� NULL�� �� ������ �Ʒ� ���� �ݺ�
	 * ���������� first�� ���� ������ ��� �ּ� ���� */
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



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	/* ���ǵ��� ���� ��� */
	if (h == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = NULL;
	node->rlink = NULL;
	node->key = key;

	/* ����Ʈ�� �� ��� */
	if (h->first == NULL) {
		printf("�� ����Ʈ�� ó������ �߰��˴ϴ�.\n");
		h->first = node;
		return 0;
	}

	listNode* p = h->first;
	listNode* trail = NULL;

	/** ù ��° ��� ���ʿ� ���Ե� ���
	 * first�� ���� ù ��° ����� llink�� ��� �ּҸ� ����
	 * ����� rlink�� ���� ù ��° ����� �ּ� ���� */
	if (p->key >= key) {
		h->first = node;
		node->rlink = p;
		p->llink = node;
	}
	/** �߰��̳� �������� ���Ե� ���
	 * ���� ����� rlink, ���� ����� llink�� ��� �ּҸ� ����
	 * ����� llink�� ���� ���, rlink�� ���� ��� �ּҸ� ���� */
	else {
		do {
			trail = p;
			p = p->rlink;
			/** ���������� �� ū key ���� ���� ��尡 ���� ��� 
			 * ������ ����� rlink�� ��� �ּҸ�, ����� llink�� ������ ��� �ּҸ� ���� */
			if (p == NULL) {
				printf("��尡 ����Ʈ�� �������� �߰��˴ϴ�.\n");
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
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	/* ����Ʈ�� �� ��� */
	if (h->first == NULL) {
		printf("����Ʈ�� ������ϴ�.\n");
		return 0;
	}

	listNode* p = h->first;

	/** �ش� ��尡 ù ��° ����� ��� first�� ���� ��� �ּ� ����
	 * ���� ����� llink�� NULL �����ϰ� ��� ���� */
	if (p->key == key) {
		h->first = p->rlink;
		/* ù ��°���� ������ ����� ��� �׳� ��� ���� */
		if (p->rlink == NULL) {
			free(p);
			return 1;
		}
		p->rlink->llink = NULL;
		free(p);
	}
	/** �ش� ��尡 �߰��̳� ������ ����� ��� 
	 * �ش� ��带 �߰��� ������ �̵�
	 * �߰��ϸ� ���� ����� rlink�� ���� ��� �ּ� ����,
	 * ���� ����� llink�� ���� ��� �ּ� �����ϰ� ���� */
	else {
		while (p != NULL) {
			if (p->key == key) {
				p->llink->rlink = p->rlink;
				/* �ش� ��尡 ������ ����� ��� �׳� ��� ���� */
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
		/* �ش� ��尡 ���� ��� */
		printf("�ش��ϴ� ��尡 �����ϴ�.\n");
	}

	return 1;
}


