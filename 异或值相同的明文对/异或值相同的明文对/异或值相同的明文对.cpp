#include <iostream>
#include <vector>
#include <ctime>
#include <bitset>
using namespace std;

// 生成随机16位二进制明文对
void generatePlaintextPairs(int numPairs, vector<unsigned short>& plaintexts1, vector<unsigned short>& plaintexts2) {
    srand(time(0));
    for (int i = 0; i < numPairs; i++) {
        unsigned short p1 = rand() & 0xFFFF; // 随机生成16位二进制数
        unsigned short p2 = p1 ^ (1 << (rand() % 16)); // 生成和p1异或值相同的明文
        plaintexts1.push_back(p1);
        plaintexts2.push_back(p2);
    }
}

int main() {
    int numPairs = 2000; // 生成100对明文对
    vector<unsigned short> plaintexts1;
    vector<unsigned short> plaintexts2;

    // 生成随机16位二进制明文对
    generatePlaintextPairs(numPairs, plaintexts1, plaintexts2);

    // 输出明文对
    cout << "生成的16位二进制明文对：" << endl;
    for (int i = 0; i < numPairs; i++) {
        cout << "明文对" << i + 1 << ": " << bitset<16>(plaintexts1[i]) << ", " << bitset<16>(plaintexts2[i]) << endl;
    }

    return 0;
}
