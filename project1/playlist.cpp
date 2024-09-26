#include "playlist.h"
#include <iostream>
#include <string>

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       Song Class      ///////////////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor
Song::Song() : song(""), artist("") {}

//Destructor
Song::~Song(){};

//Getter for Song
std::string Song::get_song(){
    return song;
};

//Getter for Artist
std::string Song::get_artist(){
    return artist;
};

//Setter for Song
void Song::set_song(std::string song_name){
    song = song_name;
};

//Setter for Artist
void Song::set_artist(std::string artist_name){
    artist = artist_name;
};

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       Playlist Class      ///////////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor
Playlist::Playlist(unsigned int array_size){
    size = array_size;
    playlist = new Song[array_size];

};

//Deconstructor
Playlist::~Playlist(){
    delete[] playlist;
    playlist = nullptr;
};


//Getter for Playlist size
unsigned int Playlist::get_size(){
    return size;
};

//Functions
//Play song at position n function
void Playlist::play_song(int position_add_song, int array_size){
 
    if((position_add_song >= 0) && (position_add_song < array_size)){ //if valid position to play song
        
        if((playlist[position_add_song].get_artist() == "") && playlist[position_add_song].get_song() == "") { //if empty
            std::cout << "can not play " << position_add_song << std::endl;

        } else{
            std::cout << "played " << position_add_song << " " << playlist[position_add_song].get_song() << ";" << playlist[position_add_song].get_artist() << std::endl;

        }
    } else{
        std::cout << "can not play " << position_add_song << std::endl;

    }
};

//Erase song at position n function
void Playlist::erase_song(int position_erase_song, int array_size){
    if((position_erase_song >= 0) && (position_erase_song < static_cast<int>(current_songs_added))){
        
        for(int i{position_erase_song}; i < (static_cast<int>(current_songs_added) - 1); i++){
            playlist[i] = playlist[i+1];

        }            
        //set values to nothing
        playlist[current_songs_added-1].set_artist("");
        playlist[current_songs_added-1].set_song("");
        
        current_songs_added--; // Decrement the count of added songs

        std::cout << "success" << std::endl;
    } else{
        std::cout << "can not erase " << position_erase_song << std::endl;

    }
};

//Add song to end of array function
void Playlist::add_song(std::string title, std::string artist, unsigned int size){
    if(((title == "Baby") && (artist == "Justin Bieber"))){ //restricted case 1
        std::cout << "can not insert " << title << ";" << artist << std::endl;

    } else if(title == "My Heart Will Go On"){ //restricted case 2
        std::cout << "can not insert " << title << ";" << artist << std::endl;

    } else if(current_songs_added == size){ //if list is full 
        std::cout << "can not insert " << title << ";" << artist << std::endl;

    } else if(check_same_song(title, artist) == true){ //Checking for same song already in the array
        std::cout << "can not insert " << title << ";" << artist << std::endl;

    } else{ //If everything checks out, add the song
        playlist[current_songs_added].set_artist(artist);
        playlist[current_songs_added].set_song(title);
        current_songs_added++;
        std::cout << "success" << std::endl;
    }
};

//Helper Function
bool Playlist::check_same_song(std::string title, std::string artist){
    for(unsigned int i{0}; i < current_songs_added; i++){

        if((title == playlist[i].get_song()) && (artist == playlist[i].get_artist())){
            return true;

        }
    }
    return false;
};
