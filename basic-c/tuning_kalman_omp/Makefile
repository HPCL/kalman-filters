tuned_o: non_tuned.c
	icc -c non_tuned.c -fopenmp
	icc -O1 -c correct/_correct.c -fopenmp
	icc -O2 -c predict/_predict.c -fopenmp

untuned_o: non_tuned.c
	icc -c non_tuned.c
	icc -O1 -c correct/correct.c
	icc -O2 -c predict/predict.c


gcc_tuned_o: non_tuned.c
	gcc -c non_tuned.c
	gcc -O1 -c correct/_correct.c
	gcc -O2 -c predict/_predict.c

clean:
	rm -f *.json *.dot *.o *.log
	./rm_logs.sh

