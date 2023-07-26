FLAGS = -Wall -Wextra -Werror -std=c99 -g

programa: test.o trie.o queue.o
	$(CC) -o $@ $^ $(FLAGS)

test.o: test.c trie.h queue.o
	$(CC) -c $< $(FLAGS)

trie.o: trie.c trie.h queue.o
	$(CC) -c $< $(FLAGS)

queue.o: queue.c queue.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa

.PHONY = clean