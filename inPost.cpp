#include<stdio.h>
#include <string.h>
#include <stdlib.h>

struct Stack{
  int top;
  int cap;
  int* array;
};

struct Stack* createStack(int cap){
  struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
  if (!stack) return NULL; 
  stack->top = -1;
  stack->cap = cap;
  stack->array = (int*) malloc(stack->cap * sizeof(int));
  return stack;
}

bool isEmpty(struct Stack* stack){
  return stack->top == -1;
}

char getCharInArray(struct Stack* stack){
  int tempTop = stack->top;
  return stack->array[tempTop];
}

char pop(struct Stack* stack){
  if(!isEmpty(stack)){    
    char tempChar = stack->array[stack->top];
    stack->top--;
    return tempChar;
  }
  return '$';
}

void push(struct Stack* stack, char op){
  stack->top++;
  stack->array[stack->top] = op;
}

bool isOperand(char ch){
  if(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z'){
    return true;
  }
  return false;
}

int isPriority(char ch){
  if(ch == '(')
        return 0;
  if(ch == '+' || ch == '-')
      return 1;
  if(ch == '*' || ch == '/')
      return 2;
  return 0;
}

int main(){

  char exp[100];
  char *e, x;
  
  printf("Enter the expression : ");
  scanf("%s",exp);
  printf("\n");

  e = exp;

  struct Stack* stack = createStack(strlen(exp));

  while(*e != '\0'){    
    
    if(isOperand(*e)){
      printf("%c ",*e);
    }

    else if(*e == '('){
      push(stack, *e);
    }

    else if(*e == ')'){
      x = pop(stack);
      while (x != '('){
        printf("%c ", x);
      }      
    }

    else{
      while(isPriority(stack->array[stack->top] >= isPriority(*e))){
        printf("%c ",pop(stack));
      }
      push(stack, *e);
    }

    e++;

  }

  while(stack->top != -1){
    printf("%c ",pop(stack));
  }

  return 0;
}