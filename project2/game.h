#include <string>

//Player Class
class Player{

    private:
        //Variables for the players' x and y coordinates.
        double x_position; 
        double y_position;

    public:
        //Pointer to the next player.
        Player* next;
        
        //Constructor
        Player();

        //Destructor
        ~Player();

        //Getters
        double get_x_position();
        double get_y_position();

        //Setters
        void set_x_position(double x_pos);
        void set_y_position(double y_pos);
};

//Playlist Class
class PlayerList{

    private:
        //Consists of the number of players in the game, as well as a head and tail pointer.
        int player_number;
        Player* head;
        Player* tail;

    public:
        //Constructor
        PlayerList();

        //Destructor
        ~PlayerList();

        //Getters
        int get_player_number();

        //Setters
        void set_player_number(int number);

        //Functions
        //Spawn function to create a player.
        void spawnFunction(std::string user_input);
        
        //Time function to move all players closer to the wolf.
        void timeFunction(std::string user_input);

        //Lunch function to remove all players with a distance of less than 1 to the wolf.
        void lunchFunction();

        //Num function to display the number of players currently playing to the user.
        void numFunction();

        //Print function to print all players with a distance less than d to the wolf.
        void printFunction(std::string user_input);

        //Function to output final message to the user.
        void overFunction();
};