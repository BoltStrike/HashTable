#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
//#include <stdlib.h> //For testing
//#include <bits/stdc++.h>
#include "name.h"
//might need srand
using namespace std;

struct name { //struct for students which will be hashed
  char fname [80];//all student info
  char lname [80];
  int id;
  float gpa;
  name* next = NULL;
};
//prototypes
name** addStu(name**, int, int&, int&);
int hashFunc(int, int);
name** rehash(name**, int&);
void print(name**, int);
void deletehash(name**, int);
void inittable(name**&, int);

char* getfname(); //gets first name
char* getlname(); //gets last name

int main() {
  name** hashtable = new name*[100];//make first hashtable size 100
  inittable(hashtable, 100);//inits all spots to be NULL
  int idinc = 100000;//starting id val
  int size = 100; //start size 100
  bool run = true;
  cout << "Welcome to Student Hashtable" << endl;
  while(run == true) {
    cout << "Please input one of the following: add, delete, print, or quit" << endl;
    char input [80];//grabs command
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
      run = false;//exits loop
    }
  }
}

name** addStu(name** hashtable, int numToAdd, int& idIncr, int& size) {
  bool flag = false;
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

    
    char* fnamechar = getfname(); //grabs first name
    strcpy(toAdd -> fname, fnamechar); //copies to student
    char* lnamechar = getlname();//grabs last name
    strcpy(toAdd -> lname, lnamechar); //copies to student

    //Increments id
    idIncr += 1; //increments id 1
    toAdd -> id = idIncr; // push to student
    int pos = hashFunc(idIncr, size); //gets hash func runs with id
    cout << "Pos " << pos << endl;
    cout << "hash :" << size;
    if (hashtable[pos] == NULL) {//if the table is null at point
      hashtable[pos] = toAdd; //puts to add into hashtable
    }
    else {//spot is full
      int count = 0;
      name* chain = hashtable[pos]; //starts chain at the val in table
      while(chain -> next != NULL) { //provided chain isnt at end
	count ++;//add 1 to count
	chain = chain -> next;//moves 1 down chain
      }
      count ++; //increment count 1 more for the last one added
      chain -> next = toAdd; //puts at end of chain
      if(count > 2) { //if higher than three in chain
	flag = true; //flag for rehash
      }
    }
    
    //Randomize GPA
    double ingpa = (double)rand()/(RAND_MAX)*5; //randoms double 0 - 5
    toAdd -> gpa = ingpa;
  }
  if(flag == true) { //if too big chain
    hashtable = rehash(hashtable, size); //rehashers
  }
  int full = 0;
  for(int j = 0; j < size; j++) {
    if(hashtable[j] != NULL) {
      full ++; //counts slots full
    }
  }
  
  if (full > size/2) { //if more than halfway full
    hashtable = rehash(hashtable, size);//rehash
  }

  return hashtable; //returns the hashtable
}

int hashFunc(int id, int mod) {
  int sum = 0; //holds sum of digits of id
  int summing = id; //holds id to start
  for (int i = 0; i < 6; i++) {//for 6 digits
    sum += sum + summing % 10; //adds the last number of id
    summing = summing/10; //truncates and divides entire id
  }
  int tomod = id * sum; //fold in by multiplying sum by id
  int place = tomod % mod;//mod to fit table
  return place; //return the position
}

name** rehash(name** hashtable, int& size) {
  int rep = size; //used for for loop
  bool flag = false; //flag for rehash
  size = size + 100; //increments size by 1
  name** hashtable2 = new name*[size]; //makes new table with increased size
  inittable(hashtable2, size); //init the table
  for (int i = 0; i < rep; i++) {//runs for length of original table
    if (hashtable[i] != NULL) { //provided not null
      name* torehash = hashtable[i];//holds node that is in hashtable
      do {
	name* nextre = torehash -> next; //hold next for rehash

	torehash -> next = NULL; //sets next to null
	int pos = hashFunc(torehash -> id, size); //gets the new pos with new size
	if(hashtable2[pos] == NULL) { //if the hashtable is empty at spot
	  hashtable2[pos] = torehash; //put in table
	}
	else{
	  int count = 0;//chain count starts at 0
	  name* chain = hashtable2[pos]; //start chain at node at position
	  while(chain -> next != NULL) {//goes to end of chain
	    count ++; //counts how many in chain
	    chain = chain -> next;
	  }
	  chain -> next = torehash;//adds to chain
	  count ++; //one more for new one
	  if(count > 2) {//must rehash again
	    flag = true;
	  }
	}
	torehash = nextre;//updates to be next
      }while(torehash != NULL);
    }
  }
  if (flag == true) {
    hashtable2 = rehash(hashtable2, size); //rehashes hashtable2 and returns it
  }
  int full = 0;
  for(int j = 0; j < size; j++) {
    if(hashtable2[j] != NULL) {
      full ++;//counts items in hash2
    }
  }
  
  if (full > size/2) {//if more than half full
    hashtable2 = rehash(hashtable2, size); //rehash
  }
  return hashtable2; //return hashtable
}

void print (name** hashtable, int size) {
  name* chain = NULL; //chain start as NULL
  for(int i = 0; i < size; i++) { //goes through table 
    chain = hashtable[i];//starts chain at positiion
    while(chain != NULL) {//if not null
      cout << "Slot: " << i << " Name: " << chain -> fname << " " << chain->lname << " Id: " << chain->id << " GPA: " << chain->gpa << endl;
      chain = chain -> next;//print info and goes one down chain
    }
  }
}

void deletehash(name** hashtable, int size) {
  cout << "Please input an ID to delete" << endl;
  int input; //takes in deletion id
  cin >> input;
  int pos = hashFunc(input, size); //gets pos with hash function
  if (hashtable[pos] != NULL) { //if not null
    name* chain = hashtable[pos]; //starts the chain
    if(chain -> next == NULL) {//if nothing else in chain
      if(chain -> id == input) { //if id matches
	hashtable[pos] = NULL;//clear out of table
	delete chain;//delete
	cout << "Successful delete" << endl;
      }
      else{
	cout << "The Id was not there" << endl;
      }
    }
    else {
      if (chain -> id == input) { //if id is matching
	hashtable[pos] = chain -> next; //goes to next
	delete chain;//deletes original
	cout << "Successful delete" << endl;
      }
      else {
	bool cond = true;
	while(chain != NULL && chain -> next != NULL) {//goes through chain until id matches or chain done
	  if(chain -> next -> id == input) {//if id match
	    name* del = chain -> next; //del becomes the next
	    chain -> next = del -> next; //chains next is equivalent to the to delete next
	    delete del; //gets rid of del value
	    cond = false; //do not print negative result
	    cout << "Successful delete" << endl;
	  }
	  chain = chain -> next;  //moves one down chain
	}
	if (cond == true) {
	  //negative respons
	  cout << "The Id was not there" << endl;
	}
      } 
    }
  }
  else{
    //negative response
    cout << "The Id was not there ..." << endl;
  }
}

char* getfname(){
  int randnum = rand(); //rand number to pull from the array
  return finame[(randnum % 30)];//pulls first name
}

char* getlname(){
  int randnum = rand();//random number
  return laname[(randnum % 30)]; //pulls random last name
}

void inittable(name**& hashtable, int size) {
  for(int i = 0; i < size; i++) {
    hashtable[i] = NULL; //sets all spot in table to NULL
  }
}
