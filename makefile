compile: run.c
	gcc run.c run.h

run: a.out
	./a.out

clean:
	rm a.out
	rm *~
