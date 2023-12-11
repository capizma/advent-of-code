ls = ['one','two','three','four','five','six','seven','eight','nine']

total = 0
num_total = 0

f = open("input.txt", "r")
for x in f:
    highest_pos = 0
    highest_dig = 0
    highest_str = 0
    
    for idx,char in enumerate(reversed(x)):
        if char.isdigit():
            highest_pos = len(x)-(idx+1)
            highest_str = int(char)
            highest_dig = highest_str
            break
    
    for idx,item in enumerate(ls):
        if (x.rfind(item) > highest_pos and x.rfind(item) != -1):
            highest_str = idx+1
            highest_pos = x.rfind(item)
            
    lowest_pos = len(x)+1
    lowest_str = 0
    lowest_dig = 0
    
    for idx,char in enumerate(x):
        if char.isdigit():
            lowest_pos = idx
            lowest_str = int(char)
            lowest_dig = lowest_str
            break
    
    for idx,item in enumerate(ls):
        if (x.find(item) < lowest_pos and x.find(item) != -1):
            lowest_str = idx+1
            lowest_pos = x.find(item)
        
    total += int(str(lowest_dig) + str(highest_dig))
    num_total += int(str(lowest_str) + str(highest_str))
    
print("Part 1: "+str(total))
print("Part 2: "+str(num_total))
    
