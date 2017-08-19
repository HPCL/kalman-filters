void correct_4_B(int xhn_ncols,int P_nrows,int K_ncols,double *K,double *C,double *t50,double *t47,double *t59,int __s206,int __m207){

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
let s206 = [512];
let m207 = [6];
param K_nrows[] = N;
param K_ncols[] = N;
param C_nrows[] = N;
param C_ncols[] = N;
param t50_nrows[] = N;
param t50_ncols[] = N;
param t47_nrows[] = N;
param t47_ncols[] = N;
param t59_nrows[] = N;
param t59_ncols[] = N;
param s206 = s206;
param m207 = m207;
}

def input_vars {
decl dynamic double K[K_nrows*K_ncols] = random;
decl dynamic double C[C_nrows*C_ncols] = random;
decl dynamic double t50[t50_nrows*t50_ncols] = random;
decl dynamic double t47[t47_nrows*t47_ncols] = random;
decl dynamic double t59[t59_nrows*t59_ncols] = random;
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

for (j=0; j<=__m207-1; j+=__s206) {
  // 4_2
  int __m206;

  if j + __s206 > __m207
    __m206 = __m207 - j;
  else
    __m206 = __s206;

  double *t96 = malloc(sizeof(double)*__s206);
  double *t79 = malloc(sizeof(double)*P_nrows*__s206);
  double *t76 = malloc(sizeof(double)*K_ncols*__s206);
  // double *t83 = t59 + j;
  // double *t71 = t47 + j;
  // double *t74 = t50 + j;
  for (k=0; k<=K_ncols-1; k+=1) {
    // 4_3
    // double *t100 = t76[k*__m206];
    // double *t95 = C[k*P_nrows];
    // double *t98 = t50[j + k*xhn_ncols];
    for (__zr__ = 0; __zr__ <= __m206-1; ++__zr__) t96[__zr__] = 0.0;
    for (l=0; l<=P_nrows-1; l+=1) {
      // 4_4
      // double *t121 = t47[j + l*xhn_ncols];
      for (p=0; p<=__m206-1; p+=1) {
        // 4_5
        t96[p] += (C[k*P_nrows + l]*t47[j + l*xhn_ncols+p]);
      }
    }
    for (l=0; l<=__m206-1; l+=1) {
      // 5_4
      t76[k*__m206 + l] = (t50[j + k*xhn_ncols+l]-t96[l]);
    }
  }
  for (k=0; k<=P_nrows-1; k+=1) {
    // 6_3
    // double *t103 = t79 + k*__m206;
    double *t102 = K[k*K_ncols];
    for (__zr__ = 0; __zr__ <=__m206-1; ++__zr__) t79[k*__m206+__zr__] = 0.0;
    for (l=0; l<=K_ncols-1; l+=1) {
      // 6_4
      double *t129 = t76 + l*__m206;
      for (p=0; p<=__m206-1; p+=1) {
        // 6_5
        t79[k*__m206+p] += (K[k*K_ncols+l]*t76[l*__m206+p]);
      }
    }
  }
  for (k=0; k<=P_nrows-1; k+=1) {
    // 7_3
    // double *t107 = t59[j + k*xhn_ncols];
    // double *t105 = t47[j + k*xhn_ncols];
    // double *t106 = t79 + k*__m206;
    for (l=0; l<=__m206-1; l+=1) {
      // 7_4
      t59[j + k*xhn_ncols+l] = (t47[j + k*xhn_ncols+l]+t79[k*__m206+l]);
    }
  }
  free(t96);
  free(t79);
  free(t76);
}


) @*/ 

/*@ end @*/
/*@ end @*/


}