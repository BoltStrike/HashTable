#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
//might need srand
using namespace std;

struct name { //struct for students which will be hashed
  char fname [80];//all student info
  char lname [80];
  int id;
  float gpa;
};

name* addStu(name*, int, int&);
int hashFunc(name, int);


int main() {
  name* hashtable = new name[100];
  int id = 100000;
  cout << "Welcome to Student Hashtable" << endl;
  while(true) {
    cout << "Please input one of the following: add, search, print, or quit" << endl;
    char* input;
    cin >> input;
    if (strcmp(input, "add") == 0) {
      cout << "Please input how many students to add" << endl;
      int adding;
      cin >> adding;
      hashtable = addStu(hashtable, adding, id);
    }
    
  }
}

name* addStu(name* hashtable, int numToAdd, int& idIncr) {
  for(int i = 0; i < numToAdd; i++) {
    name toAdd;

    //Firstname Randomization
    cout << "Please input the file to select firstname from" << endl;
    char filename[80];//for name of file
    cin.ignore();//ignores past cin
    cin.getline(filename, 80);//takes in the name
    ifstream newFile; //new file
    newFile.open(filename);//opens file with the name put in
    if (newFile == NULL) {//if file doesn't exist
      cout << "There was an error reading the file" << endl;
      return hashtable;
    }
    else {
      int iter = rand() % 100; //number from 0 - 99
      char s [80]; //will hold number in char array
      for (int j = 0; j <= iter; j++) {
	if (newFile.eof() != true) {//while not end of file
	  newFile.getline(s, 80, ',');//gets line splitting over comma
	}
	else { //redundancy
	  break;
	}
      }
      strcpy(toAdd.fname,s);
    }
    newFile.close();//closes file

    //Lastname Randomization
    cout << "Please input the file to select lastname from" << endl;
    char filename1[80];//for name of file
    cin.ignore();//ignores past cin
    cin.getline(filename1, 80);//takes in the name
    ifstream newFile1; //new file
    newFile1.open(filename1);//opens file with the name put in
    if (newFile1 == NULL) {//if file doesn't exist
      cout << "There was an error reading the file" << endl;
      return hashtable;
    }
    else {
      int iter = rand() % 100; //number from 0 - 99
      char s [80]; //will hold number in char array
      for (int j = 0; j <= iter; j++) {
	if (newFile.eof() != true) {//while not end of file
	  newFile.getline(s, 80, ',');//gets line splitting over comma
	}	
	else { //redundancy
	  break;
	}
      }
      strcpy(toAdd.lname,s);
    }
    newFile1.close();//closes file

    //Increments id
    idIncr ++;
    toAdd.id = idIncr;
    //Will have hash function

    //Randomize GPA
    double ingpa = (double)(rand() % 6)/(rand() % 100 + 1);
    toAdd.gpa = ingpa;
  }
  return hashtable;
}
