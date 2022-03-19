#include <iostream>
#include <string>

using namespace std;

int main(){

  string num = "";

  cout << "Masukan nilai = ";
  cin >> num;

  int sizeNum = num.length();  

  if(sizeNum < 4) {
    cout << "Nilai : "<< num << "\n";  
    return 0;  
  }

  int numSeparator = 0;

  for(int i=sizeNum-1;i>=0;i--){
    if(num.at(i) != '.'){      
      numSeparator++;
    }
    if(numSeparator == 3){ 
      if(num.at(i) != '.'){
        num.insert(i, 1, '.');
      }      
      numSeparator = 0;      
      sizeNum = num.length();
    }
  }

  cout << "Nilai : "<< num << "\n";  

  return 0;
}