// �h�����ۥ[��m��(�i��)
// ��23�� 1081639 ���q�u  1081611  ����t
// �{���\�� 1: �}���ɮ�hw.txt�A��J�G���}�C(�H�U�H�uP�}�C�v�٩I)�C
// �{���\�� 2: �N�h�����ۥ[��G�s�JP�}�C�̡C
// �{���\�� 3: �N�䵲�G�L�X�ӡC

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
	// A�h���� 4x^5-2x^4+x^2-7x+10
	// B�h���� x^8-2x^5-3x^3-x^2+4x-1
	int p[2][30];
	GetFile(p);		//Ū��

	int a_s = 1, a_f = p[0][0];	//A�h�������}�l�P������m 
	int b_s = a_f+1, b_f = p[0][0]+p[1][0];	//B�h�������}�l�P������m 
	int avail = b_f+1;			//�U�ӥi�ΪŶ���m 
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
		cout << "�ɮ׵L�k�}��";
		exit(1);
	}
	int i = 0, j = 0;
	while (inf >> p[i][j]) {	//���ƥ�i�}�C
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
	for (i, j; i <= a_f && j <= b_f; c++) {		//�p�GB���Y�Ƥ���j�N���copy_to_c��~~
		if (p[1][i] < p[1][j]) {				
			copy_to_c(p[0][j], p[1][j], p, c);  
			j++;
		}
		else if (p[1][i] == p[1][j]) {			//�p�GA�MB���Y�Ƥ@�ˤj�N�n���ۥ[�A�ᵹcopy_to_c��~~
			copy_to_c(p[0][i] + p[0][j], p[1][i], p, c);
			i++;
			j++;
		}
		else if (p[1][i] > p[1][j]) {			//�p�GA���Y�Ƥ���j�N���copy_to_c��~~
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
		if (p[1][i] < p[1][j]) {			//�p�GB���Y�Ƥ���j�N���copy_to_c��~~
			if (p[0][j] > 0) {
				p[0][j] = 0 - p[0][j];		//���t���ഫ
				copy_to_c(p[0][j], p[1][j], p, c);
				j++;
			}
			else {
				p[0][j] = 0 - p[0][j];		//���t���ഫ
				copy_to_c(p[0][j], p[1][j], p, c);
				j++;
			}
		}
		else if (p[1][i] == p[1][j]) {		//�p�GA�MB���Y�Ƥ@�ˤj�N�n���ۥ[�A�ᵹcopy_to_c��~~
			copy_to_c(p[0][i] - p[0][j], p[1][i], p, c);
			i++;
			j++;
		}
		else if (p[1][i] > p[1][j]) {		//�p�GA���Y�Ƥ���j�N���copy_to_c��~~
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
	p[0][c] = coef;	//�N�ǹL�Ӫ��Y�ƶ�i�h
	p[1][c] = exp;	////�N�ǹL�Ӫ������i�h
}

void print_p(int p[][30],int start, int finish) {

	for (int i = start, s = 1; i <= finish; i++, s++) {				
		if (p[0][i] != 0) {		//�Y�Ƥ��ର0
			if (s == 1) {
				if (p[0][i] == 1) {				//�Ĥ@�����Y�Ƥ���O 1x �� -1x (��ꤣ�u�Ĥ@���A���O�ڷQ�ΤF
					cout << "x^" << p[1][i];	
				}
				else if(p[0][i] == -1){
					cout << "-x^" << p[1][i];
				}
			}
			else {
				if (s > 1 && p[0][i] >= 0) {	//not first item �B �Y�ƭn�j��0 (�p��0���Y�Ʀ��t���S
					cout << " + ";
				}
				if (p[1][i] == 1) {				//�p�G���覡1�A������X x�A�p�G���O�N�n�[�Y��
					if (p[0][i] == 1) {
						cout << "x";
					}
					else {
						cout << p[0][i] << "x";
					}
				}
				else if (p[1][i] != 0) {		//�p�G���褣��0�����p
					cout << p[0][i] << "x^" << p[1][i];
				}
				if (p[1][i] == 0) {				//�p�G���謰0�����p
					cout << p[0][i];
					break;
				}
			}
		}
	}
}
