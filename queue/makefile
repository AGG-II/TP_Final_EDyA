FLAGS = -Wall -Wextra -Werror -std=c99 -g

test: test_queue.o queue.o
	$(CC) -o $@ $^ $(FLAGS)

test_queue.o: test_queue.c test_queue.h queue.o
	$(CC) -c $< $(FLAGS)

queue.o: queue.c queue.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm test
	
.PHONY = clean