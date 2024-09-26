#include <vector>
#include <iostream>
#include <list>

//Class for HashMap
class HashMap{
    friend class Dictionary; //For access to the private variables.

    private:
        std::list<std::pair<std::string, int>>* list; //Pointer to an array of linked lists.

    public:
        HashMap(int size); //Constructor for HashMap function.
        ~HashMap(); //Destructor for HashMap function.
};

//Class for Dictionary
class Dictionary{

    private:
        std::vector<std::string> vector; //Vector for inserting the strings
        HashMap hashmap; //Hashmap object.
        int total_size; //Total size of the hashmap.
        int number_of_elements; //Number of elements in the hashmap.
        double load_factor; //Load factor for the resizing of the hashmap.
        unsigned hashFunction(const std::string & str); //Hash Function.
 
    public:
        Dictionary(int size); //Constructor for HashMap function.
        ~Dictionary(); //Destructor for the Dictionary function.
        int get_total_size(); //Getters for total size

        //Functions
        bool insert(const std::string& string); //Function to insert the string into the dictionary.
        std::string ret(int token); //Function to retrive the strings when given a token.
        int tok(std::string& string); //Function to retrieve the token when given a string.
        void load(const std::string& file); //Function to insert all words from the file to the dictionary.
        void resizeHashMap(); //Function for resizing the hash map. (when load factor is greater than 0.8)
        void print(int k); //Function to print the key in the hash table position.
        void tok_all(std::string& string); //Function to tokenize all the words.
        void ret_all(std::string& string); //Function to retrieve all the words.
};