def parse_line(line) -> list :
    if len(line) == 0 :
        return 0
    line_list = line.strip("\n").split(" ")
    for i in range(len(line_list)) :
        line_list[i] = int(line_list[i])
    return line_list



def next_seq(curr_seq : list) -> list:
    next_s = [value - prev for prev, value in zip(curr_seq, curr_seq[1:])]
    return next_s

def is_zero(line : list) -> bool :
    for e in line :
        if e != 0 :
            return False
    return True

def build_history(line : list) -> list:
    curr_line = line
    history = [line]

    while(not is_zero(curr_line)):
        curr_line = next_seq(curr_line)
        history.append(curr_line)
    
    return history

def extrapolate_last(history : list) -> int :
    curr_val = 0
    history.pop()
    history.reverse()
    for line in history : 
        curr_val = line[-1] + curr_val
    return curr_val

def extrapolate_first(history : list) -> int :
    curr_val = 0
    history.pop()
    history.reverse()
    for line in history : 
        pv = curr_val
        curr_val = line[0] - curr_val
    return curr_val

def sol_1(inputs) -> int : 
    tot = 0
    while (line := parse_line(inputs.readline())) :
        history = build_history(line)
        tot += extrapolate_last(history)
    return tot

def sol_2(inputs) -> int : 
    tot = 0
    while (line := parse_line(inputs.readline())) :
        history = build_history(line)
        a = extrapolate_first(history)
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


