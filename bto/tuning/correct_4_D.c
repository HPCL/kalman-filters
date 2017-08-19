void correct_4_D(int xhn_ncols,int P_nrows,int K_ncols,double *P,double *t45,int __s206,int __m207){

/*@ begin PerfTuning (

def build {
arg build_command = 'gcc';
}

def performance_counter {
arg repetitions = 50;
}def performance_params {
param U_j0[] = range(1,6);
param U_k0[] = range(1,6);
param U_l0[] = range(1,6);
param RT_j0 = range[1,2,6];
param RT_k0 = range[1,2,6];
param RT_l0 = range[1,2,6];
param CFLAGS[] = ['-O1', '-O2', '-O3'];
param VEC[] = [False, True];
constraint unroll_limit_0 = ((U_j0 == 1) or (U_k0 == 1) or (U_l0 == 1));
constraint reg_capacity0 = (RT_j0 == 1)*RT_k0 == 1)*RT_l0 == 1) <= 150);
}

def input_params {
let N = [6];
let s206 = [512];
let m207 = [6];
param P_nrows[] = N;
param P_ncols[] = N;
param t45_nrows[] = N;
param t45_ncols[] = N;
param s206 = s206;
param m207 = m207;
}

def input_vars {
decl dynamic double P[P_nrows*P_ncols] = random;
decl dynamic double t45[t45_nrows*t45_ncols] = random;
}

def search {
arg algorithm = 'Randomsearch';
arg total_runs  = 10000;
}

) @*/



/*@ begin Loop (

transform Composite(
unrolljam = (['j','k','l'],[U_j0,U_k0,U_l0]),
regtile = (['j','k','l'],[RT_j0,RT_k0,RT_l0]),
vector = (VEC, ['ivdep','vector always'])
)

for (i=0; i<=P_nrows-1; i+=__s218) {
  // 12_1
  int __m218; 
  if (i + __s218 > P_nrows)
    __m218 = P_nrows - i;
  else
    __m218 = __s218;

  // double *t69 = P + i*P_ncols;
  // double *t68 = t45 + i*P_nrows;
  for (j=0; j<=__m218-1; j+=1) {
    // 12_2
    // double *t93 = P[i*P_ncols + j*P_ncols];
    // double *t92 = t45[i*P_nrows + j*P_nrows];
    for (__zr__ = 0; __zr__ <=P_ncols-1; ++__zr__) P[i*P_ncols + j*P_ncols + __zr__] = 0.0;
    for (k=0; k<=P_nrows-1; k+=1) {
      // 12_3
      // double *t117 = P + k*P_ncols;
      for (l=0; l<=P_ncols-1; l+=1) {
        // 12_4
        P[i*P_ncols + j*P_ncols + l] += (t45[i*P_nrows + j*P_nrows + k]*P[k*P_ncols+l]);
      }
    }
  }
}

) @*/ 

/*@ end @*/
/*@ end @*/


}