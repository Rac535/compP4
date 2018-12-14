#ifndef SCANNER_H
#define SCANNER_H


#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "token.h"

extern int stateTable[][11];

int Get_FSM_Col(char);


int Get_FSM_Row(char);


string GetStateName(int );


string GetTokenName(int );


TokenType make_token(string,int, int);


void keyword_filter(TokenType *); 


void delimiter_filter(TokenType *);
  

vector<TokenType> Scanner(string, int);

#endif

