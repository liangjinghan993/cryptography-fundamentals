###############################################################################################################3
# 1.实现多项式求逆元

def mybin(a: int, bit=8):
    """
    返回固定位数为bit的二进制字符串，与bin不同的是前面会补零
    """
    a = bin(a)[2:]
    return "0" * (bit - len(a)) + a


def poly_div(a: int, b: int):
    """
    多项式除法
    @return: tuple(商的多项式二进制对应的整数, 余数的二进制对应的整数)
    """
    divisor = 0
    aidx = mybin(a, bit=9).index("1")
    bidx = mybin(b, bit=9).index("1")  # 除数多项式二进制的非零最高位
    while (aidx <= bidx):  # 若被除数多项式二进制的非零最高位小于除数的，就代表可以除
        divisor += 2 ** (bidx - aidx)
        a ^= b << (bidx - aidx)  # 除数乘以差的次数，两者取异或
        if a == 0: break  # 若能整除，则得出结果
        aidx = mybin(a, bit=9).index("1")  # 再得出被除数此时的非零最高位索引
    return divisor, a


def poly_mul(a: int, b: int, m: int):
    """
    多项式乘法
    @a: 多项式a二进制形式对应的整数
    @b: 多项式b二进制形式对应的整数
    @m: 求余多项式二进制形式对应的整数, 这里没减去 x8
    @return: 多项式二进制串所对应的int
    """
    m = m - 128 if m > 127 else m
    bstr = mybin(b)
    ans = 0
    if bstr[-1] == "1": ans ^= a  # f(x)*1  时
    for i in range(1, 8):  # f(x)*xi 时
        if a > 127:  # 1.若 f(x) 最左侧是 1
            a <<= 1
            a = (a - 128) ^ m  # 那么就要左移一位，去掉左侧一，和 m-x8 异或
        else:
            a <<= 1  # 否则 只需左移一位
        if bstr[8 - i - 1] == "1":  # 2.若 g(x) 中对应有这一项，那么结果需要加（异或）这一项
            ans ^= a
    return ans


def poly_gcd(a: int, b: int, m: int):
    """
    @a: 多项式十进制形式
    @b: 多项式十进制形式
    @m: 求余余数十进制形式
    @return: (gcd结果二进制形式, 乘法逆元十进制形式)
    """
    r1, r2 = sorted([a, b], reverse=True)
    w1, w2 = 0, 1
    while int(r2):
        divisor = poly_div(r1, r2)
        r1, r2 = r2, divisor[1]
        w1, w2 = w2, w1 ^ poly_mul(divisor[0], w2, m)

    return r1, w1


###################################################################################################################
# 2.S盒生成

# 索引 0~15,   值 0~9 a~F
translis = [str(i) for i in range(10)] + [chr(ord("A") + i) for i in range(6)]
# 键  0~9 a~F, 值 0~15
inv_transdic = dict(zip(translis, list(range(16))))


def printSBox(SBox):
    """
    打印S盒方便查看
    @SBox: S盒列表
    """
    n = len(SBox)
    print("  ", end="")
    for i in range(n):  # 列坐标
        print(f" {translis[i]}", end=" ")
    print()
    for i in range(n):
        print(translis[i], end=" ")  # 行坐标
        for j in range(n):
            print(transform(SBox[i][j]), end=" ")
        print()


def transform(a: int) -> str:
    """
    @a:      a是八位可表示的十进制整数，将其前四位转化为一字母，后四位转化为一字母
    @return: 返回整数所对应的S盒中元素，如 15 -> 0F
    """
    return translis[a // 16] + translis[a % 16]


def inv_transform(b: str) -> int:
    """
    @b:      b是 S 盒中的一位，如 “0F”
    @return: 返回其对应的十进制整数
    """
    return (inv_transdic[b[0]] << 4) + inv_transdic[b[1]]  # 这里一定注意加括号


def SBox(m: int, C: str):
    """
    @m:      取余多项式的十进制整数形式
    @C:      字符串，S盒c参，如AES的"63"
    @return: S盒列表
    """
    C = [int(i) for i in list(mybin(inv_transform(C)))][::-1]

    ### 1.初始化 + 2.每个求逆元
    Sbox = [[poly_gcd(r * 16 + c, m, 0)[1] for c in range(16)] for r in range(16)]

    ### 3.位变换
    for r in range(16):
        for c in range(16):
            b = [int(i) for i in list(mybin(Sbox[r][c]))][::-1]
            Sbox[r][c] = 0
            for i in range(8):
                Sbox[r][c] += (2 ** i) * (
                            b[i] ^ b[(i + 4) % 8] ^ b[(i + 5) % 8] ^ b[(i + 6) % 8] ^ b[(i + 7) % 8] ^ C[i])
    return Sbox
m=int("100011011",2)
C="63"
sbox=SBox(m,C)
printSBox(sbox)