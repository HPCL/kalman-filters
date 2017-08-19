correct_4_B(int P_nrows, int P_ncols, int t65_nrows, int t65_ncols, int t64_nrows, int t64_ncols, int t66_nrows, int t66_ncols, 
  double *t65, double *t64, double *t66, int __s216, int __m217){

/*@ begin PerfTuning (

def build {
arg build_command = 'gcc';
}

def performance_counter {
arg repetitions = 50;
}def performance_params {
param U_k0[] = range(1,6);
param U_l0[] = range(1,6);
param RT_k0 = range[1,2,6];
param RT_l0 = range[1,2,6];
param CFLAGS[] = ['-O1', '-O2', '-O3'];
param VEC[] = [False, True];
constraint unroll_limit_0 = ((U_k0 == 1) or (U_l0 == 1));
constraint reg_capacity0 = (RT_k0 == 1)*RT_l0 == 1) <= 150);
}

def input_params {
let N = [6];
let s216 = [512];
let m217 = [6];
param P_nrows[] = N;
param P_ncols[] = N;
param t65_nrows[] = N;
param t65_ncols[] = N;
param t64_nrows[] = N;
param t64_ncols[] = N;
param t66_nrows[] = N;
param t66_ncols[] = N;
param s216 = s216;
param m217 = m217;
}

def input_vars {
decl dynamic double t65[t65_nrows*t65_ncols] = random;
decl dynamic double t64[t64_nrows*t64_ncols] = random;
decl dynamic double t66[t66_nrows*t66_ncols] = random;
}

def search {
arg algorithm = 'Randomsearch';
arg total_runs  = 10000;
}

) @*/

int disp, __zr__,j,k,l;
int jt,kt,lt;

/*@ begin Loop (

transform Composite(
unrolljam = (['k','l'],[U_k0,U_l0]),
regtile = (['k','l'],[RT_k0,RT_l0]),
vector = (VEC, ['ivdep','vector always'])
)


//ORIO B
for (j=0; j<=__m217-1; j+=__s216) {
  // 10_2

  if(j + __s216 > __m217)
    __m216 = __m217 - j;
  else
    __m216 = __s216;

  // double *t90 = t66 + j*P_nrows;
  // double *t88 = t64 + j*P_nrows;
  // double *t89 = t65 + j*P_nrows;
  for (k=0; k<=__m216-1; k+=1) {
    // 10_3
    // double *t114 = t66[j*P_nrows + k*P_nrows]; 
    // double *t112 = t64[j*P_nrows + k*P_nrows];
    // double *t113 = t65[j*P_nrows + k*P_nrows];
    for (l=0; l<=P_nrows-1; l+=1) {
      // 10_4
      t66[j*P_nrows + k*P_nrows + l] = (t64[j*P_nrows + k*P_nrows + l]-t65[j*P_nrows + k*P_nrows + l]);
    }
  }


) @*/ 

/*@ end @*/
/*@ end @*/

}