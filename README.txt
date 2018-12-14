README.txt

*P3 implements a **LOCAL** scope 

----------------------
Command Line Arguments
----------------------

Example:  	./P1 test
		./P1<test.fs182
		./P1 empty
		./P1<empty.fs182

~File Extension
	P1 implicitly adds the extension .fs182 to files passed as arguments, 
therefore when calling P1 with the file as an argument the extension 
should be omitted.

	P1 can also recieve information via file redirection. In the case of 
redirection the environment handles the extension so it is neccessary
to include the file extension in the name.

~empty file
	P1 will create the expected EndOfFile token when passed an empty argument.

~file does not exist
	P1 will display an error if the file path is incorrect or if the file does not exist.


-------------------------
Design 
-------------------------

*P3 implements a **LOCAL** scope 


   
