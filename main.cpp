// stores a list of students, their ID, and their GPA
// has ADD, PRINT, DELETE, and HELP functions
#include <iostream>
#include <vector> // for vector data type
#include <cstring> // for strcmp()
#include <cstdlib> // for strtol() + strtof()
#include <cmath> // for round()
using namespace std;

struct Student{
  // struct used for storing student values
  char name1[81] = "Anita"; // first name
  char name2[81] = "Jabłońskí"; // last name
  int id = 123456; // ID
  float gpa = 3.0; // GPA
};

namespace studentlist{
  // public objects for this program
  char version[20] = "1.0.1";
  vector<Student*> students;

}

using namespace studentlist;

void print(const char* text = ""){
  // cout wrapper, similar to python print()
  cout << text << '\n' << flush;
  return;
}

char* input(const char* text = ""){
  // cin wrapper, similar to python input()
  cout << text << flush;
  char input[81]; // handle up to 80 chars
  cin >> input;
  char* input1 = input;
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
  students.push_back(student); // finally, add this student to the vector
  return;
}

void print_students(){
  // print the students that are stored
  print("Student list:");
  short i = 1;
  for (Student* student : students){
    cout << i << ") ";
    cout << student->name1 << ' ' << student->name2 << ", ";
    cout << student->id << ", ";
    cout << student->gpa << "\n";
    ++i;
  }
  cout << flush;
  return;
}

void delete_student(){
  // remove a student at a point
  char* pEnd;
  char* student = input("Enter the student position to delete: ");
  int student1 = strtol(student, &pEnd, 10) - 1; // cast to int
  Student* student2 = students.at(student1);
  cout << "Removing " << student2->name1 << ' ' << student2->name2 << "...\n" << flush;
  students.erase(students.begin() + student1); // remove it now
  delete student2;
  return;
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
