FLAGS = -Wall -Wextra -Werror -std=c99 -g

programa: test.o parser.o trie.o queue.o slist.o intervalo.o
	$(CC) -o $@ $^ $(FLAGS)

test.o: test.c parser.o queue.o trie.o
	$(CC) -c $< $(FLAGS)

parser.o: parser/parser.c parser/parser.h trie.o slist.o queue.o intervalo.o
	$(CC) -c $< $(FLAGS)

trie.o: trie/trie.c trie/trie.h queue.o
	$(CC) -c $< $(FLAGS)

queue.o: queue/queue.c queue/queue.h
	$(CC) -c $< $(FLAGS)

slist.o: slist/slist.c slist/slist.h
	$(CC) -c $< $(FLAGS)

intervalo.o: intervalo/intervalo.c intervalo/intervalo.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa
	rm ahora_si.txt

.PHONY = clean