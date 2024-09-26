#include <iostream>
#include <string>
#include "trie.h"

int main(){
    
    //Variables 
    bool while_bool = true; //Bool variable for while logic.
    SpellChecker spell_checker; //create instance for the spell checker game.

    //While true keep iterating
    while(while_bool == true){
        std::string user_input; //Get input from user and store into string variable
        std::getline(std::cin, user_input); //Get line from user input and store it into user input string.

        if(user_input.substr(0, 2) == "i "){
            std::string string = user_input.substr(2); //Concatenate user input and store into string.
            bool output_statement; //Create bool statement for if its an empty statement or not.

            output_statement = spell_checker.insertWord(string); //Call Insert Word function and send it user_input, set return value to output statement.
            //Output statement if success of failure of insertion
            if(output_statement == true){
                std::cout << "success" << std::endl; //output success if return statement was true
            } else{
                std::cout << "failure" << std::endl; //output failure if return statement was false
            }

        } else if(user_input.substr(0, 2) == "c "){
            std::string string = user_input.substr(2); //Concatenate user input and store into string.
            
            spell_checker.outputPrefix(string); //Call Output Prefix function and send it user_input.

        } else if(user_input.substr(0, 2) == "e "){
            std::string string = user_input.substr(2); //Concatenate user input and store into string.

            spell_checker.eraseWord(string);  //Call Erase Word function and send it user_input.

        } else if(user_input.substr(0, 1) == "p"){
            spell_checker.printWords(); //Call Print Words function

        } else if(user_input.substr(0, 10) == "spellcheck"){
            std::string string = user_input.substr(11); //Concatenate user input and store into string.

            spell_checker.spellcheck(string); //Call Spell Check function and send it user_input.

        } else if(user_input.substr(0, 5) == "empty"){
            spell_checker.checkEmpty(); //Call Check Empty function

        } else if(user_input.substr(0, 5) == "clear"){
            spell_checker.clearTrie(); //Call Clear Trie function

        } else if(user_input.substr(0, 4) == "size"){
            spell_checker.printSize(); //Call Print Size function

        } else if(user_input.substr(0, 4) == "load"){
            spell_checker.loadCorpus(); //Call Load Corpus function
        }
        else if(user_input.substr(0, 4) == "exit"){
            while_bool = false; //Set the boolean to false to exit out the whole loop
        }
    }
    return 0; //return
}