myprog.exe:	main.o squared.o squareRoot.o
	g++ main.o squared.o squareRoot.o -o myprog.exe	

main.o:	main.cc squared.h squareRoot.h
	g++ -c main.cc

squared.o:	squared.cc squared.h
	g++ -c squared.cc

squareRoot.o:	squareRoot.cc squareRoot.h
	g++ -c squareRoot.cc
clean:
	rm *.o myprog.exe 

