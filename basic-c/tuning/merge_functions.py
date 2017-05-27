# script to merge the tuned functions into one file

function_list = ['add_mat', 'cofactor_matrix', 'compute_LUP', 'compute_LUP_inline', 'determinant_matrix', 'multiply_matrix', 'multiply_matrix_by_scalar', 'transpose_matrix'];

fout = open('tuned_linear_algebra.c', 'w')

    
fin = open('non_tuned.c')
for line in fin:
    fout.write(line)

for thing in function_list:
    try:
        fin = open('_' + thing + '/' + thing +'.c')
    except:
        fin = open(thing + '/' + thing +'.c')


    for line in fin:
        if line != '#include "../../linear_algebra.h"\n':
            fout.write(line)
    fout.write('\n')