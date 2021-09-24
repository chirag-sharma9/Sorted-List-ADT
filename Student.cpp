#include "Student.h"
#include <iostream>

using namespace std;

Student::Student() {
  id = -1;
  name = "None";
}

Student::Student(int i, string n) {
  id = i;
  name = n;
  }

int Student::getID() const {
  return id;
}

string Student::getName() const {
  return name;
}

void Student::setID(int i) {
  id = i;
}

void Student::setName(string n) {
    name = n;
}

bool Student::operator==(const Student& s) const {
  return (id == s.getID());
}

bool Student::operator<(const Student& s) const {
  return (id < s.getID());
}

bool Student::operator>(const Student& s) const {
  return (id > s.getID());
}

  
  
