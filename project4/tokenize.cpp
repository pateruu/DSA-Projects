#include "tokenize.h"
#include <sstream>
#include <fstream>


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       HashMap Class        //////////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor for HashMap function.
HashMap::HashMap(int size){
    list = new std::list<std::pair<std::string, int>>[size]; //Set the list pointer to the newly dynamically allocated array with size set.
};                                                           //Also each array index has a pair of a string and integer (key-value pair)

//Destructor for HashMap function.
HashMap::~HashMap(){
     delete[] list; //Delete the dynamically allocated list
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       Dictionary Class        ///////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor for the Dictionary function.
Dictionary::Dictionary(int size) :  hashmap(size) {
    load_factor = 0.0; //Set values to 0
    total_size = size;
    number_of_elements = 0;
}

//Destructor for the Dictionary function.
Dictionary::~Dictionary(){
    load_factor = 0.0;  //Set values to 0
    total_size = 0;
    number_of_elements = 0;
};

 //Getters for total size
int Dictionary::get_total_size(){
    return total_size; //return the total size.
};

//Hash Function.
unsigned Dictionary::hashFunction(const std::string & str) {
    unsigned ans = 0;
    for (auto it = str.begin(); it != str.end(); ++it){
        ans = ans * 29 + *it;
    }
    return ans % total_size; 
}

//Function to insert the string into the dictionary.
bool Dictionary::insert(const std::string& string){

    //Check if string has valid characters.
    for(int k{0}; k < string.length(); k++){ //For loop to iterate through each character in the string.
        char character = string[k]; //Store each character of the string into the character variable.
        bool boolean = ((character >= 'a') && (character <= 'z')) || ((character >= 'A') && (character <= 'Z')); //Boolean for if the string character is within the correct bounds.
        if(boolean == 0){ //if boolean returns false stating a character we do not want then return false.
            return false;
        }
    }

    //Check for resizing.
    load_factor = static_cast<double>(number_of_elements) / static_cast<double>(total_size); //Calculation for load factor for if we need to resize.
    if(load_factor >= 0.8){ //Resize Check if load_factor is greater than 0.8
        resizeHashMap(); //if so then resize the hashmap.
    }

    //If string already exists.
    int index = hashFunction(string); //Get the index from the hashfuncton by sending it the string and store it into the index variable.
    std::list<std::pair<std::string, int>>::iterator find_values; //Iterator to search through the list
    for (find_values = hashmap.list[index].begin(); find_values != hashmap.list[index].end(); find_values++) { //Keep iterating form the beginning to the end of the hashmap.
        if (find_values->first == string) { //If we find the string then return false because string already exists.
            return false;
        }
    }

    //If we need to insert the string.
    vector.push_back(string); //Store the string into the next open spot in the vector.
    hashmap.list[index].push_front(std::make_pair(string, number_of_elements + 1)); //Insert the string into the calculated index in the hash map.
    number_of_elements = number_of_elements + 1; //Increment the number of elements.
    return true; //Return true indicating that we successfully inserted a string.
}; 

//Function for resizing the hash map. (when load factor is greater than 0.8)
void Dictionary::resizeHashMap(){

    //Variable initializers.
    unsigned int new_size = 2 * total_size; //Calculate new size for the hashmap.
    std::list<std::pair<std::string, int>> *new_hash_table = new std::list<std::pair<std::string, int>>[new_size]; //Create a dynamiccally allocated hash table with the new size.
    int place_holder_size = total_size; //Create placeholder so we do not lose original size.
    total_size = new_size; //Set the new total size to the new size.

    //Copy over the elements from old hash table to new hash table.
    std::list<std::pair <std::string, int> >::iterator iterator; //Iterator to search through the list
    for (int k{0}; k < place_holder_size; k++) { //Go through the current hash table.
        for(iterator = hashmap.list[k].begin(); iterator != hashmap.list[k].end(); iterator++){ //For each bucket in the hashmap, go through all its elements. (usually 1 element)
            int new_index = hashFunction(iterator->first); //calculate the new index for the new hash table.
            new_hash_table[new_index].push_front(std::make_pair(iterator->first, iterator->second)); //inser the element at its new index in the new hash table.
        }        
    }
    delete[] hashmap.list; //Delete the old hashmap.
    hashmap.list = new_hash_table; //Make the pointer of the list point to the new hashtable.
};

//Function to retrive the strings when given a token.
std::string Dictionary::ret(int token){
    //Check for if the token is within the range of valid elements. (token-1) for the 0-index fix
    if(((token-1) >= 0) && ((token-1) < number_of_elements)){
        return vector[token - 1]; //Return the string at that given token value.
    }
return "N/A"; //Otherwise return N/A
}; 

//Function to retrieve the token when given a string.
int Dictionary::tok(std::string& string){
    int index = hashFunction(string); //Get the index from the hashfuncton by sending it the string and store it into the index variable.
    std::list<std::pair<std::string, int>>::iterator find_values; //Iterator to search through the list
    for (find_values = hashmap.list[index].begin(); find_values != hashmap.list[index].end(); find_values++) { //iterate through the linked list at the hashmaps index.
        if (find_values->first == string) { //if we find the string we want then return that token value.
            return find_values->second;
        }
    }
    return -1; //Otherwise return -1 to rep token not found.
};

//Function to tokenize all the words.
void Dictionary::tok_all(std::string& string){
    std::string full_tok_all; //string with the concatenated final string.
    std::string each_word; //String for each word in the input.
    std::istringstream output_stream(string); //Makes it so we do word by word reading.

    while(output_stream >> each_word){ //Loop over each word in the string using stream.
        int curr_token = tok(each_word); //find the current token for the word by using tok function.
        if(curr_token == -1){ //if the returned token is -1 then add that string to the full tok all string.
            full_tok_all += "-1 ";
        } else{ //else conver the token to a string and then add it to the final string.
            full_tok_all = full_tok_all + (std::to_string(curr_token) + " ");
        }
    }
    std::cout << full_tok_all << std::endl; //Output the final string here.
};

//Function to retrieve all the words.
void Dictionary::ret_all(std::string& string){
    std::string full_ret_all; //string with the concatenated final string.
    std::string each_token; //String for each token in the input.
    std::istringstream output_stream(string); //Makes it so we do word by word reading.

    while(output_stream >> each_token){ //Loop over each word in the string using stream.
        int token = std::stoi(each_token); //conver each string to an integer and store it into token variable.
        std::string get_word = ret(token); //Send token to the ret function to retrieve the string and store into the get_word variable.
        full_ret_all = full_ret_all + (get_word + " "); //Concatenate it to the end of the full ret all string.
    }
    std::cout << full_ret_all << std::endl; //Output the final ret all string.
};


//Function to print the key in the hash table position.
void Dictionary::print(int k){
    //If k is outside the valid range then return.
    if((k >= total_size) || (k < 0)){
        return;
    } else if(hashmap.list[k].empty()){ //else if the list at the hash table position is empty then return.
        return;
    }
    //Iterate through the pairs in the list at position k and print the key.
    std::list<std::pair<std::string, int>>::iterator find_values; //Iterator to search through the list
    for(find_values = hashmap.list[k].begin(); find_values != hashmap.list[k].end(); find_values++){ //iterate through the linked list at index k
        std::cout << find_values->first; //Print the first value in the pair which is the key.
        if(std::next(find_values) != hashmap.list[k].end()) { //If the current pair is not the last pair in the list then print a space.
            std::cout << " ";
        }
    }
    std::cout << std::endl; //Print an end line.
};

//Function to insert all words from the file to the dictionary.
void Dictionary::load(const std::string& curr_file){
    std::ifstream file(curr_file); //attempt to open the file.
    bool if_inserted; //Store each insertion return to if_inserted.
    bool print_statement = false; //Bool logic for the print statement.

    std::string each_word; //String for each word in the file.
    while(file >> each_word){ //While there is a word in the file left to analyze.
        if_inserted = insert(each_word); //Send that word to the insert function to insert it into our dictionary.
        if(if_inserted == true){ //if we inserted atleast 1 word, then set print_statement to true.
            print_statement = true;
        }
    }
    //Logic for if we inserted atleast one work so that we can print.
    if(print_statement == true){
        std::cout << "success" << std::endl; //Output success after fully completing the load.
    } else{
        std::cout << "failure" << std::endl; //Output failure after fully completing the load.
    }
    file.close(); //Close the file.
}; 