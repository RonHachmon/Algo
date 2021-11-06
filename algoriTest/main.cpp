#include <iostream>
#include <vector>
#include <list>

using namespace std;
void coverArray(vector<list<int>>* vec);
void coverList(vector<list<int>>* vec, int VerticeTofind, int listIndex);
void checkPartner(vector<list<int>>* vec, int VerticeTofind,int listToLookIndex);
void resetMatrix(vector<vector<int>>* vec,int size);
void printMatrix(vector<vector<int>>* vec);
void convertListToMatrix(vector<vector<int>>* matrix, vector<list<int>>* list);
vector<int> emptyVec(int size);
void multiply(vector<vector<int>>* source_matrixA, vector<vector<int>>* source_matrixB, vector<vector<int>>* target_matrix);

int main(void)
{
	string s = "hello";
	vector<list<int>> vec;
	vector<vector<int>> matrix;
	vector<vector<int>> matrixP2;
	vector<vector<int>> matrixP3;
	list <int>list1;
	list <int>list2;
	list <int>list3;
	list <int>list4;
	list <int>list5;
	list1.push_back(2);
	list1.push_back(3);
	list2.push_back(1);
	list2.push_back(4);
	list3.push_back(1);
	list3.push_back(4);
	list4.push_back(2);
	list4.push_back(3);
	list4.push_back(5);
	list5.push_back(1);
	list5.push_back(3);
	list5.push_back(4);
	vec.push_back(list1);
	vec.push_back(list2);
	vec.push_back(list3);
	vec.push_back(list4);
	vec.push_back(list5);
	/*coverArray(&vec);*/

	resetMatrix(&matrix, 5);
	resetMatrix(&matrixP2, 5);
	resetMatrix(&matrixP3, 5);
	/*printMatrix(&matrix);*/
	convertListToMatrix(&matrix, &vec);
	multiply(&matrix, &matrix,&matrixP2);
	cout << endl;
	printMatrix(&matrixP2);
	cout << endl;
	multiply(&matrix, &matrixP2, &matrixP3);
	printMatrix(&matrixP3);
}
void multiply(vector<vector<int>>* source_matrixA, vector<vector<int>>* source_matrixB, vector<vector<int>>* target_matrix)
{
	for (int i = 0; i < (*source_matrixA).size(); i++)
	{
		for (int j = 0; j < (*source_matrixA)[i].size(); j++)
		{
			for (int k = 0; k<(*target_matrix).size(); k++)
				(*target_matrix)[i][j] += (*source_matrixA)[i][k] * (*source_matrixB)[k][j];
		}
	}
}
void convertListToMatrix(vector<vector<int>>* matrix, vector<list<int>>* list)
{
	for (int i = 0; i < (*list).size(); i++)
	{
		for (int x : (*list)[i])
		{
			(*matrix)[i][x-1] = 1;
		}
	}
}
void printMatrix(vector<vector<int>>* vec)
{
	for (int i = 0; i < (*vec).size(); i++)
	{
		cout << "{";
		for (int j = 0; j < (*vec)[i].size(); j++)
		{
			cout << (*vec)[i][j]<<" , ";
		}
		cout << "}"<<endl;
	}
}
void resetMatrix(vector<vector<int>>* vec, int size)
{
	for (int i = 0; i < size; i++)
	{
		vec->push_back(emptyVec(size));
	}
}
vector<int> emptyVec(int size)
{
	vector <int> a;
	for (int i = 0; i < size; i++)
	{
		a.push_back(0);
	}
	return a;
}

void coverArray(vector<list<int>>* vec)
{
	for (int i = 0; i < (*vec).size(); i++)
	{
		for (int x : (*vec)[i])
		{
			coverList(vec, i + 1, x-1);
		}
	}
}
//	for (int i = 0; i < (*vec).size(); i++)
//	{
//		cout << i + 1 << ':';
//		for (int x : (*vec)[i]) {
//			cout << x << ',';
//		}
//		cout << endl;
//	}
//}
void coverList(vector<list<int>>* vec, int VerticeTofind,int listIndex)
{
	for (int x : (*vec)[listIndex]) {
		if (x != VerticeTofind)
		{
			checkPartner(vec, VerticeTofind, x-1);
		}
	}
}
void checkPartner(vector<list<int>>* vec, int VerticeTofind, int listToLookIndex)
{
	for (int x : (*vec)[listToLookIndex]) {
		if (x== VerticeTofind)
		{
			cout << "Start vertice:" << VerticeTofind  << endl;
			cout << "End vertice:" << listToLookIndex+1 << endl;
			cout <<endl;
		}
	}
}
