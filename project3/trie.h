#include <iostream>

//Class for nodes in the trie
class Node{

    public:
        bool terminal; //Variable to indicate the end of the word.
        Node* children[26]; //Create 26 children pointers because that is how many letters are in the alphabet.
        bool zeroChildren(Node* node); //Helper function to check if a node has 0 children.

        Node(); //Constructor
        ~Node(); //Destructor

};

//Class for the trie itself and it's various functions.
class SpellChecker{

    private:
        Node* root; //Make a root node for the root of the trie.
        int number_of_words; //Variable for number of words in trie.
        int prefix_counter; //Counter for the number of words with the same prefix.
        //Helper Functions
        void deleteTrie(Node* node); //Function to delete the trie. Only used inside function.
        void printRecurse(Node* node, const std::string& string); //Function to print the trie. 
        void countPrefixNum(Node *node); //Helper Function to get number of words with prefix given.
        void wordsWithPrefix(Node *node, const std::string& currWord); //Helper function to suggest words with the same prefix.
        bool eraseWordHelperFunction(Node *node, const std::string& string, int length, bool& deleted); //Helper function to help delete the word.

    public:
        SpellChecker(); //Constructor
        ~SpellChecker(); //Destructor

        //Functions
        void loadCorpus(); //Function to load the corupus into the trie.
        bool insertWord(const std::string& user_input);  //Function to insert word into the trie if not already there.
        void outputPrefix(const std::string& user_input); //Outputs the number of words in the trie with the given prefix.
        void eraseWord(const std::string& user_input); //Erase a word from the trie if it already exists.
        void printWords(); //Prints all words in alphabetical order.
        void spellcheck(const std::string& user_input); //To check if a word is in the trie.
        void checkEmpty(); //Check to see if the trie is empty.
        void clearTrie(); //Deletes all the words from the trie.
        void printSize(); //Print the number of words in the trie.
};
