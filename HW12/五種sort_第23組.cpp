// ��23�� 1081639 ���q�u  1081611  ����t
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void Make_Rand(int ary[], int temp_ary[]);			//�s�@�ü�
void Copy_Matrix(int ary[], int temp_ary[]);		//�üƭ��m
void Bubble_Sort_950(int ary[], int temp_ary[]);	//�Ϊw�j�ƧǪk���Ʀn950��
void Bubble_Sort(int bubble_ary[]);					//�w�j�ƧǪk
void Insert_Sort(int insert_ary[]);					//���J�ƧǪk
void Select_Sort(int select_ary[]);					//��ܱƧǪk
void Quick_Sort(int quick_ary[], int, int);			//�ֳt�ƧǪk
void Heap_Sort(int heap_ary[], int len);			//�ְ�ƧǪk

int main() {
	
	int* ary = new int[1000];		//�Q�ƧǪ��}�C
	int* temp_ary = new int[1000];	//�Mary�����e�@�ˡA���Q�Ʀn��ary���s�Q����

	Make_Rand(ary,temp_ary);		//�s�y�ü�
	
	cout << "�Ĥ@�D:" << endl;

	clock_t bubble_time1 = clock();		
	Bubble_Sort(ary);				//�w�j�Ƨ�
	clock_t bubble_time2 = clock() - bubble_time1;	//�w�j�ƧǪ��ɶ�
	cout << "Bubble Sort takes : " << double(bubble_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//�üƭ��m

	clock_t insert_time1 = clock();
	Insert_Sort(ary);				//���J�Ƨ�
	clock_t insert_time2 = clock() - insert_time1;	//���J�ƧǪ��ɶ�
	cout << "Insert Sort takes : " << double(insert_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//�üƭ��m

	clock_t select_time1 = clock();
	Select_Sort(ary);				//��ܱƧ�
	clock_t select_time2 = clock() - select_time1;	//��ܱƧǪ��ɶ�
	cout << "Select Sort takes : " << double(select_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//�üƭ��m

	clock_t quick_time1 = clock();
	Quick_Sort(ary, 0, 999);		//�ֳt�Ƨ�
	clock_t quick_time2 = clock() - quick_time1;	//�ֳt�ƧǪ��ɶ�
	cout << "Quick Sort  takes : " << double(quick_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//�üƭ��m

	clock_t heap_time1 = clock();
	Heap_Sort(ary, 1000);			//�ְ�Ƨ�
	clock_t heap_time2 = clock() - heap_time1;		//�ְ�ƧǪ��ɶ�
	cout << "Heap Sort   takes : " << double(heap_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//�üƭ��m
	cout << endl;
	
	cout << "�ĤG�D:" << endl;
	Copy_Matrix(ary, temp_ary);		//�üƭ��m
	Bubble_Sort_950(ary, temp_ary);	//��Ӱ}�C�����Ʀn950��

	bubble_time1 = clock();
	Bubble_Sort(ary);
	bubble_time2 = clock() - bubble_time1;
	cout << "Bubble Sort takes : " << double(bubble_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);

	insert_time1 = clock();
	Insert_Sort(ary);
	insert_time2 = clock() - insert_time1;
	cout << "Insert Sort takes : " << double(insert_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);

	select_time1 = clock();
	Select_Sort(ary);
	select_time2 = clock() - select_time1;
	cout << "Select Sort takes : " << double(select_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);

	quick_time1 = clock();
	Quick_Sort(ary, 0, 999);
	quick_time2 = clock() - quick_time1;
	cout << "Quick Sort  takes : " << double(quick_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);

	heap_time1 = clock();
	Heap_Sort(ary, 1000);
	heap_time2 = clock() - heap_time1;
	cout << "Heap Sort   takes : " << double(heap_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);
}

void Make_Rand(int ary[], int temp_ary[]) {
	/* �T�w�üƺؤl */
	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		ary[i] = rand() % 10000;		/* ���Ͷü� */
	}
	for (int i = 0; i < 1000; i++) {
		temp_ary[i] = ary[i];
	}
}

void Copy_Matrix(int ary[], int temp_ary[]) {	//�Nary���s�Q����
	for (int i = 0; i < 1000; i++) {
		ary[i] = temp_ary[i];
	}
}

void swap(int& x, int& y) {	//�洫����ܼƪ���
	int temp;
	temp = x;
	x = y;
	y = temp;
}

void Bubble_Sort(int bubble_ary[]) {	//�w�j�Ƨ�
	for (int i = 1000; i > 0; i--) {	//i�O�Ʀn���ơAi�U�p�A�Ʀn���ƷU�h
		for (int j = 0; j < i - 1; j++) {	//���Xary
			if (bubble_ary[j] > bubble_ary[j + 1]) {	//����j���Ʃ����
				swap(bubble_ary[j], bubble_ary[j + 1]);
			}
		}
	}
	/*for (int i = 0; i < 1000; i++) {
		cout << bubble_ary[i] << endl;
	}*/
}

void Insert_Sort(int insert_ary[]) {	//���J�ƧǪk
	for (int i = 1; i < 1000; i++) {	//���X���Ƨ�ary
		int key = insert_ary[i];		//�]�wkey
		int j = i - 1;					//���X�H�ƧǦn��ary
		while (key < insert_ary[j] && j >= 0) {	//key < ary[j]�A��ܧ��n���J����m�F
			insert_ary[j + 1] = insert_ary[j];	//���X�w�ƧǪ�ary
			j--;
		}
		insert_ary[j + 1] = key;	//�N�ȴ��J
	}
	/*for (int i = 0; i < 1000; i++) {
		cout << insert_ary[i] << endl;
	}*/
}
void Select_Sort(int select_ary[]) {			//��ܱƧ�
	for (int i = 0; i < 1000; i++) {			//���Xary
		for (int j = i + 1; j < 1000; j++) {	
			if (select_ary[i] > select_ary[j]) {
				swap(select_ary[i], select_ary[j]);
			}
		}
	}
	/*for (int i = 0; i < 1000; i++) {
		cout << select_ary[i] << endl;
	}*/
}

void Quick_Sort(int quick_ary[], int left, int right) {

	int mid;
	mid = (left + right) / 2;	//���������Y���ۥ[��2
	if (left >= right)	//����j��k���ܱƧ��F
		exit(1);
	int pivoA;
	pivoA = quick_ary[mid];	//pivot�b����
	int i, j;
	i = left;
	j = right;
	while (i <= j)
	{

		while (quick_ary[i] < pivoA)	//pivot�j��i��e���ȴN�~��
			i++;
		while (quick_ary[j] > pivoA)	//pivot�p��j��e���ȴN�~��
			j--;
		if (i <= j)		//i����m�p��j�Ai j ���Ȥ���
		{
			swap(quick_ary[i], quick_ary[j]);
			i++; j--;	//�~�򩹤U��
		}
	}
	if (i < right)	//��ܳo�@�������F�A�I�s�U�@��
		Quick_Sort(quick_ary, i, right);
	if (j > left)	//��ܳo�@�������F�A�I�s�U�@��
		Quick_Sort(quick_ary, left, j);
}

void max_heapify(int arr[], int, int);
void Heap_Sort(int heap_ary[], int len) {	// arr[ ] -> �n�ƧǪ��Ʀr���}�C , len -> ���h�ּƦr�n�Ƨ�
	for (int i = len / 2 - 1; i >= 0; i--) //���վ㦨Max Heap
	{
		max_heapify(heap_ary, i, len - 1);
	}
	//��̤W�����`�I( root ) ��̫᭱���`�I�洫��m�A
	//��洫��m�᪺���ন Max Heap
	for (int i = len - 1; i > 0; i--)
	{
		swap(heap_ary[0], heap_ary[i]);
		max_heapify(heap_ary, 0, i - 1);
	}
	/*for (int i = 0; i < 1000; i++) {
		cout << heap_ary[i] << endl;
	}*/
}
void max_heapify(int arr[], int start, int end) // arr[ ] -> �n�ƧǪ��Ʀr���}�C
					  // start , end -> �n��𪺭��̨���̽վ㦨Max Heap
{
	int dad = start;
	int son = dad * 2 + 1; //�]���o��}�C�̬O�q 0 �}�l�s �ҥH�~dad * 2 + 1 
	while (son <= end) //�Y�l�`�I�b�d�򤺤~�����
	{
		//�p�G�ڥk�䪺�l�`�I�]�b�d�򤺡A�M��k�䪺����j
		if (son + 1 <= end && arr[son] < arr[son + 1])
			son++; //���N��k�䪺
		if (arr[dad] > arr[son]) //�p�G���`�I�j��l�`�I�N��վ㧹���A�������X���
			return;
		else  //�_�h�洫���l���e�A�~��l�`�I�M�]�`�I���
		{
			swap(arr[dad], arr[son]); //swap�O�@�ӥ� �Ѧ� ���������Ȫ��禡
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void Bubble_Sort_950(int ary[], int temp_ary[]) {	//�w�j�Ƨǫe950�ӼƦr
	for (int i = 950; i > 0; i--) {
		for (int j = 0; j < i - 1; j++) {
			if (ary[j] > ary[j + 1]) {
				swap(ary[j], ary[j + 1]);
			}
		}
	}
	for (int i = 0; i < 1000; i++) {
		temp_ary[i] = ary[i];		//��temp_ary�]�ƧǦn�e950�ӼƦr
	}
}
