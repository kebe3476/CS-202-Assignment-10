/*
CS 202 Assignment 10

Name: Keith Beauvais, 5005338658, CS 202 Assignment 10
*/
#include <iostream>
#include "addressBook.h"
#include "addrBookExc.h"
#include "searchList.h"
#include "menu.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

addressBook::addressBook(string filename) {
    head = NULL;
    last = NULL;
    firstToDisplay = NULL;
    loadFile(filename);
}

addressBook::~addressBook() {
    if(head == NULL && last ==NULL){
        head = NULL;
        last = NULL;
        delete head;
    }
    else{
        while(head != NULL&& last!=NULL){
            record * del;
            del = head;
            head = head -> next;
            del -> next = NULL;
            delete del;
        }
    }
}
/* displayRecord() - takes pointer to the record type and displays the values in the multi-line format.

record * r -  takes in a pointer of type record that is pointing to the doubly linked list. 

return value - void does not return a value.
*/
void addressBook::displayRecord(record *r) {
    cout<<endl;
    cout<< "Name: "<< r -> first_name <<" "<< r->last_name<<endl;

    cout<< "Street: "<< r -> address_street<<"       "<<"City: "<< r->address_city<<"     ";
    cout<< "State: "<< r-> address_state<< "    "<<"ZIP: "<< r-> address_zip<<endl;

    cout<<"Phone: "<< r-> mobile_no<< endl;

    cout<<"Notes: "<< r->notes<<endl;
    cout<<endl;

}
/* display3() - displays only three records on the screen, using function. The 
address of the first element to be displayed is stored in the pointer variable.

return value - void does not return a value.
*/
void addressBook::display3() {
    record * temp;
    temp = firstToDisplay;
    //this is for if there is no linked list
    if(head == NULL || last == NULL){
        return;
    }
    //if this is the last one in the list
    if(temp== last){
        displayRecord(temp);
        return;
    }
    //if there are two left 
    if(temp -> next == last){
        displayRecord(temp);
        displayRecord(temp ->next);
        return;
    }
    // if there are three or more left
    for(int i =0; i < 3; i++){
        displayRecord(temp);
        temp = temp->next;
    }   
}
/* displayAll() - displays the entire addressBook, starting from the first record. Uses displayRecord() 
to display single record. This function is recursive. 

record * current -  takes in a pointer of type record that is pointing to the current spot in the doubly 
linked list. 

return value - void does not return a value.
*/
void addressBook::displayAll(record *current) {
     if(current == NULL || (head == NULL && last == NULL)){
        return;
    }
    else{
        displayRecord(current);
    }
    displayAll(current -> next);
}
/* displayTree() - displays all the records in the compact form – only id, first name and last name 
are displayed. The hierarchical structure is presented in this function. Each further level of tree hierarchy 
is represented by \t tab character This function is recursive. 

record * current -  takes in a pointer of type record that is pointing to the current spot in 
the doubly linked list. 

int indent- indicated how many time it need to be indented.

return value - void does not return a value.
*/
void addressBook::displayTree(record *current, int indent) {
    //base case
   if(current == NULL){
       return;
   }

   //this is for reseting the parent indent to 0
   if(current ->prev == NULL||current -> prev -> child == NULL){
       indent = 0;
   }

   //Did not make this one scaleable 
   
   switch(indent){
        case 0:
        cout<<"id="<<" "<<current -> id<< " "<< "name="<<current -> first_name<< " "<<current->last_name<<endl;
        break;
        case 1:
        cout<<'\t'<<"id="<<" "<<current -> id<< " "<< "name="<<current -> first_name<< " "<<current->last_name<<endl;
        break;
        case 2:
        cout<<'\t'<<'\t'<<"id="<<" "<<current -> id<< " "<< "name="<<current -> first_name<< " "<<current->last_name<<endl;
        break;
        case 3:
        cout<<'\t'<<'\t'<<'\t'<<"id="<<" "<<current -> id<< " "<< "name="<<current -> first_name<< " "<<current->last_name<<endl;
        break;
        case 4:
        cout<<'\t'<<'\t'<<'\t'<<'\t'<<"id="<<" "<<current -> id<< " "<< "name="<<current -> first_name<< " "<<current->last_name<<endl;
        break;
        case 5:
        cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"id="<<" "<<current -> id<< " "<< "name="<<current -> first_name<< " "<<current->last_name<<endl;
        break;
        case 6:
        cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"id="<<" "<<current -> id<< " "<< "name="<<current -> first_name<< " "<<current->last_name<<endl;
        break;
   }
    indent++;
   
   displayTree(current -> next, indent);
}
/* display() - this is a routing function that will do the further call to private function members, 
either displayAll() or displayTree(). This is determined by the char parameter: 1 = displayTree() 0= displayAll()

const char option - takes in the character that is going to determine which private function to call 

return value - void does not return a value.
*/
void addressBook::display(const char option) {   // 0: all, full     1: tree
    if(option == '0'){
        displayAll(firstToDisplay);
    }
    if(option == '1'){
       int indent =0 ;
       displayTree(firstToDisplay,indent);
    }
}
/* goToFirst() - sets the scrolling control to the beginning of the list and displays three records.

return value - void does not return a value.
*/
void addressBook::goToFirst() {
    firstToDisplay = head;
    display3();
}
/* operator++() - advances the scroll control to the next element of the list and displays three records.
When scroll control is pointing to the last element. Calling this function has no visible effect.

return value - void does not return a value.
*/
void addressBook::operator++() {
    //this does not let it advance past last
    if(firstToDisplay== last){
        displayRecord(firstToDisplay);
        return;
    }
    //displays 2 if there are 2 left
    if(firstToDisplay -> next == last){
        displayRecord(firstToDisplay);
        firstToDisplay = firstToDisplay -> next;
        displayRecord(firstToDisplay);
        return;
    }
    firstToDisplay = firstToDisplay ->next;
    display3();

}

/* operator--() - sets the scroll control to the element previous to the one that is currently displayed as the first of three records. 
When already pointing to first element, then calling this function has no visible effect.

return value - void does not return a value.
*/
void addressBook::operator--() {
    //does not let it advance past head
    if(firstToDisplay == head){
        display3();
        return;
    }
    firstToDisplay = firstToDisplay ->prev;
    display3();
}
/* parseAllocate() - receives a line read from the input file as a parameter. Allocates memory for record type and fills 
in the data fields. Once the object is ready, then it returns the pointer to the allocated object.

string line - passes in the line from addRecord();

return value - returns a pointer that is pointing at newly allocated double list. 
*/
record* addressBook::parseAllocate(string line) {
    string id, parentId, firstName, lastName, street, city, state, zip, mobile, note;
    int intId, intParentId ;
    record * ptr;
          
    stringstream s(line);
    getline(s,id,','); 
    getline(s,parentId,',');  
    getline(s,firstName,','); 
    getline(s,lastName,','); 
    getline(s,street,','); 
    getline(s,city,',');
    getline(s,state,','); 
    getline(s,zip,','); 
    getline(s,mobile,',');
    getline(s,note,',');

    intId = stringConvertInt(id);
    intParentId = stringConvertInt(parentId);

    ptr = new record;
    ptr -> id = intId;
    ptr -> first_name = firstName;
    ptr -> last_name = lastName;
    ptr -> address_street = street;
    ptr -> address_city = city;
    ptr -> address_state = state;
    ptr -> address_zip = zip;
    ptr -> mobile_no = mobile;
    ptr -> notes = note; 
    ptr -> prev = NULL;
    ptr -> next = NULL;

    //flags the child pointer to be as "parent node"
    if(intParentId == 0){
        ptr -> child = NULL;
        return ptr;
    }
    //has children nodes point to last pointer
    ptr -> child = last;
    return ptr;

}
/* addRecord() - receives a record in a form of comma separated values (from function). Calls parseAllocate() 
function to get new linked list element (node), ready to be added. Then updates child of the record. Lastly, 
the newly created node is added at the end of the linked list.

string line - passes in the line from loadFile();

return value - void does not return a value.
*/
void addressBook::addRecord(string line) {
    record * ptr = NULL;

    ptr = parseAllocate(line);
    //this is to establish the first node
    if(head == NULL && last == NULL){
        head = ptr;
        last = ptr;
    }
    //the rest of the linked list
    else{
        last -> next = ptr;
        ptr -> prev = last;
        //this is for if the child pointer was flagged as "parent node" and has the child pointer point to next node since it is a parent
        if(ptr->child == NULL){
            last = ptr;
        }
        //this is for a true child in the child pointer and changes it to NULL
        if(ptr->child == last){
            last -> child = ptr;
            last = ptr;
            ptr-> child = NULL;
        }
    }
}
/* loadFile() - function to load the input file records.csv. It uses exception handling 
to handle the case when the input file is missing.If the input file is missing, then the addrBookExc exception '
is thrown with the message “error opening the file: FILENAME ABORT”. In case the input file exists, it is read line by line, 
and for each line the addRecord() function is called.

string line - passes in the filename from the constructor;

return value - void does not return a value.
*/
void addressBook::loadFile(string filename) {
    ifstream infile;
    string line;
    
    try{
        infile.open(filename); // passed in from main and constructor
        if(!infile.is_open()){
            throw Error("error opening the file: "+filename+" ABORT");
        }
    }
    catch(Error& e){
        cout << e.what()<<endl;
        throw e; // rethrows up to main exception
    }
    
    while(!infile.eof()){
        getline(infile,line);
        addRecord(line); 
    }

}
/* search() - First, this function creates Menu object and adds options to the menu.This menu is then displayed, and user prompt is invoked. 
If user selects ‘q’ then program goes back to the main menu. For options 1-4, the search() function asks user to enter the keyword. Once the 
keyword is provided, the function creates an object of searchList class, named searchListObj. Then, still inside of   function – the address 
book entries are checked against the search criteria (one of 1-4) and matching records are added to the , using searchList class members. 
Finally, the search results (i.e. elements of the ) are displayed in the compact form.


return value - void does not return a value.
*/
void addressBook::search() {
    char choice;
    string userInput;
    record * ptr = NULL;

    Menu menu("SEARCH MENU");
    menu.add("First Name",'1');
    menu.add("Last Name",'2');
    menu.add("City",'3');
    menu.add("State",'4');
    menu.add("Back to previous menu",'q');

    choice = menu.displayAndRead();

    searchList searchListObj;
    ptr = head;
    switch(choice){
        case '1':
        cout<<"Enter keyword/string: ";
        cin>> userInput;
        cout <<"searching against the keyword: "+ userInput<<endl;
        while(ptr != NULL){
            //checks user input with what is in the program
            if(userInput == ptr -> first_name){
                searchListObj.add(ptr);
            }
            ptr = ptr -> next;
        }
        searchListObj.display();
        break;
        case '2':
        cout<<"Enter keyword/string: ";
        cin>> userInput;
        cout <<"searching against the keyword: "+userInput<<endl;
        while(ptr != NULL){
            //checks user input with what is in the program
            if(userInput == ptr -> last_name){
                searchListObj.add(ptr);
            }
            ptr = ptr -> next;
        }
        searchListObj.display();
        break;
        case '3':
        cout<<"Enter keyword/string: ";
        cin>> userInput;
        //getline(cin,userInput);
        cout <<"searching against the keyword: "+userInput<<endl;
        while(ptr != NULL){
            //checks user input with what is in the program
            if(userInput == ptr -> address_city){
                searchListObj.add(ptr);
            }
            ptr = ptr -> next;
        }
        searchListObj.display();
        break;
        case '4':
        cout<<"Enter keyword/string: ";
        cin>> userInput;
        cout <<"searching against the keyword: "+userInput<<endl;
        while(ptr != NULL){
            //checks user input with what is in the program
            if(userInput == ptr -> address_state){
                searchListObj.add(ptr);
            }
            ptr = ptr -> next;
        }
        searchListObj.display();
        break;
        case 'q':
        break;
    }
}
/*stringConvertInt() - This function converts strings into int.

string s - this string is passed in from parseAllocate().

return value - returns an int.
*/
int addressBook::stringConvertInt(string s){
  stringstream ss;
  int value;

  ss << s;
  ss >> value;

  return value;
}


