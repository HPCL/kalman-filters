#!/usr/bin/python
# simple script to generate annotations for Orio stuff

file_name = "anno_orio.txt"

start_str = "/*@ begin PerfTuning (\n\
\n\
def build {\n\
arg build_command = 'gcc';\n\
}\n\
\n\
def performance_counter {\n\
arg repetitions = 50;\n\
}\n\n"

search_str = "def search {\n\
arg algorithm = 'Randomsearch';\n\
arg total_runs  = 10000;\n\
}\n\n\
) @*/\n\n\n"

end_str = ") @*/ \n\n/*@ end @*/\n/*@ end @*/\n\n"

############################## performance params ############################

perf_str = "def performance_params {\n"

num_nests = int( raw_input('enter number of loop nests --> ') )

index_lst = []

for i in range(num_nests):
    lst = raw_input('enter indices separated by space --> ')
    index_lst.append(lst.split())

for i in range(len(index_lst)):
    for ind in index_lst[i]:
        perf_str += ("param U_" + ind + str(i) + "[] = range(1,6);\n")


for i in range(len(index_lst)):
    for ind in index_lst[i]:
        perf_str += ("param RT_" + ind + str(i) + "[] = [1,2,6];\n")

perf_str += "param CFLAGS[] = ['-O1', '-O2', '-O3'];\n\
param VEC[] = [False, True];\n"

for i in range(len(index_lst)):
    perf_str += "constraint unroll_limit_" + str(i) + " = ("
    for ind in index_lst[i]:
        perf_str += ("(U_" + ind + str(i) + " == 1)")
        if not ind == index_lst[i][-1]:
            perf_str += " or "
    perf_str += ");\n"

for i in range(len(index_lst)):
    perf_str += "constraint reg_capacity_" + str(i) + " = ("
    for ind in index_lst[i]:
        perf_str += ("RT_" + ind + str(i))
        if not ind == index_lst[i][-1]:
            perf_str += "*"
    perf_str += " <= 150);\n"

perf_str += "}\n\n"

##############################    input params    ############################

input_str = "def input_params {\nlet N = [6];\n"

lst = raw_input('enter matrices separated by space --> ')
mat_lst = lst.split()

for m in mat_lst:
    input_str += ("param " + m + "_nrows[] = N;\n")
    input_str += ("param " + m + "_ncols[] = N;\n")

input_str += "}\n\n"

input_str += "def input_vars {\n"

for m in mat_lst:
    input_str += ("decl dynamic double " + m + "[" + m + "_nrows*" + m + "_ncols] = random;\n")

input_str += "}\n\n"


##############################    loop stuff    ############################

loop_str = "/*@ begin Loop (\n\n"

for i in range(len(index_lst)):
    loop_str += "transform Composite(\n"
    loop_str += "unrolljam = (["
    for ind in index_lst[i]:
        loop_str += ("'" + ind + "'")
        if not ind == index_lst[i][-1]:
            loop_str += ","

    loop_str += "],["

    for ind in index_lst[i]:
        loop_str += ("U_" + ind + str(i))
        if not ind == index_lst[i][-1]:
            loop_str += ","
    loop_str += "]),\n"

    loop_str += "regtile = (["
    for ind in index_lst[i]:
        loop_str += ("'" + ind + "'")
        if not ind == index_lst[i][-1]:
            loop_str += ","

    loop_str += "],["

    for ind in index_lst[i]:
        loop_str += ("RT_" + ind + str(i))
        if not ind == index_lst[i][-1]:
            loop_str += ","
    loop_str += "]),\n"


    loop_str += "vector = (VEC, ['ivdep','vector always'])\n"
    loop_str += ")\n\n TODO put loop here \n\n"

with open(file_name, 'w') as f:
    f.write(start_str)
    f.write(perf_str)
    f.write(input_str)
    f.write(search_str)
    f.write(loop_str)
    f.write(end_str)
