// change to Class:  student version
// 完成 read_to_ary 就可以 執行 63~69  *****

#include <cstdlib>
#include <iomanip>   // for format
#include <iostream>
#include <fstream>  // for input file
#include <typeinfo>
#define N 4

using namespace std;
class C3Ary;

class C3Ary_item{  // each cell is(row, column, value)
	friend C3Ary;
	private: 
		int row, col, value;
};

class C3Ary{
	private:
		C3Ary_item* aryPtr;
		int capacity;  // indicate the available space of items
		int top;  // indicate total number of items
	public:
		C3Ary();
		void Push(int row, int col, int value);
		// 利用push 完成 read_to_ary 就可以 執行 63~69
		void read_to_ary(ifstream &infile);  
		void prn_ary(const string info);
		void prn_matrix(const string info);
		void prn_zero(int row, int col, int line);
		void Push(C3Ary &ob, int bi);

};

C3Ary::C3Ary(){ // constructor
	capacity = N;
	top = -1;
	aryPtr = new C3Ary_item[capacity];
}


int main()
{
	C3Ary obA;
	C3Ary obB;
	C3Ary obC;
	ifstream infile("t1.txt");
	if(!infile) {
		cout << "this t1.txt" << " cannot open!"<< endl;
		system("PAUSE"); 
		exit(1);
	}
/***************  完成 read_to_ary 就可以 執行 63~69  *****
	obA.read_to_ary(infile);
	obA.prn_ary("3-column ary A");
	obA.prn_matrix( "matrix A");
	
	obB.read_to_ary(infile);
	obB.prn_ary("3-column ary B");
	obB.prn_matrix( "matrix B");
****************/

/*	
	obA.add(obB, obC);
	obC.prn_ary("3-column ary C");
	obC.prn_matrix( "matrix C");
*/	
	infile.clear(); 
	infile.close();
	
	
	system("PAUSE");
	return 0;
}

		
// 利用push 完成 read_to_ary 就可以 執行 63~69	
void C3Ary::Push(int row, int col, int value){
	if (top+1 == capacity){
		capacity *= 2;
		C3Ary_item* temp = new C3Ary_item[capacity];
		copy(aryPtr, aryPtr+top+1,temp);
		delete[] aryPtr;
		aryPtr = temp;
	}
	aryPtr[++top].row = row;
	aryPtr[top].col = col;
	aryPtr[top].value = value;
}

/***************  完成 read_to_ary 就可以 執行 63~69  *****/
/*  Please complete the foloowing fuction  ***********/
void C3Ary::read_to_ary(ifstream &infile){
	int ar=0, ac=0, idx=0;
	infile >> ar >> ac;
	cout << "row= " << ar <<"   col= " << ac << endl;





}
		
void C3Ary::prn_ary(const string info){
	cout << info<< endl;
	for(int i=0; i<= aryPtr[0].value; i++)
		cout << setw(3) <<aryPtr[i].row << setw(4) << aryPtr[i].col << \
			setw(4) << right<< aryPtr[i].value <<endl;
}
		
void C3Ary::prn_matrix(const string info){// linear time
	int row_d, col_d, idx=1;  // distance: number of 0 to print
	cout << info<< endl;
	for(int old_r=-1, old_c=-1; idx<= aryPtr[0].value; idx++)
	{
		 row_d = aryPtr[idx].row-old_r-1;
		 col_d = aryPtr[idx].col-old_c-1; 
		 if(row_d || col_d)
		 	prn_zero(row_d, col_d, 0);
		 cout << setw(3) << right<< aryPtr[idx].value;
		 if(idx < aryPtr[0].value && aryPtr[idx].row != aryPtr[idx+1].row ) {// next one is at different row
		 	 prn_zero(0, aryPtr[0].col-aryPtr[idx].col-1, 1);
		 	 old_c= -1;
		 } else
		 	 old_c= aryPtr[idx].col;;
	     old_r= aryPtr[idx].row;
	}	
	idx--;
	prn_zero(0, aryPtr[0].col-aryPtr[idx].col-1, 1); //complement zero column
	prn_zero(aryPtr[0].row-aryPtr[idx].row-1,0, 0);// complement zero row
}

void C3Ary::prn_zero(int row, int col, int line)
{
	for(int i=0; i<row; i++)
	   cout << "  0  0  0  0  0  0  0  0  0  0\n";
	for(int i=0; i<col; i++)
	   cout<< setw(3) << right<< 0;
	if(line)
	   cout << endl;
}
		
		


