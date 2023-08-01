FLAGS = -Wall -Wextra -Werror -std=c99 -g

main: main.o parser.o trie.o queue.o slist.o intervalo.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c parser/parser.h
	$(CC) -c $< $(FLAGS)

parser.o: parser/parser.c parser/parser.h queue/queue.h trie/trie.h intervalo/intervalo.h
	$(CC) -c $< $(FLAGS)

trie.o: trie/trie.c trie/trie.h queue/queue.h
	$(CC) -c $< $(FLAGS)

queue.o: queue/queue.c queue/queue.h
	$(CC) -c $< $(FLAGS)

slist.o: slist/slist.c slist/slist.h
	$(CC) -c $< $(FLAGS)

intervalo.o: intervalo/intervalo.c intervalo/intervalo.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm main
.PHONY = clean