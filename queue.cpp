#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct NODE {
	char name[100];
	NODE* next;
	NODE* prev;
}*head, *tail;

void cls() {
	for(int i = 0 ; i < 30 ; i++) {
		printf("\n");
	}
}

NODE* createNode(char name[]) {
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	strcpy(temp->name, name);
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

void pushHead(char name[]) {
	NODE* temp = createNode(name);
	if(!head) {
		head = temp;
		tail = temp;
	} else {
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	head->prev = NULL;
	tail->next = NULL;
}

void pushTail(char name[]) {
	NODE* temp = createNode(name);
	if(!head) {
		pushHead(name);
	} else {
		temp->prev = tail;
		tail->next = temp;		
		tail = temp;
	}
	head->prev = NULL;
	tail->next = NULL;
}

void popHead() {
	if(!head) {
		printf(" Nobody here");
	} else {
		if(head == tail) {
			free(head);
			head = tail = NULL;
		} else {
			NODE* temp = head;
			head = head->next;
			temp->next = NULL;
			free(temp);
			head->prev = NULL;
		}
	}
}

void menu() {
	printf(" =============\n");
	printf(" Queue Manager\n");
	printf(" =============\n");
	printf("\n");
	
	if(head) {
		printf(" Next in queue : %s\n", head->name);
	} else {
		printf(" *Nobody in queue*\n");
	}
	printf("\n");
	printf(" 1. Add person to queue\n");
	printf(" 2. Serve next person\n");
	printf(" 3. Exit\n");
	printf(" Choose: ");
}

void addQueue() {
	char name[100];
	
	printf(" Input Person Name : ");
	scanf("%[^\n]", name);
	while(getchar() != '\n');
	
	pushTail(name);
	printf(" Person added to queue\n");
	getchar();
}

void serve() {
	if(!head) {
		printf(" Nobody in queue\n");
		getchar();
		return;
	}
	printf(" %s has been served", head->name);
	popHead();
	getchar();
}

void popall() {
	NODE *temp = head;
	while(head) {
		head = head->next;
		free(temp);
		temp = head;
	}
	head = tail = NULL;
	printf("all data has been cleared\n");
}

int main() {
	int selection;
	
	while(true) {
		cls();
		menu();	
		scanf("%d", &selection);
		while(getchar() != '\n');
		
		switch(selection) {
			case 1:
				addQueue();
				break;
				
			case 2:
				serve();
				break;
				
			case 3:
				cls();
				popall();
				printf("bye bye :)");
				return 0;
		}
	}
}
