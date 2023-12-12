import functools

def parse(file) -> list:
    l = file.read().split("\n")
    for i in range(len(l)) :
        l[i] = l[i].split(" ")
        l[i] += l[i].pop().split(",")
    return l

@functools.cache
def arrangements(line : tuple, curr_index : int, curr_value : int) -> int:
    if curr_value >= len(line) :
        for i in range(curr_index, len(line[0])) :
            if line[0][i] == '#' :
                return 0
        return 1

    arrang = 0

    string = line[0]
    # test on all char
    for index in range(curr_index, len(line[0])) :
        if string[index] == '?' or string[index] == '#':
            is_valid = 1
            for i in range(index, index+int(line[curr_value])):
                if i >= len(string) :
                    return arrang
                if string[i] != '?' and string[i] != '#' :
                    is_valid = 0
            if is_valid :
                next_ind = index+int(line[curr_value])
                if next_ind < len(string) and string[next_ind] == '#' :
                    if string[index] == '#' :
                        break
                    continue
                arrang += arrangements(line, next_ind+1, curr_value+1)
        if string[index] == '#' :
            break
        

    return arrang
        

def unfold(data: list) -> list :
    for index, line in enumerate(data) :
        newline = (line[0]+'?')*5
        data[index][0] = newline[:-1]
        length = len(line)
        for _ in range(4):
            for i in range(1, length):
                data[index].append(line[i])
        data[index] = tuple(data[index])
    return data



def sol_1(entry) : 
    tot = 0
    data = parse(entry)
    for i in range(len(data)) :
        data[i] = tuple(data[i])
    data = tuple(data)
    for line in data :
        arr = arrangements(line, 0, 1)
        tot += arr
    return tot
    


def sol_2(entry) : 
    tot = 0
    data = parse(entry)
    data = tuple(unfold(data))
    for i, line in enumerate(data) :
        tot += arrangements(line, 0, 1)
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