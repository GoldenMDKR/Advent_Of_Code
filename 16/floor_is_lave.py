import sys

sys.setrecursionlimit(100000000)

def parse(file) :
    data = []
    while ( line := file.readline().strip('\n')) :
        data.append([*line])
    return data

def move_light(data, enegized_vert, enegized_hori, x, y, dirr) :

    if x >= len(data) or x < 0 or y >= len(data[x]) or y < 0:
        return
    match dirr :
        case (0,1) | (0,-1):
            if enegized_hori[x][y] and data[x][y] != '\\' and  data[x][y] != '/':
                return
            enegized_hori[x][y] = 1
        case (1,0) | (-1,0):
            if enegized_vert[x][y] and data[x][y] != '\\' and  data[x][y] != '/':
                return
            enegized_vert[x][y] = 1

    match data[x][y] :
        case '.' : 
            move_light(data, enegized_vert, enegized_hori, x+dirr[0],y+dirr[1], dirr)
            return
        case '|' : 
            if dirr == (1,0) or dirr == (-1,0) :
                move_light(data, enegized_vert, enegized_hori, x+dirr[0],y+dirr[1], dirr)
                return
            move_light(data, enegized_vert, enegized_hori, x+1,y, (1,0))
            move_light(data, enegized_vert, enegized_hori, x-1,y, (-1,0))
            return 
        case '-' : 
            if dirr == (0,1) or dirr == (0,-1) :
                move_light(data, enegized_vert, enegized_hori, x+dirr[0],y+dirr[1], dirr)
                return
            move_light(data, enegized_vert, enegized_hori, x,y+1, (0,1))
            move_light(data, enegized_vert, enegized_hori, x,y-1, (0,-1))
            return 
        case '\\' : 
            move_light(data, enegized_vert, enegized_hori, x+dirr[1],y+dirr[0], (dirr[1],dirr[0]))
            return 
        case '/' : 
            move_light(data, enegized_vert, enegized_hori, x-dirr[1],y-dirr[0], (-dirr[1],-dirr[0]))
            return 
    
    print(data[x][y])
    print(wtf)
    return


def count(hori,vert) :
    return sum([sum([char_v | char_h for (char_v, char_h) in zip(line_v, line_h)]) for (line_v, line_h) in zip(vert,hori)])



def sol_1(file):
    data = parse(file)
    enegized_vert = [[0 for _ in i] for i in data]
    enegized_hori = [[0 for _ in i] for i in data]
    move_light(data,enegized_vert, enegized_hori, 0,0,(0,1))
    # for lineh,linev in zip(enegized_hori,enegized_vert):
    #     for ch, cv in zip(lineh,linev):
    #         print('#' if ch | cv else '.', end='')
    #     print(f" {lineh} , {linev}") 
    return count(enegized_hori,enegized_vert)

def sol_2(file):

    data = parse(file)
    res = 0
    for j in range(len(data)) :
        enegized_vert = [[0 for _ in i] for i in data]
        enegized_hori = [[0 for _ in i] for i in data]
        move_light(data, enegized_vert, enegized_hori, j, 0, (0,1))
        res = max(res, count(enegized_hori,enegized_vert))



        enegized_vert = [[0 for _ in i] for i in data]
        enegized_hori = [[0 for _ in i] for i in data]
        move_light(data, enegized_vert, enegized_hori, j, len(data[0])-1, (0,-1))
        res = max(res, count(enegized_hori,enegized_vert))

    for j in range(len(data[0])) :

        enegized_vert = [[0 for _ in i] for i in data]
        enegized_hori = [[0 for _ in i] for i in data]
        move_light(data, enegized_vert, enegized_hori, len(data)-1, j, (-1,0))
        res = max(res, count(enegized_hori,enegized_vert))

        enegized_vert = [[0 for _ in i] for i in data]
        enegized_hori = [[0 for _ in i] for i in data]
        move_light(data, enegized_vert, enegized_hori, 0, j, (1,0))
        res = max(res, count(enegized_hori,enegized_vert))
    return res



if __name__ == "__main__" :
    input_test = open("test.txt", "r")
    input_real = open("input.txt", "r")


    print(sol_1(input_test))
    print(sol_1(input_real))


    input_test = open("test.txt", "r")
    input_real = open("input.txt", "r")

    print(sol_2(input_test))
    print(sol_2(input_real))