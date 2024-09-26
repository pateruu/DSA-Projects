#include "graph.h"
#include <iostream>
#include <unordered_map> 
#include <queue>
#include <sstream>
#include <fstream>
#include <iomanip>

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       Edge Class        /////////////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Default Constructor for Edge class.
Edge::Edge(){
    distance = 0.0; //Set values to 0
    speed_limit = 0.0; 
    adjustment_factor = 0.0;
};

//Constructor for Edge class with parameters.
Edge::Edge(double distance, double speed_limit, double adjustment_factor){
    this->distance = distance; //Update values given for edge to the variables when initializing.
    this->speed_limit = speed_limit; 
    this->adjustment_factor = adjustment_factor;
};

//Destructor for Edge class.
Edge::~Edge(){
    distance = 0.0; //Set values to 0
    speed_limit = 0.0; 
    adjustment_factor = 0.0;
}; 

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////       Map Class        //////////////////////////////////////////////////////////////////////////////
*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Constructor for Map class.
Map::Map(){
    //nothing needed
};

//Destructor for Map class.
Map::~Map(){
    //nothing needed
}; 

//Function to insert an edge into the map.
void Map::insert_to_map(const std::string& string){
    int a; //int for vertex a.
    int b; //int for vertex b.
    double d; //distance between the two vertices.
    double s; //speed limit between the two vertices.

    std::istringstream concatenate(string);
    concatenate >> a >> b >> d >> s; //Concatenate the string with these two lines and put them into the 4 variables.

    if(map.find(a) == map.end()){ //if vertex a does not exist, then add it.
        map[a] = std::unordered_map<int, Edge>(); //Added vertex with empty map.
    }
    if(map.find(b) == map.end()){ //if vertex b does not exist, then add it.
        map[b] = std::unordered_map<int, Edge>(); //Added vertex with empty map.
    } 
    
    //Check if the edge exists so we can update values.
    if(map[a].find(b) != map[a].end()) {
        map[a][b].distance = d; //Update distance from a to b if edge exists.
        map[a][b].speed_limit = s; //Update speed limit from a to b if edge exists.
        map[b][a].distance = d; //Update distance for reverse.
        map[b][a].speed_limit = s; //Update speed limit for reverse.
    }else{ //Edge does not exist, so create the new edge.
        //Due to the map being undirected, the edge must be reachable from both vertices.
        map[a][b] = Edge(d, s, 1.0); //Map from vertex a to vertex b and send it the edge values.
        map[b][a] = Edge(d, s, 1.0); //Map from vertex b to vertex a and send it the edge values.
    }
}; 

//Function to load the dataset into the map.
void Map::load(const std::string& curr_file){
    std::ifstream file(curr_file); //attempt to open the file.

    std::string each_line; //String for each line in the file.
    while(std::getline(file, each_line)){ //Keep reading each line from file.
        insert_to_map(each_line); //Send that word to the insert function to insert it into our dictionary.
    }
    std::cout << "success" << std::endl; //Output success after fully completing the load.
    file.close(); //Close the file.
}; 

//Function to update the adjustment factor.
bool Map::traffic(const std::string& string){
    int a; //int for vertex a.
    int b; //int for vertex b.
    double a_factor; //adjustment factor between a and b.

    std::istringstream concatenate(string); 
    concatenate >> a >> b >> a_factor; //Concatenate the string with these two lines and put them into the 3 variables.

    if((a_factor <= 1) && (a_factor >= 0)){ //If the adjustment factor is a valid factor.
        if((map.find(a) != map.end()) && (map[a].find(b) != map[a].end())){ //If we find the index a and then the index b branching from index a. This means we have a edge from a to b.
            map[a][b].adjustment_factor = a_factor; //Update the adjustment factor if both indices exist.
            return true; //return true if we updated the adjustment factor correctly.
        }else{
            return false; //return false if a vertex does not exist or there is no edge from a to b.
        }
    } else{
        return false; //return false if adjustment factor is outside of range.
    }
}; 

//Function to load the dataset into the map.
bool Map::update(const std::string& curr_file){
    std::ifstream file(curr_file); //attempt to open the file.
    bool if_any_updated = false; //Bool variable for if we made any updates.

    std::string each_line; //String for each line in the file.
    while(std::getline(file, each_line)){ //Keep reading each line from file.
        bool get_each_bool = traffic(each_line); //Send that word to the insert function to insert it into our dictionary.
        if(get_each_bool == true){ //If we get any updated values.
            if_any_updated = true; //Set the overal if any updated variable to true.
        }
    }
    file.close(); //Close the file.
    return if_any_updated; //return if_any_updated to output correct statement.
}; 

//Function to print all vertices adjacent to a.
void Map::print_a(int a){
    auto iterator_find_a = map.find(a); //iterator to find vertex a from map.
    if((iterator_find_a != map.end())){ //If we find the first vertex that we want and also has neighbors.
        if(iterator_find_a->second.empty() == false){  //if that vertex has neighbours.
            for(const auto& iterating_variable : iterator_find_a->second){ //create iterator to iterate through the adj list.
                std::cout << iterating_variable.first << " "; //Print the first object which is vertex b and keep doing it until we reach the end.
            }
        }
        std::cout << std::endl; //print an endl
    } else{
        std::cout << "failure" << std::endl; //Otherwise output failure
    }
};

//Function to delete vertex a and any edges containing a.
void Map::delete_a(int a){

    if(map.find(a) != map.end()){ //If we find vertex a in the graph.
        for(auto iterating_variable = map.begin(); iterating_variable != map.end();){ //create iterator that iterates through the map.
            if(iterating_variable->first != a){ //To make sure current vertex is not a.
                iterating_variable->second.erase(a); //erase the edge from the adjacency list if it points to vertex a.
                iterating_variable++; //Increment the iterator.
            } else{ //else if current vertex is vertex a.
                iterating_variable = map.erase(iterating_variable); //get the next iterator after erasing vertex a.
            }
        }
        map.erase(a); //After erasing all the edges that contained a properly, we can now erase vertex a itself.
        std::cout << "success" << std::endl; //Print success if we find vertex.
    }else{ //If we do not find vertex a.
        std::cout << "failure" << std::endl; //Print failure if we do not find vertex.
    }
};

//Function to print all vertices along the lowest weight path.
void Map::path(const std::string& string){
    int a; //int for vertex a.
    int b; //int for vertex b.

    std::istringstream concatenate(string); 
    concatenate >> a >> b; //Concatenate the string with these two lines shown and put them into the 2 variables.

    if (map.find(a) == map.end() || map.find(b) == map.end()) { //If both vertices are not in the graph then print failure and return.
        std::cout << "failure" << std::endl; 
        return;
    }

    dijkstras_algorithm(a); //Call dijkstras algorithm and give it vertex a to calculate shortest path from it to all other vertices.

    if(predecessors[b] == -1){ //If predecessor of b is equal to -1, this means that there is no path to vertex b, and thus we output failure and return.
        std::cout << "failure" << std::endl;
        return;
    }
    if(distances[b] == std::numeric_limits<double>::infinity()){ //Else if distance to vertex b is infinite, print failure because the path is unreachable.
        std::cout << "failure" << std::endl;
        return;
    }

    std::deque<int> path; //Create a deque to store the path from index b to index a using the predecessors map. Using deque so we can add to front for correct printing.
    int current = b; //Start from b and go to the a.
    while(current != -1){ //While we have not reached a.
        path.push_front(current); //Push the current vertex to the front of the path.
        if (predecessors[current] == -1) { //If we reached the source then break.
            break;
        }
        current = predecessors[current]; //Go to the predecessor of current.
        if (current < 0 || current >= predecessors.size()) { 
            std::cout << "failure" << std::endl; //To make sure the range is valid, print failure if invalid index shows up.
            return;
        }
    }

    std::string final_string; //Create string variable for the final print statement.
    for(int k{0}; k < path.size(); k++){ //Iterate through the path which stores the shortest path.
        std::string int_to_string = std::to_string(path[k]); //Then convert each index integer to a string.
        final_string = final_string + (int_to_string + " "); //Concatenate each string into the total string for later use of printing with a " ".
    }
    std::cout << final_string << std::endl; //Now finally print the full string with an endl.
};

//Function to print the weight of the lowest weight path, if a path exists.
bool Map::lowest(const std::string& string){
    int a; //int for vertex a.
    int b; //int for vertex b.

    std::istringstream concatenate(string); 
    concatenate >> a >> b; //Concatenate the string with these two lines shown and put them into the 2 variables.

    if (map.find(a) == map.end() || map.find(b) == map.end()) { //If both vertices are not in the graph then print failure and return.
        return 0;
    }

    dijkstras_algorithm(a); //Call dijkstras algorithm and give it vertex a to calculate shortest path from it to all other vertices.

    if(distances[b] == std::numeric_limits<double>::infinity()){ //If distance to vertex b is infinite, print failure because the path is unreachable.
        return 0; //Return false
    }else{
        std::cout << std::fixed << std::showpoint;
        std::cout << std::setprecision(3);
        std::cout << distances[b] << std::endl; //Here the path exists to vertex b, so we print the lowest weight path to vertex b.
        return 1; //return true
    }
    return 0; //return false if no returns happened.
};

//Node to node shortest path searching algorithm.
void Map::dijkstras_algorithm(int a){
    //Set all the distances to infinity except the source
    for (const auto& each_vertex : map) { //Iterate through each vertex in the map.
        distances[each_vertex.first] = std::numeric_limits<double>::infinity(); //Set all the distances to infinity.
        predecessors[each_vertex.first] = -1; //-1 reperesents no predecessor.
    }
    distances[a] = 0.0; //Set the source distance to 0.

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> priority_queue; //Create a priority queue that holds vertices which are sorted by their distance. The closer to the root, the smaller the distance they have.
    priority_queue.push(std::make_pair(0.0, a)); //Add the vertex a with a distance of 0 as the starting point to the priority queue.

    while(priority_queue.empty() == false){ //Keep doing while our priority queue is not empty.
        int current_vertex = priority_queue.top().second; //put the vertex itself into current_vertex.
        priority_queue.pop(); //then remove that vertex from the priority queue.

        for(const auto& adjacent_vertices : map[current_vertex]){ //Iterate through all the adjacent vertices, and update distances and predecessors.
            int adjacent_vertex = adjacent_vertices.first; //Stores the adjacent vertex.
            double weight = adjacent_vertices.second.distance / (adjacent_vertices.second.speed_limit * adjacent_vertices.second.adjustment_factor); //Calculate the weight
            
            if((distances[adjacent_vertex]) > (distances[current_vertex] + weight)){ //If the calculated distance to the adjacent vertex is shorter than the previous distance, then update distance and predecessor.
                distances[adjacent_vertex] = distances[current_vertex] + weight; //update the distance.
                predecessors[adjacent_vertex] = current_vertex; //update the predecessor.
                priority_queue.push(std::make_pair(distances[adjacent_vertex], adjacent_vertex)); //Add the updated vertex with its updated shortest distance and give it to the priority queue for further processing of the paths until the priority queue is empty.
            }
        }
    }
};

//Print function for the map, distances, and predecessors unordered maps.
void Map::printall() {
    //Prints the Map
    std::cout << "---------MAP----------" << std::endl;
    for (auto vertex_pair:map) {
        std::cout << "A: " << vertex_pair.first << std::endl;
        for (auto edge_pair:vertex_pair.second) {
            std::cout << "\t" << edge_pair.first << ": " << edge_pair.second.distance << ", " << edge_pair.second.speed_limit << ", " << edge_pair.second.adjustment_factor << std::endl;
        }
    }

    //Prints the Distances
    std::cout << "---------DISTANCES----------" << std::endl;
    for (auto distance_pair:distances) {
        std::cout << distance_pair.first << ": " << distance_pair.second << std::endl;
    }

    //Prints the Predecessors
    std::cout << "---------PREDECESSORS----------" << std::endl;
    for (auto predecessor_pair:predecessors) {
        std::cout << predecessor_pair.first << ": " << predecessor_pair.second << std::endl;
    }
};