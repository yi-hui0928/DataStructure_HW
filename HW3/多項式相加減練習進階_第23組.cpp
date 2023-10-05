// 多項式相加減練習(進階)
// 第23組 1081639 戴益暉  1081611  謝鎬宇
// 程式功能 1: 開啟檔案hw.txt，放入二維陣列(以下以「P陣列」稱呼)。
// 程式功能 2: 將多項式相加減結果存入P陣列裡。
// 程式功能 3: 將其結果印出來。

#include <iostream> 
#include <cstdlib>
#include<fstream>
using namespace std;

void copy_to_c(int, int, int[][30], int);
void print_p(int[][30], int, int);
void GetFile(int[][30]);
void Add(int, int, int, int, int, int[][30]);
void Sub(int, int, int, int, int, int[][30]);
int main(void)
{
	// A多項式 4x^5-2x^4+x^2-7x+10
	// B多項式 x^8-2x^5-3x^3-x^2+4x-1
	int p[2][30];
	GetFile(p);		//讀檔

	int a_s = 1, a_f = p[0][0];	//A多項式的開始與結束位置 
	int b_s = a_f+1, b_f = p[0][0]+p[1][0];	//B多項式的開始與結束位置 
	int avail = b_f+1;			//下個可用空間位置 
	int i = a_s, j = b_s, c = avail;
	cout << "A+B=";
	Add(a_s, a_f, b_s, b_f, avail, p);		//A+B
	cout << endl;
	cout << "A-B=";
	Sub(a_s, a_f, b_s, b_f, avail, p);		//A-B
	
	system("PAUSE");
	return 0;
}

void  GetFile(int p[][30]) {
	ifstream inf("hw.txt");
	if (!inf) {
		cout << "檔案無法開啟";
		exit(1);
	}
	int i = 0, j = 0;
	while (inf >> p[i][j]) {	//把資料丟進陣列
		if (i < 1) {			
			i++;
		}
		else {
			j++;
			i = 0;
		}
	}
}

void Add(int a_s, int  a_f, int  b_s, int  b_f, int  avail, int p[][30]) {

	int i = a_s, j = b_s, c = avail;
	for (i, j; i <= a_f && j <= b_f; c++) {		//如果B的係數比較大就丟到copy_to_c唷~~
		if (p[1][i] < p[1][j]) {				
			copy_to_c(p[0][j], p[1][j], p, c);  
			j++;
		}
		else if (p[1][i] == p[1][j]) {			//如果A和B的係數一樣大就要先相加再丟給copy_to_c唷~~
			copy_to_c(p[0][i] + p[0][j], p[1][i], p, c);
			i++;
			j++;
		}
		else if (p[1][i] > p[1][j]) {			//如果A的係數比較大就丟到copy_to_c唷~~
			copy_to_c(p[0][i], p[1][i], p, c);
			i++;
		}
	}

	while (i <= a_f) {	//if p not finish
		copy_to_c(p[0][i], p[1][i], p, c++);
		i++;
	}
	while (j <= b_f) {	//if p not finish
		copy_to_c(p[0][j], p[1][j], p, c++);
		j++;
	}
	print_p(p, b_f + 1, c);
}

void Sub(int a_s, int a_f, int b_s, int b_f, int avail, int p[][30]) {
	int i = a_s, j = b_s, c = avail;
	for (i, j; i <= a_f && j <= b_f; c++) {
		if (p[1][i] < p[1][j]) {			//如果B的係數比較大就丟到copy_to_c唷~~
			if (p[0][j] > 0) {
				p[0][j] = 0 - p[0][j];		//正負值轉換
				copy_to_c(p[0][j], p[1][j], p, c);
				j++;
			}
			else {
				p[0][j] = 0 - p[0][j];		//正負值轉換
				copy_to_c(p[0][j], p[1][j], p, c);
				j++;
			}
		}
		else if (p[1][i] == p[1][j]) {		//如果A和B的係數一樣大就要先相加再丟給copy_to_c唷~~
			copy_to_c(p[0][i] - p[0][j], p[1][i], p, c);
			i++;
			j++;
		}
		else if (p[1][i] > p[1][j]) {		//如果A的係數比較大就丟到copy_to_c唷~~
			copy_to_c(p[0][i], p[1][i], p, c);
			i++;
		}
	}

	while (i <= a_f) {	//if p not finish
		copy_to_c(p[0][i], p[1][i], p, c++);
		i++;
	}
	while (j <= b_f) {	//if p not finish
		copy_to_c(p[0][j], p[1][j], p, c++);
		j++;
	}
	print_p(p, b_f + 1, c);
}

void copy_to_c(int coef, int exp, int p[][30], int c) {
	p[0][c] = coef;	//將傳過來的係數塞進去
	p[1][c] = exp;	////將傳過來的次方塞進去
}

void print_p(int p[][30],int start, int finish) {

	for (int i = start, s = 1; i <= finish; i++, s++) {				
		if (p[0][i] != 0) {		//係數不能為0
			if (s == 1) {
				if (p[0][i] == 1) {				//第一項的係數不能是 1x 或 -1x (其實不只第一項，但是我想睡了
					cout << "x^" << p[1][i];	
				}
				else if(p[0][i] == -1){
					cout << "-x^" << p[1][i];
				}
			}
			else {
				if (s > 1 && p[0][i] >= 0) {	//not first item 且 係數要大於0 (小於0的係數有負號惹
					cout << " + ";
				}
				if (p[1][i] == 1) {				//如果次方式1，直接輸出 x，如果不是就要加係數
					if (p[0][i] == 1) {
						cout << "x";
					}
					else {
						cout << p[0][i] << "x";
					}
				}
				else if (p[1][i] != 0) {		//如果次方不為0的情況
					cout << p[0][i] << "x^" << p[1][i];
				}
				if (p[1][i] == 0) {				//如果次方為0的狀況
					cout << p[0][i];
					break;
				}
			}
		}
	}
}
