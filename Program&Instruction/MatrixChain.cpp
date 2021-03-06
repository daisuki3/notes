#include <iostream>
using namespace std;
/*
计算M方阵上半角
按↘斜线顺序计算M[i][j], (i <= j)

m[i][j] 代表 第i个矩阵到第j个矩阵相
乘的最小操作数

s[i][j] 代表 第i个矩阵到第j个矩阵相
乘时有最小操作数的分割点

p[i] 代表第i个矩阵的横行数
p[i + 1] 代表第i个矩阵的纵行数
*/
void MatrixChain(int *p, int n, int **m, int **s){
	
	for(int i = 1; i <= n; i++) 
		m[i][i] =0;
	
	/*↘斜线上  j - i = r(常数)
	对右上角那个点 有 j - i = n - 1 
	*/
	for(int r = 1; r <= n - 1; r++)
		for(int i = 1; i <= n - r; i++){
			
			int j = i + r;

			m[i][j] = m[i][i] + m[i + 1][j] + p[i] * p[i + 1] * p[j + 1];
			s[i][j] = i;

			for(int k = i + 1; k < j; k++){
				/*探索 i + 1 到 j - 1 之间（含端点）的矩阵, 
				找寻最适合当分割点的矩阵
				*/
				int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];

				if(t < m[i][j]){
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
}
int main()
{	
	int p[]={0, 30, 35, 15, 5, 10, 20, 25};
	const int n = 6;
	int **m = new int*[n + 1];
	int **s = new int*[n + 1];

	for(int i = 0; i < n + 1; i++){
		m[i] = new int[n + 1];
		s[i] = new int[n + 1];
	}
	MatrixChain(p, n, m, s);
	cout << m[1][n]; // here m[1][n] = 15125 
	return 0;
} 
