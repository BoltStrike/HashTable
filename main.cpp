#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <stdlib.h> //For testing
#include <bits/stdc++.h>
//might need srand
using namespace std;

struct name { //struct for students which will be hashed
  char fname [80];//all student info
  char lname [80];
  int id;
  float gpa;
  name* next = NULL;
};

name** addStu(name**, int, int&, int&);
int hashFunc(int, int);
name** rehash(name**, int&);
void print(name**, int);
void deletehash(name**, int);

string getanyname(string*); //for home testing

int main() {
  name** hashtable = new name*[100];
  int idinc = 100000;
  int size = 100;
  cout << "Welcome to Student Hashtable" << endl;
  while(true) {
    cout << "Please input one of the following: add, search, print, or quit" << endl;
    char* input;
    cin >> input;
    if (strcmp(input, "add") == 0) {
      cout << "Please input how many students to add" << endl;
      int adding;
      cin >> adding;
      hashtable = addStu(hashtable, adding, idinc, size);
    }
    else if (strcmp(input, "print") == 0) {
      print(hashtable, size);
    }
    else if (strcmp(input, "delete") == 0) {
      deletehash(hashtable, size);
    }
    else if (strcmp(input, "quit") == 0) {
      break;
    }
  }
}

name** addStu(name** hashtable, int numToAdd, int& idIncr, int& size) {
  for(int i = 0; i < numToAdd; i++) {
    name* toAdd = new name();
    /*   //Firstname Randomization
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
      strcpy(toAdd -> fname,s);
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
      strcpy(toAdd->lname,s);
    }
    newFile1.close();//closes file */

    //char fnamearray [MAX_NAME_LEN];
    //char lnamearray [MAX_NAME_LEN];
    string fnamestr;
    string lnamestr;

    string* finame = new string[30] {
      "Aidan", 
      "Ellie", 
      "Joe", 
      "Georgie", 
      "Biff",
      "Rory",
      "Elise",
      "Collin",
      "John",
      "Deandre",
      "Megan",
      "Cameron",
      "Olivia",
      "Ethan",
      "Annika",
      "James",
      "Claire",
      "Rohan",
      "Linnea",
      "Jeff",
      "Adriane",
      "Henry",
      "Noel",
      "Jose",
      "Austin",
      "Elizabeth",
      "Jackson",
      "Jordan",
      "Gretchen",
      "Everett"
    };
    
    string* laname = new string[30] {
      "Smith", 
      "Klein", 
      "Johnson", 
      "Purdy", 
      "Li",
      "Price",
      "Larson",
      "Christian",
      "Hernandez",
      "Rosen",
      "Blum",
      "Hamid",
      "Ingraham",
      "Kerry",
      "Hsu",
      "Singh",
      "Brogan",
      "Cole",
      "Kaplan",
      "Warner",
      "Churchill",
      "Lehman",
      "Washington",
      "Lopez",
      "Coleson",
      "Hildebrandt",
      "Peters",
      "Gould",
      "Freiling",
      "McNamee"
    };
    fnamestr = getanyname(finame);
    strcpy(toAdd -> fname, fnamestr.c_str());
    lnamestr = getanyname(laname);
    strcpy(toAdd -> lname, lnamestr.c_str());

    //Increments id
    //cout << "ID bfore: " << idIncr << endl;
    idIncr += 19;
    toAdd -> id = idIncr;
    int pos = hashFunc(idIncr, size);
    cout << "Pos " << pos << endl;
    //cout << "ID after: " << idIncr << endl;
    cout << "hash :" << size;
    if (hashtable[pos] == NULL) {
      hashtable[pos] = toAdd;
      //cout << "a" << endl;
    }
    else {
      int count = 0;
      name* chain = hashtable[pos];
      cout << hashtable[pos] -> id;
      while(chain -> next != NULL) {
	count ++;
	chain = chain -> next;
      }
      chain -> next = toAdd;
      if(count > 1) {
	hashtable = rehash(hashtable, size);
      }
    }
    int full = 0;
    for(int j = 0; j < size; j++) {
      if(hashtable[j] != NULL) {
	full ++;
      }
    }

    if (full > size/2) {
      rehash(hashtable, size);
    }
    
    //Randomize GPA
    double ingpa = (double)rand()/(RAND_MAX)*5;
    toAdd -> gpa = ingpa;
  }
  return hashtable;
}

int hashFunc(int id, int mod) {
  int place = id % mod;
  return place;
}

name** rehash(name** hashtable, int& size) {
  int rep = size;
  size = size + 100;
  name** hashtable2 = new name*[size];
  for (int i = 0; i < rep; i++) {
    if (hashtable[i] != NULL) {
      name* torehash = hashtable[i];
      do {
	//cout << "a" << endl;
	int pos = hashFunc(torehash -> id, size);
	if(hashtable2[pos] == NULL) {
	  hashtable2[pos] = torehash;
	  torehash -> next = NULL;
	}
	else{
	  name* nextre = torehash -> next;
	  torehash -> next = NULL;
	  int count = 0;
	  name* chain = hashtable2[pos];
	  while(chain -> next != NULL) {
	    count ++;
	    chain = chain -> next;
	  }
	  if(count < 2) {
	    chain -> next = torehash;
	  }
	  else {
	    size += 100;
	    //cout << "a" << endl;
	    hashtable2 = rehash(hashtable, size);
	    return hashtable2;
	  }
	  torehash = nextre;
	}
      }while(torehash != NULL);
    }
  }
  //print(hashtable2, size);
  return hashtable2;
}

void print (name** hashtable, int size) {
  for(int i = 0; i < size; i++) {
    name* chain = hashtable[i];
    while(chain != NULL) {
      cout << "Slot: " << i << " Name: " << chain -> fname << " " << chain->lname << " Id: " << chain->id << " GPA: " << chain->gpa << endl;
      chain = chain -> next;
    }
  }
}

void deletehash(name** hashtable, int size) {
  cout << "Please input one of the following: add, search, print, or quit" << endl;
  char* input;
  cin >> input;
  int pos = hashFunc(atoi(input), size);
  if (hashtable[pos] != NULL) {
    name* chain = hashtable[pos];
    if(chain -> next == NULL) {
      if(chain -> id == atoi(input)) {
	hashtable[pos] = NULL;
	delete chain;
	cout << "Successful delete" << endl;
      }
      else{
	cout << "The Id was not there" << endl;
      }
    }
    else {
      bool cond = true;
      while(chain != NULL && chain -> next != NULL) {
	if(chain -> next -> id == atoi(input)) {
	  name* del = chain -> next;
	  chain -> next = del -> next;
	  delete del;
	  cond = false;
	  chain = chain -> next;
	  cout << "Successful delete" << endl;
	}
      }
      if (cond == true) {
	cout << "The Id was not there" << endl;
      }
      
    }
  }
  else{
    cout << "The Id was not there ..." << endl;
  }
}

string getanyname(string* namearray){
  int randnum = rand();
  cout << "randnum = ";
  cout << randnum;
  cout << " randnum % 30 = ";
  cout << (randnum % 30) << endl;
  return namearray[(randnum % 30)];
}
