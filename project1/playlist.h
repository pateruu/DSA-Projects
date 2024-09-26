#include <string>


class Song{

    private:
        std::string song;
        std::string artist;

    public:

        //Constructor
        Song();

        //Deconstructor
        ~Song();

        //Getters
        std::string get_song();
        std::string get_artist();
        
        //Setters
        void set_song(std::string song_name);
        void set_artist(std::string artist_name);

};


class Playlist{
    
    private:
        unsigned int size;
        Song* playlist;
        unsigned int current_songs_added;

    public:
        
        //Constructor
        Playlist(unsigned int array_size);

        //Deconstructor
        ~Playlist();

        //Getters
        unsigned int get_size();

        //Functions
        //To play song at position n
        void play_song(int position_add_song, int array_size);

        //To erase song at position n
        void erase_song(int position_erase_song, int array_size);

        //to add song (contains a artist and a song name)
        void add_song(std::string title, std::string artist, unsigned int size);

        //Helper Function for adding a song to check for duplicates
        bool check_same_song(std::string title, std::string artist);

};