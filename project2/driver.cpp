#include <iostream>
#include <string>
#include "game.h"

int main(){
    
    //Variables 
    bool while_bool = true; //Bool variable for while logic
    PlayerList player_list; //Create an instance of PlayerList class.


    while(while_bool == true){
        
        //Get input from user and store into string variable
        std::string user_input;
        std::getline(std::cin, user_input); //Get line from user input and store it into user input string.

        if(user_input.substr(0,5) == "SPAWN"){
            //Call spawn function to create a player and send it the user input.
            player_list.spawnFunction(user_input);

        } else if(user_input.substr(0,4) == "TIME"){
            //Call time function to move all players closer to the wolf and send it the user input.
            player_list.timeFunction(user_input);

        } else if(user_input.substr(0,5) == "LUNCH"){
            //Call lunch function to remove all players closer than a distance of 1 from the wolf.
            player_list.lunchFunction();

        } else if(user_input.substr(0,3) == "NUM"){
            //Call num function to output the number of players still playing the game.
            player_list.numFunction();

        } else if(user_input.substr(0,3) == "PRT"){
            //Call prt function to print all players within a distance declared by user.
            player_list.printFunction(user_input);

        } else if(user_input.substr(0,4) == "OVER"){
            //Call over function to give final game message.
            player_list.overFunction();    //Send call to over function to output who wins
            player_list.~PlayerList();     //Deallocate the player list here
 
            while_bool = false;            //Set the boolean to false to exit out the whole loop
        }
    }
    return 0;
}