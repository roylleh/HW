all: hello library


main.o: main.c bar.h
	clang -c -Wall main.c


bar.o: bar.c
	clang -c -Wall bar.c


hello: main.o bar.o
	clang -Wall main.o bar.o -o hello


math_lib.o: math_lib.c
	clang -c -Wall math_lib.c


libmath.a: math_lib.o
	ar rc libmath.a math_lib.o


useLib.o: useLib.c mathlib.h
	clang -c -Wall useLib.c


library: useLib.o libmath.a
	clang -L. -Wall useLib.o -lmath -o library


clean:
	rm -rf hello library *.o
