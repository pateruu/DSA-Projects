#include <iostream>
#include <unordered_map> 

//Class for Edges
class Edge{
    friend class Map; //Friend class makes it's content accessible to Map class.
    private:
        double distance; //Distance between two vertices.
        double speed_limit; //Speed limit between two vertices.
        double adjustment_factor; //Adjustment factor that represents the traffic data.

    public:
        Edge(); //Default Constructor for Edge class.
        Edge(double distance, double speed_limit, double adjustment_factor); //Parameterized constructor for Edge class.
        ~Edge(); //Destructor for Edge class.
};

//Class for Map
class Map{

    private:
        std::unordered_map<int, std::unordered_map<int, Edge>> map; //Represents the adjacency list, where each node is associated with a map (outer map) of its adjacent nodes (inner map) and has the edges connecting the two.
        std::unordered_map<int, double> distances; //Stores the shortest distances from the source.
        std::unordered_map<int, int> predecessors; //Stores predecessors to reconstruct the shortest path.

    public:
        Map(); //Constructor for Map class.
        ~Map(); //Destructor for Map class.
        void printall(); //Print function for the map, distances, and predecessors unordered maps.

        void insert_to_map(const std::string& string); //Function to insert an edge into the map.
        void load(const std::string& curr_file); //Function to load the dataset into the map.
        bool traffic(const std::string& string); //Function to update the adjustment factor.
        bool update(const std::string& file); //Function to load the dataset into the map.
        void print_a(int a); //Function to print all vertices adjacent to a.
        void delete_a(int a); //Function to delete vertex a and any edges containing a.
        void path(const std::string& string); //Function to print all vertices along the lowest weight path.
        bool lowest(const std::string& string); //Function to print the weight of the lowest weight path, if a path exists.
        void dijkstras_algorithm(int a); //Node to node shortest path searching algorithm.
};  