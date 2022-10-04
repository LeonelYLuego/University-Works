import re

def get_condition(line):
    s = line.find('(')
    f = line.find('):')
    return line[s + 1:f]

def evaluate_condition(condition):
    operators = re.search(r'\+|-|\*|\/|=|\<|\>|&|\|')
    if(len(operators) == 0):
        raise Exception('Invalid condition, must have more than one operator')
    for op in operators:
        first = condition[op:]
        last = condition[:op]
        if(op == '+'):
            return first + last
        elif(op == '-'):
            return first - last
        elif(op == '*'):
            return first * last
        elif(op == '/'):
            return first / last
        elif(op == '<'):
            return first < last
        elif(op == '>'):
            return first > last
        elif(op == '='):
            exec("% = %"%(first, last))
        elif(op == '&'):
            return first & last
        elif(op == '|'):
            return first | last
        else:
            raise Exception('Operator not found')


f = open('code.txt').read()
exec(f)
f = open('code.txt', 'r')
code = []
condition_res = False

for line in f:
    code.append(line)

"""
Operation:
    1: while
    2: if
    3: variable
"""
def exec_code(tab, line_counter, condition = None, return_line = None, operation = None):
    while(line_counter < len(code)):
        line = code[line_counter]

        if(condition):
            condition_res = evaluate_condition(condition)
            if(not condition_res):
                line_counter = return_line
                return
            else:
                line_counter += 1
                while(code[line_counter].count('\t') > tab):
                    line_counter += 1
                return
        
        if(operation == 1):
            if(line.count('\t') < tab):
                line_counter = return_line
                if(operation == 1):
                    continue
                elif(operation == 2):
                    return
                else:
                    raise Exception('Identation error')
        
        if(re.match('while', line)): # while
            condition = get_condition(line)
            evaluate_condition(condition)
            exec_code(tab + 1, line_counter, condition, line_counter, 1)
        elif(re.match('if', line)): # if
            condition = get_condition(line)
            evaluate_condition(condition)
            if(condition_res):
                exec_code(tab + 1, line_counter, None, line_counter, 2)
        elif(re.match('[a-zA-Z][a-zA-Z0-9]*\ *=\ *\d+', line)): #variable <var> = <integer>
            operation = 3
            tabs = ''
            for _ in range(tab):
                tabs += '\t'
            exec(tabs + line)
        else: #others instructions that are not recognized
            tabs = ''
            for _ in range(tab):
                tabs += '\t'
            exit()
        
        line_counter = line_counter +  1

exec_code(0, 0)