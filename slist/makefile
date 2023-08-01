FLAGS = -Wall -Wextra -Werror -std=c99 -g

test_slist: test_slist.o slist.o
	$(CC) -o $@ $^ $(FLAGS)

test_slist.o: test_slist.c test_slist.h slist.o
	$(CC) -c $< $(FLAGS)

slist.o: slist.c slist.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm test_slist

.PHONY = clean