#include<iostream>
#include<cstring>
#include <math.h>
#include<fstream>
using namespace std;
ifstream input;
int S[16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 };

//将字符‘0’‘1’分开处理，分别赋值0和1，更清晰地表示二进制的0和1
void fuzhi(char* w, int* r)
{
	int len = strlen(w);
	for (int i = 0; i < len; i++)
	{
		if ( w[i] == '1' || w[i] == '0'  )
		{
			r[i] = w[i] - '0';
		}
	}
}
//十进制转4位二进制,简化循环，将递减操作放在循环内部，以更简洁实现将十进制转化为4位二进制的功能
void siweierjinzhi(int decimal, int* binary, int j)
{
	for (int i = j; i >= j - 3; i--)
	{
		binary[i] = decimal % 2;
		decimal /= 2;
	}
}


//S盒的逆矩阵
void niS1(int* S, int* S1)
{
	for (int i = 0; i < 16; i++)
	{
		S1[S[i]] = i;
	}
}


int main()
{
	
	int s1[16];
	int n;
	
	
	
	input.open("D:\\密码学基础\\四元正确对.txt");
	niS1(S, s1);


	int p[16][16];
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			p[i][j] = 0;
		}
	}
	cin >> n;

	int v1[16], u1[16], u_2[16];
	int La[4], Lb[4];
	int x[16], y[16], x1[16], y1[16];
	for (int t = 0; t < n; t++)
	{
		char* X = new char[16];
		char* Y = new char[16];
		char* X1 = new char[16];
		char* Y1 = new char[16];
		for (int j = 0; j < 16; j++)
		{
			input >> X[j];
		}
		for (int j = 0; j < 16; j++)
		{
			input >> Y[j];
		}
		for (int j = 0; j < 16; j++)
		{
			input >> X1[j];
		}
		for (int j = 0; j < 16; j++)
		{
			input >> Y1[j];
		}


		fuzhi(X, x);
		fuzhi(Y, y);
		fuzhi(X1, x1);
		fuzhi(Y1, y1);

		int v2, v4, v21, v41, u2, u4, u21, u41, z = -1;
		int v[16], u[16];
		
		for (int i = 0; i < 16; i++)
		{
			siweierjinzhi(i, La, 3);
			for (int j = 0; j < 16; j++)
			{
				siweierjinzhi(j, Lb, 3);
				 

				v[4] = (La[0] + y[4]) % 2;
				v[5] = (La[1] + y[5]) % 2;
				v[6] = (La[2] + y[6]) % 2;
				v[7] = (La[3] + y[7]) % 2;

				v[12] = (Lb[0] + y[12]) % 2;
				v[13] = (Lb[1] + y[13]) % 2;
				v[14] = (Lb[2] + y[14]) % 2;
				v[15] = (Lb[3] + y[15]) % 2;
				v2 = 0; 


				if (v[4] == 1)	
					v2 +=8;
				if (v[5] == 1)	
					v2 +=4;
				if (v[6] == 1)	
					v2 +=2;
				if (v[7] == 1)	
					v2 +=1;
				u2 = s1[v2];
				siweierjinzhi(u2, u, 7);
				v4 = 0;


				if (v[12] == 1)	
					v4+=8;
				if (v[13] == 1)	
					v4+=4;
				if (v[14] == 1)	
					v4+=2;
				if (v[15] == 1)	
					v4+=1;
				u4 = s1[v4];
				siweierjinzhi(u4, u, 15);


				v1[4] = (La[0] + y1[4]) % 2;
				v1[5] = (La[1] + y1[5]) % 2;
				v1[6] = (La[2] + y1[6]) % 2;
				v1[7] = (La[3] + y1[7]) % 2;
				v1[12] = (Lb[0] + y1[12]) % 2;
				v1[13] = (Lb[1] + y1[13]) % 2;
				v1[14] = (Lb[2] + y1[14]) % 2;
				v1[15] = (Lb[3] + y1[15]) % 2;
				v21 = 0;


				if (v1[4] == 1)	
					v21 += 8;
				if (v1[5] == 1)	
					v21+= 4;
				if (v1[6] == 1)
					v21 += 2;
				if (v1[7] == 1)	
					v21 += 1;
				u21 = s1[v21];
				siweierjinzhi(u21, u1, 7);
				v41 = 0;



				if (v1[12] == 1)	
					v41 += 8;
				if (v1[13] == 1)	
					v41 += 4;
				if (v1[14] == 1)	
					v41 += 2;
				if (v1[15] == 1)	
					v41 += 1;
				u41 = s1[v41];
				siweierjinzhi(u41, u1, 15);


				
				u_2[4] = (u[4] + u1[4]) % 2;
				u_2[5] = (u[5] + u1[5]) % 2;
				u_2[6] = (u[6] + u1[6]) % 2;
				u_2[7] = (u[7] + u1[7]) % 2;
				u_2[12] = (u[12] + u1[12]) % 2;
				u_2[13] = (u[13] + u1[13]) % 2;
				u_2[14] = (u[14] + u1[14]) % 2;
				u_2[15] = (u[15] + u1[15]) % 2;
				
				
				
				if (u_2[4] == 0 &&u_2[5] == 1 &&u_2[6] == 1 &&u_2[7] == 0 &&u_2[12] == 0 &&u_2[13] == 1 &&u_2[14] == 1&&u_2[15] == 0)
				{
					p[i][j] += 1;
				}
			}
		}

	}
	
	
	int a, b;
	int max = -1;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (p[i][j] > max)
			{
				max = p[i][j];
				a = i;
				b = j;
			}
		}
	}
	siweierjinzhi(a, La, 3);


	for (int i = 0; i < 4; i++)
	{
		cout << La[i];
	}
	siweierjinzhi(b, Lb, 3);



	for (int i = 0; i < 4; i++)
	{
		cout << Lb[i];
	}
	cout << endl;
	return 0;
}