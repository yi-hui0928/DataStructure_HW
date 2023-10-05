// 小組 學生資訊 (名字學號) 
// 作業:多項式相加 
// 將A多項式與B多項式相加(A+B)，放進陣列
// 並將其結果印出來 
// 如係數或冪次為零無須印出 
// A-B可自由選擇做
/****請註解 ****/
//檔名請加上第幾組(ex.多項式練習_第X組) 
#include <iostream> 
#include <cstdlib>
using namespace std;

void copy_to_c(int, int, int[][30], int);
void print_p(int[][30], int, int);
int main(void)
{
	// A多項式 10x^8+6x^5-7x^4-3x^2+5
	// B多項式 -2x^10-10x^8+7x^7+3x^4-2x^3-3x^2+x^1 
	int p[2][30] = { {10,6,-7,-3,5,-2,-10,7,3,-2,-3,1},{8,5,4,2,0,10,8,7,4,3,2,1} };

	int a_s = 0, a_f = 4;	//A多項式的開始與結束位置 
	int b_s = 5, b_f = 11;	//B多項式的開始與結束位置 
	int avail = 12;			//下個可用空間位置 
	int i = a_s, j = b_s, c = avail;

	for (i, j; i <= a_f && j <= b_f; c++) {
		if (p[1][i] < p[1][j]) {			//如果B的係數比較大就丟到copy_to_c唷~~
			copy_to_c(p[0][j], p[1][j], p, c);
			j++;
		}
		else if (p[1][i] == p[1][j]) {	//如果A和B的係數一樣大就要先相加再丟給copy_to_c唷~~
			copy_to_c(p[0][i] + p[0][j], p[1][i], p, c);
			i++;
			j++;
		}
		else if (p[1][i] > p[1][j]) {	//如果A的係數比較大就丟到copy_to_c唷~~
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

	print_p(p, b_f+1, c);
	system("color 70");	//換個顏色換個心情
	system("PAUSE");
	return 0;
}

void copy_to_c(int coef, int exp, int p[][30], int c) {
	p[0][c] = coef;	//將傳過來的係數塞進去
	p[1][c] = exp;	////將傳過來的次方塞進去
}

void print_p(int p[][30],int start, int finish) {

	for (int i = start, s = 1; i <= finish; i++, s++) {		
		
		if (p[0][i] != 0) {		//係數不能為0
			if (s > 1 && p[0][i] >= 0) {	//not first item 且 係數要大於0 (小於0的係數有負號惹
				cout << " + ";
			}
			if (p[1][i] == 1) {		//如果次方式1，直接輸出 x^1 ，如果不是就要加係數
				if (p[0][i] == 1) {
					cout << "x^1";
				}
				else {
					cout << p[0][i] << "x^1";
				}
			}
			else if ( p[1][i] != 0) {	//如果次方不為0的情況
				cout << p[0][i] << "x^" << p[1][i];
			}
			if (p[1][i] == 0) {		//如果次方為0的狀況
				cout << p[0][i];
				break;
			}
		}
	}
}
