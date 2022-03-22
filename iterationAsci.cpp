#include <iostream>
#include <string>

using namespace std;

void convertIteration(int iteration, string nilaiAwal){
  
  int satuan = int(nilaiAwal.at(3));
  int puluhan = int(nilaiAwal.at(2));
  int ratusan = int(nilaiAwal.at(1));
  int ribuan = int(nilaiAwal.at(0));

  for(int i=0;i<iteration;i++)  {

    cout << char(ribuan) << char(ratusan) << char(puluhan) << char(satuan) << "\n";    

    if(satuan >= 49 && satuan < 57 || satuan >= 65 && satuan < 90){
      satuan++;      
    }else if(satuan == 57){
      satuan = 65;
    }else if(satuan == 90){
      satuan = 49;
      if(puluhan >= 49 && puluhan < 57 || puluhan >= 65 && puluhan < 90){
        puluhan++;
      }else if(puluhan == 57){
        puluhan = 65;        
      }else if(puluhan == 90){
        puluhan = 49;
        if(ratusan >= 49 && ratusan < 57 || ratusan >= 65 && ratusan < 90){
          ratusan++;          
        }else if(ratusan == 57){
          ratusan = 65;
        }else if(ratusan == 90){
          ratusan = 49;
          if(ribuan >= 49 && ribuan < 57 || ribuan >= 65 && ribuan < 90){
            ribuan++;
          }else if(ribuan == 57){
            ribuan = 65;
          }else if(ribuan == 90){
            break;
          } 
        } 
      }
    }

  }

}

int main(){
  
  int iteration = 0;
  string nilaiAwal = "";

  cout << "Masukan nilai awal = ";
  cin >> nilaiAwal;
  
  cout << "Masukan nilai iteration = ";
  cin >> iteration;

  convertIteration(iteration, nilaiAwal);

  return 0;
}