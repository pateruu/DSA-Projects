import random
import os

# Author: Kevin Patel
# Date: March 25, 2024
# Project: ECE250 - Project4

#Test Case Generator for Project4
class TestGenerator:
    
    #Initial definition function
    def __init__(self) -> None:
        self.vertex_range = (1, 500000)
        self.distance_range = (0.1, 9999999999)
        self.speed_range = (0.1, 9999999999)
        self.adjustment_range = (0,1)
        self.commands = ["insert", "load", "traffic", "update", "print", "delete", "path", "lowest"]
        self.filenames = ["files/4-load.txt", "files/4-load_update.txt"]

    #Generate random vertex value
    def generate_vertex(self):    
        return random.randint(*self.vertex_range)
    
    #Generate random distance range
    def generate_distance_range(self):
        return random.uniform(*self.distance_range)
    
    #Generate random speed limit
    def generate_speed(self):
        return random.uniform(*self.speed_range)

    #Generate random adjustment factor
    def generate_adjustment(self):
        return random.uniform(*self.adjustment_range)
    
    #To generate the insert command
    def generate_insert_command(self):
        a = self.generate_vertex()
        b = self.generate_vertex()
        d = self.generate_distance_range()
        s = self.generate_speed()
        return f"insert {a} {b}{d: .2f}{s: .2f}\n"

    #To generate the load command
    def generate_load_command(self):
        return f"load {self.filenames[0]}\n"

    #To generate the traffic command
    def generate_traffic_command(self):
        a = self.generate_vertex()
        b = self.generate_vertex()
        A = self.generate_adjustment()
        return f"traffic {a} {b}{A: .2f}\n"

    #To generate the update command
    def generate_update_command(self):
        return f"load {self.filenames[1]}\n"
    
    #To generate the print command
    def generate_print_command(self):
        a = self.generate_vertex()
        return f"print {a}\n"

    #To generate the delete command
    def generate_delete_command(self):
        a = self.generate_vertex()
        return f"delete {a}\n"
    
    #To generate the path command
    def generate_path_command(self):
        a = self.generate_vertex()
        b = self.generate_vertex()
        return f"path {a} {b}\n"
    
    #To generate the lowest command
    def generate_lowest_command(self):
        a = self.generate_vertex()
        b = self.generate_vertex()
        return f"lowest {a} {b}\n"
    
    #To generate a random input command
    def generate_command(self):
        command_type = random.choice(self.commands)
        return getattr(self, f"generate_{command_type}_command")()
    
    #To generate test cases
    def generate_test_cases(self, num_commands=100):
        commands = [self.generate_command() for _ in range(num_commands)]
        commands.append("exit\n")
        return ''.join(commands)
    
    #To write to the test files
    def write_test_file(self, file_name, num_commands=100):
        test_case = self.generate_test_cases(num_commands)
        with open(file_name, 'w') as f:
            f.write(test_case)
    
#Main Function
if __name__ == "__main__":
    generator = TestGenerator()
    input_directory = 'test_inputs/1Mtest'
    os.makedirs(input_directory, exist_ok=True)

    for i in range(1, 5):  #Number of test cases to generate.
        file_name = f'{input_directory}{i:03d}.in'  #filename generator
        num_commands = 1000000  #number of lines.
        
        #Call the method to generate and write the test file
        generator.write_test_file(file_name, num_commands)
        print(f'Generated file: {file_name}')