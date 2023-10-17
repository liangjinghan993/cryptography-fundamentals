#include <iostream>
#include <vector>
#include <bitset>
#include <random>
using namespace std;

const int BLOCK_SIZE = 16;
const int NUM_PLAINTEXT_PAIRS = 2000; // 生成的明文对数量
const int TARGET_XOR_VALUE = 0x0;      // 目标异或值

// S-box
const unsigned char S_BOX[16] = {
    0x0E, 0x04, 0x0D, 0x01,
    0x02, 0x0F, 0x0B, 0x08,
    0x03, 0x0A, 0x06, 0x0C,
    0x05, 0x09, 0x00, 0x07
};

// P4 permutation
const int P4[4] = { 1, 3, 2, 0 };

// SPN encryption function
unsigned char spn_encrypt(unsigned char plaintext, unsigned char key)
{
    unsigned char xored = plaintext ^ key;
    unsigned char sboxed = S_BOX[xored & 0x0F];
    unsigned char permuted = 0;
    for (int i = 0; i < 4; ++i)
    {
        permuted |= ((sboxed >> i) & 0x01) << P4[i];
    }
    return permuted;
}

int main()
{
    // 生成随机引擎
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 0xFFFF); // 16位明文对的范围

    vector<pair<unsigned short, unsigned short>> plaintext_pairs;

    // 生成明文对
    while (plaintext_pairs.size() < NUM_PLAINTEXT_PAIRS)
    {
        unsigned short p1 = dis(gen);
        unsigned short p2 = p1 ^ TARGET_XOR_VALUE;
        if (spn_encrypt(p1, 0x00) == spn_encrypt(p2, 0x00)) // 过滤异或值相同的明文对
        {
            plaintext_pairs.push_back(make_pair(p1, p2));
        }
    }

    // 输出生成的明文对
    for (const auto& pair : plaintext_pairs)
    {
        cout << "Plaintext Pair: "
            << bitset<BLOCK_SIZE>(pair.first) << " , "
            << bitset<BLOCK_SIZE>(pair.second) << endl;
    } return 0;
}
