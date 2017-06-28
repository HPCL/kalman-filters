tuned_o: non_tuned.c
	gcc -c non_tuned.c
	gcc -O1 -c correct/_correct.c
	gcc -O2 -c predict/_predict.c

clean:
	rm -f *.json *.dot *.o *.log
	./rm_logs.sh

