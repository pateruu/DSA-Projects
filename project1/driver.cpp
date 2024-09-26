#include "playlist.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string initial_user_input; // user input from cin (first input)
  unsigned int size{};            // size of array

  std::getline(std::cin, initial_user_input); // get user input

  // check for "m <number>"
  if ((initial_user_input[0] == 'm') && (initial_user_input[1] == ' ')) {
    // Logic to store char number into int number
    std::string number_string = initial_user_input.substr(
        2); // stores all characters from 3 and onward into number string
    size = std::stoi(number_string); // string to int
    std::cout << "success" << std::endl;
  }

  // Create playlist and send the array size
  Playlist *playlist = new Playlist(size);

  // Variables
  std::string user_input;
  std::string song_name;
  std::string artist_name;
  unsigned int find_semicolon;
  int play_song_int;
  int erase_song_int;
  std::string play_song_string;
  std::string erase_song_string;

  while (user_input !=
         "done") { // If user input is equal to done then exit while loop.
    std::getline(std::cin, user_input); // get input from user

    if ((user_input[0] == 'e') && (user_input[1] == ' ')) {
      // Code to concatenate string and store number into int variable to send
      // to erase_song function.
      erase_song_string =
          user_input.substr(2); // get the number part of the string
      erase_song_int =
          std::stoi(erase_song_string); // string to integer converter.
      playlist->erase_song(erase_song_int,
                           size); // call playlist erase function and send
                                  // values of n and size of array

    } else if ((user_input[0] == 'p') && (user_input[1] == ' ')) {
      // Code to concatenate string and store number into int variable to send
      // to play_song function.
      play_song_string =
          user_input.substr(2); // get the number part of the string
      play_song_int =
          std::stoi(play_song_string); // string to integer converter.
      playlist->play_song(play_song_int,
                          size); // call playlist play function and send values
                                 // of n and size of array

    } else if ((user_input[0] == 'i') && (user_input[1] == ' ')) {
      // Code to concatenate string into song name and artist name to send to
      // add_song function.
      find_semicolon =
          user_input.find(';'); // Find semi colon to then find the strings of
                                // the artist and song name.
      song_name = user_input.substr(2, find_semicolon -
                                           2); // substring for the song name
      artist_name = user_input.substr(find_semicolon +
                                      1); // substring for the artist name
      playlist->add_song(song_name, artist_name,
                         size); // send song name, artist name, and array size
                                // to the add song function.
    }
  }
  // Clean up the dynamically allocated memory
  delete playlist;
  return 0;
}
