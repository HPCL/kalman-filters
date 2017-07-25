CC = icpc -std=c++11

OCV_LIBS = -lopencv_imgproc # 
OCV_LIBS+= -lopencv_highgui # I think this one lets us get keyboard input
OCV_LIBS+= -lopencv_objdetect #
OCV_LIBS+= -lopencv_core -lopencv_videoio # basic opencv
OCV_LIBS+= -lopencv_video # background subtractor MOG2
OCV_LIBS+= -lopencv_imgcodecs #
#OCV_LIBS+= -lraspicam -lraspicam_cv # to live stream with raspicam not on arya

#OCV_PATH  = -I/usr/include/ # on pi
OCV_PATH  = -L/usr/local/packages/opencv/lib # on arya
OCV_PATH_SANSA  = -L/usr/local/packages/opencv-3.2/lib # on sansa
CUDA_PATH = -L/usr/local/cuda-8.0/lib64 # on sansa?
OCV_PATH += -I/usr/local/packages/opencv/include # on arya
OCV_PATH_SANSA += -I/usr/local/packages/opencv-3.2/include # on arya

KALMAN_FILES  = linear_algebra.o # 
KALMAN_FILES += kalman_filter.o #

CBLAS_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl #
CBLAS_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #

TUNED_KAL_FILES  = ../basic-c/tuning_kalman/non_tuned.o 
TUNED_KAL_FILES += ../basic-c/tuning_kalman/_predict.o 
TUNED_KAL_FILES += ../basic-c/tuning_kalman/_correct.o 

TUNED_LA_FILES  = ../basic-c/tuning/non_tuned.o
TUNED_LA_FILES += ../basic-c/tuning/_add_mat.o
TUNED_LA_FILES += ../basic-c/tuning/_compute_LUP_inline.o
TUNED_LA_FILES += ../basic-c/tuning/_multiply_matrix.o
TUNED_LA_FILES += ../basic-c/tuning/_multiply_matrix_by_scalar.o
TUNED_LA_FILES += ../basic-c/tuning/_transpose_matrix.o

TUNED_PATH  = -L../basic-c/tuning/
# TUNED_PATH += -L../basic-c/

BLAS_KAL_FILES  = kalman_filter.o #

ATLAS_LINK = -L${ATLASLIB} -lcblas -llapack -lptcblas -lpthread -latlas
ATLAS_INC  = -I${ATLASINC}
ATLAS_SYS  = -DSYS=\"sys_atlas.h\"

CBLAS_LINK = -L${MKLROOT}/lib/intel64 -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core -lpthread -ldl #
CBLAS_OPT  = -DMKL_ILP64 -I${MKLROOT}/include #
MKL_SYS    = -DSYS=\"sys_mkl.h\"

all: projectile_tester projectile_tester_MKL projectile_tester_ATLAS  projectile_tester_tuned_LA projectile_tester_tuned_KAL
	./projectile_tester.out
	./mkl_projectile_tester.out
	./atlas_projectile_tester.out 
	./tuned_LA_projectile_tester.out
	./tuned_KAL_projectile_tester.out

projectile_tester: projectile_tester.cpp Target.o
	icc -c ../basic-c/linear_algebra.c ../basic-c/kalman_filter.c
	$(CC) projectile_tester.cpp Target.o $(KALMAN_FILES) -o projectile_tester.out
	./projectile_tester.out

projectile_tester_MKL: projectile_tester.cpp Target.o
	icc ../kalman-blas/kalman_filter.c -c $(MKL_SYS) $(CBLAS_LINK) $(CBLAS_OPT)
	$(CC) projectile_tester.cpp Target.o $(BLAS_KAL_FILES) -o mkl_projectile_tester.out $(CBLAS_LINK) $(CBLAS_OPT)
	./mkl_projectile_tester.out

projectile_tester_ATLAS: projectile_tester.cpp Target.o
	icc ../kalman-blas/kalman_filter.c -c $(ATLAS_SYS) $(ATLAS_LINK) $(ATLAS_INC)
	$(CC) projectile_tester.cpp Target.o $(BLAS_KAL_FILES) -o atlas_projectile_tester.out $(ATLAS_LINK) $(ATLAS_INC) 
	./atlas_projectile_tester.out

projectile_tester_tuned_LA: projectile_tester.cpp Target.o
	icc -c ../basic-c/kalman_filter.c
	$(CC) projectile_tester.cpp Target.o $(TUNED_LA_FILES) kalman_filter.o -o tuned_LA_projectile_tester.out 
	./tuned_LA_projectile_tester.out

projectile_tester_tuned_KAL: projectile_tester.cpp Target.o
	$(CC) projectile_tester.cpp Target.o $(TUNED_KAL_FILES) -o tuned_KAL_projectile_tester.out 
	./tuned_KAL_projectile_tester.out



gcc: gcc_projectile_tester gcc_projectile_tester_tuned_LA gcc_projectile_tester_tuned_KAL projectile_tester_BLAS
	./projectile_tester.out
	./blas_projectile_tester.out
	./tuned_LA_projectile_tester.out
	./tuned_KAL_projectile_tester.out

gcc_projectile_tester: projectile_tester.cpp gcc_Target.o
	gcc -c ../basic-c/linear_algebra.c ../basic-c/kalman_filter.c 
	g++ $(OCV_PATH) projectile_tester.cpp Target.o $(KALMAN_FILES) -o projectile_tester.out

gcc_projectile_tester_tuned_LA: projectile_tester.cpp gcc_Target.o
	gcc -c ../basic-c/kalman_filter.c
	g++ $(OCV_PATH) projectile_tester.cpp Target.o $(TUNED_LA_FILES) kalman_filter.o -o tuned_LA_projectile_tester.out

gcc_projectile_tester_tuned_KAL: projectile_tester.cpp gcc_Target.o
	g++ projectile_tester.cpp Target.o $(TUNED_KAL_FILES) -o tuned_KAL_projectile_tester.out 



projectile_tester_gdb: projectile_tester.cpp
	$(CC) $(OCV_PATH) projectile_tester.cpp $(KALMAN_FILES) -g -o projectile_tester.out $(OCV_LIBS)

Target.o: Target.cpp Target.hpp
	$(CC) Target.cpp -c

gcc_Target.o: Target.cpp Target.hpp
	g++ Target.cpp -c


econ_tester: econ_tester.cpp
	$(CC) $(OCV_PATH) econ_tester.cpp $(KALMAN_FILES) -o econ_tester.out $(OCV_LIBS)

econ_tester_gdb: econ_tester.cpp
	$(CC) $(OCV_PATH) econ_tester.cpp $(KALMAN_FILES) -g -o econ_tester.out $(OCV_LIBS)


clean:
	rm -f *.o
	rm -f *.out
