DISTANCE = 1000000


def parse(file) -> list:
    l = file.read().split("\n")
    for i in range(len(l)) :
        l[i] = [*l[i]]
    return l

def expand(image : list) -> list : 
    new_image = []
    for l in image : 
        if '#' not in l :
            new_image.append(l)
        new_image.append(l)
    
    final_image = [[] for _ in new_image]

    for i in range(len(new_image[0])) :
        if '#' not in [new_image[j][i] for j in range(len(new_image))] :
            for j in range(len(final_image)) :
                final_image[j].append(new_image[j][i]) 
        for j in range(len(final_image)) :
            final_image[j].append(new_image[j][i]) 
    return final_image

def find_dist_this(image : list, x : int, y : int) -> int :
    this_dist = 0
    for j in range(y, len(image[x])) :
        if image[x][j] == '#' :
            this_dist += j - y
    
    for i in range(x+1, len(image)) :
        for j in range(len(image[i])) :
            if image[i][j] == '#' :
                this_dist += abs(j - y) + abs(i - x)
    
    return this_dist


def find_dist(image : list) -> int :
    tot_dist = 0
    for i in range(len(image)) :
        for j in range(len(image[i])) :
            if image[i][j] == '#' :
                tot_dist += find_dist_this(image, i, j) 
    return tot_dist

def sol_1(entry) :
    image = parse(entry) 
    expended = expand(image)
    return find_dist(expended)


def expand_2(image : list) -> list : 
    expanded_list_x = []
    for i in range(len(image)) : 
        if '#' not in image[i] :
            expanded_list_x.append(i)

    expanded_list_y = []

    for i in range(len(image[0])) :
        if '#' not in [image[j][i] for j in range(len(image))] :
            expanded_list_y.append(i)

    return (expanded_list_x,expanded_list_y)

def find_dist_this_2(image : list, x : int, y : int, ex : int, ey : int) -> int :
    this_dist = 0
    real_y = 0
    for j in range(y+1, len(image[x])) :
        if j in ey :
            real_y += DISTANCE
        else :
            real_y += 1
        if image[x][j] == '#' :
            this_dist += real_y
    real_x = 0
    
    for i in range(x+1, len(image)) :
        real_y = 0
        if i in ex :
            real_x += DISTANCE
        else :
            real_x += 1
        if image[i][y] == '#' :
            this_dist += real_x
        for j in range(y+1, len(image[i])) :
            if j in ey :
                real_y += DISTANCE
            else :
                real_y += 1
            if image[i][j] == '#' :
                this_dist += real_y + real_x

        real_y = 0
        for j in range(y-1, -1, -1) :
            if j in ey :
                real_y += DISTANCE
            else :
                real_y += 1
            if image[i][j] == '#' :
                this_dist += real_y + real_x

    
    return this_dist


def find_dist_2(image : list, ex : int, ey : int) -> int :
    tot_dist = 0
    for i in range(len(image)) :
        for j in range(len(image[i])) :
            if image[i][j] == '#' :
                tot_dist += find_dist_this_2(image, i, j, ex, ey) 
    return tot_dist

def sol_2(entry) :
    image = parse(entry) 
    (ex,ey) = expand_2(image)
    return find_dist_2(image, ex, ey)

if __name__ == "__main__" :
    input_test = open("test.txt", "r")
    input_real = open("input.txt", "r")


    print(sol_1(input_test))
    print(sol_1(input_real))


    input_test = open("test.txt", "r")
    input_real = open("input.txt", "r")

    print(sol_2(input_test))
    print(sol_2(input_real))