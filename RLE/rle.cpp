#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;
#include "rle.h"
 
int main(int argc, char **argv)
    {
    rle obj;
	string arch = "archiving";
	string dearch = "dearchiving";
	string full = "full";
	if(argv[1] == arch){
		obj.filename1 = argv[2];
        obj.archiv();
        obj.stat_of_archiv();
	}
    else if(argv[1] == dearch){
    	obj.filename2 = argv[2];
        obj.dearchiv();
  	    obj.stat_of_dearchiv();	
        remove("archiv.txt");
    }	
    else if(argv[1] == full){
    	obj.filename1 = argv[2];
  	    obj.archiv();
        obj.stat_of_archiv();
        obj.filename2 = argv[3];
        obj.dearchiv();
        obj.stat_of_full();
        }
	else cout<<"This command does not exist"<<endl;
		
    system("pause");
    return 0;		
}
