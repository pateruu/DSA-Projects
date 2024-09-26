#include <iostream>
#include <string>
#include "tokenize.h"
#include <climits>

int main(){
    //Variables 
    bool while_bool = true; //Bool variable for while logic.

    //Get input from user for the first statement and create the dictionary by sending it the size value.
    std::string first_input; //Get input from user and store into string variable
    std::getline(std::cin, first_input); //Get line from user input and store it into user input string.
    std::string first_string = first_input.substr(7); //Concatenate user input and store into string.
    int send_size = std::stoi(first_string); //Concatenate integer value from string and store into size.
    Dictionary dictionary(send_size); //Insert function here and send size value once.
    std::cout << "success" << std::endl; //print success.

    //While true keep iterating
    while(while_bool == true){
        std::string user_input; //Get input from user and store into string variable.
        std::getline(std::cin, user_input); //Get line from user input and store it into user input string.

        if(user_input.substr(0, 7) == "insert "){
            std::string string = user_input.substr(7); //Concatenate user input and store into string.
            bool if_inserted = dictionary.insert(string); //Check if we inserted the word already.
            if(if_inserted == true){ //if true then print success
                std::cout << "success" << std::endl;
            } else{ //else print failure
                std::cout << "failure" << std::endl;
            }

        } else if(user_input.substr(0, 5) == "load "){
            std::string string = user_input.substr(5); //Concatenate user input and store into string.
            dictionary.load(string); //Create function and send it string.

        } else if(user_input.substr(0, 4) == "tok "){
            std::string string = user_input.substr(4); //Concatenate user input and store into string.
            int answer = dictionary.tok(string); //Create function and send it string.
            std::cout << answer << std::endl; //Print value that is returned.

        } else if(user_input.substr(0, 4) == "ret "){
            std::string string = user_input.substr(4); //Concatenate user input and store into string.
            int token = std::stoi(string); //Concatenate integer value from string and store into size.

            std::string returned_string = dictionary.ret(token); //send token to ret function and store returned string into a string variable. 
            std::cout << returned_string << std::endl; //Print the returned string.

        } else if(user_input.substr(0, 8) == "tok_all "){
            std::string string = user_input.substr(8); //Concatenate user input and store into string.
            dictionary.tok_all(string); //Send the string to the tok_all function to tokenize.

        } else if(user_input.substr(0, 8) == "ret_all "){
            std::string string = user_input.substr(8); //Concatenate user input and store into string.
            dictionary.ret_all(string); //Insert function here and send size value

        } else if(user_input.substr(0, 6) == "print "){
            std::string string = user_input.substr(6); //Concatenate user input and store into string.
            int k = std::stoi(string); //Concatenate integer value from string and store into size.
            dictionary.print(k); //Call the print function in dictionary and send it the given k value from user.

        } else if(user_input.substr(0, 4) == "exit"){
            while_bool = false; //Set the boolean to false to exit out the whole loop
        }
    }
    return 0; //return
}