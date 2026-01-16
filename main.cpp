// stores a list of students, their ID, and their GPA
// has ADD, PRINT, DELETE, and HELP functions
#include <iostream>
#include <cstring> // for strcmp()
#include <cstdlib> // for strtol() + strtof()
#include <cmath> // for round()
#include "student.h"
#include "node.h"
using namespace std;

namespace studentlist{
  // public objects for this program
  char version[20] = "1.0.1";
  Node* headptr = new Node(nullptr); // this is the first in the linked list, and will not be printed or deleteable
}
using namespace studentlist;
// NODE FUNCTIONS
Node* get_end(){
  // returns the end of the linked list
  Node* endptr = studentlist::headptr;
  while (endptr->getNext() != nullptr){
    endptr = endptr->getNext();
  }
  return endptr;
}

void node_add_student(Student*student){
  // adds student to the end of the linked list
  Node* endptr = get_end();
  Node* newptr = new Node(student);
  endptr->setNext(newptr);
}

void print_remaining(Node*ptr, int i){
  // prints the next node and all the nodes after it
  if (ptr == nullptr){
    return;
  }
  // this part only runs if the pointer exists
  Student* student = ptr->getStudent();
  cout << i << ") ";
  cout << student->name1 << ' ' << student->name2 << ", ";
  cout << student->id << ", ";
  cout << student->gpa << "\n";
  i++;
  print_remaining(ptr->getNext(), i);

}
// END OF NODE FUNCTIONS

void print(const char* text = ""){
  // cout wrapper, similar to python print()
  cout << text << '\n' << flush;
  return;
}

char* input(const char* text = ""){
  // cin wrapper, similar to python input()
  cout << text << flush;
  char* input1 = new char[81]; // handle up to 80 chars (dynamically allocate, i actually forgot what this meant on the test)
  cin >> input1;
  return input1;
}

void add_student(){
  // adds a student based on user input
  char* pEnd; // this is needed for some low-level memory stuff in strtol and strtof
  char name1[81]; strcpy(name1, input("Enter the student's first name: ")); // does this break style? the function was already bulky so i wanted to combine like terms
  char name2[81]; strcpy(name2, input("Enter the student's last name: "));
  char* id = input("Enter the student ID: ");
  int id1 = strtol(id, &pEnd, 10); // cast to int
  char* gpa = input("Enter the student's GPA: ");
  float gpa1 = strtof(gpa, &pEnd); // cast to float
  float gpa2 = round(100 * gpa1) / 100; // round to 2 decimal points
  Student* student = new Student; // to keep it in memory after this scope ends; be sure to free this memory when it gets deleted
  strcpy(student->name1, name1);
  strcpy(student->name2, name2);
  student->id = id1; // id
  student->gpa = gpa2; // gpa
  node_add_student(student);
  return;
}

void print_students(){
  // print the students that are stored
  print("Student list:");
  short i = 1;
  Node* ptr = studentlist::headptr;
  print_remaining(headptr->getNext(), i);
  cout << flush;
  return;
}

void delete_student(){
  // remove a student at a point
  print_students();
  char* pEnd;
  char* indexstr = input("Enter the student position in the array to delete: ");
  int index = strtol(indexstr, &pEnd, 10) - 1; // cast to int
  Node* ptr = headptr->getNext();
  Node* lastptr = headptr;
  for (int i = 0; i < index; i++){ // stop at the right student
    lastptr = ptr;
    ptr = ptr->getNext();
  }
  Student* student = ptr->getStudent();
  cout << "Removing " << student->name1 << "..." << endl;
  lastptr->setNext(ptr->getNext());
  delete ptr;
}
  
int main(){
  print("Student List - 10/9/25");
  print("Welcome! Type 'HELP' for a list of commands.");
  bool running = 1;
  while (running){ // main loop
    const char* cmd = input("$ ");
    // command list starts here
    if (strcmp(cmd, "HELP") == 0){ // HELP
      print("HELP: print list of commands");
      print("QUIT: quit this program");
      print("ADD: add a student");
      print("PRINT: print all the students currently stored");
      print("DELETE: delete a student");
    }
    if (strcmp(cmd, "QUIT") == 0){ // QUIT
      running = 0; // program will stop after completing this loop
      print("Goodbye!");
    }
    if (strcmp(cmd, "ADD") == 0){ // ADD
      add_student();
    }
    if (strcmp(cmd, "PRINT") == 0){ // PRINT
      print_students();
    }
    if (strcmp(cmd, "DELETE") == 0){ // DELETE
      delete_student();
    }
  }
  return 0;
}
