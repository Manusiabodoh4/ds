#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int length = 0;

struct NODE {
	char name[100];
	int weight;
	
	NODE* next;
	NODE* prev;
}*head, *tail;

void cls() {
	for(int i = 0 ; i < 30 ; i++) {
		printf("\n");
	}
}

NODE* createNode(char name[], int weight) {
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	strcpy(temp->name, name);
	temp->weight = weight;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

void pushHead(char name[], int weight) {
	NODE* temp = createNode(name, weight);
	if(!head) {
		head = tail = temp;
	} else {
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	head->prev = NULL;
	tail->next = NULL;
	length++;
}

void popHead() {
	if(!head) {
		printf("no data");
	} else {
		if(head == tail) {
			free(head);
			head = tail = NULL;
		} else {
			NODE* temp = head;
			head = head->next;
			free(temp);
			head->prev = NULL;
		}
		length--;
	}
}

void menu() {
	printf(" BLUE RICE STOCK\n");
	printf(" ^^^^^^^^^^^^^^^\n");
	printf("\n");
	printf(" Rice Stock <STACK>\n");
	printf("\n");
	
	NODE* temp = head;
	while(temp) {
		printf("[ %-17s| %-3d kg(s) ]", temp->name, temp->weight);
		if(temp == head) {
			printf(" -> [top]");
		}
		printf("\n");
		temp = temp->next;
	}
	printf("\n");
	printf(" Option :\n");
	printf(" 1. Stock Rice Sack\n");
	printf(" 2. Sell Rice Sack\n");
	printf(" 3. Exit\n");
	printf("\n");
	printf(" >> Input choice : ");
}

void stock() {
	cls();
	if(length == 10) {
		printf(" --- The Rice Storage is Full --- ");
		getchar();
		return;
	}
	
	char name[100];
	int weight;
	
	do {
		printf(" Input Rice Type [long/medium/short] grain: ");
		scanf("%[^\n]", name);
		while(getchar() != '\n');	
	}while(strcmp(name, "long") != 0 && strcmp(name, "medium") != 0 && strcmp(name, "short") != 0);
	
	do {
		printf(" Input Weight of the Rice Sack [10..100 kg(s)]: ");
		scanf("%d", &weight);
		while(getchar() != '\n');
	}while(weight < 10 || weight > 100);
	
	strcat(name, " grain");
	pushHead(name, weight);
	printf("\n\n\n --- Add Rice Sack Success ---\n");
	getchar();
}

void sell() {
	if(!head) {
		printf(" --- The Rice Storage is Empty ---");
		getchar();
		return;
	}
	popHead();	
	printf("\n\n\n --- Sell Rice Sack Success ---\n");
	getchar();
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
				stock();
				break;
				
			case 2:
				sell();
				break;
				
			case 3:
				while(head) {
					popHead();
				}
				return 0;
		}
	}
	
	return 0;
}
