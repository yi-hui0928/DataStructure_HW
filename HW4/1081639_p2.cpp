// 特訓 1-2: 請根據15行，完成 82行的add()，再執行38,39,40行 。 
// 特訓 1-3: change to Class (with private data and construtors)
// 特訓 1-4: change int m3Ary to dynmaic and re-new when idx > N
// 特訓 1-4: add deconstructor
#include <cstdlib>
#include <iomanip>   // for format
#include <iostream>
#include <fstream>  // for input file

#define N 20
using namespace std;

void set_ary(int [][3], int, int, int, int);
void read_to_ary(int [][3], ifstream &);
void add(int [][3], int [][3], int [][3]);
void prn_ary(int [][3],  const string);	
void prn_matrix(int [][3],  const string);	
void prn_zero(int, int, int);

int main(void)
{
	
	int m3Ary[N][3], m3AryB[N][3], m3AryC[N][3]; 
	ifstream infile("t1.txt");
	if(!infile) {
		cout << "this t1.txt" << " cannot open!"<< endl;
		system("PAUSE"); exit(1);
	}
	read_to_ary(m3Ary, infile);
	prn_ary(m3Ary, "3-column ary A");
	prn_matrix(m3Ary, "matrix A");

	read_to_ary(m3AryB,  infile);
	prn_ary(m3AryB, "3-column ary B");
	prn_matrix(m3AryB, "matrix B");

/****完成 82行的add()，再執行38,39,40行 ********	
	add(m3Ary, m3AryB, m3AryC);
	prn_ary(m3AryC, "3-column ary C");
	prn_matrix(m3AryB, "matrix C");
**************************************/	

	add(m3Ary, m3AryB, m3AryC);
	prn_ary(m3AryC, "3-column ary C");
	prn_matrix(m3AryC, "matrix C");

	infile.clear(); infile.close();
	system("PAUSE");
	return 0;
}

void set_ary(int m3Ary[][3], int i,int row,int col, int value)
{   // set values to i-th row of array
	m3Ary[i][0]=row;
	m3Ary[i][1]=col;
	m3Ary[i][2]=value;
}

void read_to_ary(int m3Ary[][3], ifstream &infile)
{	// read the input file and set value to s-column array
    int ar=0, ac=0, idx=0;
	infile >> ar >> ac;
	cout << "row= " << ar <<"   col= " << ac << endl;
	set_ary(m3Ary, idx++, ar, ac, 0);  // give 1st row of 3-column array
	for(int i=0; i<ar; i++ )
		for(int v, j =0; j< ac; j++) {
			if( !(infile >> v)) { // not get value successfully
				cout << "this t1.txt" << " cannot open!"<< endl;
				system("PAUSE");  exit(1);
		    }
			if(v)      // if (v != 0)  i.e., no zero term
				 set_ary(m3Ary, idx++, i, j, v); 				    
		}
	 m3Ary[0][2]=idx-1;  // set the number of non-zero terms
  
}

void prn_ary(int m3Ary[][3], const string info){
	cout << info<< endl;
	for(int i=0; i<= m3Ary[0][2]; i++)
		cout << setw(3) <<m3Ary[i][0] << setw(4) << m3Ary[i][1] << 
		setw(4) << right<< m3Ary[i][2] <<endl;
}

//**********	 Here is you work  ********		 
void add(int m3Ary[][3], int m3AryB[][3], int m3AryC[][3])
{
	int i = 1, j = 1, avail = 1;
	for (i,j; i <= m3Ary[0][2] && j <= m3AryB[0][2]; avail++) {
		if (m3Ary[i][0] < m3AryB[j][0]) {
			set_ary(m3AryC, avail, m3Ary[i][0], m3Ary[i][1], m3Ary[i][2]);
			i++;
		}
		else if (m3Ary[i][0] > m3AryB[j][0]) {
			set_ary(m3AryC, avail, m3AryB[j][0], m3AryB[j][1], m3AryB[j][2]);
			j++;
		}
		else if (m3Ary[i][0] == m3AryB[j][0]) {
			if (m3Ary[i][1] < m3AryB[j][1]) {
				set_ary(m3AryC, avail, m3Ary[i][0], m3Ary[i][1], m3Ary[i][2]);
				i++;
			}
			else if (m3Ary[i][1] > m3AryB[j][1]) {
				set_ary(m3AryC, avail, m3AryB[j][0], m3AryB[j][1], m3AryB[j][2]);
				j++;
			}
			else if (m3Ary[i][1] == m3AryB[j][1]) {
				if (m3Ary[i][2] + m3AryB[j][2] == 0) {
					avail--;
				}
				else if (m3Ary[i][2] + m3AryB[j][2] != 0) {
					set_ary(m3AryC, avail, m3Ary[i][0], m3Ary[i][1], m3Ary[i][2] + m3AryB[j][2]);
				}
				i++;
				j++;
			}
		}
	}
	while (i <= m3Ary[0][2]) {
		set_ary(m3AryC, avail, m3Ary[i][0], m3Ary[i][1], m3Ary[i][2]);
		i++;
		avail++;
	}
	while (j <= m3AryB[0][2]) {
		set_ary(m3AryC, avail, m3AryB[j][0], m3AryB[j][1], m3AryB[j][2]);
		j++;
		avail++;
	}
	set_ary(m3AryC, 0, m3Ary[0][0], m3Ary[0][1], avail-1);
}


/*void prn_matrix(int m3Ary[][3], const string info){// linear time
	int row_d, col_d, idx=1;  // distance: number of 0 to print
	cout << info<< endl;
	for(int i=-1; idx<= m3Ary[0][2]; idx++)
	{
		 row_d = m3Ary[idx][0]-i-1;
		 col_d = m3Ary[idx][1]; 
		 if(row_d || col_d)
		 	prn_zero(row_d, col_d, 0);
		 cout << setw(3) << right<< m3Ary[idx][2];
		 if(idx < m3Ary[0][2] && m3Ary[idx][0] != m3Ary[idx+1][0] ) // next one is at different row
		 	 prn_zero(0, m3Ary[0][1]-m3Ary[idx][1]-1, 1);
	     i= m3Ary[idx][0];
	}	
	idx--;
	prn_zero(0, m3Ary[0][1]-m3Ary[idx][1]-1, 1); //complement zero column
	prn_zero(m3Ary[0][0]-m3Ary[idx][0]-1,0, 0);// complement zero row
}*/

void prn_zero(int row, int col, int line)
{
	for(int i=0; i<row; i++)
	   cout << "  0  0  0  0  0  0  0  0  0  0\n";
	for(int i=0; i<col; i++)
	   cout<< setw(3) << right<< 0;
	if(line)
	   cout << endl;
}

/*** This one is more easy but need O(N^2) time  **/
void prn_matrix(int m3Ary[][3], const string info){  
	int i, j, idx;
	cout << info<< endl;
	for(i=0, j=0, idx=1; idx<= m3Ary[0][2]; i++) {
	    for(int j=0; j< m3Ary[0][1]; j++)  {
			 if(i==m3Ary[idx][0] && j== m3Ary[idx][1]) {
				cout << setw(3) << right<< m3Ary[idx][2];
				idx++;  // to the next non zero term
			}  else
	        	cout << setw(3) << right<< 0;
	    }
		cout << endl;  
    }
    for(  ; i< m3Ary[0][0]; i++) {  // 補足列  complement zero rows
	    for(int j=0; j< m3Ary[0][1]; j++)  
			cout << setw(3) << right<< 0;
	    cout << endl;  
    }
}   




