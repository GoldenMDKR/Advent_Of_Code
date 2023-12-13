def parse(file) -> list:
    l = file.read().split("\n\n")
    for i in range(len(l)) :
        l[i] = l[i].split("\n")
    return l

def find_reflect(pattern: list) -> int :

    for i, row in enumerate(pattern) :
        if i == len(pattern)-1 :
            break
        for j in range(1, len(pattern)-1):
            if j+i >= len(pattern) or i-j+1 < 0 :
                return 100*(i+1)
            if pattern[i+j] != pattern[i-j+1] :
                break
            
    for i, collum in enumerate(pattern[0]) :
        if i == len(pattern[0])-1 :
            break
        for j in range(1, len(pattern[0])-1):
            out = 0
            if j+i >= len(pattern[0]) or i-j+1 < 0 :
                return i+1
            for k in range(len(pattern)) : 
                if pattern[k][i+j] != pattern[k][i-j+1] :
                    out = 1
                    break
            if out :
                break
    print(wtf)
    return 0
    

def find_reflect_smudged(pattern: list) -> int :

    for i, row in enumerate(pattern) :
        if i == len(pattern)-1 :
            break
        smudge = 0
        for j in range(1, len(pattern)-1):
            if j+i >= len(pattern) or i-j+1 < 0 :
                break
            for k in range(len(pattern[i])) : 
                if pattern[i+j][k] != pattern[i-j+1][k] :
                    smudge += 1
        if smudge == 1 :
            return 100*(i+1)
            
    for i, collum in enumerate(pattern[0]) :
        if i == len(pattern[0])-1 :
            break
        smudge = 0
        for j in range(1, len(pattern[0])-1):
            if j+i >= len(pattern[0]) or i-j+1 < 0 :
                break
            for k in range(len(pattern)) : 
                if pattern[k][i+j] != pattern[k][i-j+1] :
                    smudge += 1

        if smudge == 1 :
            return i+1
    print(wtf)
    return 0



def sol_1(file) -> int:
    parsed = parse(file)
    tot = 0
    for pattern in parsed :
        tot += find_reflect(pattern)
    return tot
    

def sol_2(file) -> int:
    parsed = parse(file)
    tot = 0
    for pattern in parsed :
        tot += find_reflect_smudged(pattern)
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