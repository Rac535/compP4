/*****************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

******************************************************************************/




#include <vector>
#include <iostream>
#include "parser.h"
#include "token.h"
#include <stdio.h>  
#include <fstream>
#include <istream>
#include <string>
#include <stdlib.h>
#include <algorithm>

using namespace std;



/*
Node parser ();
Node program ();
Node block(tokens);
Node node.children.push_back(vars(tokens));
Node expr(tokens);
Node A();
Node M();
Node R();
Node     node.children.push_back(stats(tokens));
Node mStat(tokens);
Node stat(tokens);
Node IF(tokens);
Node in(tokens);
Node out(tokens);
Node loop(tokens);
Node assign(tokens);
Node RO(tokens);
void display(Node);
*/
/*
int main()
{

    Node root;
    
    //cout<<"Hello World";
    root=parser();
    display(root);

    return 0;
}
*/








//__________________________________________________________________________________________________________________________

void error(string nodelabel,string token){
	cout<<" error in <"<<nodelabel<<">: "<<nodelabel<<" was followed by "<<token<<"\n";
	exit(1);
	return;
}


static int LabelCntr=0;                                     // for unique labels //
static int VarCntr=0;                                    // for unique variables //
typedef enum {VAR, LABEL} nameType;
static char Name[20];                        // for creation of unique names //

static char *newName(nameType what)
{ if (what==VAR)
    sprintf(Name,"V%d",VarCntr++);    // generate a new label as V0, V1, etc //
  else
    sprintf(Name,"L%d",LabelCntr++);            // new lables as L0, L1, etc //
  return(Name);
}

char label[20], label2[20], argR[20];

string branch="";
//__________________________________________________________________________________________________________________________








int finder(vector<string> vector,string var){
    int n = -2;
    for(int i = 0; i<vector.size();i++){
        if(vector[i]==var){
            n=i;
        }
    }
    return n;
}





int string_to_int(string str){
    int integer=0;
    int factor;
    int value;
    
    for(int i=0;i<str.length()-1;i++){
        factor=(i+1)*10;
        //cout<<" the factor"<<factor;
        value=(int(str[i])-'0');
        //cout<<"\n the value "<<value;
        integer+= factor*value;
    }
    
   // cout<<" \n integer "<<integer<<"\n ";
    return integer;   
}






Node parser (std::vector<TokenType> *tokens, std::ofstream &outfile){
	
	
    Node node;
    node.label="parser";
    //tk=dummy;
    node.children.push_back(program(tokens,outfile));
    
    if ((*tokens)[0].token!="EOF"){
        error(" parser. Last token ",(*tokens)[0].token);
    }else{
	
        return node;
    }  
    
    return node;
}



Node program(std::vector<TokenType> *tokens, std::ofstream &outfile){
    Node node;
    node.label="program";
	int count=0;
	std::vector<string> dummy;
	
	std::vector<string> varnames;
	
    
    
  if((*tokens)[0].token=="void"){
	 node.tokens.push_back((*tokens)[0].token);

    (*tokens).assign((*tokens).begin()+1, (*tokens).end());

    node.children.push_back(vars(tokens,&node.local_stack,&dummy,&count,outfile,&varnames));
	//outfile<<"\n back in program ";
	//cout<<" count in program is "<<count;
    node.children.push_back(block(tokens,&node.local_stack,outfile,&varnames));
	//outfile<<"\n back in program ";
	
			for(int i=0;i<count;i++){
				(node.local_stack).pop_back();
				outfile<<"\nPOP";
			}
			
    }else error(node.label,(*tokens)[0].token);
	
	outfile<<"\nSTOP";
	
	for(int i=0;i<varnames.size();i++){
			outfile<<"\n"<<varnames[i]<<"\t"<<0;
	}
	outfile<<"\nX0\t0";
		
	outfile<<"\n";
	outfile<<"\n";
	outfile<<"\n";


    
    
 return node;   
}



// ***  ASM Should be Good


Node block(std::vector<TokenType> *tokens, std::vector<string> *global_stack, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="block";
	int count=0;
    
    if((*tokens)[0].token=="start"){
        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
		
        node.children.push_back(vars(tokens,&node.local_stack,global_stack,&count,outfile,varnames));
			
        node.children.push_back(stats(tokens,&node.local_stack,global_stack,&count,outfile, varnames));

        if((*tokens)[0].token=="stop"){
			
			(*tokens).assign((*tokens).begin()+1, (*tokens).end());
	
			
			for(int i=0;i<count;i++){
				(*global_stack).pop_back();
				outfile<<"\nPOP";
			}
			
		/*	
			outfile<<"\n the global_stack after removal is : \n";
		for(int i=0; i<(*global_stack).size();i++){
			cout<<" "<<(*global_stack)[i]<<" ";
		} 
		*/

            return node;
        }else error(node.label,(*tokens)[0].token);
        
    }else error(node.label,(*tokens)[0].token);
    
    
  return node;  
}





//ASM needs to be checked

Node vars(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="vars";
		//check for var keyword
	    if((*tokens)[0].token=="var"){
		//consume token
		node.tokens.push_back((*tokens)[0].token);

       (*tokens).assign((*tokens).begin()+1, (*tokens).end());
	   //check for ID_TKN
		    if((*tokens)[0].tokenID==ID_TKN){ 
				node.tokens.push_back((*tokens)[0].token);
				node.vars.push_back((*tokens)[0].token);
				node.setflags.push_back(0);


				int n = finder((*local_stack),(*tokens)[0].token);
				//here need to check if it is defined in the var vector
				if(n>0){
						cout<<"\n on line "<<(*tokens)[0].line_num<<": variable "<<(*tokens)[0].token<< " is already declared in this scope \n";	
						exit(1);
				} else {
					(*local_stack).push_back((*tokens)[0].token);
					(*global_stack).push_back((*tokens)[0].token);
					(*count)++;
					
				}
				

				


				(*tokens).assign((*tokens).begin()+1, (*tokens).end());
				
				if((*tokens)[0].token==":"){  
					node.tokens.push_back((*tokens)[0].token);
					

					(*tokens).assign((*tokens).begin()+1, (*tokens).end());
				    if((*tokens)[0].tokenID==INT_TKN){
						node.tokens.push_back((*tokens)[0].token);
						node.val.push_back(int(  (*tokens)[0].token[0]-'0'  )  );
						node.setflags[node.setflags.size()-1]=0;
						outfile<<"\nLOAD\t";
						for(int i=0;i<((*tokens)[0].token.size());i++){
							if(isdigit((*tokens)[0].token[0])){
								outfile<<int((*tokens)[0].token[0]-'0');
							}
						}
						outfile<<"\nPUSH";
						outfile<<"\nSTACKW\t"<<0;

						(*tokens).assign((*tokens).begin()+1, (*tokens).end());
						node.children.push_back(vars(tokens,local_stack,global_stack,count,outfile,varnames));
						
						return node;
						
					}else error(node.label,(*tokens)[0].token);
					
				}else error(node.label,(*tokens)[0].token);
				
			}else error(node.label,(*tokens)[0].token);
           
		}else return node;
		
}





// ***  ASM Should be Good

Node expr(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="expr";
	string sign="/";
    node.children.push_back(A(tokens,local_stack,global_stack,count,outfile,varnames));
	
	
    if((*tokens)[0].token=="/"||(*tokens)[0].token=="*"){
		
		if((*tokens)[0].token=="/"){
			sign="/";
		}else{
		    sign="*";
		}
		
		node.tokens.push_back((*tokens)[0].token);
		
		strcpy(argR,newName(VAR)); //create a temporary variable 
		outfile<<"\nSTORE\t"<<argR;
		string temp=argR;
		(*varnames).push_back(temp);
		
		

        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));
		
		
		if(sign=="/"){
		outfile<<" \nSTORE\tX0";
		outfile<<" \nLOAD\t"<<temp;
		outfile<<"\nDIV\tX0";
		}else{
			outfile<<"\nMULT\t"<<temp;
		}
        return node;
    }
    
	return node;
}





// ***  ASM Should be Good

Node A(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="A";

    node.children.push_back(M(tokens,local_stack,global_stack,count,outfile,varnames));
   
	
    if((*tokens)[0].token=="+"||(*tokens)[0].token=="-"){
	string sign=(*tokens)[0].token;
	strcpy(argR,newName(VAR)); //create a temporary variable 
	outfile<<"\nSTORE\t"<<argR;
	string temp=argR;
	(*varnames).push_back(temp);
		node.tokens.push_back((*tokens)[0].token);
	
        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
		node.children.push_back(A(tokens,local_stack,global_stack,count,outfile,varnames));
		
		
		if(sign=="+"){
			outfile<<"\nADD\t"<<temp;
		}else{
			outfile<<"\nSUB\t"<<temp;
			outfile<<"\nMULT\t"<<"-1";
		}
		
        return node;
		
		
    }else return node;
    
  
}





// ***  ASM Should be Good


Node M(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="M";

    
    if((*tokens)[0].token=="-"){
		node.tokens.push_back((*tokens)[0].token);
		

        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
		node.children.push_back(M(tokens,local_stack,global_stack,count,outfile,varnames));
		outfile<<"\nMULT\t -1";

    }else{
		node.children.push_back(R(tokens,local_stack,global_stack,count,outfile,varnames));

    }
    
   return node; 
}




// Needs ASM checked
Node R(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="R";
	int n;
    
    

 
    if((*tokens)[0].token=="("){
        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));

        if((*tokens)[0].token==")"){
            return node;
        }else error(node.label,(*tokens)[0].token);
        
    }else if((*tokens)[0].tokenID==ID_TKN||(*tokens)[0].tokenID==INT_TKN){
		node.tokenstash.push_back((*tokens)[0]);

		if((*tokens)[0].tokenID==ID_TKN){
			
				if(std::find((*local_stack).begin(), (*local_stack).end(), (*tokens)[0].token) != (*local_stack).end()) {
						//outfile<<"\n  variable "<<(*tokens)[0].token<< " is indeed declared in this scope \n";	
				} else if(std::find((*global_stack).begin(), (*global_stack).end(), (*tokens)[0].token) != (*global_stack).end()) {
						//outfile<<"\n variable "<<(*tokens)[0].token<< " is indeed declared in the global scope \n";	
						
				} else {
						cout<<"\t\n on line "<<(*tokens)[0].line_num<<": variable "<<(*tokens)[0].token<< " is not declared in this scope \n";	
						exit(1);
				}

			int n = finder((*global_stack),(*tokens)[0].token);
			
			outfile<<"\nSTACKR\t"<<(*global_stack).size()-(n+1);		

		}else if((*tokens)[0].tokenID==INT_TKN){
			int n = finder((*local_stack),(*tokens)[0].token);
			outfile<<"\nLOAD\t";
				ACC=int((*tokens)[0].token[0]-'0');
				for(int i=0;i<((*tokens)[0].token.size());i++){
					outfile<<int((*tokens)[0].token[0]-'0');
				}
			
			
		}
		
		node.tokens.push_back((*tokens)[0].token);
		
		// check this line below vvv
			
		
        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        return node;
    }else error(node.label,(*tokens)[0].token);
    
   return node; 
}




// ***  ASM Should be Good

Node stats(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="stats";
	
    node.children.push_back(stat(tokens,local_stack,global_stack,count,outfile,varnames));
    node.children.push_back(mStat(tokens,local_stack,global_stack,count,outfile,varnames));

   return node; 
}




// ***  ASM Should be Good

Node mStat(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="mStat";
    //cout<<\t"\n in mStat ";
    //node.children.push_back(stat(tokens,local_stack,global_stack,count,outfile,varnames));
    //mStat(tokens,local_stack,global_stack,count,outfile,varnames);

	//cout<<" in mStat before diving into stats"<<(*tokens)[0].token;
    //how do you handle empty?
    if((*tokens)[0].token=="scan"){
		
        node.children.push_back(stat(tokens,local_stack,global_stack,count,outfile,varnames));

        node.children.push_back(mStat(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="out"){
		node.children.push_back(stat(tokens,local_stack,global_stack,count,outfile,varnames));

        node.children.push_back(mStat(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="start"){
        node.children.push_back(stat(tokens,local_stack,global_stack,count,outfile,varnames));


        node.children.push_back(mStat(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="if"){
        node.children.push_back(stat(tokens,local_stack,global_stack,count,outfile,varnames));

        node.children.push_back(mStat(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="loop"){
        node.children.push_back(stat(tokens,local_stack,global_stack,count,outfile,varnames));

        node.children.push_back(mStat(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="let"){
        node.children.push_back(stat(tokens,local_stack,global_stack,count,outfile,varnames));

        node.children.push_back(mStat(tokens,local_stack,global_stack,count,outfile,varnames));

    } 
    //cout<<"leaving mStat";
	return node;
}





// ***  ASM Should be Good

Node stat(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="stat";
    //node.children.push_back(in(tokens,local_stack,global_stack,count,outfile,varnames));
    //node.children.push_back(out(tokens,local_stack,global_stack,count,outfile,varnames));
		//cout<<"\t\n ******in stat "<<(*tokens)[0].token<<"\n";

 
    if((*tokens)[0].token=="scan"){
		node.children.push_back(in(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="out"){
        node.children.push_back(out(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="start"){
        node.children.push_back(block(tokens, global_stack,outfile,varnames));

    }else if((*tokens)[0].token=="if"){
        node.children.push_back(IF(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="loop"){
        node.children.push_back(loop(tokens,local_stack,global_stack,count,outfile,varnames));

    }else if((*tokens)[0].token=="let"){
        node.children.push_back(assign(tokens,local_stack,global_stack,count,outfile,varnames));

    }else error(node.label,(*tokens)[0].token);
      
   return node; 
}




// Needs ASM checked


Node in(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="in";
	int n=-2;
    //cout<<"\t\n in \"in\" ";

	//cout<<"top of stack is "<<(*tokens)[0].token<<"\n";
    if((*tokens)[0].token=="scan"){
		node.tokens.push_back((*tokens)[0].token);

        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
		
        if((*tokens)[0].tokenID==ID_TKN){
			
			n=finder((*global_stack),(*tokens)[0].token);
			
			if((n=finder((*local_stack),(*tokens)[0].token))<0) {	
						
				if((n=finder((*global_stack),(*tokens)[0].token))<0) {
						
						cout<<"\t\n variable "<<(*tokens)[0].token<< " is not declared in this scope \n";	
						exit(1);
				}
			}	
			node.tokens.push_back((*tokens)[0].token);
			
			
			n=finder((*global_stack),(*tokens)[0].token);
			strcpy(argR,newName(VAR)); //create a temporary variable 
			string temp=argR;
			(*varnames).push_back(temp);
			
			outfile<<"\nREAD\t"<<argR;
			outfile<<"\nLOAD\t"<<argR;
			
			if(n<0){
				outfile<<"\nPUSH\t";
				n=(*global_stack).size()-1;
			}
			outfile<<"\nSTACKW\t"<<(*global_stack).size()-(n+1);
			
            (*tokens).assign((*tokens).begin()+1, (*tokens).end());			
			
			if((*tokens)[0].token=="."){
					node.tokens.push_back((*tokens)[0].token);

		            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
			}else error(node.label,(*tokens)[0].token);
        }else error(node.label,(*tokens)[0].token);
    }else error(node.label,(*tokens)[0].token);
    
    return node;
}




// ***  ASM Should be Good


Node out(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="out";
    //outfile<<"\n in out ";
    //node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));

 
 if((*tokens)[0].token=="out"){
        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        if((*tokens)[0].token=="["){
            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
            node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));
				
            if((*tokens)[0].token=="]"){
				(*tokens).assign((*tokens).begin()+1, (*tokens).end());
				if((*tokens)[0].token=="."){
		            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
					strcpy(argR,newName(VAR)); //create a temporary variable 
					string temp=argR;
					(*varnames).push_back(temp);
					outfile<<"\nSTORE\t"<<argR;
					outfile<<"\nWRITE\t"<<argR;
				}else error(node.label,(*tokens)[0].token);
            }else error(node.label,(*tokens)[0].token);
        }else error(node.label,(*tokens)[0].token);
    }else error(node.label,(*tokens)[0].token);
    
   return node; 
}





// ASM should be Good


Node IF(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="if";
    //outfile<<"\n in if ";
    strcpy(label,newName(LABEL));
	string IF=label;
 
 if((*tokens)[0].token=="if"){
        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
		
        if((*tokens)[0].token=="("){
			
            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
            node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));
			
			strcpy(argR,newName(VAR));
			// check below!!!
			node.children.push_back(RO(tokens,local_stack,global_stack,count,outfile,varnames));
			string temp=argR;
			(*varnames).push_back(temp);
			
			outfile<<"\n STORE\t"<<argR;
		
			node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));
			outfile<<"\n SUB\t"<<temp;
			outfile<<"\n "<<branch;
			

            if((*tokens)[0].token==")"){
                (*tokens).assign((*tokens).begin()+1, (*tokens).end());
                stat(tokens,local_stack,global_stack,count,outfile,varnames);
				outfile<<"\n "<<IF<<":\tNOOP";
            }else error(node.label,(*tokens)[0].token);
			
        }else error(node.label,(*tokens)[0].token);
		
    }else error(node.label,(*tokens)[0].token);
    
   return node; 
}







// Needs ASM checked

Node loop(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="loop";
	//outfile<<"\n  ";
	
	strcpy(label,newName(LABEL));
	string loop=label;
	strcpy(label,newName(LABEL));
	string loop2=label;
	outfile<<"\n"<<loop<<": NOOP\n";
	
	if((*tokens)[0].token=="loop"){
        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        if((*tokens)[0].token=="("){
            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
			
            node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));
			strcpy(argR,newName(VAR)); //create a temporary variable 
			outfile<<"\nSTORE\t"<<argR;
			string temp=argR;
			(*varnames).push_back(temp);
			
			
			// check below!!!

			node.children.push_back(RO(tokens,local_stack,global_stack,count,outfile,varnames));
						//outfile<<"\n back ";

			node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));
			outfile<<"\nSUB\t"<<temp;
			outfile<<"\n"<<branch;

            if((*tokens)[0].token==")"){
                (*tokens).assign((*tokens).begin()+1, (*tokens).end());
                stat(tokens,local_stack,global_stack,count,outfile,varnames);
				
				// check below!!!
				outfile<<"\nBR\t"<<loop;
				outfile<<"\n  "<<loop2<<":  NOOP\n";
				
            }else error(node.label,(*tokens)[0].token);
        }else error(node.label,(*tokens)[0].token);
    }else error(node.label,(*tokens)[0].token);
    
   return node; 
}



//need to update ASM
Node assign(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="assign";
	int n;
    //outfile<<"\n assign ";
    //node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));
  
	//outfile<<"\n ******in assign\n";
	
	
    if((*tokens)[0].token=="let"){
		node.tokens.push_back((*tokens)[0].token);

        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        if((*tokens)[0].tokenID==ID_TKN){
			node.tokens.push_back((*tokens)[0].token);
			//write to stack
				//cout<<"\n the token is "<<(*tokens)[0].token<<"\n";
				n = finder((*global_stack),(*tokens)[0].token);		
				

            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
            if((*tokens)[0].token=="="){
				
				node.tokens.push_back((*tokens)[0].token);
				(*tokens).assign((*tokens).begin()+1, (*tokens).end());

                node.children.push_back(expr(tokens,local_stack,global_stack,count,outfile,varnames));
				
				outfile<<"\nSTACKW\t"<<(*global_stack).size()-(n+1)<<"\n";
				if((*tokens)[0].token=="."){
					
					node.tokens.push_back((*tokens)[0].token);

		            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
					
				}else error(node.label,(*tokens)[0].token);
				
            }else error(node.label,(*tokens)[0].token);
			
        }else error(node.label,(*tokens)[0].token);
		
    }else error(node.label,(*tokens)[0].token);
    
   return node; 
   
}




Node RO(std::vector<TokenType> *tokens, std::vector<string> *local_stack , std::vector<string> *global_stack, int *count, std::ofstream &outfile, std::vector<string>* varnames){
    Node node;
    node.label="RO";
    //outfile<<"\n in RO ";
	//strcpy(label,newName(LABEL));
 
    if((*tokens)[0].token=="<"){
		node.tokens.push_back((*tokens)[0].token);

        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        if((*tokens)[0].token=="="){
			node.tokens.push_back((*tokens)[0].token);
			branch="BRNEG\t"+string(label);

            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        }else{
			branch="BRNEG\t"+string(label)+"\nBRZERO\t"+string(label);
		}
    }else  if((*tokens)[0].token==">"){
		node.tokens.push_back((*tokens)[0].token);

        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        if((*tokens)[0].token=="="){
			node.tokens.push_back((*tokens)[0].token);
			branch="BRPOS\t"+string(label);

            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        }else{
			branch="BRPOS\t"+string(label)+"\nBRZERO\t"+string(label);	
		}
    }else  if((*tokens)[0].token=="="){
		node.tokens.push_back((*tokens)[0].token);

        (*tokens).assign((*tokens).begin()+1, (*tokens).end());
        if((*tokens)[0].token=="="){
			node.tokens.push_back((*tokens)[0].token);

			branch="BRZERO\t"+string(label);
			
            (*tokens).assign((*tokens).begin()+1, (*tokens).end());
		}else{
			branch="BRNONZ\t"+string(label);
		}
    }else error(node.label,(*tokens)[0].token);
    
   return node; 
}



void display(Node node,int level){
    
	for(int i=0;i<level;i++){
		cout<<"\t";
	}
	cout<<" <"<<node.label<<"> ";
	 for(int i=0;i<node.tokens.size();i++){
        cout<<" "<<node.tokens[i];
    }
	
	cout<<"\n";
	
    for(int i=0;i<node.children.size();i++){
        display(node.children[i],level+1);
    }
    
    
}





