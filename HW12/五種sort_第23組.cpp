// 第23組 1081639 戴益暉  1081611  謝鎬宇
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void Make_Rand(int ary[], int temp_ary[]);			//製作亂數
void Copy_Matrix(int ary[], int temp_ary[]);		//亂數重置
void Bubble_Sort_950(int ary[], int temp_ary[]);	//用泡沫排序法先排好950個
void Bubble_Sort(int bubble_ary[]);					//泡沫排序法
void Insert_Sort(int insert_ary[]);					//插入排序法
void Select_Sort(int select_ary[]);					//選擇排序法
void Quick_Sort(int quick_ary[], int, int);			//快速排序法
void Heap_Sort(int heap_ary[], int len);			//累堆排序法

int main() {
	
	int* ary = new int[1000];		//被排序的陣列
	int* temp_ary = new int[1000];	//和ary的內容一樣，讓被排好的ary重新被打亂

	Make_Rand(ary,temp_ary);		//製造亂數
	
	cout << "第一題:" << endl;

	clock_t bubble_time1 = clock();		
	Bubble_Sort(ary);				//泡沫排序
	clock_t bubble_time2 = clock() - bubble_time1;	//泡沫排序的時間
	cout << "Bubble Sort takes : " << double(bubble_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//亂數重置

	clock_t insert_time1 = clock();
	Insert_Sort(ary);				//插入排序
	clock_t insert_time2 = clock() - insert_time1;	//插入排序的時間
	cout << "Insert Sort takes : " << double(insert_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//亂數重置

	clock_t select_time1 = clock();
	Select_Sort(ary);				//選擇排序
	clock_t select_time2 = clock() - select_time1;	//選擇排序的時間
	cout << "Select Sort takes : " << double(select_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//亂數重置

	clock_t quick_time1 = clock();
	Quick_Sort(ary, 0, 999);		//快速排序
	clock_t quick_time2 = clock() - quick_time1;	//快速排序的時間
	cout << "Quick Sort  takes : " << double(quick_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//亂數重置

	clock_t heap_time1 = clock();
	Heap_Sort(ary, 1000);			//累堆排序
	clock_t heap_time2 = clock() - heap_time1;		//累堆排序的時間
	cout << "Heap Sort   takes : " << double(heap_time2) / CLOCKS_PER_SEC << " seconds" << endl;
	Copy_Matrix(ary, temp_ary);	//亂數重置
	cout << endl;
	
	cout << "第二題:" << endl;
	Copy_Matrix(ary, temp_ary);		//亂數重置
	Bubble_Sort_950(ary, temp_ary);	//兩個陣列都先排好950個

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
	/* 固定亂數種子 */
	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		ary[i] = rand() % 10000;		/* 產生亂數 */
	}
	for (int i = 0; i < 1000; i++) {
		temp_ary[i] = ary[i];
	}
}

void Copy_Matrix(int ary[], int temp_ary[]) {	//將ary重新被打亂
	for (int i = 0; i < 1000; i++) {
		ary[i] = temp_ary[i];
	}
}

void swap(int& x, int& y) {	//交換兩個變數的值
	int temp;
	temp = x;
	x = y;
	y = temp;
}

void Bubble_Sort(int bubble_ary[]) {	//泡沫排序
	for (int i = 1000; i > 0; i--) {	//i是排好的數，i愈小，排好的數愈多
		for (int j = 0; j < i - 1; j++) {	//走訪ary
			if (bubble_ary[j] > bubble_ary[j + 1]) {	//比較大的數往後丟
				swap(bubble_ary[j], bubble_ary[j + 1]);
			}
		}
	}
	/*for (int i = 0; i < 1000; i++) {
		cout << bubble_ary[i] << endl;
	}*/
}

void Insert_Sort(int insert_ary[]) {	//插入排序法
	for (int i = 1; i < 1000; i++) {	//走訪未排序ary
		int key = insert_ary[i];		//設定key
		int j = i - 1;					//走訪以排序好的ary
		while (key < insert_ary[j] && j >= 0) {	//key < ary[j]，表示找到要插入的位置了
			insert_ary[j + 1] = insert_ary[j];	//走訪已排序的ary
			j--;
		}
		insert_ary[j + 1] = key;	//將值插入
	}
	/*for (int i = 0; i < 1000; i++) {
		cout << insert_ary[i] << endl;
	}*/
}
void Select_Sort(int select_ary[]) {			//選擇排序
	for (int i = 0; i < 1000; i++) {			//走訪ary
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
	mid = (left + right) / 2;	//中間等於頭尾相加除2
	if (left >= right)	//左邊大於右邊表示排完了
		exit(1);
	int pivoA;
	pivoA = quick_ary[mid];	//pivot在中間
	int i, j;
	i = left;
	j = right;
	while (i <= j)
	{

		while (quick_ary[i] < pivoA)	//pivot大於i當前的值就繼續走
			i++;
		while (quick_ary[j] > pivoA)	//pivot小於j當前的值就繼續走
			j--;
		if (i <= j)		//i的位置小於j，i j 的值互換
		{
			swap(quick_ary[i], quick_ary[j]);
			i++; j--;	//繼續往下走
		}
	}
	if (i < right)	//表示這一輪結束了，呼叫下一輪
		Quick_Sort(quick_ary, i, right);
	if (j > left)	//表示這一輪結束了，呼叫下一輪
		Quick_Sort(quick_ary, left, j);
}

void max_heapify(int arr[], int, int);
void Heap_Sort(int heap_ary[], int len) {	// arr[ ] -> 要排序的數字的陣列 , len -> 有多少數字要排序
	for (int i = len / 2 - 1; i >= 0; i--) //把樹調整成Max Heap
	{
		max_heapify(heap_ary, i, len - 1);
	}
	//把最上面的節點( root ) 跟最後面的節點交換位置，
	//把交換位置後的樹轉成 Max Heap
	for (int i = len - 1; i > 0; i--)
	{
		swap(heap_ary[0], heap_ary[i]);
		max_heapify(heap_ary, 0, i - 1);
	}
	/*for (int i = 0; i < 1000; i++) {
		cout << heap_ary[i] << endl;
	}*/
}
void max_heapify(int arr[], int start, int end) // arr[ ] -> 要排序的數字的陣列
					  // start , end -> 要把樹的哪裡到哪裡調整成Max Heap
{
	int dad = start;
	int son = dad * 2 + 1; //因為這邊陣列裡是從 0 開始存 所以才dad * 2 + 1 
	while (son <= end) //若子節點在範圍內才做比較
	{
		//如果我右邊的子節點也在範圍內，然後右邊的比較大
		if (son + 1 <= end && arr[son] < arr[son + 1])
			son++; //那就選右邊的
		if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else  //否則交換父子內容再繼續子節點和孫節點比較
		{
			swap(arr[dad], arr[son]); //swap是一個用 參考 直接互換值的函式
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void Bubble_Sort_950(int ary[], int temp_ary[]) {	//泡沫排序前950個數字
	for (int i = 950; i > 0; i--) {
		for (int j = 0; j < i - 1; j++) {
			if (ary[j] > ary[j + 1]) {
				swap(ary[j], ary[j + 1]);
			}
		}
	}
	for (int i = 0; i < 1000; i++) {
		temp_ary[i] = ary[i];		//讓temp_ary也排序好前950個數字
	}
}
