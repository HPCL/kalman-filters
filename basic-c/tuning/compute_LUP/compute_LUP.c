#include "../../linear_algebra.h"


int compute_LUP(TYPE* mat_a, TYPE* L, TYPE* U, TYPE* P, int n) {
  int i, j, k, ind_max, curr_row, next_row;
  int cnt_pivots = 0;
  int size_a = n*n;
  TYPE tolerance = 5E-300;
  TYPE max_a, abs_a, coeff;
  TYPE temp_row[n];

  set_identity(P, n, n);
  set_identity(L, n, n);
  copy_mat(mat_a, U, size_a);

  for(i = 0; i < n; i++) {
    curr_row = i * n;
    max_a = get_abs(U[curr_row + i]);
    ind_max = i;

    for (j = i+1; j < n; j++) {
      abs_a = get_abs(U[j * n + i]);
      if (abs_a > max_a) {
        max_a = abs_a;
        ind_max = j;
      }
    }
    
    if (max_a < tolerance) return -1;
    
    if (ind_max != i) {
      cnt_pivots++;
      ind_max *= n;

      copy_mat(&P[curr_row], temp_row, n);
      copy_mat(&P[ind_max], &P[curr_row], n);
      copy_mat(temp_row, &P[ind_max], n);

      copy_mat(&U[curr_row], temp_row, n);
      copy_mat(&U[ind_max], &U[curr_row], n);
      copy_mat(temp_row, &U[ind_max], n);
    }

    for(j = i+1; j < n; j++) {
      next_row = j * n;
      coeff = (U[next_row+i]/U[curr_row+i]);
      L[next_row+i] = coeff;
      for (k = i; k < n; k++) {
        U[next_row + k] -= coeff * U[curr_row + k];
      }
    }

  } //end main for

  return cnt_pivots;
}
