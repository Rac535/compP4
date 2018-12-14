
#include "scanner.h"
#include <stdlib.h>
#include "token.h"
#include "parser.h"


// A function that reads from the stream line by line
void test_scanner(istream  &infile, ofstream &outfile){
	/* create variables to store the line read, modified line, list of total tokens, list of tokens to be added to the total list,
	line count, and  if a comment has been encountered. (in respective order)
	*/

	string expression = "";
	string stripped_expression="";
    	vector<TokenType> tokens;
    	vector<TokenType> tokentemp;
	int linecount=0;
	int commentflag=1;
	
	//read from input stream line by line
	while(getline(infile, expression)) 
			 {
				 
				stripped_expression="";
				linecount++;
				/* getline strips the new line token from the string it reads. here we add it back
					so that it can be used by the FSA 
				*/
			 	expression+='\n';
				 
				/* Here we move through the line retrieved by getline and add each character to a string 
					variable called stripped string ONLY if it is not contained in a comment. We have 
					a flag called comment flag to track if we are in a comment state or not.
				*/
				
				 for(unsigned x = 0; x < expression.length();x++){
					 if(expression[x]=='$'){
						 commentflag= -commentflag;
					 }
					 if(commentflag>0){
						 stripped_expression+=expression[x];
					 }
				 }
				 
				//set expression to the stripped expression
				expression=stripped_expression;
			
				/* tokentemp recieves a vector of tokens from scanner for the line and we append 
					this vector to the vector called tokens to keep track of all tokens encountered 
					through the program.
				*/				
			   tokentemp = Scanner(expression,linecount);
			   tokens.insert( tokens.end(), tokentemp.begin(), tokentemp.end() );
				 
			}	
			/* The while loop will not execute if getline encounters an end of file character. Here
				we check for the end of file and pass it to scanner to create the appropriate token
			*/
			 if(infile.eof()){
					//if a comment has not been encountered by the end of the file, We produce and error message
				  if(commentflag<0){
					  cout<<"Error on line : "<<linecount<<" No closing comment";
					  exit(1);
				  }
				  expression=EOF;
				  tokentemp = Scanner(expression,linecount);
				  tokens.insert( tokens.end(), tokentemp.begin(), tokentemp.end() );
				  
			  }


	// display the tokens to the screen
	//cout<<"token size is "<<tokens.size();
	Node root;
    
    
    root=parser(&tokens,outfile);
    display(root,0);
    cout<<"\n \n";
   
    
    return;   
}
 
