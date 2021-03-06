#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
  string outputFileName = "output1.txt";
  string answerFileName = "test1.txt";
  int line = 1;
  string oline;
  string aline;
  bool pass = true;
  ifstream outputFile, answerFile;
  outputFile.open(outputFileName.c_str());
  answerFile.open(answerFileName.c_str());

  while (true){
    getline(outputFile, oline);
    getline(answerFile, aline);
  
    if (outputFile.eof() || answerFile.eof() )
      break;

    if (oline != aline) {
      cout << "-------------" << endl;
      cout << "Fail at line " << line << endl;
      cout << "output: " << oline << endl;
      cout << "expected: " << aline << endl;
      cout << "-------------" << endl;
      pass = false;
    }
  line++;
  }  
  if (pass){
    cout << "PASS" << endl;
  }

  outputFile.close();
  answerFile.close();
}
