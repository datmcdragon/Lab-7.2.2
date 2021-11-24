#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo);
void CreateRows(int** a, const int N, const int Low, const int High, int rowNo);
void PrintRow(int** a, const int rowNo, const int N, int colNo);
void PrintRows(int** a, const int N, int rowNo);
void MinInterRow(int** a, const int i, int j, int& index_min_h, int& index_min_v);
int MinInterRows(int** a, const int N, int i, int j, int& index_min_h, int& index_min_v);
void MaxInterRow(int** a, const int N, const int i, int j, int& index_max_h, int& index_max_v);
int MaxInterRows(int** a, const int N, int i, int j, int& index_max_h, int& index_max_v);
void Change(int** a, const int N, int maxi1, int maxi2, int mini1, int mini2);
int Sum(int** a, const int N, int i, int j, int& index_max_h, int& index_max_v, int& index_min_h, int& index_min_v);

int main()
{
    srand((unsigned)time(NULL));
    int N;

    cout << "N = "; cin >> N;
    cout << endl;

    int** a = new int* [N];
    for (int i = 0; i < N; i++)
        a[i] = new int[N];
    int min = 0;
    int Low = -100, High = 100;

    CreateRows(a, N, Low, High, 0);
    PrintRows(a, N, 0);

    int i1 = 0, i2 = 0;
    cout << MinInterRows(a, N, 0, 0, i1, i2) << endl;

    i1 = i2 = 0;
    cout << MaxInterRows(a, N, 0, 0, i1, i2) << endl;

    int maxi1=0, maxi2=0, mini1=0, mini2=0;
    Change(a, N, maxi1, maxi2, mini1, mini2);

    PrintRows(a, N, 0);

    cout << Sum(a, N, 0, 0, i1, i2, i1, i2) << endl;

    for (int i = 0; i < N; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1);
}
void CreateRows(int** a, const int N, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, N, Low, High, 0);
    if (rowNo < N - 1)
        CreateRows(a, N, Low, High, rowNo + 1);
}
void PrintRow(int** a, const int rowNo, const int N, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1);
    else
        cout << endl;
}
void PrintRows(int** a, const int N, int rowNo)
{
    PrintRow(a, rowNo, N, 0);
    if (rowNo < N - 1)
        PrintRows(a, N, rowNo + 1);
    else
        cout << endl;
}

void MinInterRow(int** a, const int i, int j, int& index_min_h, int& index_min_v)
{
    if (j <= i)
    {
        if (a[i][j] < a[index_min_h][index_min_v])
        {
            index_min_h = i;
            index_min_v = j;
        }
        MinInterRow(a, i, j + 1, index_min_h, index_min_v);
    }
}

int MinInterRows(int** a, const int N, int i, int j, int& index_min_h, int& index_min_v)
{
    if (i < N)
    {
        MinInterRow(a, i, 0, index_min_h, index_min_v);
        MinInterRows(a, N, i + 1, j, index_min_h, index_min_v);
    }
    return a[index_min_h][index_min_v];
}

void MaxInterRow(int** a, const int N, const int i, int j, int& index_max_h, int& index_max_v)
{
    if (j < N)
    {
        if (a[i][j] > a[index_max_h][index_max_v])
        {
            index_max_h = i;
            index_max_v = j;
        }
        MaxInterRow(a, N, i, j + 1, index_max_h, index_max_v);
    }
}

int MaxInterRows(int** a, const int N, int i, int j, int& index_max_h, int& index_max_v)
{
    if (i < N)
    {
        MaxInterRow(a, N, i, i, index_max_h, index_max_v);
        MaxInterRows(a, N, i + 1, j, index_max_h, index_max_v);
    }
    return a[index_max_h][index_max_v];
}

void Change(int** a, const int N, int maxi1, int maxi2, int mini1, int mini2)
{
    mini1 = mini2 = 0;
    MinInterRows(a, N, 0, 0, mini1, mini2);

    maxi1 = maxi2 = 0;
    MaxInterRows(a, N, 0, 0, maxi1, maxi2);

    auto tmp = a[maxi1][maxi2];
    a[maxi1][maxi2] = a[mini1][mini2];
    a[mini1][mini2] = tmp;
}

int Sum(int** a, const int N, int i, int j, int& index_max_h, int& index_max_v, int& index_min_h, int& index_min_v)
{
    return  MinInterRows(a, N, i, j, index_min_h, index_min_v) + MaxInterRows(a, N, i, j, index_max_h, index_max_v);
}