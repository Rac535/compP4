#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include "token.h"
#include <algorithm>

using namespace std;

typedef struct Node{
    string label;
    vector<Node> children; 
	vector<string> tokens;
	vector<string> local_stack;
	vector<TokenType> tokenstash;
	
	vector<string> vars;
	vector<bool> setflags;
	vector<int> val;
    
}Node;



Node parser(std::vector<TokenType>*,std::ofstream&);
Node program (std::vector<TokenType>*,std::ofstream&);
Node block(std::vector<TokenType>*, std::vector<string>*,std::ofstream&, std::vector<string>*);
Node vars(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node expr(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node A(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node M(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node R(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node stats(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node mStat(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node stat(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node IF(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node in(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node out(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node loop(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node assign(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
Node RO(std::vector<TokenType>*, std::vector<string>*, std::vector<string>*, int*,std::ofstream&, std::vector<string>*);
void display(Node, int);

#endif