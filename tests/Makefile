FLAGS = -pthread -g
S = -fsanitize=address #-fno-omit-frame-pointer
T = -fsanitize=thread 
END = echo "let's see --> \n" && ./test

all:
	rm test
#	@./test
#	gcc -g -pthread -fsanitize=thread -g t1.c -o test

ll:
	valgrind --tool=helgrind ./test

1:
	gcc $(FLAGS) t1.c -o test && echo "let's see --> \n" && ./test

2:
	gcc $(FLAGS) t2.c -o test && $(END)

3:
	gcc $(FLAGS) t3.c -o test && $(END)

4:
	gcc $(FLAGS) t4.c -o test && $(END)

5:
	gcc $(FLAGS) t5.c -o test && $(END)

t:
	gcc $(FLAGS) time.c -o test && $(END)

y1:
	gcc $(FLAGS) main1.c -o test && $(END)

y2:
	gcc $(FLAGS) main2.c -o test && $(END)

y3:
	gcc $(FLAGS) $(S) main2test.c -o test && $(END)

y4:
	gcc $(FLAGS) main--2.c -o test && $(END)

pp:
	gcc $(FLAGS) p2rimes.c -o test && $(END)

ff:
	gcc $(FLAGS) cond_pth.c -o test && $(END)

bb:
	gcc $(FLAGS) brad_thr.c -o test && $(END)