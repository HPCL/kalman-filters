CC = g++

ALL_LIBS  = -lopencv_imgproc # 
ALL_LIBS += -lopencv_highgui # I think this one lets us get keyboard input
ALL_LIBS += -lopencv_objdetect #
ALL_LIBS += -lopencv_core -lopencv_videoio # basic opencv
ALL_LIBS += -lopencv_video # background subtractor MOG2
ALL_LIBS += -lopencv_imgcodecs #
#ALL_LIBS += -lraspicam -lraspicam_cv # to live stream with raspicam not on arya

#OCV_PATH  = -I/usr/include/ # on pi
OCV_PATH  = -L/usr/local/packages/opencv/lib # on arya / sansa?
CUDA_PATH = -L/usr/local/cuda-8.0/lib64 # on sansa?
OCV_PATH += -I/usr/local/packages/opencv/include # on arya

KALMAN_FILES  = ../basic-c/linear_algebra.c # 
KALMAN_FILES += ../basic-c/kalman_filter.c # 

KALMAN_FILES_TUNED  = ../basic-c/tuning/tuned_linear_algebra.c # 
KALMAN_FILES_TUNED += ../basic-c/kalman_filter.c # TODO



projectile_tester: projectile_tester.cpp
		$(CC) $(OCV_PATH) $(CUDA_PATH) projectile_tester.cpp $(KALMAN_FILES) -o projectile_tester.out $(ALL_LIBS)

projectile_tester_tuned: projectile_tester.cpp
		$(CC) $(OCV_PATH) $(CUDA_PATH) projectile_tester.cpp $(KALMAN_FILES_TUNED) -o projectile_tuned_tester.out $(ALL_LIBS)

projectile_tester_gdb: projectile_tester.cpp
		$(CC) $(OCV_PATH) projectile_tester.cpp $(KALMAN_FILES) -g -o projectile_tester.out $(ALL_LIBS)


econ_tester: econ_tester.cpp
		$(CC) $(OCV_PATH) econ_tester.cpp $(KALMAN_FILES) -o econ_tester.out $(ALL_LIBS)

econ_tester_gdb: econ_tester.cpp
		$(CC) $(OCV_PATH) econ_tester.cpp $(KALMAN_FILES) -g -o econ_tester.out $(ALL_LIBS)


clean:
	rm *.o
	rm *.out