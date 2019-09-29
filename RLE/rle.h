#ifndef RLE_H
#define RLE_H
class rle{
	public: 
	char sym, sym1,sym2, sym3; 
    char iter = 1, iter2 = -1;
	clock_t begin;
    float one =1.00;
    float timearchiv, timedearchiv, sizeoffirstfile, sizeofarchivfile;
    float compression=sizeoffirstfile/sizeofarchivfile;
    char *filename1;
    char *filename2;
	void archiv(){
		
		ifstream file(filename1, ios_base::binary);
        ofstream file_archiv("archiv.txt", ios_base::binary);
        file.seekg (0, ios::end);
        sizeoffirstfile = file.tellg() / 1024;
        file.seekg (0, ios::beg);
        begin=clock();
       
    
    while(file.good())
    {   
    
        file.read(&sym, 1);
		
		
       if(sym!=file.peek()){
        
            	
            if(iter==1){
            	
            while(sym!=file.peek() && file.good())	{
				file.read(&sym, 1);
            	iter2--;
            	if(iter2==-128){
            		file.seekg(iter2, ios::cur);
            		
                    file_archiv.write(&iter2, ios::cur);		
                    for(int i=0; i<abs(iter2)-1; i++){
             	
             	    file.read(&sym, 1);
             	    file_archiv.write(&sym, 1);
				}
				iter2=0;
			}
            	if(file.peek()==EOF){
            		
            		file.seekg(iter2, ios::cur);
            		
            		iter2--;
            		if(iter2==-128){
            		file.seekg(iter2, ios::cur);
            		
                    file_archiv.write(&iter2, ios::cur);		
                    for(int i=0; i<abs(iter2)-1; i++){
             	
             	    file.read(&sym, 1);
             	    file_archiv.write(&sym, 1);
				}
				iter2=0;
            	}
                    file_archiv.write(&iter2, ios::cur);		
                    for(int i=0; i<abs(iter2)-1; i++){
             	
             	    file.read(&sym, 1);
             	    file_archiv.write(&sym, 1);
             }
             goto l1;
				}
            	
            }
            
			 file.seekg(iter2, ios::cur);
             file_archiv.write(&iter2, ios::cur);		
             for(int i=0; i<abs(iter2)-1; i++){
             	
             	file.read(&sym, 1);
             	file_archiv.write(&sym, 1);
             }
             iter2=-1;
            }
            else{
            file_archiv.write(&iter, 1);
            file_archiv.write(&sym, 1);	
            }
			iter=0;
    }

        iter++;
        if(iter==127){
        	 file_archiv.write(&iter, 1);
             file_archiv.write(&sym, 1);
             iter=0;
        } 
        
         }
    
    l1:
    file.close();
    file_archiv.close();
    timearchiv = ceil( 100 * ((float) (clock() - begin) / CLOCKS_PER_SEC) )   /   100.0;}
	
	
	
	void dearchiv(){
		ifstream f1("archiv.txt", ios_base::binary);
        ofstream file_dearchiv(filename2, ios_base::binary);
        f1.seekg(0, ios::end);
        sizeofarchivfile = f1.tellg() / 1024;
        f1.seekg(0, ios::beg);
        begin=clock();
    while(f1.peek()!=EOF){
    
        f1.read(&sym1, 1); 
        if(sym1<0){
        	
        	for(int j=0; j<abs(sym1)-1; j++){
        		f1.read(&sym3,1);
        		file_dearchiv.write(&sym3, 1);
        	}
        }
        
        else{
        f1.read(&sym2, 1);
        for(int i=0; i<sym1; i++){
        
        file_dearchiv.write(&sym2, 1);} }
    }

    f1.close();
    file_dearchiv.close();
    timedearchiv =  ceil( 100 * ((float) (clock() - begin) / CLOCKS_PER_SEC) )   /   100.0;}
	
	void stat_of_archiv(){
        cout<<" Size of first file = "<<sizeoffirstfile<<" kb\n";
		cout<<" Time of archiving = "<<timearchiv<<" s\n";
	}
	void stat_of_dearchiv(){
		cout<<" Size of archiv file = "<<sizeofarchivfile<<" kb\n";
		cout<<" Time of dearchiving = "<<timedearchiv<<" s\n";
	}
	void stat_of_full(){
		cout<<" Size of archiv file = "<<sizeofarchivfile<<" kb\n";
		cout<<" Time of dearchiving = "<<timedearchiv<<" s\n";
	    cout<<" Compression = "<<ceil( 100 * (sizeoffirstfile/sizeofarchivfile) )   /   100.0<<"\n";
	    if(sizeoffirstfile/sizeofarchivfile < one){
	    	cout<<" Bad result of compression \n";
	    }
	    else{
	    	if(sizeoffirstfile/sizeofarchivfile > one){
	    	cout<<" Good result of compression \n";}
	    }
	    
	}
	

};
#endif
