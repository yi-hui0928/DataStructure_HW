// �p�� �ǥ͸�T (�W�r�Ǹ�) 
// �@�~:�h�����ۥ[ 
// �NA�h�����PB�h�����ۥ[(A+B)�A��i�}�C
// �ñN�䵲�G�L�X�� 
// �p�Y�Ʃξ������s�L���L�X 
// A-B�i�ۥѿ�ܰ�
/****�е��� ****/
//�ɦW�Х[�W�ĴX��(ex.�h�����m��_��X��) 
#include <iostream> 
#include <cstdlib>
using namespace std;

void copy_to_c(int, int, int[][30], int);
void print_p(int[][30], int, int);
int main(void)
{
	// A�h���� 10x^8+6x^5-7x^4-3x^2+5
	// B�h���� -2x^10-10x^8+7x^7+3x^4-2x^3-3x^2+x^1 
	int p[2][30] = { {10,6,-7,-3,5,-2,-10,7,3,-2,-3,1},{8,5,4,2,0,10,8,7,4,3,2,1} };

	int a_s = 0, a_f = 4;	//A�h�������}�l�P������m 
	int b_s = 5, b_f = 11;	//B�h�������}�l�P������m 
	int avail = 12;			//�U�ӥi�ΪŶ���m 
	int i = a_s, j = b_s, c = avail;

	for (i, j; i <= a_f && j <= b_f; c++) {
		if (p[1][i] < p[1][j]) {			//�p�GB���Y�Ƥ���j�N���copy_to_c��~~
			copy_to_c(p[0][j], p[1][j], p, c);
			j++;
		}
		else if (p[1][i] == p[1][j]) {	//�p�GA�MB���Y�Ƥ@�ˤj�N�n���ۥ[�A�ᵹcopy_to_c��~~
			copy_to_c(p[0][i] + p[0][j], p[1][i], p, c);
			i++;
			j++;
		}
		else if (p[1][i] > p[1][j]) {	//�p�GA���Y�Ƥ���j�N���copy_to_c��~~
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
	system("color 70");	//�����C�⴫�Ӥ߱�
	system("PAUSE");
	return 0;
}

void copy_to_c(int coef, int exp, int p[][30], int c) {
	p[0][c] = coef;	//�N�ǹL�Ӫ��Y�ƶ�i�h
	p[1][c] = exp;	////�N�ǹL�Ӫ������i�h
}

void print_p(int p[][30],int start, int finish) {

	for (int i = start, s = 1; i <= finish; i++, s++) {		
		
		if (p[0][i] != 0) {		//�Y�Ƥ��ର0
			if (s > 1 && p[0][i] >= 0) {	//not first item �B �Y�ƭn�j��0 (�p��0���Y�Ʀ��t���S
				cout << " + ";
			}
			if (p[1][i] == 1) {		//�p�G���覡1�A������X x^1 �A�p�G���O�N�n�[�Y��
				if (p[0][i] == 1) {
					cout << "x^1";
				}
				else {
					cout << p[0][i] << "x^1";
				}
			}
			else if ( p[1][i] != 0) {	//�p�G���褣��0�����p
				cout << p[0][i] << "x^" << p[1][i];
			}
			if (p[1][i] == 0) {		//�p�G���謰0�����p
				cout << p[0][i];
				break;
			}
		}
	}
}
