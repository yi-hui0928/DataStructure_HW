#include <iostream>
#include <cstdlib>
#include <fstream> 
using namespace std;

void Add(int m3[][3],int t3[][3]){
	int mt[6][6];
	int n1 , n2;
		
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			mt[i][j] = 0;
		}
	}
	for(int i=1; i <= m3[0][2]; i++){
		for(int j=0; j<3; j++){			
			if(j == 2){
				mt[ m3[i][j-2] - 1 ][ m3[i][j-1] - 1 ] += m3[i][j];
			}
		}
	}
	for(int i=1; i <= m3[0][2]; i++){
		for(int j=0; j<3; j++){			
			if(j == 2){
				mt[ t3[i][j-2] - 1 ][ t3[i][j-1] - 1 ] += t3[i][j];
			}
		}
	}
	cout << "part3 :" << endl;
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			cout << mt[i][j] << "	";
		}
		cout << endl;
	}
	cout << "--------------------------------------" << endl;

}

void coulmn_ary(int m[][6],int t[][6]){
    int temp1 = 0;
    int temp2 = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6 ; j++) {
            if (m[i][j] > 0) {
                temp1++;               
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6 ; j++) {
            if (t[i][j] > 0) {
                temp2++;               
            }
        }
    }
       
    int m3[temp1 + 1][3];
    m3[0][0] = 6;
    m3[0][1] = 6;
    m3[0][2] = temp1;
    int i1 = 1;
    int j1 = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (m[i][j] > 0) {
                m3[i1][j1]=i+1;                
                m3[i1][j1+1]=j+1;                
                m3[i1][j1+2]=m[i][j];				                
                i1++;
            }
        }
    }
    cout << "m3 :" <<endl;
    for(int i=0; i<temp1+1; i++){
		for(int j=0; j<3; j++){
			cout << m3[i][j] << "	";
		}
		cout << endl;
	}
	cout<<"-------------------"<<endl;
		
    int t3[temp2 + 1][3];
    t3[0][0] = 6;
    t3[0][1] = 6;
    t3[0][2] = temp2;
    int i2 = 1;
    int j2 = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (t[i][j] > 0) {
                t3[i2][j2]=i+1;                
                t3[i2][j2+1]=j+1;                
                t3[i2][j2+2]=t[i][j];				                
                i2++;
            }
        }
    }
    cout<<"t3 :"<< endl;
	for(int i=0; i<temp2+1; i++){
		for(int j=0; j<3; j++){
			cout << t3[i][j] << "	";
		}
		cout << endl;
	}
	cout<<"-------------------"<<endl;
	cout<<"test"<<endl;
	for(int i=0; i<temp2+1; i++){
		for(int j=0; j<3; j++){
			cout << t3[i][j] << " ";
		}
		cout<< endl;
	}
	cout << "test endl"<<endl;
	cout<<"------------------"<<endl;
	Add(m3,t3);
}

int main()
{    
    int m[6][6] = { {0,20,0,0,0,0},{10,0,0,0,8,0},
        {0,4,0,0,0,6},{0,0,3,0,0,0},
        {0,0,0,0,0,0},{40,0,0,0,0,0} };
    
    int t[6][6] = { {0,0,0,8,0,0},{0,0,0,0,0,0},
        {0,12,0,0,0,0},{0,0,0,0,0,0},
        {0,0,0,0,10,0},{6,0,0,30,0,0} };
        
    coulmn_ary(m,t);
	    	
	ifstream readfile;
	readfile.open("hw1.in",ios::in);
	if(readfile.fail()){
		cout<<"hw1.inµLªk¶}±Ò";
		exit(1);
	}
	char ch ;
	char ch1[72];
	while(1){
		ch = readfile.get();
		if(readfile.eof()){
			break;
		}
		cout << ch ;		
	}
	readfile.clear();
	readfile.close();
	
    system("PAUSE");
    return 0;
}

