steps = ""
nodes = {}

# Read input file + append to array
with open('input_day8.txt', 'r') as file:
    # Enumerate since we need to perform different operations for different lines
    for idx,line in enumerate(file):
        # Fetch steps on line 0
        if idx == 0:
            steps = line.strip()
        # Everything left is nodes
        elif idx > 1:
            # Transform AAA = (BBB,CCC) into nodes['AAA'] = ['BBB','CCC']
            # so we can easily index this later
            index = line[:3]
            branches = [line[7:10],line[12:15]]
            nodes[index] = branches
            
# As left and right will equate to 0 and 1 respectively indexing the node,
# represent them as such

steps = steps.replace("L","0").replace("R","1")

######################## Part 1 ############################
            
curr_node = "AAA"
end_reached = False
current_step = 0

# Recursively gets the next node and follows path
while (end_reached == False):
    # Modulus to repeat list indexing
    curr_node = nodes[curr_node][int(steps[(current_step % len(steps))])]
    current_step += 1
    if curr_node == "ZZZ":
        end_reached = True
    
# Answer 1 
# print(current_step)

######################## Part 2 ############################

import math

node_steps = []

# Gather nodes that end in A
curr_nodes = []

for key in nodes.keys():
    if key[2] == "A":
        curr_nodes.append(key)
        
# Get the amount of steps until a key that ends in Z is reached
for node in curr_nodes:
    curr_node = node
    end_reached = False
    current_step = 0
    
    # Recursively gets the next node and follows path
    while (end_reached == False):
        # Modulus to repeat list indexing
        curr_node = nodes[curr_node][int(steps[(current_step % len(steps))])]
        current_step += 1
        if curr_node[2] == "Z":
            end_reached = True
            
    node_steps.append(current_step)

# Least common multiple
def lcm(*step_counts):
    a = step_counts[0]
    for b in step_counts[1:]:
        a = (a * b) // math.gcd(a, b)
    return a
    
# Answer 2
# I have learned a lesson about trying to use parallel. And ghosts are much less efficient at traveling!!
# print(lcm(*node_steps))