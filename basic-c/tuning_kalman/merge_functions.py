# script to merge the tuned functions into one file

function_list = ['add_mat', 'cofactor_matrix', 'compute_LUP', 'compute_LUP_inline', 'determinant_matrix', 'multiply_matrix', 'multiply_matrix_by_scalar', 'transpose_matrix'];

fout = open('tuned_linear_algebra.c', 'w')
    
print('putting functions not worth tuning into tuned_linear_algebra.c')
fin = open('non_tuned.c')
for line in fin:
    fout.write(line)
fin.close()

print('putting tuned functions into tuned_linear_algebra.c')
for thing in function_list:
    try:
        fin = open(thing + '/' + '_' + thing +'.c')
    except:
        fin = open(thing + '/' + thing +'.c')
        print(thing + ' failed to be tuned')


    for line in fin:
        if line != '#include "../../linear_algebra.h"\n':
            fout.write(line)
    fout.write('\n')
    fin.close()
    