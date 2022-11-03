import math
import sys
 
class stacks:
 
    def __init__(self, n):
        self.size = n
        self.arr = [None] * n
        self.top = math.floor(n/2) + 1
 
    def push(self, x):
        if self.top > 0:
            self.top = self.top - 1
            self.arr[self.top] = x
        else:
            print("Stack Overflow by element : ", x)
 
    def isEmpty(self):
        if self.top - 1 >= self.size / 2:
            return True

    def peek(self):
        return self.arr[self.top] if self.top is not None else None

    def pop(self):
        if self.top <= self.size / 2:
            x = self.arr[self.top]
            self.top = self.top + 1
            return x
        else:
            print("Stack Underflow")
            exit(1)
 
if __name__ == '__main__':
    with open("crackme.hspal", "r") as f:
        hspal = f.read().encode()

    arr = []
    temp = ''
    reg = 0
    labels = {}
    idx = 0
    ip = 0
    for c in hspal:
        if '\n' in chr(c):
            arr.append(temp.strip())
            temp = ''
        temp += chr(c)
    arr.append(temp.strip())

    ts = []
    for s in range(256):
        ts.insert(s, stacks(256))

    while True:
        cmd = arr[ip]
        match cmd[:2]:
            case '00':
                print(f"label: {cmd[2:]}")
                labels[f"{cmd[2:]}"] = ip
                ip += 1
            case '01':
                print(f"goto: {cmd[2:]}")
                ip = labels[f"{cmd[2:]}"]
            case '02':
                print(f"pop(stack[{cmd[2:4]}]) goto {ts[int(cmd[2:4], 16)].pop()}")
                ip += 1
            case '03':
                val = ts[int(cmd[2:4], 16)].pop()
                print(f"pop(stack[{cmd[2:4]}] if value != 0 skip next instruction | value = {val})")
                if val != 0:
                    ip += 1
                ip += 1
            case '04':
                if cmd[2:] == 0:
                    print("exit (status code:0)")
                    exit(1)
                elif cmd[2:] == -1:
                    print(f"exit (status code -1)")
                    exit(1)
                else:
                    print(f"exit (status code {cmd[2:]})")
                    exit(1)
            case '10':
                print(f"getchar(stdin) && push(stack[{cmd[2:4]}])")
                c = ''
                c = input("Enter Char: ")
                if len(c) == 1:
                    val = hex(ord(c))
                    ts[int(cmd[2:4], 16)].push(int(val, 16))
                ip += 1
            case '11':
                print(f"getnum(stdin) && push(stack[{cmd[2:4]}])")
                ts[int(cmd[2:4], 16)].push(sys.stdin.read(1))
                ip += 1
            case '12':
                val = ts[int(cmd[2:4], 16)].pop()
                print(f"pop(stack[{cmd[2:4]}]) && print(\"{val}\")")
                ip += 1
            case '13':
                val = chr(ts[int(cmd[2:4], 16)].pop())
                print(f"pop(stack[{cmd[2:4]}]) && print(\"{val}\")")
                ip += 1
            case '14':
                print(f"while !isEmpty(stack[{cmd[2:4]}]): pop(*) && print(\"", end='')
                while ts[int(cmd[2:4], 16)].isEmpty() != True:
                    print(chr(ts[int(cmd[2:4], 16)].pop()), end='')
                print("\")")
                ip += 1
            case '20':
                print(f"reg = {cmd[2:]}")
                reg = int(cmd[2:], 16)
                ip += 1
            case '21':
                val1 = ts[int(cmd[2:4], 16)].pop()
                val2 = ts[int(cmd[2:4], 16)].pop()
                result = val1 + val2
                ts[int(cmd[2:4], 16)].push(result)
                print(f"stack[{cmd[2:4]}] = add({val1}, {val2}) | result = {result}")
                ip += 1
            case '22':
                val1 = ts[int(cmd[2:4], 16)].pop()
                val2 = ts[int(cmd[2:4], 16)].pop()
                result = val1 - val2
                print(f"stack[{cmd[2:4]}] = sub({val1}, {val2}) if result >= 0 | result = {result}")
                if result >= 0:
                    ts[int(cmd[2:4], 16)].push(result)
                ip += 1
            case '23':
                print(f"POP 2 VALUES FROM STACK[{cmd[2:4]}] MULTIPLY THEM AND STORE IN STACK[{cmd[2:4]}] IF STACK HAS < 2 VALUES THROW EXCEPTION")
            case '24':
                print(f"POP 2 VALUES FROM STACK[{cmd[2:4]}] DIVIDE 1st BY 2nd AND ROUND DOWN TO NEAREST INTEGER STORE RESULT IN STACK[{cmd[2:4]}] THROW EXCEPTION IF STACK < 2 VALUES")
            case '25':
                print(f"POP 2 VALUES FROM STACK[{cmd[2:4]}] RAISE THE 1st TO THE POWER OF THE 2nd PUSH RESULT INTO STACK[{cmd[2:4]}] THROW EXCEPTION IF STACK < 2 VALUES")
            case '26':
                print(f"TAKE RANDOM INTEGER ON INTERVAL [0, {cmd[2:]}] AND WRITE IT TO REGISTER")
            case '30':
                print(f"if pop(stack[{cmd[2:4]}]) == pop(stack[{cmd[2:4]}]) then stack[{cmd[4:]}] = push(1) else stack[{cmd[4:]}] = push(0)")
                val1 = ts[int(cmd[2:4], 16)].pop()
                val2 = ts[int(cmd[2:4], 16)].pop()
                print(val1, val2)
                if val1 == val2:
                    ts[int(cmd[4:], 16)].push(1)
                else:
                    ts[int(cmd[4:], 16)].push(0)
                ip += 1
            case '31':
                print(f"POP 2 VALUES FROM STACK[{cmd[2:4]}] PUSH 1 INTO STACK[{cmd[4:]}] IF VALUES 1 > VALUES 2 PUSH 1 ELSE PUSH 0 THROW EXCEPTION IF STACK < 2 VALUES")
            case '32':
                print(f"POP 2 VALUES FROM STACK[{cmd[2:4]}] PUSH 1 INTO STACK[{cmd[4:]}] IF VALUES 1 < VALUES 2 PUSH 1 ELSE PUSH 0 THROW EXCEPTION IF STACK < 2 VALUES")
            case '33':
                print(f"POP 2 VALUES FROM STACK[{cmd[2:4]}] PUSH 1 INTO STACK[{cmd[4:]}] IF ONE OF THE VALUES OR BOTH ARE NOT EQUAL ZERO ELSE PUSH 0 THROW EXCEPTION IF STACK < 2 VALUES")
            case '34':
                print(f"POP 2 VALUES FROM STACK[{cmd[2:4]}] PUSH 1 INTO STACK[{cmd[4:]}] IF TWO OF THE VALUES ARE NOT EQUAL ZERO ELSE PUSH 0 THROW EXCEPTION IF STACK < 2 VALUES")
            case '35':
                print(f"POP 2 VALUES FROM STACK[{cmd[2:4]}] PUSH 1 INTO STACK[{cmd[4:]}] IF ONE OF THE VALUES ARE NOT EQUAL ZERO ELSE PUSH 0 THROW EXCEPTION IF STACK < 2 VALUES")
            case '36':
                print(f"if reg == 0: stack[{cmd[2:4]}] = push(1) else stack[{cmd[2:4]}] = push(0)")
                if reg == 0:
                    ts[int(cmd[2:4], 16)].push(1)
                elif reg == 1:
                    ts[int(cmd[2:4], 16)].push(0)
                ip += 1
            case '40':
                print(f"push(stack[{cmd[2:4]}]) reg")
                print(type(reg))
                if isinstance(reg, str):
                    ts[int(cmd[2:4], 16)].push(int(reg, 16))
                elif isinstance(reg, int):
                    ts[int(cmd[2:4], 16)].push(reg)
                else:
                    print("Wrong fucking data type dickhead")
                    exit(1)
                ip += 1
            case '41':
                print(f"reg = pop(stack[{cmd[2:4]}])")
                reg = ts[int(cmd[2:4], 16)].pop()
                ip += 1
            case '42':
                print(f"reg = stack[{cmd[2:4]}]")
                reg = ts[int(cmd[2:4], 16)].peek()
                ip += 1
            case '43':
                print(f"COUNT VALUES ON STACK[{cmd[2:4]}] AND WRITE TO REGISTER")
            case _:
                print("Invalid opcode")
