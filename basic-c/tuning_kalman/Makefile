tuned_o: non_tuned.c
	icc -c non_tuned.c
	icc -O1 -c correct/_correct.c
	icc -O2 -c predict/_predict.c

untuned_o: non_tuned.c
	icc -c non_tuned.c
	icc -O1 -c correct/correct.c
	icc -O2 -c predict/predict.c


gcc_tuned_o: non_tuned.c
	gcc-4.9 -c non_tuned.c
	gcc-4.9 -O1 -c correct/_correct.c
	gcc-4.9 -O2 -c predict/_predict.c

clean:
	rm -f *.json *.dot *.o *.log
	./rm_logs.sh

