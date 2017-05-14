CC = g++

ALL_LIBS  = -lopencv_imgproc # 
ALL_LIBS += -lopencv_highgui # I think this one lets us get keyboard input
ALL_LIBS += -lopencv_objdetect #
ALL_LIBS += -lopencv_core -lopencv_videoio # basic opencv
ALL_LIBS += -lopencv_video # background subtractor MOG2
ALL_LIBS += -lopencv_imgcodecs #
#ALL_LIBS += -lraspicam -lraspicam_cv # to live stream with raspicam not on arya

#OCV_PATH  = -I/usr/include/ # on pi
OCV_PATH  = -L/usr/local/packages/opencv/lib # on arya 
OCV_PATH += -I/usr/local/packages/opencv/include # on arya

KALMAN_FILES  = ../basic-c/linear_algebra.c # 
KALMAN_FILES += ../basic-c/kalman_filter.c # 

projectile_tester: projectile_tester.cpp
		$(CC) $(OCV_PATH) projectile_tester.cpp $(KALMAN_FILES) -o projectile_tester.out $(ALL_LIBS)

projectile_tester_gdb: projectile_tester.cpp
		$(CC) $(OCV_PATH) projectile_tester.cpp $(KALMAN_FILES) -g -o projectile_tester.out $(ALL_LIBS)


clean:
	rm *.o
	rm *.out