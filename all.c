#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Tree.h"

typedef enum { FALSE, TRUE } BOOL;

typedef const char* TreeType;

typedef struct listNode
{
	struct treeNode* data;
	struct listNode* next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}List;

typedef struct treeNode
{
	TreeType data;
	List sons;
} TreeNode;



//List Functions Prototypes
void insertDataToEndList(List* lst, TreeNode* data);
ListNode* creatNewListNode(TreeNode* data, ListNode* next);
void insertNodeToEndList(List* lst, ListNode* node);
BOOL isEmpty(List* lst);
void makeEmptyList(List *lst);
void checkMemoryAllocation(void *ptr);

TreeNode *findParentInSonsList(List *lst, TreeType data);
TreeNode *findParentInSonsListHelper(ListNode *node, TreeType data);




//Tree Functions Prototypes
TreeNode* createNewTreeNode(TreeType data);
void addSons(TreeNode* root, TreeType data, ...);
List* findSonsListInTree(TreeNode* root, TreeType data);
int doesTreeNodeHasSons(int num);
void saveTreeToFile();
void printTree(TreeNode* root);
int countNodes(TreeNode* root);
int coundNodesIf(TreeNode* root, int foo(int));
void freeTree(TreeNode* root, int num);
TreeNode* loadTreeFromFile(char* binFileName);

void main()
{
	{
		TreeNode* family = createNewTreeNode("a1");

		addSons(family, "a1", "b1", NULL);
		addSons(family, "a1", "b2", "b3", NULL);

		addSons(family, "b1", "c1", "c2", NULL);

		addSons(family, "b3", "d1", "d2", "d3", NULL);
		addSons(family, "b3", "d4", NULL);

		addSons(family, "d3", "e1", NULL);
		addSons(family, "e1", "f1", "f2", NULL);

		saveTreeToFile(family, "family.bin");

		printTree(family);

		printf("\nNum of nodes: %d\n", countNodes(family));
		printf("Num of nodes with sons: %d\n", coundNodesIf(family, doesTreeNodeHasSons));

		freeTree(family, FALSE);
	}


	{
		TreeNode* family = loadTreeFromFile("family.bin");
		printf("\n");
		printTree(family);
		printf("\nNum of nodes: %d\n", countNodes(family));
		printf("Num of nodes with sons: %d\n", coundNodesIf(family, doesTreeNodeHasSons));

		freeTree(family, TRUE); // need to free strings as well!
	}

	system("pause");
}//main


TreeNode* createNewTreeNode(TreeType data)
{
	int length;
	TreeNode* newNode = (TreeNode*)calloc(1, sizeof(TreeNode));

	//there is a name to tree type
	if (data != NULL)
	{
		length = strlen(data);	//get the string length
		newNode->data = (TreeType)calloc(length + 1, sizeof(char));
		newNode->data = data;

	}
	//there isn't a tree type name

	else
	{
		newNode->data = NULL;
	}

	makeEmptyList(&newNode->sons);

	return newNode;
}//createNewTreeNode

void addSons(TreeNode* root, TreeType data, ...)
{
	TreeNode* temp;
	List* tempList;
	va_list sons;
	TreeType tempName;
	va_start(sons, data);

	//the parent isn't "a1"
	if (!(strcmp(root->data, data) == 0))
		//finding sons list in the tree
		tempList = findSonsListInTree(root, data);

	else
	{
		tempList = &(root->sons);
	}

	tempName = va_arg(sons, TreeType);

	while (tempName != NULL)
	{
		temp = createNewTreeNode(tempName);
		insertDataToEndList(tempList, temp);

		tempName = va_arg(sons, TreeType);

	}//while

	va_end(sons);


}//addSons

List* findSonsListInTree(TreeNode* root, TreeType data)
{
	TreeNode* temp;
	temp = findParentInSonsList(&root->sons, data);
	
	return &temp->sons;

}//findSonsListInTree



TreeNode *findParentInSonsList(List *lst, TreeType data)
{
	return findParentInSonsListHelper(lst->head, data);

}//findParentInSonsList

TreeNode *findParentInSonsListHelper(ListNode *node, TreeType data)
{
	TreeNode *item;

	if (node == NULL)
		return NULL;
	else if (strcmp(node->data->data, data) == 0)
		return node->data;


	item = findParentInSonsListHelper(node->next, data);
	if (item != NULL)
		return item;
	else
		return findParentInSonsList(&node->data->sons, data);

}//findParentInSonsListHelper


void insertDataToEndList(List* lst, TreeNode* data)
{
	ListNode* tail;
	tail = creatNewListNode(data, NULL);
	insertNodeToEndList(lst, tail);

}//insertDataToEndList

 //create a new list node
ListNode* creatNewListNode(TreeNode* data, ListNode* next)
{
	ListNode* node;

	//memory allocating the new node values
	node = (ListNode*)malloc(sizeof(ListNode));
	checkMemoryAllocation((ListNode*)node);

	//insert values to node
	node->data = data;
	node->next = next;

	return node;
}//creatNewListNode

void insertNodeToEndList(List* lst, ListNode* node)
{
	if (isEmpty(lst) == TRUE)
		lst->head = lst->tail = node;
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}//else

	lst->tail->next = NULL;

}//insertNodeToEnList

 //check if a list is empty
BOOL isEmpty(List* lst)
{
	return lst->head == NULL;
}//isEmpty

 //recieves a list pointer and reset it to NULL
void makeEmptyList(List* lst)
{
	lst->head = lst->tail = NULL;

}//makeEmptyList



 //check if memory allocation si valid
void checkMemoryAllocation(void *ptr)
{

	if (ptr == NULL)
	{
		puts("Terminating the program! A memory allocation error has been detected.\n");
		exit(1);
	}
}//checkMemoryAllocation

int doesTreeNodeHasSons(int num)
{
	return 0;
}
void saveTreeToFile()
{
	;
}

void printTree(TreeNode* root)
{
	;
}

int countNodes(TreeNode* root)
{
	return 0;
}
int coundNodesIf(TreeNode* root, int foo(int))
{
	return 0;
}

void freeTree(TreeNode* root, int num)
{
	;
}
TreeNode* loadTreeFromFile(char* binFileName)
{
	return NULL;
}