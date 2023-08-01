FLAGS = -Wall -Wextra -Werror -std=c99 -g

test_parser: test_parser.o parser.o trie.o queue.o slist.o intervalo.o
	$(CC) -o $@ $^ $(FLAGS)

test_parser.o: test_parser.c test_parser.h parser.h
	$(CC) -c $< $(FLAGS)

parser.o: parser.c parser.h ../queue/queue.h ../trie/trie.h ../intervalo/intervalo.h
	$(CC) -c $< $(FLAGS)

trie.o: ../trie/trie.c ../trie/trie.h ../queue/queue.h
	$(CC) -c $< $(FLAGS)

queue.o: ../queue/queue.c ../queue/queue.h
	$(CC) -c $< $(FLAGS)

slist.o: ../slist/slist.c ../slist/slist.h
	$(CC) -c $< $(FLAGS)

intervalo.o: ../intervalo/intervalo.c ../intervalo/intervalo.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm test_parser
	rm ../ejemplos/resultado_correccion.txt
.PHONY = clean