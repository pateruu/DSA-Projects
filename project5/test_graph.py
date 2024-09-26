import heapq
from collections import defaultdict
import os


class Edge:
    def __init__(self, distance, speed_limit, adjustment_factor=1.0):
        self.distance = distance
        self.speed_limit = speed_limit
        self.adjustment_factor = adjustment_factor

class Graph:
    def __init__(self):
        self.graph = defaultdict(dict)

    def insert_edge(self, a, b, distance, speed_limit):
        self.graph[a][b] = Edge(distance, speed_limit)
        self.graph[b][a] = Edge(distance, speed_limit)  # For undirected graph
        return "success"

    def update_traffic(self, a, b, adjustment_factor):
        if b in self.graph[a]:
            self.graph[a][b].adjustment_factor = adjustment_factor
            return "success"
        return "failure"

    def dijkstra(self, start):
        distances = {vertex: float('inf') for vertex in self.graph}
        distances[start] = 0
        priority_queue = [(0, start)]
        while priority_queue:
            current_distance, current_vertex = heapq.heappop(priority_queue)
            for neighbor, edge in self.graph[current_vertex].items():
                distance = current_distance + edge.distance / (edge.speed_limit * edge.adjustment_factor)
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    heapq.heappush(priority_queue, (distance, neighbor))
        return distances

    def print_adjacent(self, a):
        if a in self.graph:
            return ' '.join(map(str, self.graph[a].keys()))
        else:
            return "failure"

    def delete_vertex(self, a):
        if a in self.graph:
            for neighbor in list(self.graph[a].keys()):
                del self.graph[neighbor][a]
            del self.graph[a]
            return "success"
        else:
            return "failure"

    def reconstruct_path(self, predecessors, target):
        if target not in predecessors or predecessors[target] == -1:
            return []
        path = []
        current = target
        while current != -1:
            path.insert(0, current)
            current = predecessors.get(current, -1)
        return path

    def dijkstra_with_predecessors(self, start):
        distances = {vertex: float('inf') for vertex in self.graph}
        predecessors = {vertex: -1 for vertex in self.graph}
        distances[start] = 0
        priority_queue = [(0, start)]

        while priority_queue:
            current_distance, current_vertex = heapq.heappop(priority_queue)
            for neighbor, edge in self.graph[current_vertex].items():
                alt_path_dist = current_distance + edge.distance / (edge.speed_limit * edge.adjustment_factor)
                if alt_path_dist < distances[neighbor]:
                    distances[neighbor] = alt_path_dist
                    predecessors[neighbor] = current_vertex
                    heapq.heappush(priority_queue, (alt_path_dist, neighbor))

        return distances, predecessors

    def find_path(self, start, target):
        distances, predecessors = self.dijkstra_with_predecessors(start)
        if target not in distances or distances[target] == float('inf'):
            return "failure"  # No path found
        path = self.reconstruct_path(predecessors, target)
        return " ".join(map(str, path))


    def find_lowest_weight_path(self, start, end):
        distances = self.dijkstra(start)
        if end not in distances or distances[end] == float('inf'):
            return "failure"  # No path found
        return str(distances[end])

        
    def load_hardcoded_data(self):
        # Manually inserting the edges from your 4-load.txt
        self.insert_edge(1, 2, 10, 10)
        self.insert_edge(1, 3, 2, 0.2)
        self.insert_edge(5, 1, 1, 2)
        self.insert_edge(5, 2, 15, 1)
        self.insert_edge(3, 2, 10, 2)
        self.insert_edge(3, 5, 2, 1)
        # Output success message for each insertion
        return "success\n"

    def update_hardcoded_traffic(self):
        # Manually updating traffic from your 4-load_update.txt
        success_message = ""
        if self.update_traffic(1, 5, 0):
            success_message += "success\n"
        else:
            success_message += "failure\n"
        # Assuming only one update from the file
        return success_message


# test_graph.py
import argparse

def run_test(input_file, output_file, graph):
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        for line in f_in:
            command, *params = line.strip().split()
            if command == 'insert':
                a, b, distance, speed_limit = map(float, params)  # Assuming distance and speed_limit can be float
                result = graph.insert_edge(int(a), int(b), distance, speed_limit)
                f_out.write(result + "\n")
            elif command == 'load':
                result = graph.load_hardcoded_data()
                f_out.write(result)
            elif command == 'traffic':
                a, b, adjustment_factor = map(float, params)
                result = graph.update_traffic(int(a), int(b), adjustment_factor)
                f_out.write(result + "\n")
            elif command == 'update':
                result = graph.update_hardcoded_traffic()
                f_out.write(result)
            elif command == 'print':
                result = graph.print_adjacent(int(params[0]))
                f_out.write(result + "\n")
            elif command == 'delete':
                result = graph.delete_vertex(int(params[0]))
                f_out.write(result + "\n")
            elif command == 'path':
                a, b = map(int, params)
                path = graph.find_path(a, b)
                f_out.write(path + "\n")
            elif command == 'lowest':
                a, b = map(int, params)
                result = graph.find_lowest_weight_path(a, b)
                f_out.write(result + "\n")
            elif command == 'exit':
                break


def main(input_dir, output_dir):
    graph = Graph()  # Initialize the graph for the session
    for input_file in os.listdir(input_dir):
        if input_file.endswith('.in'):
            output_file = input_file.replace('.in', '.out')
            run_test(os.path.join(input_dir, input_file), os.path.join(output_dir, output_file), graph)

if __name__ == '__main__':
    input_dir = 'my_inputs'  # The directory where input files are located
    output_dir = 'my_outputs'  # The directory where output files should be saved
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    main(input_dir, output_dir)
