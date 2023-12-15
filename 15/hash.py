
LABEL = 0
FOCAL = 1

def parse(file) :
    return file.read().split(',')

def hash(step) :
    value = 0
    for char in step:
        value += ord(char)
        value *= 17
        value %= 256
    return value

def update_hashmap(hashmap : list, step : str) :
    label = step.split('-')
    label = label[0].split('=')
    label_hash = hash(label[0])
    match len(label) :
        case 1 :
            if label[0] in hashmap[LABEL][label_hash] :
                rm = hashmap[LABEL][label_hash].index(label[0])
                del hashmap[LABEL][label_hash][rm]
                del hashmap[FOCAL][label_hash][rm]
            return
        case 2 :
            if label[0] in hashmap[LABEL][label_hash] :
                change = hashmap[LABEL][label_hash].index(label[0])
                hashmap[FOCAL][label_hash][change] = label[1]
            else :
                hashmap[LABEL][label_hash].append(label[0])
                hashmap[FOCAL][label_hash].append(label[1])
            return









def sol_1(file) :
    parsed = parse(file)
    tot = 0
    for step in parsed :
        tot += hash(step)
    return tot


def sol_2(file) :
    parsed = parse(file)
    hashmap = [[[] for _ in range(256)], [[] for _ in range(256)]]
    for step in parsed :
        update_hashmap(hashmap, step)
    # for i,box in enumerate(hashmap[LABEL]) :
    #     if len(box) :
    #         print(f"Box {i}: ", end='')
    #         for j, label in enumerate(box) :
    #             print(f"[{label} {hashmap[FOCAL][i][j]}] ", end='')
    #         print()
    tot = 0
    for i, box in enumerate(hashmap[FOCAL]) :
        for j, focal in enumerate(box) :
            tot += (1+i)*(1+j)*int(focal) 
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