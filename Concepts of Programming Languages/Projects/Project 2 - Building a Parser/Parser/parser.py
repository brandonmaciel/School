import sys

# get input from file
try:
    file = open(sys.argv[1], 'r')
except IOError:
    print("File '" + sys.argv[1] +"' does not exist.")
    exit()

# file = open('scannerTest.txt', 'r')

tokens = []
words = []

while True:
      
    # read by character
    char = file.read(1)

    # skip any white spaces
    if char in [" ", "\t", "\n"]:
        continue

    if char == "(":
        words.append("(")
        tokens.append("lparen")
        continue
    elif char == ")":
        words.append(")")
        tokens.append("rparen")
        continue
    elif char == "+":
        words.append("+")
        tokens.append("plus")
        continue
    elif char == "-":
        words.append("-")
        tokens.append("minus")
        continue
    elif char == "*":
        words.append("*")
        tokens.append("times")
        continue

    if char == ':':
        char = file.read(1)

        if char == "=":
            words.append(":=")
            tokens.append("assign")
            continue
        else:
            print("Error")
            exit()
    
    if char == '/':
        # peek at the next char
        peek = file.read(1)

        # block comment
        if peek == "*":
            while True:
                char = file.read(1)
                if char == '*':
                    char = file.read(1)
                    if char == '/':
                        break
        # line comment
        elif peek == "/":
            while True:
                char = file.read(1)
                if char == '\n':
                    break
        else:
            words.append("/")
            tokens.append("div")
            char = peek
        continue
    
    if char == '.':
        char = file.read(1)
        tmpString = char
        if char.isdigit():
            while(char.isdigit()):
                char = file.read(1)
                tmpString = tmpString + char
            words.append(tmpString.replace(" ", "").replace("\n", ""))
            tokens.append("number")
        else:
            print("Error")
            exit()
        continue
    
    if char.isdigit():
        tmpString = char
        while char.isdigit():
            char = file.read(1)
            tmpString = tmpString + char
        words.append(tmpString.replace(" ", "").replace("\n", ""))
        tokens.append("number")
        continue
    
    if char.isalpha():

        tmpString = char
        if char == "r":
            char = file.read(1)
            tmpString = tmpString + char
            if char == "e":
                char = file.read(1)
                tmpString = tmpString + char
                if char == "a":
                    char = file.read(1)
                    tmpString = tmpString + char
                    if char == "d":
                        words.append("read")
                        tokens.append("read")
                        continue
        
        if char == "w":
            char = file.read(1)
            tmpString = tmpString + char
            if char == "r":
                char = file.read(1)
                tmpString = tmpString + char
                if char == "i":
                    char = file.read(1)
                    tmpString = tmpString + char
                    if char == "t":
                        char = file.read(1)
                        tmpString = tmpString + char
                        if char == "e":
                            words.append("write")
                            tokens.append("write")
                            continue
                    
        while char.isalpha():
            char = file.read(1)
            tmpString = tmpString + char
        
        words.append(tmpString.replace(" ", "").replace("\n", ""))
        tokens.append("id")
        continue

    if not char: 
        break

file.close()
tokens.append("$$")
tokens.append("")
input = words

# print(tokens)
# print(words)


spacing = 4
token_i = 0
level = 0

def match(expected_token):
    global token_i
    global level

    if tokens[token_i] == expected_token:
        token_i = token_i + 1
    else:
        print("Error")
        exit()

def print_token(string):
    global level
    level += spacing
    print(("\t" + string).expandtabs(level))
    level -= spacing

def print_general(type, string):
    global level
    level += spacing
    print(("\t<" + type + ">").expandtabs(level))
    print_token(string)
    print(("\t</" + type + ">").expandtabs(level))
    level -= spacing


def program():
    global token_i
    global level

    print("<Program>")
    
    if "id" == tokens[token_i]:
        stmt_list()
        match("$$")
    elif "read" == tokens[token_i]:
        stmt_list()
        match("$$")
    elif "write" == tokens[token_i]:
        stmt_list()
        match("$$")
    elif "$$" == tokens[token_i]:
        stmt_list()
        match("$$")
    else:
        print("Error")
        exit()

    print("</Program>")

def stmt_list():
    global token_i
    global level

    level += spacing
    print("\t<stmt_list>".expandtabs(level))

    if "id" == tokens[token_i]:
        stmt()
        stmt_list()
    elif "read" == tokens[token_i]:
        stmt()
        stmt_list()
    elif "write" == tokens[token_i]:
        stmt()
        stmt_list()
    elif "$$" == tokens[token_i]:
        # skip
        None
    else:
        print("Error")
        exit()

    print("\t</stmt_list>".expandtabs(level))
    level -= spacing

def stmt():
    global token_i
    global level

    level += spacing
    print("\t<stmt>".expandtabs(level))

    if "id" == tokens[token_i]:
        match("id")
        print_general("id", input[token_i-1])
        match("assign")
        print_general("assign", input[token_i-1])
        expr()
    elif "read" == tokens[token_i]:
        match("read")
        print_general("read", input[token_i-1])
        match("id")
        print_general("id", input[token_i-1])
    elif "write" == tokens[token_i]:
        match("write")
        print_general("write", input[token_i-1])
        expr()
    else:
        print("Error")
        exit()

    print("\t</stmt>".expandtabs(level))
    level -= spacing

def expr():
    global level

    level += spacing
    print("\t<expr>".expandtabs(level))

    if "id" == tokens[token_i]:
        term()
        term_tail()
    elif "number" == tokens[token_i]:
        term()
        term_tail()
    elif "lparen" == tokens[token_i]:
        term()
        term_tail()
    else:
        print("Error")
        exit()

    print("\t</expr>".expandtabs(level))
    level -= spacing

def term_tail():
    global token_i
    global level

    level += spacing
    print("\t<term_tail>".expandtabs(level))

    if "plus" == tokens[token_i]:
        add_op()
        term()
        term_tail()
    elif "minus" == tokens[token_i]:
        add_op()
        term()
        term_tail()
    elif "rparen" == tokens[token_i]:
        # skip
        None
    elif "id" == tokens[token_i]:
        # skip
        None
    elif "read" == tokens[token_i]:
        # skip
        None
    elif "write" == tokens[token_i]:
        # skip
        None
    elif "$$" == tokens[token_i]:
        # skip
        None
    else:
        print("Error")
        exit()

    print("\t</term_tail>".expandtabs(level))
    level -= spacing

def term():
    global token_i
    global level

    level += spacing
    print("\t<term>".expandtabs(level))

    if "id" == tokens[token_i]:
        factor()
        fact_tail()
    elif "number" == tokens[token_i]:
        factor()
        fact_tail()
    elif "lparen" == tokens[token_i]:
        factor()
        fact_tail()
    else:
        print("Error")
        exit()

    print("\t</term>".expandtabs(level))
    level -= spacing

def fact_tail():
    global token_i
    global level

    level += spacing
    print("\t<fact_tail>".expandtabs(level))

    if "times" == tokens[token_i]:
        mult_op()
        factor()
        fact_tail()
    elif "div" == tokens[token_i]:
        mult_op()
        factor()
        fact_tail()
    elif "plus" == tokens[token_i]:
        # skip
        None
    elif "minus" == tokens[token_i]:
        # skip
        None
    elif "rparen" == tokens[token_i]:
        # skip
        None
    elif "id" == tokens[token_i]:
        # skip
        None
    elif "read" == tokens[token_i]:
        # skip
        None
    elif "write" == tokens[token_i]:
        # skip
        None
    elif "$$" == tokens[token_i]:
        # skip
        None
    else:
        print("Error")
        exit()

    print("\t</fact_tail>".expandtabs(level))
    level -= spacing

def factor():
    global level

    level += spacing
    print("\t<factor>".expandtabs(level))

    if "id" == tokens[token_i]:
        match("id")
        print_general("id", input[token_i-1])
    elif "number" == tokens[token_i]:
        match("number")
        print_general("number", input[token_i-1])
    elif "(" == tokens[token_i]:
        match("lparen")
        print_general("lparen", input[token_i-1])
        expr()
        match("rparen")
        print_general("rparen", input[token_i-1])
    else:
        print("Error")
        exit()

    print("\t</factor>".expandtabs(level))
    level -= spacing

def add_op():
    global level

    level += spacing
    print("\t<add_op>".expandtabs(level))

    if "plus" == tokens[token_i]:
        match("plus")
        print_general("plus", input[token_i-1])
    elif "minus" == tokens[token_i]:
        match("minus")
        print_general("minus", input[token_i-1])
    else:
        print("Error")
        exit()

    print("\t</add_op>".expandtabs(level))
    level -= spacing

def mult_op():
    global level

    level += spacing
    print("\t<mult_op>".expandtabs(level))

    if "times" == tokens[token_i]:
        match("times")
        print_general("times", input[token_i-1])
    elif "div" == tokens[token_i]:
        match("div")
        print_general("div", input[token_i-1])
    else:
        print("Error")
        exit()

    print("\t</mult_op>".expandtabs(level))
    level -= spacing

program()