import copy

def parse(file) -> list:
    l = file.read().split("\n")
    for i in range(len(l)) :
        l[i] = [*l[i]]
    return l


def push_add(platform) :
    tot = 0
    for j in range(len(platform[0])) :
        curr_send = 0
        for i in range(len(platform)) :
            if platform[i][j] == '#' :
                curr_send = i+1
            if platform[i][j] == 'O' :
                tot += len(platform)-curr_send
                curr_send += 1
    return tot
            
def roll(platform, dirr) :
    match dirr :
        case 0 :
            for j in range(len(platform[0])) :
                curr_send = 0
                for i in range(len(platform)) :
                    if platform[i][j] == '#' :
                        curr_send = i+1
                    if platform[i][j] == 'O' :
                        platform[i][j] , platform[curr_send][j] = platform[curr_send][j], platform[i][j]
                        curr_send += 1
            return platform

        case 1 :
            for i in range(len(platform)) :
                curr_send = 0
                for j in range(len(platform[0])) :
                    if platform[i][j] == '#' :
                        curr_send = j+1
                    if platform[i][j] == 'O' :
                        platform[i][j] , platform[i][curr_send] = platform[i][curr_send], platform[i][j] 
                        curr_send += 1
            return platform

        case 2 :
            for j in range(len(platform[0])) :
                curr_send = len(platform)-1
                for i in reversed(range(len(platform))) :
                    if platform[i][j] == '#' :
                        curr_send = i-1
                    if platform[i][j] == 'O' :
                        platform[i][j] , platform[curr_send][j] = platform[curr_send][j], platform[i][j]
                        curr_send -= 1
            return platform

        case 3 :
            for i in range(len(platform)) :
                curr_send = len(platform[0])-1
                for j in reversed(range(len(platform[0]))) :
                    if platform[i][j] == '#' :
                        curr_send = j-1
                    if platform[i][j] == 'O' :
                        platform[i][j] , platform[i][curr_send] = platform[i][curr_send], platform[i][j] 
                        curr_send -= 1
            return platform

def as_tuple(lis) :
    temp = copy.deepcopy(lis)
    for i in range(len(lis)) :
        temp[i] = tuple(temp[i]) 
    return tuple(temp)

def cycle(platform, nb) :
    seen=[copy.deepcopy(platform)]
    for i in range(nb) :
        for i in range(4) :
            roll(platform, i)  
        equal = 1
        for i in range(len(seen)) :
            if platform == seen[i]:
                loop = len(seen)-i
                return seen[(nb-i) % loop + i]

        seen.append(copy.deepcopy(platform))
    return platform

def count_load(platform):
    tot =0
    for i, line in enumerate(platform) :
        for char in line :
            if char == 'O' :
                tot += len(platform)-i
    return tot

def sol_1(file) :
    parsed = parse(file)
    tot = push_add(parsed)
    return tot 

def sol_2(file) :
    parsed = parse(file)
    platform = cycle(parsed,1000000000)
    return count_load(platform)


if __name__ == "__main__" :
    input_test = open("test.txt", "r")
    input_real = open("input.txt", "r")


    print(sol_1(input_test))
    print(sol_1(input_real))


    input_test = open("test.txt", "r")
    input_real = open("input.txt", "r")

    print(sol_2(input_test))
    print(sol_2(input_real))