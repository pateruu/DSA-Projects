#include "trie.h"
#include <iostream>
#include <fstream>
#include <sstream>

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       Node Class        /////////////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor for each Node
Node::Node(){
  //Set every node as terminal indicating end of string.
  terminal = false;

  //Set all children of each node to nullptr.
  for (int k = 0; k < 26; k++){
    children[k] = nullptr;
  }
}

//Destructor for each Node
Node::~Node(){

}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       SpellChecker Class        /////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor for SpellChecker
SpellChecker::SpellChecker(){

  number_of_words = 0; //Initialize number of words to 0.
  prefix_counter = 0; //Initialize prefix counter to 0.
  root = new Node(); //Set root pointer to the newly created node.
}

//Destructor for SpellChecker
SpellChecker::~SpellChecker(){
  deleteTrie(root); //Delete the trie.
  root = nullptr;
  number_of_words = 0; //Set number of words to 0
  prefix_counter = 0; //Set prefix counter to 0
}

//Helper function that deletes the trie that can be used for both erase function and destructor.
void SpellChecker::deleteTrie(Node* node){
  //For loop to iterate through the children.
  for (int k = 0; k < 26; k++) {
    if(node->children[k] != nullptr){ 
      deleteTrie(node->children[k]); //If node has a children then recurse again using that children node.
    }
  }
  delete node; //Now that we are at the leaf nodes start deleting the node.
  node = nullptr; //Set node to nullptr.
};

//Function to insert word into the trie if not already there.
bool SpellChecker::insertWord(const std::string& string){
  int string_index = 0; //String index to keep track of index while going through string.
  Node* curr = root; //pointer to go through the string.
  bool output_statement{false}; //Boolean value for the print statement.

  //As long as the index is less than the total length keep iterating.
  while(string_index < string.length()){
    
    char current_char = string[string_index]; //Stores the current char into char variable.
    int char_index = current_char - 65; //Takes the capital character and moves it down to start 'A' at index 0 to 'Z' at index 25.

    //If there is no node currently for that character, then add it.
    if(curr->children[char_index] == nullptr){
        curr->children[char_index] = new Node();
        output_statement = true; //Set output statement to true

    }
    //Increment the current pointer and the starting index to move to the next character.
    curr = curr->children[char_index];
    string_index++; //Increment the string index.
  }
  //If the terminal value after inserting word is false.
  if(curr->terminal == false){
      curr->terminal = true; //Set the terminal value to true indicating end of word.
      number_of_words = number_of_words + 1; //increment word count if its a new word in the trie.
      output_statement = true; //Set output statement to true
    }

  return output_statement; //Return the output statement on whether if we correctly added a word.
}; 

//Helper Function to get number of words with prefix given.
void SpellChecker::countPrefixNum(Node *node){
  //If node points to nothing
  if(node != nullptr){
    //Traverse through all the possible character values.
    for(int k=0; k < 26; k++){
      //Recursively call each branch from current node.
      countPrefixNum(node->children[k]); //Use recursion to go through all the possible children and nodes.
    }

    //If we find a node with the terminal value set to true.
    if(node->terminal == true){
        prefix_counter++; //If we encounter a terminal node then add 1 to the counter.
      }
  } else{
    //do nothing
  }
};

//Outputs the number of words in the trie with the given prefix.
void SpellChecker::outputPrefix(const std::string& string){

  int string_index = 0; //Integer for the index of the string.
  Node* curr = root; //set curr to root.
  
  //Traverse through the current prefix string.
  while(string_index < string.length()){
    char current_char = string[string_index]; //Stores the current char into char variable.
    int char_index = current_char - 65; //Takes the capital character and moves it down to start 'A' at index 0 to 'Z' at index 25
    
    //if at any point in the actual string, where it points to nullptr, then there are none with that prefix so return.
    if(curr->children[char_index] == nullptr){
      std::cout << "not found" << std::endl; //Output statement
      return; //return
    }
    curr = curr->children[char_index]; //Increment current pointer
    string_index++; //Increment string index
  }
  prefix_counter = 0; //Re set the prefix counter to 0 so that it does not keep adding up each time.
  countPrefixNum(curr); //Send curr node to the count prefix helper function.
  std::cout << "count is " << prefix_counter << std::endl; //Output number of words with that same prefix.
};

//Helper function to check if a node has 0 children.
bool zeroChildren(Node* node){
  //iterate through all children nodes
  for(int k= 0; k < 26; k++){
    if(node->children[k] != nullptr){
      return false; //If we see that a children node does not point to nullptr then return false.
    }
  }
  return true; //otherwise return true.
};

 //Helper function to help delete the word.
 bool SpellChecker::eraseWordHelperFunction(Node *node, const std::string& string, int length, bool& if_word_deleted) {
    
    if(node == nullptr){ //if current node is nullptr then return false
      return false;
    }
    //If we are on the last character in the string.
    if (length == string.size()) {
      //Check if the terminal value on the node is true.
      if (node->terminal == true) {
          node->terminal = false; //Set the node's terminal value to false to make it not the end of the word.
          number_of_words = number_of_words - 1; //Decrement the nunmber of words.
          if_word_deleted = true; //set the if word deleted variable to true because we have deleted the word successfully.
      }
      return zeroChildren(node); //If function returns true then that means we can delete our node, thus return this value.
    }
    
    char current_char = string[length]; //Store the current character into the char variable.
    int index = current_char - 65; //find the index by subtracting 65 from the current character.
    bool childDeleted = eraseWordHelperFunction(node->children[index], string, length + 1, if_word_deleted); //Recurse the function with the children (for deletion of subtree purposes)

    if (node->children[index] == nullptr) { //if the next character does not have a child node then return false. 
        return false;
    } else{
      //do nothing
    }

    if (childDeleted == true) { //Using the recursive function stored in childDeletd, if it was ever found that we wanted to delete the child then this deletes it.
        delete node->children[index]; //delete the children.
        node->children[index] = nullptr; //Set the children to nullptr.
    } else{
      //do nothing
    }
    //Return statement consists of three conditions to ensure that it does not delete any nodes that are needed for other words in the tree.
    return ((node->terminal == false) && (if_word_deleted == true) && (zeroChildren(node) == true));
}

//Erase a word from the trie if it already exists.
void SpellChecker::eraseWord(const std::string& string) {
    bool if_word_deleted = false; //bool variable to track if word has been deleted or not.
    eraseWordHelperFunction(root, string, 0, if_word_deleted); //call the function and get the return value to output the correct statement.

    if(if_word_deleted == true){ //If we deleted the word then print success.
      std::cout << "success" << std::endl;
    }else{ //Otherwise print failure.
      std::cout << "failure" << std::endl;
    }
};

//Helper Function that helps with print words function
void SpellChecker::printRecurse(Node* node, const std::string& string){
  //If node points to nullptr then return
  if(node != nullptr){
    //If it is a terminal node then print the word
    if(node->terminal == true){
      std::cout << string << " ";
    }
    // Loop through all children nodes.
    for(int k = 0; k < 26; k++){
      if(node->children[k] != nullptr){  //If a node does not equal nullptr then recurse again.
        char nextcharacter = 65 + k; //calculate the next character to compute.
        printRecurse(node->children[k], string + nextcharacter); //Recurse with updated values
      }
    }
  }else{
    return; //else return
  }
};

//Prints all words in alphabetical order.
void SpellChecker::printWords(){
  printRecurse(root, ""); //Send the root and a empty string to the helper function.
  if(number_of_words > 0){
  std::cout << std::endl; //Need to create helper function so that we can print an endl without printing multiple.
  }

};

//Helper function for printing words with the same prefix as the entered input and giving them as suggestions.
void SpellChecker::wordsWithPrefix(Node *node, const std::string& string){
  //If node points to nullptr then return.
  if(node == nullptr){
    return;
  }
  //If we are at the end of a word then print it with a space.
  if(node->terminal == true){
    std::cout << string << " ";
  }
  //Loop through all children nodes.
  for(int k = 0; k < 26; k++){
    if (node->children[k] != nullptr){  //If a node does not equal nullptr then recurse again.
        char current_char = 65 + k; //calculate the next character to compute.
        wordsWithPrefix(node->children[k], string + current_char); //Recurse with updated values.
    }
  }
};

//To check if a word is in the trie or give suggestions.
void SpellChecker::spellcheck(const std::string& string){
  int string_index = 0; //create the string index integer and initiate with 0.
  Node* curr = root; //Create curr pointer and assign it root.
  std::string prefix; //create string called prefix to store the prefix of the word being searched.
  bool isMatch = true; //flag to indicate if we find a match.
  char first_char = string[0]; //Stores the first character of the string.
  int first_char_index = first_char - 65; //Stores the first character to an integer.
  //If that first children with that index is equal to nullptr then output an endl.
  if(curr->children[first_char_index] == nullptr){
      std::cout << std::endl; //print end line.
    }
  
  //Go through each character in the string.
  while(string_index < string.length()){
    char current_char = string[string_index]; //Stores the current char into char variable.
    int char_index = current_char - 65; //Takes the capital character and moves it down to start 'A' at index 0 to 'Z' at index 25
        
    //If we find that the character in the string is not found then we did not find a match.
    if(curr->children[char_index] == nullptr){ 
      isMatch = false; //Set isMatch to false and break
      break;
    } 
    prefix = prefix + current_char; //Add the current character to the prefix.
    curr = curr->children[char_index]; //Move to the next node in the tree.
    string_index++; //Move to the next character in the string.
  }
  //exit the function if we find that the first character is not a match.
  if (!isMatch && prefix.empty()) {
    return; // Exit the function if the first character does not match.
  }
  //If we find that the string is a match and that the last node has true for the terminal then its a match.
  if(((curr->terminal == true) && (isMatch == true))){
    std::cout << "correct"; //output that we found a match
  }
  //if it is not a match but we find a prefix, then we now need to suggest strings with same prefix.
  else if(isMatch != true && prefix.empty() != true){
    //Check if there are suggestions starting with the first character in the prefix.
    if((prefix.length() > 0) && (root->children[prefix[0] - 65] != nullptr)){
      wordsWithPrefix(curr, prefix); //send the curr pointer and prefix to get suggestions for that prefix.
    }
  }else{ //If isMatch is false but there are possible suggestions.
    wordsWithPrefix(curr, prefix); //send the curr pointer and prefix to get suggestions for that prefix.
  }
  std::cout << std::endl; //go to next line.
}; 

//Check to see if the trie is empty.
void SpellChecker::checkEmpty(){
  //If there are no words in the trie, then print empty 1
  if(number_of_words == 0){
    std::cout << "empty 1" << std::endl;
  }else{ //else print empty 0
    std::cout << "empty 0" << std::endl;
  }
}; 

//Deletes all the words from the trie.
void SpellChecker::clearTrie(){
  deleteTrie(root); //Call the delete trie function and send it the root pointer.
  root = nullptr; //Set root to nullptr to avoid pointer errors.
  root = new Node();  //Create a new Node and set root pointer to that node so that you can readd strings.
  number_of_words = 0; //Set the number of words to 0.
  std::cout << "success" << std::endl; //print the sucess statement.
}; 

//Print the number of words in the trie.
void SpellChecker::printSize(){
  std::cout << "number of words is " << number_of_words << std::endl; //Print out the number of words.
}; 

//Function that loads the Corpus file into the tree.
void SpellChecker::loadCorpus(){
  std::ifstream corpusfile("corpus.txt"); //Open the corpus file and name it corpusfile.
  std::string eachline; //string that stores each line.

  //If file was opened
  if (corpusfile.is_open() == true) { 
    //Keep iterating the file line by line until the end of the file is reached.
    while (getline(corpusfile, eachline)) {
        std::istringstream parse(eachline); //Parse line into words and store into parse. 
        std::string word; //string called word that stores each word that was parsed from the line.

        //extract the word from the line and then insert into the tree using corresponding function.
        while ((parse >> word)) {
          insertWord(word);
        }
    }

    corpusfile.close(); //slose the corpus file
    std::cout << "success" << std::endl; //output success
    return; //return

  } else{ //If file was not opened then output failure and return
    std::cout << "failure" << std::endl;
    return;
  }
};
  