#include "../../kalman_filter.h"

void correct(double* y, double* x_hat, 
            int n, int m,
            double* C, double* R, double* P, double* K,
            double* x_hat_new, double* C_T, double* id,
            double* temp_1, double* temp_2, double* temp_3, double* temp_4) {


/*@ begin PerfTuning (

 def build {
   arg build_command = 'gcc';
   #arg libs = '-lrt';  # Only needed on linux
 } 

 def performance_counter {
   arg repetitions = 50;
 }

 def performance_params {  
  param U1_I[] = range(1,6);
  param U1_J[] = range(1,6);

  param U2_I[] = range(1,6);
  param U2_J[] = range(1,6);

  param U3_I[] = range(1,6);
  param U3_J[] = range(1,6);
  param U3_K[] = range(1,6);

  param U4_I[] = range(1,6);
  param U4_J[] = range(1,6);
  param U4_K[] = range(1,6);

  param U5_I[] = range(1,6);
  param U5_J[] = range(1,6);

  param U6_I[] = range(1,6);
  param U6_J[] = range(1,6);

  param U7_I[] = range(1,6);
  
  param U8_J[] = range(1,6);

  param U9_I[] = range(1,6);

  param U10_J[] = range(1,6);
  param U10_K[] = range(1,6);

  param U11_I[] = range(1,6);
  param U11_J[] = range(1,6);

  param U12_I[] = range(1,6);
  param U12_J[] = range(1,6);

  param U13_I[] = range(1,6);

  param U14_I[] = range(1,6);
  param U14_J[] = range(1,6);

  param U15_J[] = range(1,6);
  param U15_K[] = range(1,6);

  param U16_I[] = range(1,6);

  param U17_I[] = range(1,6);
  param U17_J[] = range(1,6);

  param U18_I[] = range(1,6);
  param U18_J[] = range(1,6);

  param U19_I[] = range(1,6);
  param U19_J[] = range(1,6);
  param U19_K[] = range(1,6);

  param U20_I[] = range(1,6);
  param U20_J[] = range(1,6);

  param U21_I[] = range(1,6);
  param U21_J[] = range(1,6);
  param U21_K[] = range(1,6);

  param U22_I[] = range(1,6);

  param U23_I[] = range(1,6);
  param U23_K[] = range(1,6);

  param U24_I[] = range(1,6);

  param U25_I[] = range(1,6);

  param U26_I[] = range(1,6);
  param U26_K[] = range(1,6);

  param U27_I[] = range(1,6);
  param U27_J[] = range(1,6);

  param U28_I[] = range(1,6);
  param U28_J[] = range(1,6);
  param U28_K[] = range(1,6);

  param U29_I[] = range(1,6);
  param U29_J[] = range(1,6);

  param U30_I[] = range(1,6);
  param U30_J[] = range(1,6);

  param U31_I[] = range(1,6);
  param U31_J[] = range(1,6);
  param U31_K[] = range(1,6);

  param U32_I[] = range(1,6);



  param RT1_I[] = [1,2,6];
  param RT1_J[] = [1,2,6];

  param RT2_I[] = [1,2,6];
  param RT2_J[] = [1,2,6];

  param RT3_I[] = [1,2,6];
  param RT3_J[] = [1,2,6];
  param RT3_K[] = [1,2,6];

  param RT4_I[] = [1,2,6];
  param RT4_J[] = [1,2,6];
  param RT4_K[] = [1,2,6];

  param RT5_I[] = [1,2,6];
  param RT5_J[] = [1,2,6];

  param RT6_I[] = [1,2,6];
  param RT6_J[] = [1,2,6];

  param RT7_I[] = [1,2,6];
  
  param RT8_J[] = [1,2,6];

  param RT9_I[] = [1,2,6];

  param RT10_J[] = [1,2,6];
  param RT10_K[] = [1,2,6];

  param RT11_I[] = [1,2,6];
  param RT11_J[] = [1,2,6];

  param RT12_I[] = [1,2,6];
  param RT12_J[] = [1,2,6];

  param RT13_I[] = [1,2,6];

  param RT14_I[] = [1,2,6];
  param RT14_J[] = [1,2,6];

  param RT15_J[] = [1,2,6];
  param RT15_K[] = [1,2,6];

  param RT16_I[] = [1,2,6];

  param RT17_I[] = [1,2,6];
  param RT17_J[] = [1,2,6];

  param RT18_I[] = [1,2,6];
  param RT18_J[] = [1,2,6];

  param RT19_I[] = [1,2,6];
  param RT19_J[] = [1,2,6];
  param RT19_K[] = [1,2,6];

  param RT20_I[] = [1,2,6];
  param RT20_J[] = [1,2,6];

  param RT21_I[] = [1,2,6];
  param RT21_J[] = [1,2,6];
  param RT21_K[] = [1,2,6];

  param RT22_I[] = [1,2,6];

  param RT23_I[] = [1,2,6];
  param RT23_K[] = [1,2,6];

  param RT24_I[] = [1,2,6];

  param RT25_I[] = [1,2,6];

  param RT26_I[] = [1,2,6];
  param RT26_K[] = [1,2,6];

  param RT27_I[] = [1,2,6];
  param RT27_J[] = [1,2,6];

  param RT28_I[] = [1,2,6];
  param RT28_J[] = [1,2,6];
  param RT28_K[] = [1,2,6];

  param RT29_I[] = [1,2,6];
  param RT29_J[] = [1,2,6];

  param RT30_I[] = [1,2,6];
  param RT30_J[] = [1,2,6];

  param RT31_I[] = [1,2,6];
  param RT31_J[] = [1,2,6];
  param RT31_K[] = [1,2,6];

  param RT32_I[] = [1,2,6];


  param VEC[] = [False,True];

  param CFLAGS[] = ['-O1', '-O2', '-O3'];

  constraint unroll_limit_1  = ((U1_I == 1) or (U1_J == 1));
  constraint unroll_limit_2  = ((U2_I == 1) or (U2_J == 1));
  constraint unroll_limit_3  = ((U3_I == 1) or (U3_J == 1) or (U3_K == 1));
  constraint unroll_limit_4  = ((U4_I == 1) or (U4_J == 1) or (U4_K == 1));
  constraint unroll_limit_5  = ((U5_I == 1) or (U5_J == 1));
  constraint unroll_limit_6  = ((U6_I == 1) or (U6_J == 1));
  constraint unroll_limit_10 = ((U10_J == 1) or (U10_K == 1));
  constraint unroll_limit_11 = ((U11_I == 1) or (U11_J == 1));
  constraint unroll_limit_12 = ((U12_I == 1) or (U12_J == 1));
  constraint unroll_limit_15 = ((U15_J == 1) or (U15_K == 1));
  constraint unroll_limit_17 = ((U17_I == 1) or (U17_J == 1));
  constraint unroll_limit_18 = ((U18_I == 1) or (U18_J == 1));
  constraint unroll_limit_19 = ((U19_I == 1) or (U19_J == 1) or (U19_K == 1));
  constraint unroll_limit_20 = ((U20_I == 1) or (U20_J == 1));
  constraint unroll_limit_21 = ((U21_I == 1) or (U21_J == 1) or (U21_K == 1));
  constraint unroll_limit_23 = ((U23_I == 1) or (U23_K == 1));
  constraint unroll_limit_26 = ((U26_I == 1) or (U26_K == 1));
  constraint unroll_limit_27 = ((U27_I == 1) or (U27_J == 1));
  constraint unroll_limit_28 = ((U28_I == 1) or (U28_J == 1) or (U28_K == 1));
  constraint unroll_limit_29 = ((U29_I == 1) or (U29_J == 1));
  constraint unroll_limit_30 = ((U30_I == 1) or (U30_J == 1));
  constraint unroll_limit_31 = ((U31_I == 1) or (U31_J == 1) or (U31_K == 1));

  constraint reg_capacity_1  = (RT2_I*RT2_J <= 150);
  constraint reg_capacity_2  = (RT2_I*RT2_J <= 150);
  constraint reg_capacity_3  = (RT3_I*RT3_J*RT3_K <= 150);
  constraint reg_capacity_4  = (RT4_I*RT4_J*RT4_K <= 150);
  constraint reg_capacity_5  = (RT5_I*RT5_J <= 150);
  constraint reg_capacity_6  = (RT6_I*RT6_J <= 150);
  constraint reg_capacity_10 = (RT10_J*RT10_K <= 150);
  constraint reg_capacity_11 = (RT11_I*RT11_J <= 150);
  constraint reg_capacity_12 = (RT12_I*RT12_J <= 150);
  constraint reg_capacity_15 = (RT15_J*RT15_K <= 150);
  constraint reg_capacity_17 = (RT17_I*RT17_J <= 150);
  constraint reg_capacity_18 = (RT18_I*RT18_J <= 150);
  constraint reg_capacity_19 = (RT19_I*RT19_J*RT19_K <= 150);
  constraint reg_capacity_20 = (RT20_I*RT20_J <= 150);
  constraint reg_capacity_21 = (RT21_I*RT21_J*RT21_K <= 150);
  constraint reg_capacity_23 = (RT23_I*RT23_K <= 150);
  constraint reg_capacity_26 = (RT26_I*RT26_K <= 150);
  constraint reg_capacity_27 = (RT27_I*RT27_J <= 150);
  constraint reg_capacity_28 = (RT28_I*RT28_J*RT28_K <= 150);
  constraint reg_capacity_29 = (RT29_I*RT29_J <= 150);
  constraint reg_capacity_30 = (RT30_I*RT30_J <= 150);
  constraint reg_capacity_31 = (RT31_I*RT31_J*RT31_K <= 150);

 }
 
 def input_params {
    let N = [6];
    let M = [2];
    param n[] = N;
    param m[] = M;
 }
 
 def input_vars {
   decl dynamic double y[m] = random;
   decl dynamic double x_hat[n] = random;
   decl dynamic double C[m*n] = random;
   decl dynamic double R[m*m] = random;
   decl dynamic double P[n*n] = random;
   decl dynamic double K[n*m] = random;
   decl dynamic double x_hat_new[n] = 0;
   decl dynamic double C_T[m*n] = 0;
   decl dynamic double id[n*n] = 0;
   decl dynamic double temp_1[n*n] = 0;
   decl dynamic double temp_2[n*n] = 0;
   decl dynamic double temp_3[n*n] = 0;
   decl dynamic double temp_4[n*n] = 0;
 }
 
 def search {
   arg algorithm = 'Simplex';
   arg total_runs  = 1000;
 }

) @*/


  // stuff that is generally useful (particularly add and mult)
  int i, j, k;
  int it, jt, kt;
  int c_ind, a_row, c_row;

  // stuff for inverting
  double cofactor[n*n];
  double adjoint[n*n];
  double det;

  // stuff for determinant
  int num_pivots;
  int size_a = m*m;
  double L[size_a];
  double U[size_a];
  double P2[size_a];

  // stuff for LUP
  int ind_max, curr_row, next_row;
  int i2, j2, k2;
  int i2t, j2t, k2t;
  double max_a, abs_a, coeff;
  double temp_row[m];

  // for cofactor
  double det2 = 0;
  int r2, c2, row, rr;
  int n_b = m-1;
  int size_b = (m-1) * (m-1);
  int sign = 1;
  double mat_b[size_b];

  // stuff for the inner determinant and LUP
  int i3, j3, k3;
  int i3t, j3t, k3t;
  double L_small[size_b];
  double U_small[size_b];
  double P_small[size_b];
  int i4, j4, k4;
  int i4t, j4t, k4t;
  double temp_row_small[n_b];
  int i5, j5, row5;
  int i5t, j5t, row5t;

  // stuff for other
  int row2, ind;
  double scalar_1, scalar_2;
  double scalar_3, scalar_4;


/*@ begin Loop ( 

  transform Composite(
    unrolljam = (['i','j'],[U1_I,U1_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT1_I,RT1_J])
  ) 
  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= n-1; j++) {
      C_T[m * j + i] = C[n * i + j];
    }
  }

  transform Composite(
    unrolljam = (['i','j'],[U2_I,U2_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT2_I,RT2_J])
  ) 
  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= n-1; j++) {
      temp_1[j + n * i] = 0;
      temp_2[j + n * i] = 0;
    }
  }
  
  transform Composite(
    unrolljam = (['i','j','k'],[U3_I,U3_J,U3_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j','k'],[RT3_I,RT3_J,RT3_K])
  ) 
  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_1[j + n * i] += C[n * i + k] * P[n * k + j];
      }
    } 
  }


  transform Composite(
    unrolljam = (['i','j','k'],[U4_I,U4_J,U4_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j','k'],[RT4_I,RT4_J,RT4_K])
  ) 
  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_2[j + n * i] += temp_1[n * i + k] * C_T[n * k + j];
      }
    } 
  }

  transform Composite(
    unrolljam = (['i','j'],[U5_I,U5_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT5_I,RT5_J])
  )  
  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= m-1; j++) {
      temp_1[m * i + j] = temp_2[m * i + j] + R[m * i + j];
    }
  }

  if (m == 1) {
    temp_2[0] = 1 / temp_1[0];
  } else {
    
      det = 1.0;
        num_pivots = 0;

        transform Composite(
          unrolljam = (['i2','j2'],[U6_I,U6_J]),
          vector = (VEC, ['ivdep','vector always']),
          regtile = (['i2','j2'],[RT6_I,RT6_J])
        )  
        for (i2 = 0; i2 <= m-1; i2++) {
          for (j2 = 0; j2 <= m-1; j2++) {
            if(i2 == j2)
              P2[m * i2 + j2] = L[m * i2 + j2] = 1;
            else
              P2[m * i2 + j2] = L[m * i2 + j2] = 0;
          }
        }

        transform Composite(
          unrolljam = (['i2'],[U7_I]),
          vector = (VEC, ['ivdep','vector always']),
          regtile = (['i2'],[RT7_I])
        )  
        for (i2 = 0; i2 <= size_a-1; i2++) {
          U[i2] = temp_1[i2];
        }

        for(i = 0; i <= m-1; i++) {
          if(U[i * m + i] > 0) max_a = U[i * m + i]; 
          else max_a = 0 - U[i * m + i];
          ind_max = i;

          transform Composite(
            unrolljam = (['j'],[U8_J]),
            vector = (VEC, ['ivdep','vector always']),
            regtile = (['j'],[RT8_J])
          ) 
          for (j = i+1; j <= m-1; j++) {
            if(U[j * m + i] > 0) abs_a = U[j * m + i]; 
            else abs_a = 0 - U[j * m + i];
            if (abs_a > max_a) {
              max_a = abs_a;
              ind_max = j;
            }
          }

          if (ind_max == i) {}
          else {
            num_pivots++;
            transform Composite(
              unrolljam = (['i2'],[U9_I]),
              vector = (VEC, ['ivdep','vector always']),
              regtile = (['i2'],[RT9_I])
            ) 
            for (i2 = 0; i2 <= size_a-1; i2++) {
              scalar_1 = P2[i * m + i2];
              P2[i * m + i2] = P2[ind_max * m + i2];
              P[ind_max * m + i2] = scalar_1;

              scalar_2 = U[i * m + i2];
              U[ind_max * m + i2] = U[i * m + i2];
              U[ind_max * m + i2] = scalar_2;
            }

          }

          transform Composite(
            unrolljam = (['j','k'],[U10_J,U10_K]),
            regtile = (['j','k'],[RT10_J,RT10_K]),
            vector = (VEC, ['ivdep','vector always'])
          )
          for(j = i+1; j <= m-1; j++) {
            coeff = (U[j * m + i]/U[i * m + i]);
            L[j * m + i] = coeff;
            for (k = i; k <= m-1; k++) {
              U[j * m + k] -= coeff * U[i * m + k];
            }
          }

        } 

      if((num_pivots%2) == 1)
        det = 0 -1.0; 
      else
        det = 1.0;
      
      for (i = 0; i <= m-1; i++) 
        det *= U[i*m+i];

    //# end determinant

    det = 1 / det;

    for (i2 = 0; i2 <= m-1; i2++) {
      for (j2 = 0; j2 <= m-1; j2++) {
          k2 = 0;
          for (r2 = 0; r2 <= m-1; r2++) {
            if(r2 == i2){}
            else {
              for (c2 = 0; c2 <= m-1; c2++) {
                if(c2 == j2) {}
                else mat_b[k2++] = temp_1[m * r2 + c2];
              }
            }
          }

        // det2 = determinant_matrix(mat_b, n_b);

        det2 = 1.0;
        
        // num_pivots = compute_LUP(mat_b, L_small, U_small, P_small, n_b);
          num_pivots = 0;
          transform Composite(
            unrolljam = (['i5','j5'],[U12_I,U12_J]),
            regtile = (['i5','j5'],[RT12_I,RT12_J]),
            vector = (VEC, ['ivdep','vector always'])
          )
          for (i5 = 0; i5 <= n_b-1; i5++) {
            for (j5 = 0; j5 <= n_b-1; j5++) {
              if(i5 == j5)
                P_small[n_b * i5 + j5] = L_small[n_b * i5 + j5] = 1;
              else
                P_small[n_b * i5 + j5] = L_small[n_b * i5 + j5] = 0;
            }
          }

          // copy_mat(mat_b, U_small, size_b);
          transform Composite(
            unrolljam = (['i5'],[U13_I]),
            regtile = (['i5'],[RT13_I]),
            vector = (VEC, ['ivdep','vector always'])
          )
          for (i5 = 0; i5 <= size_b-1; i5++)
            U_small[i5] = mat_b[i5];

          for(i4 = 0; i4 <= n_b-1; i4++) {
            if(U[i4 * n_b + i4] < 0)
              max_a = 0 - U[i4 * n_b + i4];
            else 
              max_a = U[i4 * n_b + i4];
            ind_max = i4;

            transform Composite(
              unrolljam = (['j4'],[U14_J]),
              regtile = (['j4'],[RT14_J]),
              vector = (VEC, ['ivdep','vector always'])
            )
            for (j4 = i4+1; j4 <= n_b-1; j4++) {
              if(U[j4 * n_b + i4] < 0)
                max_a = 0 - U[j4 * n_b + i4];
              else 
                max_a = U[j4 * n_b + i4];              
              if (abs_a > max_a) {
                max_a = abs_a;
                ind_max = j4;
              }
            }

            if (ind_max == i4) {}
            else {
              num_pivots++;

              transform Composite(
                unrolljam = (['i5'],[U14_I]),
                regtile = (['i5'],[RT14_I]),
                vector = (VEC, ['ivdep','vector always'])
              )
              for (i5 = 0; i5 <= n_b-1; i5++){
                scalar_3 = P_small[i4 * n_b + i5];
                P_small[i4 * n_b + i5] = P_small[ind_max*n_b + i5];
                P_small[ind_max*n_b + i5] = scalar_3;

                scalar_4 = U_small[i4 * n_b + i5];
                U_small[i4 * n_b + i5] = U_small[ind_max*n_b + i5];
                U_small[ind_max*n_b + i5] = scalar_4;
              }
            }
            transform Composite(
              unrolljam = (['j4','k4'],[U15_J,U15_J]),
              regtile = (['j4','k4'],[RT15_J,RT15_J]),
              vector = (VEC, ['ivdep','vector always'])
            )
            for(j4 = i4+1; j4 <= n_b-1; j4++) {
              coeff = (U[j4 * n_b+i4]/U[i4 * n_b+i4]);
              L_small[j4 * n_b+i4] = coeff;
              for (k4 = i4; k4 <= n_b-1; k4++) {
                U_small[j4 * n_b + k4] -= coeff * U_small[i4 * n_b + k4];
              }
            }

          }

        if ((num_pivots%2) == 1)
          det2 = 0 - 1.0;
        else
          det2 = 1.0;

        transform Composite(
          unrolljam = (['i3'],[U16_I]),
          regtile = (['i3'],[RT16_I]),
          vector = (VEC, ['ivdep','vector always'])
        )
        for (i3 = 0; i3 <= n_b-1; i3++) {
          det2 *= U_small[i3*n_b+i3];
        }
        // end det2

        cofactor[m * i2 + j2] = sign * det2;
        sign = sign * -1;
      }
      sign = sign * -1;
    }
    // end cofactor

    // transpose_matrix(cofactor, m, m, adjoint);
    // multiply_matrix_by_scalar(adjoint, m, m, det, temp_2);
    transform Composite(
      unrolljam = (['i5','j5'],[U17_I,U17_J]),
      regtile = (['i5','j5'],[RT17_I,RT17_J]),
      vector = (VEC, ['ivdep','vector always'])
    )  
    for (i5 = 0; i5 <= m-1; i5++) {
      for (j5 = 0; j5 <= m-1; j5++) {
        temp_2[m * j5 + i5] = cofactor[m * i5 + j5] * det;
      }
    }


  }
  // end invert

  // multiply_matrix(P, n, n, C_T, m, temp_1); // P*C_T
  transform Composite(
    unrolljam = (['i','j'],[U18_I,U18_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT18_I,RT18_J])
  )
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= m-1; j++)
      temp_1[j + m * i] = 0;

  transform Composite(
    unrolljam = (['i','j','k'],[U19_I,U19_J,U19_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j','k'],[RT19_I,RT19_J,RT19_K])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= m-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_1[j + m * i] += P[n * i + k] * C_T[m * k + j];
      }
    } 
  }
  // multiply_matrix(temp_1, n, m, temp_2, m, K);
  transform Composite(
    unrolljam = (['i','j'],[U20_I,U20_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT20_I,RT20_J])
  )
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= m-1; j++)
      K[j + m * i] = 0;

  transform Composite(
    unrolljam = (['i','j','k'],[U21_I,U21_J,U21_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j','k'],[RT21_I,RT21_J,RT21_K])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= m-1; j++) {
      for (k = 0; k <= m-1; k++) {
        K[j + m * i] += temp_1[m * i + k] * temp_2[m * k + j];
      }
    } 
  }

  // multiply_matrix(C, m, n, x_hat_new, 1, temp_3);
  // multiply_matrix_by_scalar(temp_3, m, 1, -1, temp_4);
  transform Composite(
    unrolljam = (['i'],[U22_I]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i'],[RT22_I])
  )
  for (i = 0; i <= m-1; i++)
    temp_4[i] = 0;

  transform Composite(
    unrolljam = (['i','k'],[U23_I,U23_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','k'],[RT23_I,RT23_K])
  )
  for (i = 0; i <= m-1; i++) {
    for (k = 0; k <= n-1; k++) {
      temp_4[i] += C[n * i + k] * x_hat_new[k];
    }
  }

  // multiply_matrix_by_scalar(temp_3, m, 1, -1, temp_4);
  // add_matrix(y, m, 1, temp_4, temp_3);
  transform Composite(
    unrolljam = (['i'],[U24_I]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i'],[RT24_I])
  )
  for (i = 0; i <= m-1; i++) {
    temp_3[i] = y[i] + temp_4[i]*(0-1);
  }





  // multiply_matrix(K, n, m, temp_3, 1, temp_4);
  // add_matrix(x_hat_new, n, 1, temp_4, x_hat);
  transform Composite(
    unrolljam = (['i'],[U25_I]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i'],[RT25_I])
  )
  for (i = 0; i <= n-1; i++)
    x_hat[i] = x_hat_new[i];

  transform Composite(
    unrolljam = (['i','k'],[U26_I,U26_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','k'],[RT26_I,RT26_K])
  )
  for (i = 0; i <= n-1; i++) {
    for (k = 0; k <= m-1; k++) {
      x_hat[i] += K[m * i + k] * temp_3[k];
    }
  }

  // multiply_matrix(K, n, m, C, n, temp_1);
  transform Composite(
    unrolljam = (['i','j'],[U27_I,U27_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT27_I,RT27_J])
  )
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= n-1; j++)
      temp_1[j + n * i] = 0;

  transform Composite(
    unrolljam = (['i','j','k'],[U28_I,U28_J,U28_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j','k'],[RT28_I,RT28_J,RT28_K])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= m-1; k++) {
        temp_1[j + n * i] += K[m * i + k] * C[n * k + j];
      }
    } 
  }

  // multiply_matrix_by_scalar(temp_1, n, n, -1, temp_2);
  // add_matrix(id, n, n, temp_2, temp_1);
  transform Composite(
    unrolljam = (['i','j'],[U29_I,U29_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT29_I,RT29_J])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      temp_1[n * i + j] = id[n * i + j] + temp_1[n * i + j] *(0-1);
    }
  }

  // multiply_matrix(temp_1, n, n, P, n, temp_2);
  transform Composite(
    unrolljam = (['i','j'],[U30_I,U30_J]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j'],[RT30_I,RT30_J])
  )
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= n-1; j++)
      temp_2[j + n * i] = 0;

  transform Composite(
    unrolljam = (['i','j','k'],[U31_I,U31_J,U31_K]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i','j','k'],[RT31_I,RT31_J,RT31_K])
  )
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_2[j + n * i] += temp_1[n * i + k] * P[n * k + j];
      }
    } 
  }

  // copy_mat(temp_2, P, n * n);
  size_a = n*n;
  transform Composite(
    unrolljam = (['i'],[U32_I]),
    vector = (VEC, ['ivdep','vector always']),
    regtile = (['i'],[RT32_I])
  )
  for (i = 0; i <= size_a-1; i++)
    P[i] = temp_2[i];

) @*/




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




 
  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= n-1; j++) {
      C_T[m * j + i] = C[n * i + j];
    }
  }

  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= n-1; j++) {
      temp_1[j + n * i] = 0;
      temp_2[j + n * i] = 0;
    }
  }
   
  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_1[j + n * i] += C[n * i + k] * P[n * k + j];
      }
    } 
  }

  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_2[j + n * i] += temp_1[n * i + k] * C_T[n * k + j];
      }
    } 
  }

  for (i = 0; i <= m-1; i++) {
    for (j = 0; j <= m-1; j++) {
      temp_1[m * i + j] = temp_2[m * i + j] + R[m * i + j];
    }
  }

  if (m == 1) {
    temp_2[0] = 1 / temp_1[0];
  } else {
    
      det = 1.0;
        num_pivots = 0;
 
        for (i2 = 0; i2 <= m-1; i2++) {
          for (j2 = 0; j2 <= m-1; j2++) {
            if(i2 == j2)
              P2[m * i2 + j2] = L[m * i2 + j2] = 1;
            else
              P2[m * i2 + j2] = L[m * i2 + j2] = 0;
          }
        }


        for (i2 = 0; i2 <= size_a-1; i2++) {
          U[i2] = temp_1[i2];
        }

        for(i = 0; i <= m-1; i++) {
          if(U[i * m + i] > 0) max_a = U[i * m + i]; 
          else max_a = 0 - U[i * m + i];
          ind_max = i;

 
          for (j = i+1; j <= m-1; j++) {
            if(U[j * m + i] > 0) abs_a = U[j * m + i]; 
            else abs_a = 0 - U[j * m + i];
            if (abs_a > max_a) {
              max_a = abs_a;
              ind_max = j;
            }
          }

          if (ind_max == i) {}
          else {
            num_pivots++;

            for (i2 = 0; i2 <= size_a-1; i2++) {
              scalar_1 = P2[i * m + i2];
              P2[i * m + i2] = P2[ind_max * m + i2];
              P[ind_max * m + i2] = scalar_1;

              scalar_2 = U[i * m + i2];
              U[ind_max * m + i2] = U[i * m + i2];
              U[ind_max * m + i2] = scalar_2;
            }

          }

          for(j = i+1; j <= m-1; j++) {
            coeff = (U[j * m + i]/U[i * m + i]);
            L[j * m + i] = coeff;
            for (k = i; k <= m-1; k++) {
              U[j * m + k] -= coeff * U[i * m + k];
            }
          }

        } 

      if((num_pivots%2) == 1)
        det = 0 -1.0; 
      else
        det = 1.0;
      
      for (i = 0; i <= m-1; i++) 
        det *= U[i*m+i];

    //# end determinant

    det = 1 / det;

    for (i2 = 0; i2 <= m-1; i2++) {
      for (j2 = 0; j2 <= m-1; j2++) {
          k2 = 0;
          for (r2 = 0; r2 <= m-1; r2++) {
            if(r2 == i2){}
            else {
              for (c2 = 0; c2 <= m-1; c2++) {
                if(c2 == j2) {}
                else mat_b[k2++] = temp_1[m * r2 + c2];
              }
            }
          }

        // det2 = determinant_matrix(mat_b, n_b);

        det2 = 1.0;
        
        // num_pivots = compute_LUP(mat_b, L_small, U_small, P_small, n_b);
          num_pivots = 0;

          for (i5 = 0; i5 <= n_b-1; i5++) {
            for (j5 = 0; j5 <= n_b-1; j5++) {
              if(i5 == j5)
                P_small[n_b * i5 + j5] = L_small[n_b * i5 + j5] = 1;
              else
                P_small[n_b * i5 + j5] = L_small[n_b * i5 + j5] = 0;
            }
          }

          // copy_mat(mat_b, U_small, size_b);

          for (i5 = 0; i5 <= size_b-1; i5++)
            U_small[i5] = mat_b[i5];

          for(i4 = 0; i4 <= n_b-1; i4++) {
            if(U[i4 * n_b + i4] < 0)
              max_a = 0 - U[i4 * n_b + i4];
            else 
              max_a = U[i4 * n_b + i4];
            ind_max = i4;

            for (j4 = i4+1; j4 <= n_b-1; j4++) {
              if(U[j4 * n_b + i4] < 0)
                max_a = 0 - U[j4 * n_b + i4];
              else 
                max_a = U[j4 * n_b + i4];              
              if (abs_a > max_a) {
                max_a = abs_a;
                ind_max = j4;
              }
            }

            if (ind_max == i4) {}
            else {
              num_pivots++;

              for (i5 = 0; i5 <= n_b-1; i5++){
                scalar_3 = P_small[i4 * n_b + i5];
                P_small[i4 * n_b + i5] = P_small[ind_max*n_b + i5];
                P_small[ind_max*n_b + i5] = scalar_3;

                scalar_4 = U_small[i4 * n_b + i5];
                U_small[i4 * n_b + i5] = U_small[ind_max*n_b + i5];
                U_small[ind_max*n_b + i5] = scalar_4;
              }
            }

            for(j4 = i4+1; j4 <= n_b-1; j4++) {
              coeff = (U[j4 * n_b+i4]/U[i4 * n_b+i4]);
              L_small[j4 * n_b+i4] = coeff;
              for (k4 = i4; k4 <= n_b-1; k4++) {
                U_small[j4 * n_b + k4] -= coeff * U_small[i4 * n_b + k4];
              }
            }

          }

        if ((num_pivots%2) == 1)
          det2 = 0 - 1.0;
        else
          det2 = 1.0;

        for (i3 = 0; i3 <= n_b-1; i3++) {
          det2 *= U_small[i3*n_b+i3];
        }
        // end det2

        cofactor[m * i2 + j2] = sign * det2;
        sign = sign * -1;
      }
      sign = sign * -1;
    }
    // end cofactor

    // transpose_matrix(cofactor, m, m, adjoint);
    // multiply_matrix_by_scalar(adjoint, m, m, det, temp_2);
    for (i5 = 0; i5 <= m-1; i5++) {
      for (j5 = 0; j5 <= m-1; j5++) {
        temp_2[m * j5 + i5] = cofactor[m * i5 + j5] * det;
      }
    }


  }
  // end invert




//TODO



  // multiply_matrix(P, n, n, C_T, m, temp_1); // P*C_T
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= m-1; j++)
      temp_1[j + m * i] = 0;

  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= m-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_1[j + m * i] += P[n * i + k] * C_T[m * k + j];
      }
    } 
  }
  // multiply_matrix(temp_1, n, m, temp_2, m, K);
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= m-1; j++)
      K[j + m * i] = 0;

  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= m-1; j++) {
      for (k = 0; k <= m-1; k++) {
        K[j + m * i] += temp_1[m * i + k] * temp_2[m * k + j];
      }
    } 
  }

  // multiply_matrix(C, m, n, x_hat_new, 1, temp_3);
  for (i = 0; i <= m-1; i++)
    temp_4[i] = 0;

  for (i = 0; i <= m-1; i++) {
    for (k = 0; k <= n-1; k++) {
      temp_4[i] += C[n * i + k] * x_hat_new[k];
    }
  }

  // multiply_matrix_by_scalar(temp_3, m, 1, -1, temp_4);
  // add_matrix(y, m, 1, temp_4, temp_3);
  for (i = 0; i <= m-1; i++) {
    temp_3[i] = y[i] + temp_4[i]*(0-1);
  }

  // multiply_matrix(K, n, m, temp_3, 1, temp_4);
  // add_matrix(x_hat_new, n, 1, temp_4, x_hat);
  for (i = 0; i <= n-1; i++)
    x_hat[i] = x_hat_new[i];

  for (i = 0; i <= n-1; i++) {
    for (k = 0; k <= m-1; k++) {
      x_hat[i] += K[m * i + k] * temp_3[k];
    }
  }

  // multiply_matrix(K, n, m, C, n, temp_1);
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= n-1; j++)
      temp_1[j + n * i] = 0;

  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= m-1; k++) {
        temp_1[j + n * i] += K[m * i + k] * C[n * k + j];
      }
    } 
  }

  // multiply_matrix_by_scalar(temp_1, n, n, -1, temp_2);
  // add_matrix(id, n, n, temp_2, temp_1);
  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      temp_1[n * i + j] = id[n * i + j] + temp_1[n * i + j] *(0-1);
    }
  }

  // multiply_matrix(temp_1, n, n, P, n, temp_2);
  for (i = 0; i <= n-1; i++)
    for (j = 0; j <= n-1; j++)
      temp_2[j + n * i] = 0;

  for (i = 0; i <= n-1; i++) {
    for (j = 0; j <= n-1; j++) {
      for (k = 0; k <= n-1; k++) {
        temp_2[j + n * i] += temp_1[n * i + k] * P[n * k + j];
      }
    } 
  }

  // copy_mat(temp_2, P, n * n);
  size_a = n*n;
  for (i = 0; i <= size_a-1; i++)
    P[i] = temp_2[i];


/*@ end @*/
/*@ end @*/


}
