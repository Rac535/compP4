/******************************************************************************
Ramon Crayton
Compilers
P1
10/29/2018
*******************************************************************************/

#include "test_scanner.h"
#include "scanner.h"

using namespace std;

	
	
void write_list(std::vector<std::string> list,int depth, char* filename){
        	int i=0;


    std::ofstream myfile;
  	myfile.open (filename,std::ios_base::app); 
	myfile<<"\n";
	for(int i=0;i<(2*depth);i++){
		myfile<<"\t";
	}  	
	for(i=0;i<list.size();i++){
		//cout<<list[i]<<" ";		
		myfile <<list[i]<<" " ;  	     
	}           
 	 myfile.close();			
}    	
	
	
	
	
//the main function is driver function of this program	
int main(int argc, char* argv[])
{

				
				
	ifstream infile;
	std::ofstream outfile;
    string fileName = "";
	string outasm="";
  			
			
   
				
    	// if program recieves less than two argument (including itself) use standard input as its input stream
   	if(argc<2){
		outasm="out.asm";
		outfile.open (outasm.c_str(),std::ios_base::app);
		test_scanner(cin,outfile);
    	
	}else{

////////////////////////////////////////////////////////////////
//   file input

	
    	string file=argv[1];

	//add implicit extension
     	fileName=file+".fs182";
		cout<<fileName<<" ";
		outasm=file+".asm";
		
	
	//open file with file stream
        infile.open(fileName.c_str());
		outfile.open(outasm.c_str(),std::ios_base::app);
		
		// if the file cannot be opened produce an error message and exit
		if(infile.fail())
        {
            cout<<"\n ERROR: the file \""<<fileName<<"\" cannot be found. Please check that the file exists \n"; 
            exit(1);
        }

		//call test scanner with the file stream
		test_scanner(infile,outfile);
           		 
   		 
    }
	//close file 
	infile.close();
	outfile.close();
	
	return 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------------









