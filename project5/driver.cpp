#include <iostream>
#include <string>
#include "graph.h"


int main(){
    //Variables 
    bool while_bool = true; //Bool variable for while logic.
    Map map; //Instance of map.

    //While true keep iterating
    while(while_bool == true){
        std::string user_input; //Get input from user and store into string variable.
        std::getline(std::cin, user_input); //Get line from user input and store it into user input string.

        if(user_input.substr(0, 7) == "insert "){
            std::string string = user_input.substr(7); //Concatenate user input and store into string.
            map.insert_to_map(string); //Send string to the insert to map function.
            std::cout << "success" << std::endl; //Print success.

        } else if(user_input.substr(0, 5) == "load "){
            std::string string = user_input.substr(5); //Concatenate user input and store into string.
            map.load(string); //Send string to the load function

        } else if(user_input.substr(0, 8) == "traffic "){
            std::string string = user_input.substr(8); //Concatenate user input and store into string.
            bool if_exists = map.traffic(string); //Create function and send it string, store it into bool if_exists for what the function returns.
            
            if(if_exists == true){ //If we updated value then print success.
                std::cout << "success" << std::endl;
            } else{ //else print failure.
                std::cout << "failure" << std::endl;
            }

        } else if(user_input.substr(0, 7) == "update "){
            std::string string = user_input.substr(7); //Concatenate user input and store into string.
            bool if_updated = map.update(string); //Store the return value from update edge function to a bool variable.

            if(if_updated == true){
                std::cout << "success" << std::endl; //Output success after fully completing the update.
            } else{
                std::cout << "failure" << std::endl; //Output failure after fully completing the update.
            }

        } else if(user_input.substr(0, 6) == "print "){
            std::string string = user_input.substr(6); //Concatenate user input and store into string.
            int a = std::stoi(string); //Turn the string to an integer.
            map.print_a(a); //Send the int a to the print function.

        } else if(user_input.substr(0, 7) == "delete "){
            std::string string = user_input.substr(7); //Concatenate user input and store into string.
            int a = std::stoi(string); //Turn the string to an integer.
            map.delete_a(a); //Send the int a to the print function.

        } else if(user_input.substr(0, 5) == "path "){
            std::string string = user_input.substr(5); //Concatenate user input and store into string.
            map.path(string); //Send string to the path function.

        } else if(user_input.substr(0, 7) == "lowest "){
            std::string string = user_input.substr(7); //Concatenate user input and store into string.
            bool print = map.lowest(string); //Create function and send it string, store it into bool print for what the function returns.
            if(print == false){ //if returned false, then print failure.
                std::cout << "failure" << std::endl;
            }

        } else if(user_input.substr(0, 4) == "exit"){
            while_bool = false; //Set the boolean to false to exit out the whole loop

        } else if (user_input == "printall") { //FOR TESTING PURPOSES
            map.printall(); //Call printall function to print the 3 maps.

        }
    }
    return 0; //return
}