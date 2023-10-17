#include <iostream>
#include <vector>
#include <ctime>
#include <bitset>
using namespace std;

// �������16λ���������Ķ�
void generatePlaintextPairs(int numPairs, vector<unsigned short>& plaintexts1, vector<unsigned short>& plaintexts2) {
    srand(time(0));
    for (int i = 0; i < numPairs; i++) {
        unsigned short p1 = rand() & 0xFFFF; // �������16λ��������
        unsigned short p2 = p1 ^ (1 << (rand() % 16)); // ���ɺ�p1���ֵ��ͬ������
        plaintexts1.push_back(p1);
        plaintexts2.push_back(p2);
    }
}

int main() {
    int numPairs = 2000; // ����100�����Ķ�
    vector<unsigned short> plaintexts1;
    vector<unsigned short> plaintexts2;

    // �������16λ���������Ķ�
    generatePlaintextPairs(numPairs, plaintexts1, plaintexts2);

    // ������Ķ�
    cout << "���ɵ�16λ���������Ķԣ�" << endl;
    for (int i = 0; i < numPairs; i++) {
        cout << "���Ķ�" << i + 1 << ": " << bitset<16>(plaintexts1[i]) << ", " << bitset<16>(plaintexts2[i]) << endl;
    }

    return 0;
}
