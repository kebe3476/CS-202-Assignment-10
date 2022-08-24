/*
CS 202 Assignment 10

Name: Keith Beauvais, 5005338658, CS 202 Assignment 10
*/
#include <vector> 
#include "addrBookExc.h"


struct menuEntry {
    std::string text;
    char key;
};

class Menu {
    std::string title;
    std::vector<menuEntry> options;
    
/* validate() - checks if menu option character is valid, if option is found, then exit the function. if all menu entries 
were checked, and menu option hasn’t been found, then throws exception with the text “invalid menu entry”. In the related 
catch block, use function of exception object and print: “ERROR: “ followed by what() message. Then rethrows the caught exception.

char option -  takes in user input char to be compared to key char in the vector.

return value - void does not return a value.
*/
    void validate(char option) {

        try {
            for(unsigned long i = 0; i< options.size();i++){
                if(option == options[i].key){
                    return;
                }
            }
            throw Error("invalid menu entry");
            // your code here, if option doesn't exist = throw exception
        }
        catch (Error& e) {
            std:: cout<< std::endl;
            std::cout <<"ERROR: "<< e.what()<<std::endl;
            throw e;
        }
    }
    
    public:
    Menu(std::string title) {
       this -> title = title;
    }
/* add() - adds a menuEntry record to the vector, values of menuEntry object data members text, key are set to the string
 and char parameters respectively.

string option_text - passes in a string to be set int the vector

char key - passes in a char to be set in the vector 

return value - void does not return a value.
*/
    void add(std::string option_text, char key) {
        menuEntry option;
        option.text = option_text;
        option.key = key;

        options.push_back(option);
    }
/* add() - function displays the menu: all the menu options stored in the vector, and prompts user for the selection. 
The character corresponding to the option is validated using validate() function. If character is successfully validated – 
it is converted to lowercase and returned. If validation fails,the exception from validate() function is caught, message 
“try again” is displayed, and menu is displayed again and user is prompted for menu selection again.

return value - returns a lowercase char.
*/
    char displayAndRead() {
        char userInput;
        bool flag = true;

        while(flag){
            flag = false;
            try{
                std::cout << title << std::endl;
                std::cout <<"======================"<< std::endl;
                for(unsigned long i = 0; i< options.size(); i++){
                        std::cout<< options[i].text<<" "<<"("<<options[i].key<<")"<<std::endl;
                }
                std::cout<<"Choice : ";
                std::cin>>userInput;
                std:: cout<< std::endl;
                validate(userInput);
            }
            catch(Error& e){
                flag = true;
                std::cout<<"try again"<<std::endl;
                std:: cout<< std::endl;
            }
        }
         return userInput;
    }
};
