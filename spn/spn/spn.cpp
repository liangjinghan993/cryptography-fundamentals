#include<iostream>
#include<math.h>
#include<string>
using namespace std;
const int pais[20] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 };
const int paip[20] = { 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };
int seize(int n[4])
{
	int answer = 0;
	for (int i = 1; i <= 4; i++)
	{
		answer += (int)pow(2.0, 4 - i) * n[i - 1];
	}
	return answer;
}
int* UpaisV(int u[16])
{
	int* v = new int[21], n[4];
	int j = 0, k = 0;
	for (int i = 0; i < 16; i++)
	{
		n[j++] = u[i];
		if (j == 4)
		{
			int s = seize(n);
			s = pais[s];
			v[k++] = s / 8;
			s -= s / 8 * 8;
			v[k++] = s / 4;
			s -= s / 4 * 4;
			v[k++] = s / 2;
			s -= s / 2 * 2;
			v[k++] = s;
			j = 0;
		}
	}
	return v;
}
void SPN()
{
	int w[16], u[16], k[16], * v = new int[20];
	int y[16] = { 0 };
	string x(17, 0);
	string K(33, 0);
	cin >> x >> K;
	//w0=x
	//cout << "w0:";
	for (int i = 0; i < 16; i++)
	{
		w[i] = x[i] - 48;
		//cout << w[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 32; i++)
	{
		K[i] -= 48;
	}
	//循环
	for (int i = 1; i <= 3; i++)
	{
		//k[0]=K[4i-3]
		//cout << "k" << i << ":";
		for (int j = 0; j < 16; j++)
		{
			k[j] = K[(4 * i - 4) + j];
			//cout << k[j] << " ";
		}
		//cout << endl;

		//u=w异或k
		//cout << "u" << i << ":";
		for (int j = 0; j < 16; j++)
		{
			u[j] = w[j] ^ k[j];
			//cout << u[j] << " ";
		}
		//cout << endl;

		//v是S盒的代换
		//cout << "v" << i << ":";
		v = UpaisV(u);
		for (int j = 0; j < 16; j++)
		{
			//cout << v[j] << " ";
		}
		//cout << endl;

		//w=v paip
		//cout << "w" << i << ":";
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				if (j == paip[k] - 1)
				{
					w[j] = v[k];
				}
			}
		}
	}
	//循环结束
	//cout << "K4:" ;
	for (int i = 0; i < 16; i++)
	{
		k[i] = K[12 + i];
		//cout << k[i] << " ";
	}
	//cout << endl;

	//u=w异或k
	//cout << "u4:";
	for (int i = 0; i < 16; i++)
	{
		u[i] = w[i] ^ k[i];
		//cout << u[i] << " ";
	}
	//cout << endl;
	//v是pais置换
	//cout << "v4:";
	v = UpaisV(u);
	/*for (int i = 0; i < 16; i++)
	{
		cout << v[i] << " ";
	}*/
	//cout << endl;

	//k
	//cout << "K5:";
	for (int i = 0; i < 16; i++)
	{
		k[i] = K[16 + i];
		//cout << k[i] << " ";
	}
	//cout << endl;

	//y=v^K
	//cout << "y: ";
	for (int i = 0; i < 16; i++)
	{
		y[i] = v[i] ^ k[i];
		cout << y[i];
	}
	cout << endl;
	return;
}

int main()
{
	SPN();
	return 0;
}