correct_4_A(int P_nrows, double *C, int K_ncols, double *t61, double *t62, int __s214, int __m215){

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
param U_p0[] = range(1,6);
param RT_j0 = range[1,2,6];
param RT_k0 = range[1,2,6];
param RT_l0 = range[1,2,6];
param RT_p0 = range[1,2,6];
param CFLAGS[] = ['-O1', '-O2', '-O3'];
param VEC[] = [False, True];
constraint unroll_limit_0 = ((U_j0 == 1) or (U_k0 == 1) or (U_l0 == 1) or (U_p0 == 1));
constraint reg_capacity0 = (RT_j0 == 1)*RT_k0 == 1)*RT_l0 == 1)*RT_p0 == 1) <= 150);
}

def input_params {
let N = [6];
let s214 = [512];
let m215 = [6];
param C_nrows[] = N;
param C_ncols[] = N;
param t61_nrows[] = N;
param t61_ncols[] = N;
param t62_nrows[] = N;
param t62_ncols[] = N;
param s214 = s214;
param m215 = m215;
}

def input_vars {
decl dynamic double C[C_nrows*C_ncols] = random;
decl dynamic double t61[t61_nrows*t61_ncols] = random;
decl dynamic double t62[t62_nrows*t62_ncols] = random;
}

def search {
arg algorithm = 'Randomsearch';
arg total_runs  = 10000;
}

) @*/

int disp, __zr__,j,k,l,p;
int jt,kt,lt,pt;



/*@ begin Loop (

transform Composite(
unrolljam = (['j','k','l','p'],[U_j0,U_k0,U_l0,U_p0]),
regtile = (['j','k','l','p'],[RT_j0,RT_k0,RT_l0,RT_p0]),
vector = (VEC, ['ivdep','vector always'])
)

// ORIO A
for (j=0; j<=__m215-1; j+=__s214) {
  // 9_2

  int __m214;
  if(j + __s214 > __m215)
    __m214 = __m215 - j;
  else
    __m214 = __s214;

  // double *t86 = t62 + j*P_nrows;
  // double *t85 = t61 + j*K_ncols;
  for (k=0; k<=__m214-1; k+=1) {
    // 9_3
    // double *t110 = t62[j*P_nrows] + k*P_nrows;
    // double *t109 = t61[j*K_ncols] + k*K_ncols;
    for (__zr__ = 0; __zr__ <= P_nrows-1; ++__zr__) t62[j*P_nrows + k*P_nrows + __zr__] = 0.0;
    for (l=0; l<K_ncols; l+=1) {
      // 9_4
      double *t137 = C + l*P_nrows;
      for (p=0; p<=P_nrows-1; p+=1) {
        // 9_5
        t62[j*P_nrows + k*P_nrows + p] += (t61[j*K_ncols + k*K_ncols + l]*C[l*P_nrows + p]);
      }
    }
  }
}

) @*/ 


/*@ end @*/
/*@ end @*/

}
