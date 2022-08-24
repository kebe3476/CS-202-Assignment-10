/*
CS 202 Assignment 10

Name: Keith Beauvais, 5005338658, CS 202 Assignment 10
*/
#include <iostream>
#include "addressBook.h"
#include "menu.h"

using namespace std;

int main() {
    addressBook *myBook;
    try {
        myBook = new addressBook("records.csv");
        // create / allocate myBook object here
        
    } 
    catch (...) {
        cout<< "FATAL ERROR: failed to read file, terminating"<<endl;
        exit(0);
    }

    myBook->goToFirst();

    while(true){
        Menu menu("MAIN MENU");
        menu.add("Next",'s');
        menu.add("Previous",'w');
        menu.add("Go to first",'f');
        menu.add("Display all",'d');
        menu.add("Display tree",'t');
        menu.add("Search",'j');
        menu.add("Quit",'q');

        char userInput = menu.displayAndRead();

        switch(userInput){
            case 's':
            myBook->operator++();
            break;
            case 'w':
            myBook -> operator--();
            break;
            case 'f':
            myBook -> goToFirst();
            break;
            case 'd':
            myBook ->display('0');
            break;
            case 'q':
            delete myBook;
            break;
            case 't':
            myBook ->display('1');
            break;
            case 'j':
            myBook->search();
            break;
        }
        if(userInput=='q'){
            break;
        }
    }
    
    return 0;
    
    // default action is to display 3 records
    
    // display main menu and take actions related to options
    
}
