
#include <stdlib.h>
#include <sstream>
#include "token.h"


 // stateTable is a 2 dimensional array that stores our representation of our finite state automata

 						//integer real operator string unknown space
	int stateTable[][11]=
	                    
	               /*   START,	        ALPHAUPPER,	    ALPHALOWER,     INTEGER,        UNDERSCORE     DELIMITER,  OPERATOR,   IDENTIFIER,  SPACE,    COMMENT,     EOF */
	   		
	/*START*/           {{ERROR,	    ERROR,          IDENTIFIER,	    INTEGER,        ERROR,         DEL_TKN,    OP_TKN,     ERROR,      START,    COMMENT,     EOF_TKN},
	
	/*IDENTIFIER*/		{ERROR,         IDENTIFIER,     IDENTIFIER,	    IDENTIFIER,     IDENTIFIER,    DELIMITER,  OPERATOR,    ERROR,     ID_TKN,   COMMENT,      ID_TKN},
	
	/*INTEGER*/	    	{ERROR,         ERROR,          ERROR,          INTEGER,        ERROR,         DELIMITER,  OPERATOR,    ERROR,     INT_TKN,  COMMENT,     ID_TKN},
    
    /*COMMENT*/	    	{ERROR,         COMMENT,        COMMENT,	    COMMENT,        COMMENT,       COMMENT,    COMMENT,    COMMENT,     COMMENT,  COMMENT_TKN, ERROR},					   
 	};

//------------------Helper Functions

//a function to determine the column of FSA table based on the current character encountered 

int Get_FSM_Col(char currChar){
	
	if(isspace(currChar)){
		return SPACE;
	}else if(isdigit(currChar)){
		return INTEGER;
	}else if((currChar== '.')||(currChar=='(')||(currChar==')')||(currChar=='{')||(currChar=='}')||(currChar==';')||(currChar=='[')||(currChar==']')    ){
		return DELIMITER;
	}else if(isupper(currChar)){
		return ALPHAUPPER;
	}else if(islower(currChar)){
		return ALPHALOWER;	
	}else if((currChar=='*')||(currChar=='+')||(currChar=='-')||(currChar=='/')||(currChar=='%')||(currChar==':')||(currChar=='<')||(currChar=='>')||(currChar=='=')){
		return OPERATOR;
	}else if(currChar=='_'){
		return UNDERSCORE;
	}else if(currChar=='$'){
		return COMMENT;
	}else if(currChar==EOF){
		return ENDFILE;
	}
	else{
		return START;
	}
}// end Get_FSM_Col

//a function to determine the row of FSA table based on the current character encountered 

int Get_FSM_Row(char currState){
	if(currState==IDENTIFIER){
		return 1;
	}else if(currState==INTEGER){
		return 2;
	}else if(currState==COMMENT){
		return 3;
	}else{
		return 0;
	}
}// end Get_FSM_Row



//a function to get translate the tokenID from an integer to an easily understood string.
// This function is useful for errors in which a token may not have been encountered

string GetStateName(int tokenID){
	switch(tokenID){
		case IDENTIFIER:
			return "IDENTIFIER";
			break;
		case INTEGER:
			return "INTEGER";
			break;
		case COMMENT:
			return "COMMENT";
			break;
		case START:
			return "START";
			break;
		case DEL_TKN:
			return "DEL_TKN";
			break;
		case EOF_TKN:
			return "EOF_TKN";
		case COMMENT_TKN: 
			return "COMMENT_TKN";
		default:
			return "ERROR";
			break;
	}
}

//a function to get translate the tokenID from an integer to an easily understood string for Tokens specifically.
// this is used to set the tokenInstance attribute of a token


string GetTokenName(int tokenID){
	switch(tokenID){
		case ID_TKN:
			return "ID_TKN";
			break;
		case INT_TKN:
			return "INT_TKN";
			break;
		case OP_TKN:
			return "OP_TKN";
			break;
		case SPACE:
			return "SPACE";
			break;
		case DEL_TKN:
			return "DEL_TKN";
			break;
		case EOF_TKN:
			return "EOF_TKN";
		case COMMENT_TKN: 
			return "COMMENT_TKN";
		default:
			return "ERROR";
			break;
	}
}



// a function that is responsible for the actual creation of a token

TokenType make_token(string currentToken,int currState, int line){
	TokenType access;
    access.token= currentToken;
	access.tokenID= currState;
	access.tokenInstance= GetTokenName(access.tokenID);
	access.line_num=line;  
	
	return access;
}


// a function to identify keyword tokens and modify their tokens to reflect their status
void keyword_filter(TokenType *token){
    if(token->token=="start"||token->token=="stop"||token->token=="loop"||token->token=="void"||token->token=="var"||
    token->token=="return"||token->token=="scan"||token->token=="out"||token->token=="program"||token->token=="if"||
    token->token=="then"||token->token=="let"){
        
        token->tokenID=KEYWORD; 
        token->tokenInstance="KEYWORD";
    }
  
    
}



//a function to specify delimiters. Not used at the moment but may be useful in future projects
void delimiter_filter(TokenType *token){
    if(token->token=="="||token->token=="<"||token->token==">"||token->token==":"||token->token=="+"||
    token->token=="-"||token->token=="*"||token->token=="/"||token->token=="%"||token->token=="."||
    token->token=="("||token->token==")"||token->token==","||token->token=="{"||token->token=="}"||
    token->token==";"||token->token=="["||token->token=="]"){
        
        //token->tokenID="KEYWORD"; 
        token->tokenInstance="DELIMITER";
    }
  
    
}


//--------------------------------------------------------------Scanner------------------------------------------------------------------
//Scanner function to create tokens
vector<TokenType> Scanner(string expression, int line)
{
    TokenType access;
    vector<TokenType> tokens;
    char currentChar = ' ';
    int col = START;
    int row = START;
	int lastrow = START;
    int currState = START;
    int prevState = START;
    std::string currentToken = "";
 
    // use an FSM to parse the expression
    for(unsigned x = 0; x < expression.length();)
    {
        currentChar = expression[x];
        col = Get_FSM_Col(currentChar);
		row = Get_FSM_Row(currState);
 
        /* ========================================================
 
            THIS IS WHERE WE CHECK THE FINITE STATE MACHINE TABLE
               USING THE "col" VARIABLE FROM ABOVE ^
 
          ========================================================= */
	
		 

        // get the current state of the expression
		
        currState = stateTable[row][col];
		/* cout<<endl<<" new State after the table look up is  " <<currState<<" the name is "<<GetStateName(currState)<<" the previous state is "<<prevState<<" named "<<GetStateName(prevState)<<
		" col is "<<col<<"the row is "<<row<<" on line: "<<line<<endl;
		*/
		
 
	//	cout<<endl<<"currState after "<<currState<<endl; 
        /* ===================================================
 
          THIS IS WHERE WE CHECK FOR A SUCESSFUL PARSE
 
            - ELSE we continue trying to find a sucessful token
 
            =================================================== */
		if(currState==ERROR){
			std::stringstream ss; 
			ss << line;
			currentToken="Error on line: "+ss.str()+" - "+GetStateName(prevState)+" state followed by input \'"+currentChar+"\' \n";
		
			access=make_token(currentToken,currState,line);	
			tokens.push_back(access);
			cout<<currentToken;
			currentToken="";
			currState=START;
			prevState=START;
			exit(1);
			x++;
		}else if(currState==ID_TKN){

				access=make_token(currentToken,currState,line);
				keyword_filter(&access);
				tokens.push_back(access);
			currentToken="";
			currState=START;
			prevState=START;
			++x;	
		}else if(currState==INT_TKN){

				access=access=make_token(currentToken,currState,line);
				tokens.push_back(access);
			currState=START;
			prevState=START;
			currentToken="";
			++x;
		}else if(currState==DELIMITER){
			//cout<<"\n"<<" delimiter : "<<currentChar;
			
				if(prevState!=START){
				//cout<<" delimiter hit prev state is "<<prevState<<" for "<<currentToken;
				/*
					cout<<" making the token for "<<currentToken;
					cout<<"/n the last row is "<<lastrow;
					cout<<"/n SPACE is "<<SPACE;
					cout<<"\n in the table [lastrow][space] is ", stateTable[row][SPACE];
					*/
					row=Get_FSM_Row(prevState);
					access=make_token(currentToken,stateTable[row][SPACE],line);
					keyword_filter(&access);
					tokens.push_back(access);
				}
			    currentToken=currentChar;
				access=make_token(currentToken,stateTable[START][currState],line);
				tokens.push_back(access);
			currentToken="";
			currState=START;
			prevState=START;
			++x;
		}else if(currState==OPERATOR){
			
				//cout<<" delimiter hit prev state is "<<prevState<<" for "<<currentToken;
				
					row=Get_FSM_Row(prevState);
					/*
					cout<<" making the token for "<<currentToken;
					cout<<"/n the row is "<<row;
					cout<<"/n SPACE is "<<SPACE;
					cout<<"\n in the table [row][space] is ", stateTable[row][SPACE];
					*/
					
					access=make_token(currentToken,stateTable[row][SPACE],line);
					keyword_filter(&access);
					tokens.push_back(access);
				
			    currentToken=currentChar;
				access=make_token(currentToken,stateTable[START][currState],line);
				tokens.push_back(access);
			currentToken="";
			currState=START;
			prevState=START;
			++x;
		
		}else if(currState==EOF_TKN){
			
				access=make_token("EOF",currState,line);
				tokens.push_back(access);
			currentToken="";
			currState=START;
			prevState=START;
			++x;
		}else if(currState==OP_TKN){
				currentToken+=currentChar;
				access=make_token(currentToken,currState,line);
				tokens.push_back(access);
			currentToken="";
			currState=START;
			++x;
		}else if(currState==DEL_TKN){
				currentToken+=currentChar;
				access=make_token(currentToken,currState,line);
				tokens.push_back(access);
			currentToken="";
			currState=START;
			++x;
		}else if(currState==COMMENT_TKN){

				access=make_token(currentToken,currState,line);
				tokens.push_back(access);

			currentToken="";
			currState=START;
			++x;
		}else if(currState==START){
			currentToken="";
			currState=START;
			access.line_num=0;
			x++;
		}else{
			if(!(isspace(currentChar))&&currState!=ERROR)
			currentToken+=currentChar;
			x++;
        }
	//store the previous state and last row for special case handling for delimiters and operators where two tokens
	// are required.
	
        prevState = currState;
		lastrow=row;

  	}
 
    // this ensures the last token gets saved when
    // we reach the end of the loop (if a valid token exists)
   //END OF FOR LOOP
    // ^^ we dont care about whitespace
    return tokens;
}// end of Scanner





