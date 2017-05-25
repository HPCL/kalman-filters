#include "../../linear_algebra.h"


int compute_LUP_inline(TYPE* mat_a, TYPE* L, TYPE* U, TYPE* P, int n) {
  int i, j, k, ind_max, curr_row, next_row, row;
  int cnt_pivots = 0;
  int size_a = n*n;
  TYPE tolerance = 5E-300;
  TYPE max_a, abs_a, coeff;
  TYPE temp_row[n];

  // set_identity(P, n, n);
  for (i = 0; i < n; i++) {
    row = n * i;
    for (j = 0; j < n; j++) {
      P[row + j] = (double)(i == j);
    }
  }
  // set_identity(L, n, n);
  for (i = 0; i < n; i++) {
    row = n * i;
    for (j = 0; j < n; j++) {
      L[row + j] = (double)(i == j);
    }
  }

  // copy_mat(mat_a, U, size_a);
  for (i = 0; i < size_a; i++)
    U[i] = mat_a[i];

  for(i = 0; i < n; i++) {
    curr_row = i * n;
    // max_a = get_abs(U[curr_row + i]);
    max_a = (((U[curr_row + i] < 0) * -2) + 1) * U[curr_row + i];
    ind_max = i;

    for (j = i+1; j < n; j++) {
      // abs_a = get_abs(U[j * n + i]);
      abs_a = (((U[j * n + i] < 0) * -2) + 1) * U[j * n + i];
      if (abs_a > max_a) {
        max_a = abs_a;
        ind_max = j;
      }
    }
    
    if (max_a < tolerance) return -1;

    if (ind_max != i) {
      cnt_pivots++;
      ind_max *= n;

      // copy_mat(&P[curr_row], temp_row, n);
      for (k = 0; k < n; k++)
        temp_row[k] = (&P[curr_row])[k];
      // copy_mat(&P[ind_max], &P[curr_row], n);
      for (k = 0; k < n; k++)
        (&P[curr_row])[k] = (&P[ind_max])[k];
      // copy_mat(temp_row, &P[ind_max], n);
      for (k = 0; k < n; k++)
        (&P[ind_max])[k] = temp_row[k];

      // copy_mat(&U[curr_row], temp_row, n);
      for (k = 0; k < n; k++)
        temp_row[k] = (&U[curr_row])[k];
      // copy_mat(&U[ind_max], &U[curr_row], n);
      for (k = 0; k < n; k++)
        (&U[curr_row])[k] = (&U[ind_max])[k];
      // copy_mat(temp_row, &U[ind_max], n);
      for (k = 0; k < n; k++)
        (&U[ind_max])[k] = temp_row[k];

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
