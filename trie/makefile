FLAGS = -Wall -Wextra -Werror -std=c99 -g

test_trie: test_trie.o trie.o queue.o
	$(CC) -o $@ $^ $(FLAGS)

test_trie.o: test_trie.c test_trie.h trie.h
	$(CC) -c $< $(FLAGS)

trie.o: trie.c trie.h ../queue/queue.h
	$(CC) -c $< $(FLAGS)

queue.o: ../queue/queue.c ../queue/queue.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm test_trie

.PHONY = clean