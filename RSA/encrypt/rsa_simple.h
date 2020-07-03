#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <QDebug>
using namespace std;

class RSASimple
{
public:
    RSASimple();
    ~RSASimple();
    void test();
    int  cipherLen();
    int  plainLen();
    void setPlaintext(char *data, int len);
    void setCiphertext(char *data, int len);
    char *plaintext();
    char *ciphertext();
    void generateKey();
    void setPublicKey(char *key);
    void setPrivateKey(char *key);
    char *publicKey();
    char *privateKey();
    void clearData();
private:
    void RSA_Initialize();

    int RSA_Encrypt();
    int RSA_Decrypt();

    int Exgcd(int m,int n,int &x);//欧几里得扩展算法

    int ProducePrimeNumber(int prime[]);//生成1000以内素数
    long long Modular_Exonentiation(long long a, int b, int n);//反复平方求幂
    int BianaryTransform(int num, int bin_num[]);//二进制转换


    int         *Plaintext = nullptr;  //明文
    long long   *Ciphertext= nullptr;  //密文
    char        *m_mid_buffer = nullptr;
    int         m_len = 0;

    int         n, e = 0, d;
    char        pubkey[24];
    char        prikey[24];
};

#endif // ENCRYPT_H
