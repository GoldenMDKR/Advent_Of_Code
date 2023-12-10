def parse(file) -> list:
    l = file.read().split("\n")
    for i in range(len(l)) :
        l[i] = [*l[i]]
    return l

def find_next(l : list, x : int,y : int, dirr : int) -> (int, int, int) :
    match l[x][y] :
        case '-' :
            if dirr == 1 :
                return (x, y+1, 1)
            return (x, y-1, 3)
        case '|' :
            if dirr == 2:
                return (x+1, y, 2)
            return (x-1, y, 4)
        case 'L' : 
            if dirr == 3:
                return (x-1 , y, 4)
            return (x, y+1, 1)
        case 'J' : 
            if dirr == 1:
                return (x-1, y, 4)
            return (x, y-1, 3)
        case '7' : 
            if dirr == 1:
                return (x+1, y, 2)
            return (x, y-1, 3)
        case 'F' : 
            if dirr == 3:
                return (x+1, y, 2)
            return (x, y+1, 1)
        case _ :
            return (0,0,0)

def find_further(l : list, x : int, y : int, dirr : int) -> int :
    dist = 1
    curr_pos_x = x
    curr_pos_y = y
    curr_dirr = dirr

    while (l[curr_pos_x][curr_pos_y] != 'S') :
        (curr_pos_x, curr_pos_y, curr_dirr) = find_next(l, curr_pos_x, curr_pos_y, curr_dirr)
        dist += 1
    

    return dist/2

def sol_1(entry) -> int:
    l = parse(entry)
    x, y = 0, 0
    for i in range(len(l)) :
        for j in range(len(l[i])) :
            if l[i][j] == 'S' :
                x, y = i, j
    dist = 0
    if l[x-1][y] == 'F' or l[x-1][y] == '|' or l[x-1][y] == '7' : 
        dist = find_further(l, x-1, y, 4)
    elif l[x+1][y] == 'J' or l[x+1][y] == '|' or l[x+1][y] == 'L' :
        dist = find_further(l, x+1, y, 2)
    elif l[x][y+1] == 'J' or l[x][y+1] == '-' or l[x][y+1] == '7' :
        dist = find_further(l, x, y+1, 1)
    
    return dist

def is_inside(l : list, x : int, y : int, loop : list) -> int :
    encounter = 0
    prev = 0

    for i in range(x, len(l)):
        if l[i][y] == '-' and (i, y) in loop:
            encounter += 1
            prev = 0
        elif l[i][y] == 'F' and (i, y) in loop : 
            prev = 1
        elif l[i][y] == 'J' and (i, y) in loop :
            if prev == 1 :
                encounter += 1
            prev = 0
        elif l[i][y] == '7' and (i, y) in loop : 
            prev = 2   
        elif l[i][y] == 'L' and (i, y) in loop : 
            if prev == 2 :
                encounter += 1
            prev = 0
    return encounter %2

def make_loop(l : list, x : int, y : int, dirr : int) -> int :
    curr_pos_x = x
    curr_pos_y = y
    curr_dirr = dirr
    loop = [(x,y)]
    while (l[curr_pos_x][curr_pos_y] != 'S') :
        (curr_pos_x, curr_pos_y, curr_dirr) = find_next(l, curr_pos_x, curr_pos_y, curr_dirr)
        loop.append((curr_pos_x, curr_pos_y))
    

    return loop


def sol_2(entry) -> int :
    l = parse(entry)
    x, y = 0, 0
    for i in range(len(l)) :
        for j in range(len(l[i])) :
            if l[i][j] == 'S' :
                x, y = i, j
    if l[x-1][y] == 'F' or l[x-1][y] == '|' or l[x-1][y] == '7' : 
        loop = make_loop(l, x-1, y, 4)
    elif l[x+1][y] == 'J' or l[x+1][y] == '|' or l[x+1][y] == 'L' :
        loop = make_loop(l, x+1, y, 2)
    elif l[x][y+1] == 'J' or l[x][y+1] == '-' or l[x][y+1] == '7' :
        loop = make_loop(l, x, y+1, 1)
    
    # hardcoded with my input cause fuck you    
    l[x][y] = '7'

    tot = 0
    for i in range(len(l)) :
        for j in range(len(l[i])) :
            if (i,j) not in loop :
                a = is_inside(l, i, j, loop)
                tot += a
    return tot



if __name__ == "__main__" :
    input_test = open("test.txt", "r")
    input_real = open("input.txt", "r")


    print(sol_1(input_test))
    print(sol_1(input_real))


    input_test = open("test.txt", "r")
    input_real = open("input.txt", "r")

    print(sol_2(input_test))
    print(sol_2(input_real))