// generate.c contains assembler generation routines                         //
//   assembler routines are those from chapter2 of "Program Translation" by  //
//   P. Calingaert                                                           //

#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "parser.h"
#include "token.h"
#include <stdio.h>       
#include <stdlib.h>
#include <algorithm>

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

static void recGen(Node *stats,FILE *out)
{ char label[20], label2[20], argR[20];
  if (stats==NULL)
    return;
  
  
    if (stats->label== "program"){    
		recGen(&(stats->children[0]),out);           // evaluate rhs //
		recGen(&(stats->children[1]),out);  
		// evaluate rhs //
    }else if(stats->label== "block"){  
	
		recGen(&(stats->children[0]),out);           // evaluate rhs //
		recGen(&(stats->children[1]),out);           // evaluate rhs //
    }
	
	/*   look into this one!
    if (stats->label== "vars"){    
		if(!stats->children.empty{
			strcpy(argR,newName(VAR)); //create a temporary variable 
			cout<<"\tREAD\t%s\n"<<argR;
			cout<<"\tSTORE\t%s\n"<<argR;
			cout<<"\tPUSH\t%s\n";
			cout<<"\tSTACKW\t%s\n"<<argR;
		}		
		recGen(&(stats->children[0]),out);           // evaluate rhs //
    } */
	
	if (stats->label=="expr"){
		recGen(&(stats->children[1]),out);     // first evaluate rhs //
        strcpy(argR,newName(VAR)); //create a temporary variable 
		cout<<"\tSTORE\t%s\n"<<argR;
		recGen(&(stats->children[0]),out);       // result is in ACC /
		if (stats->tokens[0]=="/")
			cout<<"\tDIV\t%s\n"<<argR;
			else if (stats->tokens[0]=="*")
			  cout<<"\tMULT\t%s\n"<<argR;
                        else cout<<"Invalid tokenId in expression node";
		


		
	}else if(stats->label=="A"){
		
		recGen(&(stats->children[1]),out);     // first evaluate rhs //
        strcpy(argR,newName(VAR)); //create a temporary variable 
		cout<<"\tSTORE\t%s\n"<<argR;
		recGen(&(stats->children[0]),out);       // result is in ACC /
		if (stats->tokens[0]=="+")
			cout<<"\tADD\t%s\n"<<argR;
		else if (stats->tokens[0]=="-")
			cout<<"\tSUB\t%s\n"<<argR;
        else cout<<"Invalid tokenId in expression node";
		
		
		
		
		
	}else if (stats->label== "M"){ 
	
		if(stats->children[0].label== "R"){
			recGen(&(stats->children[0]),out); 
		}else{
		cout<<"\tMULT -1\t%s\n";
		}
		
		
		
		
		
    } else if (stats->label== "R"){    
	
		if(!stats->children.empty()){
			recGen(&(stats->children[0]),out);
		}else if(stats->tokenstash[0].tokenID==ID_TKN){
			cout<<"\tLOAD\t%s\n"<<stats->tokens[0];
		}else if(stats->tokenstash[0].tokenID==INT_TKN){
			cout<<"\tLOAD\t%s\n"<<stats->tokens[0];
		}
		
		
		////////////////
	}else if(stats->label== "stats"){    
	
		recGen(&(stats->children[0]),out);           // evaluate rhs //
		cout<<"\tSTORE\t%s\n"<<stats->tokens[1];
	
	
	
	
		/////////////
	}else if(stats->label== "mstat"){    
	
		recGen(&(stats->children[0]),out);           // evaluate rhs //
		cout<<"\tSTORE\t%s\n"<<stats->tokens[1];	
	
	
		/////////////	
	}else if(stats->label== "stat"){    
	
		recGen(&(stats->children[0]),out);           // evaluate rhs //
		cout<<"\tSTORE\t%s\n"<<stats->tokens[1];
	
		
		
    }else if(stats->label== "assign"){    
	
		recGen(&(stats->children[0]),out);           // evaluate rhs //
		cout<<"\tSTORE\t%s\n"<<stats->tokens[1];
	
	
	
	
	
    }else if(stats->label== "in"){
		cout<<"\tREAD\t%s\n"<<stats->tokens[1];
		
		
		
		
		
		
		
	} else if (stats->label== "out"){    
	
		recGen(&(stats->children[0]),out);           // evaluate rhs //
        strcpy(argR,newName(VAR)); //create a temporary variable 
		cout<<"\tSTORE\t%s\n"<<argR;
		cout<<"\tWRITE\t%s\n"<<argR;
		
		////////
    }else if(stats->label== "IF"){
		
			recGen(&(stats->children[0]),out);              // condition //
			strcpy(label,Name);           // memorize jump label //
			recGen(&(stats->children[1]),out);   // dependent statements //
			cout<<"%s\tNOOP\n"<<label;
			
			
	}else if(stats->label== "loop"){
		
			recGen(&(stats->children[0]),out);              // condition //
			strcpy(label,Name);           // memorize jump label //
			recGen(&(stats->children[1]),out);   // dependent statements //
			cout<<"%s\tNOOP\n"<<label;
			
	
	}else if(stats->label== "RO"){
			
			recGen(&(stats->children[1]),out);
			strcpy(argR,newName(VAR));
			cout<<"\tSTORE\t%s\n"<<argR;
			recGen(&(stats->children[0]),out);
			cout<<"\tSUB\t%s\n"<<argR;
			strcpy(label,newName(LABEL));
			if (stats->tokens[0]=="<"){
				if (stats->tokens[1]=="="){
					cout<<"\tBRPOS\t%s\n"<<label;
					
				}else{
					
					cout<<"\tBRPOS\t%s\n",label;
			 	 	cout<<"\tBRZERO\t%s\n",label;
				}
			}else if (stats->tokens[0]==">"){
			
				if (stats->tokens[1]=="="){
					
					cout<<"\tBRNEG\t%s\n"<<label;
					
				}else{
				cout<<"\tBRNEG\t%s\n"<<label;
			  	cout<<"\tBRZERO\t%s\n"<<label;
				}
			}else if(stats->tokens[0]=="="){
				if(stats->tokens[1]=="="){
					
				}
				
			}
	/*   
			  case EQUALtk: fprintf(out,"\tBRNONZ\t%s\n",label);
					break;
			  default: fprintf(out,"\tBRZERO\t%s\n",label);
			}
			break;
						/
    default:            recGen(*(stats->children[0]),out);
                        recGen(*(stats->children[1]),out);
						recGen(&(stats->children[2]),out);     
	*/
  } 
}

// generate assembler code for parse tree pointed by prog, with variables    //
//   listed in st subtree                                                    //

/*
void generate(const Node *prog, Node *st, FILE *out)
{ int i;
  if (prog==NULL || prog->label!=programNode || prog->children[0]==NULL ||
      prog->children[0]->label!=programBlockNode)
    error("something wrong with parse tree in generate",NULL,0);
  recGen(prog->children[0]->children[1],out);     // children[0]->children[1] points to statList //
  fprintf(out,"\tSTOP\n");
  while(st!=NULL)                  // allocate storage for program variables //
  { fprintf(out,"%s\tSPACE\n",st->tokenP->str);
    st=st->children[0];
  }
  for (i=0;i<VarCntr; i++)      // allocate space for temporary variables V* //
    fprintf(out,"V%d\tSPACE\n",i);
}

*/

