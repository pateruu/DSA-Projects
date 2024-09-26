#include "game.h"
#include <iostream>
#include <cmath>

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       Player Class      /////////////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor
Player::Player(){
    x_position = 0;
    y_position = 0;
    next = nullptr;
};

//Destructor
Player::~Player(){
    x_position = 0;
    y_position = 0;
    next = nullptr;
};

//Getters
//Return the x position
double Player::get_x_position(){
    return x_position;
};
//Return for y position
double Player::get_y_position(){
    return y_position;
};

//Setters
//Setter for the x position
void Player::set_x_position(double x_pos){
    x_position = x_pos;
};
//Setter for the y position
void Player::set_y_position(double y_pos){
    y_position = y_pos;
};

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       playerList Class      /////////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor
PlayerList::PlayerList(){
    player_number = 0;
    head = nullptr;
}

//Destructor
PlayerList::~PlayerList(){
    //Go through the player list and delete all the nodes.
    Player* current = head;
    while(current != nullptr){
        Player* next = current->next; // Save the next pointer before deleting
        delete current; // Delete the current node
        current = next; //Go to next node
        }
    //Set head to nullptr
    head = nullptr;
    //Set player number to 0
    player_number = 0;
}

//Getters
//Return the player number
int PlayerList::get_player_number(){
    return player_number;
};

//Setters
//Set the player number
void PlayerList::set_player_number(int number){
    player_number = number;
};

//Functions
//Spawn function to create a player.
void PlayerList::spawnFunction(std::string user_input){
    //Get user input and find x and y positions then set then to double variables.
    unsigned int find_space = user_input.find(" ", 6);
    std::string x_string = user_input.substr(6, find_space-6);
    std::string y_string = user_input.substr(find_space+1);
    double x_pos = std::stod(x_string);
    double y_pos = std::stod(y_string);

    if((x_pos > 0 && x_pos <= 500) && (y_pos > 0 && y_pos <= 500)){ //If x and y positions are valid.
        
        //Dynamically allocate a new player to add a new player.
        Player* player = new Player();

        //Set x and y positions to the players node.
        player->set_x_position(x_pos);
        player->set_y_position(y_pos);

        //If there is no nodes in the linked list.
        if(head == nullptr){
            head = player; //set the head pointer to the new node.
            player_number++; //Increment player number by 1.

        } else{ //If there exists a node in the linked list.
            Player* current = head; //Create current and set it to head.
            current = player; //Set current to player.
            player->next = head; //Make next node of player equal to head.
            head = current; //Move head pointer up.
            player_number++; //Increment player number by 1.
        }
        
        std::cout << "success" << std::endl; //Print output to user.

    } else{ //If x and y positions are not valid.
        std::cout << "failure" << std::endl; //Print output to user.
    }
};

//Time function to move all players closer to the wolf.
void PlayerList::timeFunction(std::string user_input){
        
    //Get user input and store into t variable
    std::string time_pos_string = user_input.substr(5);
    double time = std::stod(time_pos_string);

    if((time > 0) && (time <= 500)){ //If t is from (0,500]
        //Create two pointers (a current node pointer and a previous node pointer)
        //Logic behind pointers is to move both pointers simultaneously throughout the linkedlist so that deleting the node is much easier.
        Player* current = head;
        Player* previous = nullptr;

        //Traverse through the list to update x and y values and the correct player values.
        while(current != nullptr){
            //Get values from each player and store into x and y double variables.
            double x_pos = current->get_x_position();
            double y_pos = current->get_y_position();

            //Update x and y values to move the player closer to the x and y position according to the time value entered by user.
            x_pos -= time * cos(atan2(y_pos, x_pos));
            y_pos -= time * sin(atan2(y_pos,current->get_x_position()));

            //Set updated x and y values to the current player
            current->set_x_position(x_pos);
            current->set_y_position(y_pos);
    
            //If updated values in each node is outside the boundary then delete the node.
            if((x_pos <= 0) || (y_pos <= 0)){
                
                //If we want to delete the first node in the linked list.
                if(previous == nullptr){ 
                    head = current->next;                    //Move head forward.
                    delete current;                          //Delete the node.
                    current = head;                          //Move current forward to where head is.

                } else{ //For any other node deletion.
                    previous->next = current->next;         //Make previous node point to the node after the node that needs to be deleted.
                    delete current;                         //delete the node that needs to be deleted.
                    current = previous->next;               //Move current to the node after the deleted node.

                }
                player_number--; //If node is deleted, subtract the total player number

            } else{
                //Move both pointers up by one to traverse to the next node in the linked list.
                previous = current; 
                current = current->next;

            }
        }
        std::cout << "num of players: " << player_number << std::endl; //Print number of players to user.
    } else{ //if t is not in range
        std::cout << "num of players: " << player_number << std::endl; //Print number of players to user.
    }
}

//Lunch function to remove all players with a distance of less than 1 to the wolf.
void PlayerList::lunchFunction(){
    //Create two pointers (a current node pointer and a previous node pointer)
    //Logic behind pointers is to move both pointers simultaneously throughout the linkedlist so that deleting the node is much easier.
    Player* current = head;
    Player* previous = nullptr;

    //If the linked list is empty.
    if(head == nullptr){
        std::cout << "num of players: " << player_number << std::endl;
    } else{ //If linked list is not empty.
        while(current != nullptr){ //While we have not finished going through the list      
            //Calculate the distance between the player and the wolf.
            double distance_to_wolf = sqrt(pow(current->get_x_position(), 2) + pow(current->get_y_position(), 2));

            //If distance is less than 1 then delete the node.
            if(distance_to_wolf < 1){
                //If we want to delete the first node in the linked list.
                if(previous == nullptr){ 
                    head = current->next;                   //Move head forward
                    delete current;                         //Delete the node
                    current = head;                         //Move current forward to where head is
                } else{ //For any other node deletion.
                    previous->next = current->next;         //Make previous node point to the node after the node that needs to be deleted.
                    delete current;                         //delete the node that needs to be deleted.
                    current = previous->next;               //Move current to the node after the deleted node.
                }
                player_number--; //If node is deleted, subtract the total player number

            } else{
                //Move both pointers up by one to traverse to the next node in the linked list.
                previous = current; 
                current = current->next;
            }
        }
        std::cout << "num of players: " << player_number << std::endl; //Print number of players to user.
    }
};

//Num function to display the number of players currently playing to the user.
void PlayerList::numFunction(){
    //Print the number of players to the user.
    std::cout << "num of players: " << player_number << std::endl;
};

//Print function to print all players with a distance less than d to the wolf.
void PlayerList::printFunction(std::string user_input){

    //Take user input and store d value into string then into a double variable.
    std::string prt_pos_string = user_input.substr(4);
    double prt_pos = std::stod(prt_pos_string);

    if((prt_pos > 0) && (prt_pos <= 500)){ //If value of d (position) is within the correct range (0, 500]
        Player* current = head;
        bool if_any_found = false; //if any players are found

        //Traverse through the list to print the correct player values.
        while (current != nullptr) {
            double distance_to_wolf = sqrt(pow(current->get_x_position(), 2) + pow(current->get_y_position(), 2)); //Calculate the distance between the player and the wolf.

            //If distance is less than the value of d
            if(distance_to_wolf < prt_pos){
                std::cout << current->get_x_position() << " " << current->get_y_position() <<  " " ; //print x and y values.
                if_any_found = true; //Set boolean to true so that it does not print "no players found"
            }
            current = current->next; // Move to the next player in the list
        }

        //If after going through the list, if boolean is false then print no players found
        if(if_any_found == false){ 
            std::cout << "no players found";
        }

        std::cout << std::endl; //print to next line to get expected output.
    } else{
        std::cout << "no players found" << std::endl;
    }
};

//Function to output final message to the user.
void PlayerList::overFunction(){

    if(player_number == 0){ //If there are no players in the linkedlist.
        std::cout << "wolf win" << std::endl;        
    } else{ //If there are players in the linked list.
        std::cout << "players win" << std::endl;
    }
};
