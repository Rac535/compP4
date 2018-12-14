

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

typedef struct TokenType
{
    string token;
    int tokenID;
    string tokenInstance;
	int line_num;
}TokenType;


   	enum FSM_STATES{
		START=0,
		ALPHAUPPER=1,
		ALPHALOWER=2,
		INTEGER=3, 
		UNDERSCORE=4,
		DELIMITER=5,
		OPERATOR=6,
		IDENTIFIER=7, 
		SPACE=8, 
		COMMENT=9,
		ENDFILE=10
	};

	
    
	enum FINAL_STATES{
		ERROR=-1,
		ID_TKN=1001,
		INT_TKN=1002,
		OP_TKN=1003,
		DEL_TKN=1004,
		COMMENT_TKN=1005,
		EOF_TKN=1006,
		KEYWORD=1007
		
	};
	
#endif