#include <iostream>
#include <string>

using namespace std;

int sizeNum = 0;

string separator(string num){

  sizeNum = num.length();    

  int numSeparator = 0;

  if(sizeNum < 4) return num;

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
  return num;
}

string matchNum(char num){
  switch (num){
    case '1':
      return "Satu";
      break;  
    case '2':
      return "Dua";
      break;  
    case '3':
      return "Tiga";
      break;  
    case '4':
      return "Empat";
      break;  
    case '5':
      return "Lima";
      break;  
    case '6':
      return "Enam";
      break;  
    case '7':
      return "Tujuh";
      break;  
    case '8':
      return "Delapan";
      break;  
    case '9':
      return "Sembilan";
      break;    
  }  
  return "";
}

string matchSatuan(int simbol){
  switch (simbol){
    case 1:
      return "";
      break;
    case 2 :      
      return "Puluh";
      break;
    case 3 :
      return "Ratus";
      break;    
  }
  return "";
}

string matchSatuanLanjutan(int simbol){
  switch (simbol){
    case 1:
      return "Ribu";
      break;
    case 2 :
      return "Juta";
      break;
    case 3 :
      return "Milyar";
      break;    
    case 4 :
      return "Trilyun";
      break;
  }
  return "";
}

int main(){

  int lengStr = 100;
  int valueStr = 0;

  string stread[lengStr];  

  string num = "";

  cout << "Masukan nilai : ";
  cin >> num;

  string resNum = separator(num);    

  int satuan = 1;
  int satuanLanjutan = 0;

  string strBilangan = "";
  string strSatuan = "";
  string strSatuanLanjutan = "";
  
  int i = sizeNum-1;

  while(i>=0){
    char ch = resNum.at(i);    
    if(ch != '0'){
      strBilangan = matchNum(ch);
      strSatuan = matchSatuan(satuan);
      if(strBilangan == "Satu" && strSatuan == "Puluh"){
        strBilangan = "";
        strSatuan = "Belas";        
      }
      strSatuanLanjutan = matchSatuanLanjutan(satuanLanjutan);
      if(strSatuanLanjutan != ""){        
        satuanLanjutan = 0;
      }      
      stread[valueStr] = strBilangan+" "+strSatuan+" "+ strSatuanLanjutan;
      valueStr++;      
    }
    if(ch == '.'){
      satuanLanjutan++;
      satuan = 0;
    }    
    satuan++;
    i--;
  }  

  bool statusRenderBelas = true;
  int indexBlocked = -1;

  for(int j=valueStr;j>=0;j--){    

    if(stread[j].find("Belas") == 1 && statusRenderBelas){       
      statusRenderBelas = false;
      string tempStread =  stread[j-1];
      int lengStread = tempStread.length(); 
      for(int v=0;v<lengStread;v++){
        if(tempStread.at(v) == ' '){                                                            
          tempStread.insert(v, 1, 's');          
          tempStread.insert(v, 1, 'a');
          tempStread.insert(v, 1, 'l');
          tempStread.insert(v, 1, 'e');
          tempStread.insert(v, 1, 'B');
          tempStread.insert(v, 1, ' ');
          cout << tempStread << "";
          break;
        }
      }      
      indexBlocked = j-1;
      continue;  
    }    
    
    if(indexBlocked == j) continue;

    cout << stread[j] << "";

  }  

  cout << "Rupiah \n";

  return 0;
}