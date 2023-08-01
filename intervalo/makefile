FLAGS = -Wall -Wextra -Werror -std=c99 -g

test_intervalo: test_intervalo.o intervalo.o
	$(CC) -o $@ $^ $(FLAGS)

test_intervalo.o: test_intervalo.c test_intervalo.h intervalo.o
	$(CC) -c $< $(FLAGS)

intervalo.o: intervalo.c intervalo.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm test_intervalo
	
.PHONY = clean