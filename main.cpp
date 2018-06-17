#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <stdlib.h> //For testing
//might need srand
using namespace std;

struct name { //struct for students which will be hashed
  char fname [80];//all student info
  char lname [80];
  int id;
  float gpa;
  name* next;
};

name** addStu(name**, int, int&);
int hashFunc(int, int);
name** rehash(name**, int);
void print(name**);
void deletehash(name**);

string getanyname(string*); //for home testing

int main() {
  name** hashtable = new name*[100];
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
    else if (strcmp(input, "print") == 0) {
      print(hashtable);
    }
    else if (strcmp(input, "delete") == 0) {
      deletehash(hashtable);
    }
    else if (strcmp(input, "quit") == 0) {
      break;
    }
  }
}

name** addStu(name** hashtable, int numToAdd, int& idIncr) {
  for(int i = 0; i < numToAdd; i++) {
    name* toAdd;

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
    strcpy(toadd -> fname, fnamestr.c_str());
    lnamestr = getanyname(laname);
    strcpy(toadd -> lname, lnamestr.c_str());

    //Increments id
    idIncr ++;
    toAdd -> id = idIncr;
    int pos = hashFunc(idIncr, sizeof(hashtable));
    if (hashtable[pos] == NULL) {
      hashtable[pos] = toAdd;
    }
    else {
      int count = 0;
      name* chain = hashtable[pos];
      while(chain -> next != NULL) {
	count ++;
	chain = chain -> next;
      }
      chain -> next = toAdd;
      if(count > 1) {
	rehash(hashtable, sizeof(hashtable));
      }
    }
    int full = 0;
    for(int j = 0; j < sizeof(hashtable); j++) {
      if(hashtable[j] != NULL) {
	full ++;
      }
    }

    if (full > sizeof(hashtable)/2) {
      rehash(hashtable, sizeof(hashtable));
    }
    
    //Randomize GPA
    double ingpa = (double)(rand() % 6)/(rand() % 100 + 1);
    toAdd -> gpa = ingpa;
  }
  return hashtable;
}

int hashFunc(int id, int mod) {
  int place = id % mod;
  return place;
}

name** rehash(name** hashtable, int size) {
  name** hashtable2 = new name*[size + 100];
  for (int i = 0; i < size; i++) {
    if (hashtable[i] != NULL) {
      name* torehash = hashtable[i];
      do {
	int pos = hashFunc(torehash -> id, sizeof(hashtable2));
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
	    hashtable2 = rehash(hashtable, size + 200);
	    return hashtable2;
	  }
	  torehash = nextre;
	}
      }while(torehash != NULL);
    }
  }
  return hashtable2;
}

void print (name** hashtable) {
  for(int i = 0; i < sizeof(hashtable); i++) {
    name* chain = hashtable[i];
    while(chain != NULL) {
      cout << "Slot: " << i << " Name: " << chain -> fname << " " << chain->lname << " Id: " << chain->id << " GPA: " << chain->gpa << endl;
      chain = chain -> next;
    }
  }
}

void deletehash(name** hashtable) {
  cout << "Please input one of the following: add, search, print, or quit" << endl;
  char* input;
  cin >> input;
  int pos = hashFunc(atoi(input), sizeof(hashtable));
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
