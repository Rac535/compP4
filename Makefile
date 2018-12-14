
#CFLAGS is an environmental variable
#Wall shows warnings and -g is enabled for debugging
#*****************



CC=g++
CFLAGS=-I.

P3 : scanner.o test_scanner.o main.o parser.o
	$(CC) -o  P3	main.o scanner.o test_scanner.o parser.o
	

main.o : test_scanner.o scanner.o  scanner.h test_scanner.h
	$(CC) -c main.cpp test_scanner.cpp scanner.cpp 
		
test_scanner.o : test_scanner.cpp scanner.cpp scanner.h test_scanner.h token.h
	$(CC) -c test_scanner.cpp scanner.cpp
	
parser.o : parser.cpp
	$(CC) -c parser.cpp
	$(CC) -c parser.h 
	
scanner.o : scanner.cpp 
	$(CC) -c scanner.cpp
	$(CC) -c scanner.cpp
	$(CC) -c scanner.cpp
	
		
				
		




#-----------------------------------------
#clean is a rule that removes listed files
#***************


clean:
	rm P2
	rm main.o
	rm test_scanner.o
	rm scanner.o
	rm parser.o
	
	rm test.inorder
	rm test.preorder
	rm test.postorder
	rm out.inorder
	rm out.preorder
	rm out.postorder

	
