#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int sizeHashTable = 100;
const int MR[3] = {'M', 'r', '.'};
const int MRS[4] = {'M', 'r', 's', '.'};

int sizeArray = 0;

struct Book{
  char* bookId;
  char* nameBook;
  char* authorName;
  char* ISBN;
  int totalPage;
};

struct Search{
  bool isFound;
  int key;
  struct Book data;
};

struct Book book[sizeHashTable];

//convert int to string
char* itos(int data){
  char *text = (char*) malloc(10);   
  snprintf(text, 10, "%d", data);    
  return text;
}

char* generateId(char* ISBN, char* author, char* title){
  
  char *num = (char*) malloc(10);
  char *result = (char*) malloc(50);

  strcpy(num, itos(sizeArray+1));

  
  int len = strlen(num);
  int loopGenerate = 5 - len;

  strcat(result, "B");  

  for(int i=0;i<loopGenerate;i++){
    strcat(result, "0");
  }

  strcat(result, num);
  strcat(result, "-");
  strcat(result, ISBN);  
  strcat(result, "-");

  int lenAuthor = strlen(author);

  for(int i=0;i<lenAuthor;i++){
    if(author[i] == ' '){
      strncat(result, &author[i+1], 1);
      break;
    }
  }

  strncat(result, &title[0], 1);  

  return result;  

}

int hashFunction(char *bookId){
  int len = strlen(bookId);
  int asci = 0;
  for(int i=0;i<len;i++){
    asci+= (int) bookId[i];
  }
  return asci % sizeHashTable;
}

bool validateNumeric(char* data){
  int len = strlen(data);
  for(int i=0;i<len;i++){
    int asci = (int) data[i];
    if(asci >= 48 && asci <= 57){
      return true;
    }
  }
  return false;
}

bool validateRange(char* data, int min, int max){
  int len  = strlen(data);
  if(len >= min && len <= max) return true;
  return false;
}

bool validateMax(int* data, int max){
  if(*data <= max) return true;
  return false;
}

bool validateMin(int* data, int min){
  if(*data >= min) return true;
  return false;
}

bool validate(int* data, int min, int max){
  if(validateMin(data, min) && validateMax(data, max)) return true;
  return false;
}

bool validate(char* data, int min, int max){
  
  int len = (int) strlen(data);  
  
  int lengKarakter = 0;

  bool isSpace = false;  
  bool isMr = true;
  bool isMrs = true;

  for(int i=0;i<len;i++){

    char c = data[i];
    int asci = (int) c;

    //printf("Asci : %d\n", asci);
    
    if(!isSpace && asci == 32){
      //printf("Masuk ke IF\n");
      isSpace = true;
      continue;
    }
    if(!isSpace && i < 3){      
      //printf("Mr: %c = Data: %c\n", MR[i], c);
      if(MR[i] != c) isMr = false;
    }
    if(!isSpace && i < 4){      
      //printf("Mrs: %c = Data: %c\n", MRS[i], c);
      if(MRS[i] != c) isMrs = false;
    }
    if(isSpace) lengKarakter++;
  }

  //printf("Leng Karakter : %d\n", lengKarakter);

  bool resRange = validate(&lengKarakter, min, max);

  //printf("Validate Range : %d\n",resRange);
  //printf("Validate Mr Mrs : %d %d\n", isMr, isMrs);

  return (isMr||isMrs) && resRange;

}

bool search(char* bookTitle){
  if(sizeArray == 0) return false;
  for(int i=0;i<sizeHashTable;i++){
    struct Book tm = book[i];      
    if(tm.bookId == NULL) continue;

    if(strcmp(tm.nameBook, bookTitle) == 0){
      return true;
    }
  }
  return false;
}

Search searchBookId(char *id){
  struct Search newSearch;
  int index = hashFunction(id);
  struct Book dataFound = book[index];
  if(strlen(dataFound.bookId) == 0){
    newSearch.isFound = false;    
  }else{
    newSearch.isFound = true;    
  }
  newSearch.key = index;
  newSearch.isFound = true;
  newSearch.data = dataFound;
  return newSearch;
}

void menu1(){

  if(sizeArray == 0) {
    printf("\nThere is no book \n\n");    
    return;
  }

  for(int i=0;i<sizeHashTable;i++){
    if(book[i].bookId == NULL) continue;
    printf("\n");
    printf("BookId : %s\n", book[i].bookId);
    printf("Title Book : %s\n", book[i].nameBook);
    printf("Author Name : %s\n", book[i].authorName);
    printf("ISBN : %s\n", book[i].ISBN);
    printf("Total Page : %d\n", book[i].totalPage);
    printf("\n");
  }

}

void menu2(){

  struct Book *tm = (struct Book*) malloc(sizeof(Book));

  char* bookTitle = (char*) malloc(55*sizeof(char));
  char* authorName = (char*) malloc(55*sizeof(char));
  char* ISBN = (char*) malloc(55*sizeof(char));
  int totalPage;

  char enter;

  printf("\n");

  while(true){  
    scanf("%c", &enter);
    printf("Input book title [unique] : ");    
    scanf("%[^\n]s", bookTitle);    
    if(!search(bookTitle)){      
      break;
    }
  }

  while(true){
    scanf("%c", &enter);
    printf("Input author name [3-25] [Mr. ] [Mrs. ] : ");    
    scanf("%[^\n]s", authorName);            
    if(validate(authorName, 3, 25)){      
      break;
    }
  }

  while(true){  
    scanf("%c", &enter);
    printf("Input ISBN [10-13][numeric] : ");    
    scanf("%[^\n]s", ISBN);
    if(validateRange(ISBN, 10, 13)&&validateNumeric(ISBN)){      
      break;
    }
  }

  while(true){  
    scanf("%c", &enter);
    printf("Input page number [>=16] : ");    
    scanf("%d", &totalPage);
    if(validateMin(&totalPage, 16)){      
      break; 
    }
  }  

  tm->bookId = generateId(ISBN, authorName, bookTitle);
  
  tm->authorName = (char*) malloc(55*sizeof(char));
  tm->ISBN = (char*) malloc(55*sizeof(char));
  tm->nameBook = (char*) malloc(55*sizeof(char));

  strcpy(tm->authorName, authorName);
  strcpy(tm->ISBN, ISBN);
  strcpy(tm->nameBook, bookTitle);  
  tm->totalPage = totalPage;

  book[hashFunction(tm->bookId)] = *tm;

  sizeArray++;

  printf("\n\n");

}

void menu3(){

  char* id = (char*) malloc(25*sizeof(char));

  printf("\n");

  if(sizeArray == 0){
    printf("Book List Empty\n\n");  
    return;
  }

  while(true){    
    printf("Input Book id to delete : ");    
    scanf("%s", id);
    if(strlen(id) == 0) continue;
    struct Search resSearch = searchBookId(id);
    if(resSearch.isFound == false){
      printf("Book id not found\n\n");  
      break;
    }
    book[resSearch.key] = {};
    printf("Book id success delete\n\n");
    sizeArray--;
    break;
  }  

}

int main(){

  int menu;
  void (*func_ptr[])() = {menu1, menu2, menu3};

  //validate("Mr. Reza", 3, 25);

  while(true){    
    
    printf(" Bluejack Libary \n");
    printf(" 1. View Book \n");
    printf(" 2. Insert Book \n");
    printf(" 3. Remove Book \n");
    printf(" 4. Exit \n");
    printf("\n");
    printf(">> ");
    scanf("%d", &menu);

    if(menu == 4) break;
    if(menu < 1 && menu > 4) continue;

    (*func_ptr[menu-1])();

  }

  return 0;
}