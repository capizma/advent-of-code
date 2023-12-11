ls = []
symbols = ['*','+','-','#','@','%','/','&','$','=']
total = 0
gears = {}
gears_total = 0

f = open("input.txt", "r")
for x in f:
    ls.append([char for char in x])

def check_bounds(pos_x,pos_y,lendigit,digit):
    found = False
    for r in range(max(pos_x-1,0),min(pos_x+lendigit+1,139)):
        if ls[pos_y][r] in symbols: 
            found = True
        if ls[pos_y][r] == "*":
            if str((pos_y*139)+(r)) not in gears.keys():
                gears[str((pos_y*139)+(r))] = []
            gears[str((pos_y*139)+(r))].append(int(digit))
            
    if pos_y > 0:
        for r in range(max(pos_x-1,0),min(pos_x+lendigit+1,139)):
            if ls[pos_y-1][r] in symbols: 
                found = True
            if ls[pos_y-1][r] == "*":
                if str(((pos_y-1)*139)+(r)) not in gears.keys():
                    gears[str(((pos_y-1)*139)+(r))] = []
                gears[str(((pos_y-1)*139)+(r))].append(int(digit))
    if pos_y < 139:
        for r in range(max(pos_x-1,0),min(pos_x+lendigit+1,139)):
            if ls[pos_y+1][r] in symbols: 
                found = True
            if ls[pos_y+1][r] == "*":
                if str(((pos_y+1)*139)+(r)) not in gears.keys():
                    gears[str(((pos_y+1)*139)+(r))] = []
                gears[str(((pos_y+1)*139)+(r))].append(int(digit))
    return found
        
for idx_y,line in enumerate(ls):
    current_digit = "";
    ondigit = False
    pos = 0
    for idx,char in enumerate(ls[idx_y]):
        if char.isdigit():
            if (ondigit == False):
                pos = idx
            ondigit = True
            current_digit += char;
        elif current_digit != "":
            ondigit = False
            if check_bounds(pos,idx_y,len(current_digit),current_digit):
                total+=int(current_digit)
            
            current_digit = ""

for key,val in gears.items():
    if len(val) == 2:
        print(val)
        gears_total += val[0]*val[1]
        
print("Part 1: "+str(total))
print("Part 2: "+str(gears_total))

