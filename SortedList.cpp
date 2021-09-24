#include "SortedList.h"

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

template <class ItemType>
SortedList<ItemType>::SortedList() {
  head = NULL;
  length = 0;
}

template <class ItemType>
SortedList<ItemType>::~SortedList() {
  makeEmpty();
}

template <class ItemType>
void SortedList<ItemType>::makeEmpty() {
  Node<ItemType>* temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    delete temp;
  }
  length = 0;
  head = NULL;
}

template <class ItemType>
bool SortedList<ItemType>::isEmpty() const {
  return (length == 0);
}

template <class ItemType>
pair<bool, Node<ItemType>*> SortedList<ItemType>::findItem(ItemType item) {
  bool isThere = NULL;
  Node<ItemType>* pred = NULL;
  Node<ItemType>* current = head;
  
  while (current != NULL) {
    if (current->info == item) {
      isThere = true;
      return make_pair(isThere, pred);
    } else if (current->info > item) {
      isThere = false;
      return make_pair(isThere, pred);
    }
    pred = current;
    current = current->next;
  }
  return make_pair(isThere, pred);
}

template <class ItemType>
void SortedList<ItemType>::putItem(ItemType newItem) {
  Node<ItemType>* prev = NULL;
  Node<ItemType>* newNode = new Node<ItemType>;
  newNode->info = newItem;
  
  pair<bool, Node<ItemType>*> myPair = findItem(newItem);
  prev = myPair.second;
  
  //Checking for duplicates
  if (myPair.first) {
    throw DuplicateItem();
  } else {
    //Adding node into the list
    if (prev == NULL) {  //insert as first node
      newNode->next = head;
      head = newNode;
    } else {
      newNode->next = prev->next;
      prev->next = newNode;
    }
    length++;
  }
}
  
template <class ItemType>
void SortedList<ItemType>::deleteItem(ItemType item) {
  Node<ItemType>* prevNode = NULL;
  
  pair<bool, Node<ItemType>*> myPair2 = findItem(item);
  prevNode = myPair2.second;
  
  //Check if item is in the list
  if (!(myPair2.first) || (length == 0)) {
    throw DeletingMissingItem();
  } else {
    //If deleting first node
    if (head->info == item) {
      Node<ItemType>* temp = head;
      head = head->next;
      delete temp;
    } else {
      //Find and delete node
      Node<ItemType>* deleteNode = prevNode->next;
      prevNode->next = deleteNode->next;
      delete deleteNode;
    }
    length--;
  }
}

template <class ItemType>
int SortedList<ItemType>::getLength() const {
  return length;
}

template <class ItemType>
ItemType SortedList<ItemType>::getAt(int i) {
  Node<ItemType>* current = head;
  if (1 <= i && i <= length) {
    for (int index = 1; index < i; index++) {
      current = current->next;
    }
    return current->info;
  }
  else {
    throw OutOfBound();
  }
}

template <class ItemType>
void SortedList<ItemType>::merge(SortedList& otherList) {
  if (head != nullptr && otherList.head != nullptr) {
    Node<ItemType>* mergedHead = nullptr;
    Node<ItemType>* head1 = head;
    Node<ItemType>* head2 = otherList.head;
    
    //Sets beginning to the list with lower starting value
    if (head1->info < head2->info) {
      mergedHead = head1;
      head1 = head1->next;
    } else {
      mergedHead = head2;
      head2 = head2->next;
    }
  
    Node<ItemType>* curr = mergedHead;

    //Links nodes from both lists in ascending order
    while (head1 != nullptr && head2 != nullptr) {
      if (head1->info < head2->info) {
	curr->next = head1;
	head1 = head1->next;
	curr = curr->next;
      } else if (head1->info > head2->info) {
	curr->next = head2;
	head2 = head2->next;
	curr = curr->next;
      } else { //Handles duplicates
	head1 = head1->next;
      }
    }

    //Handles case when one of the lists is shorter than the other
    if (head2 == nullptr) {
      curr->next = head1;
    } else {
      curr->next = head2;
    }
    
    head = mergedHead;
  }
  
  if (head == nullptr) {
    head = otherList.head;
    otherList.head = nullptr;
  }

  //Empty otherList
  if (otherList.head != nullptr) {
    otherList.head = nullptr;
  }
}

template <class ItemType>
void SortedList<ItemType>::printList(ofstream& out) {
  Node<ItemType>* current = head;
  out << "List Items : ";
  while (current != NULL) {
    out << current->info << "->";
    current = current->next;
  }
  out << "NULL.";
}
