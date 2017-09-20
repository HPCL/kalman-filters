CC = g++ -std=c++11

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

TUNED_KAL_FILES  = ../basic-c/tuning_kalman/non_tuned.o 
TUNED_KAL_FILES += ../basic-c/tuning_kalman/_predict.o 
TUNED_KAL_FILES += ../basic-c/tuning_kalman/_correct.o 

TUNED_LA_FILES  = ../basic-c/tuning/non_tuned.o
TUNED_LA_FILES += ../basic-c/tuning/_add_mat.o
TUNED_LA_FILES += ../basic-c/tuning/_compute_LUP_inline.o
TUNED_LA_FILES += ../basic-c/tuning/_multiply_matrix.o
TUNED_LA_FILES += ../basic-c/tuning/_multiply_matrix_by_scalar.o
TUNED_LA_FILES += ../basic-c/tuning/_transpose_matrix.o


ATLAS_LINK = -L/usr/local/atlas/lib -lcblas -llapack -lptcblas -lpthread -latlas
ATLAS_INC  = -I/usr/local/atlas/include
ATLAS_SYS  = -DSYS=\"sys_atlas.h\"

CBLAS_LINK = -L/usr/lib/ -llapacke -lopenblas
CBLAS_SYS  = -DSYS=\"sys_cblas.h\"

TUNED_PATH  = -L../basic-c/tuning/
# TUNED_PATH += -L../basic-c/

all: projectile_tester projectile_tester_BLAS projectile_tester_ATLAS projectile_tester_tuned_LA projectile_tester_tuned_KAL
	./projectile_tester.out
	./blas_projectile_tester.out
	./atlas_projectile_tester.out
	./tuned_LA_projectile_tester.out
	./tuned_KAL_projectile_tester.out

projectile_tester: projectile_tester.cpp Target.o
	gcc -c ../basic-c/linear_algebra.c ../basic-c/kalman_filter.c
	$(CC) projectile_tester.cpp Target.o $(KALMAN_FILES) -o projectile_tester.out

projectile_tester_BLAS: projectile_tester.cpp Target.o
	gcc ../kalman-blas/kalman_filter.c -c $(CBLAS_SYS) $(CBLAS_LINK)
	$(CC) projectile_tester.cpp Target.o kalman_filter.o -o blas_projectile_tester.out $(CBLAS_LINK)

projectile_tester_ATLAS: projectile_tester.cpp Target.o
	gcc ../kalman-blas/kalman_filter.c -c $(ATLAS_SYS) $(ATLAS_LINK) $(ATLAS_INC)
	$(CC) projectile_tester.cpp Target.o kalman_filter.o -o atlas_projectile_tester.out $(ATLAS_LINK) $(ATLAS_INC)

projectile_tester_tuned_LA: projectile_tester.cpp Target.o
	gcc -c ../basic-c/kalman_filter.c
	$(CC) projectile_tester.cpp Target.o $(TUNED_LA_FILES) kalman_filter.o -o tuned_LA_projectile_tester.out 

projectile_tester_tuned_KAL: projectile_tester.cpp Target.o
	$(CC) projectile_tester.cpp Target.o $(TUNED_KAL_FILES) -o tuned_KAL_projectile_tester.out 

arya_projectile_tester: projectile_tester.cpp Target.o
	gcc -c ../basic-c/linear_algebra.c ../basic-c/kalman_filter.c 
	$(CC) $(OCV_PATH) projectile_tester.cpp Target.o $(KALMAN_FILES) -o projectile_tester.out $(OCV_LIBS)

arya_projectile_tester_tuned: projectile_tester.cpp Target.o
	gcc -c ../basic-c/kalman_filter.c
	$(CC) $(OCV_PATH) projectile_tester.cpp Target.o $(TUNED_LA_FILES) kalman_filter.o -o tuned_projectile_tester.out $(OCV_LIBS)

projectile_tester_gdb: projectile_tester.cpp
	$(CC) $(OCV_PATH) projectile_tester.cpp $(KALMAN_FILES) -g -o projectile_tester.out $(OCV_LIBS)

Target.o: Target.cpp Target.hpp
	$(CC) Target.cpp -c


econ_tester: econ_tester.cpp
	$(CC) $(OCV_PATH) econ_tester.cpp $(KALMAN_FILES) -o econ_tester.out $(OCV_LIBS)

econ_tester_gdb: econ_tester.cpp
	$(CC) $(OCV_PATH) econ_tester.cpp $(KALMAN_FILES) -g -o econ_tester.out $(OCV_LIBS)


clean:
	rm -f *.o
	rm -f *.out
