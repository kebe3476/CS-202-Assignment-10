/*
CS 202 Assignment 10

Name: Keith Beauvais, 5005338658, CS 202 Assignment 10
*/
#include "record.h"
#include <iomanip>
#include <iostream>
#include <cstdlib>

//using namespace std;

struct searchListEl {
    record *addrBookElem;
    searchListEl *link;
};

class searchList {
    searchListEl *head;
    searchListEl *last;
    public:
    searchList();
    ~searchList();
    void add(record*);
    void display();
};

searchList::searchList() {
    head = NULL;
    last = NULL;

}

searchList::~searchList() {
    if( head == NULL){
        return;
    }
    else{
        while( head != NULL){
            searchListEl * del;
            del = head;
            head = head -> link;
            delete del;
        }
    }
}
/* add() - adds element to the searchlist.Takes the parameter–pointer to the record type. New element of searchListEl is 
allocated and the pointer passed as the parameter is stored in the newly created node. Then, this new element is added at 
the end of the list.

record *element -  passes in a pointer that is pointing to the addressBook double linked list

return value - void does not return a value.
*/
void searchList::add(record *element) {
    searchListEl * ptr = NULL;
    ptr = new searchListEl;
    ptr -> addrBookElem = element;

    if(head == NULL && last == NULL){
        head = ptr;
        last = ptr;
        ptr -> link = NULL;
        return;
    }
    last ->link = ptr;
    last = ptr;
    ptr -> link = NULL;
}
/* display() - displays all the records, that are referenced by list’s nodes. The display is in the condensed, one-line format

return value - void does not return a value.
*/
void searchList::display() {
    searchListEl * ptr = NULL;
    ptr = head;

    while(ptr!=NULL){
    std::cout<<std::left<<std::setw(10)<< ptr -> addrBookElem -> first_name<<std::left<<std::setw(15)<< ptr -> addrBookElem -> last_name<<std::left<<std::setw(20);
    std::cout<< ptr -> addrBookElem -> address_street<<std::left<<std::setw(20)<< ptr -> addrBookElem -> address_city<<std::left<<std::setw(5);
    std::cout<< ptr -> addrBookElem -> address_state<<std::left<<std::setw(10)<< ptr -> addrBookElem -> address_zip<<std::left<<std::setw(6);
    std::cout<<"phone="<<std::left<<std::setw(20)<< ptr -> addrBookElem -> mobile_no << ptr -> addrBookElem -> notes<<std::endl;
    ptr = ptr ->link; 
    }

}

