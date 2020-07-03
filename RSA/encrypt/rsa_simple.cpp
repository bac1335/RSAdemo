#include "rsa_simple.h"

#define DEBUG 0

RSASimple::RSASimple()
{
    //Initialize();

    clearData();

    //while(!e)
    //    RSA_Initialize();

    memset(pubkey, 0, sizeof(pubkey));
    memset(prikey, 0, sizeof(prikey));

}
RSASimple::~RSASimple()
{
    clearData();
}

//二进制转换
int RSASimple::BianaryTransform(int num, int bin_num[])
{

    int i = 0,  mod = 0;

    //转换为二进制，逆向暂存temp[]数组中
    while(num != 0)
    {
        mod = num%2;
        bin_num[i] = mod;
        num = num/2;
        i++;
    }

    //返回二进制数的位数
    return i;
}

//反复平方求幂
long long RSASimple::Modular_Exonentiation(long long a, int b, int n)
{
    int c = 0, bin_num[1000];
    long long d = 1;
    int k = BianaryTransform(b, bin_num)-1;

    for(int i = k; i >= 0; i--)
    {
        c = 2*c;
        d = (d*d)%n;
        if(bin_num[i] == 1)
        {
            c = c + 1;
            d = (d*a)%n;
        }
    }
    return d;
}

//生成1000以内素数
int RSASimple::ProducePrimeNumber(int prime[])
{
    int c = 0, vis[1001];
    memset(vis, 0, sizeof(vis));
    for(int i = 2; i <= 1000; i++)if(!vis[i])
    {
        prime[c++] = i;
        for(int j = i*i; j <= 1000; j+=i)
            vis[j] = 1;
    }

    return c;
}


//欧几里得扩展算法
int RSASimple::Exgcd(int m,int n,int &x)
{
    int x1,y1,x0,y0, y;
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;
    int r=m%n;
    int q=(m-r)/n;
    while(r)
    {
        x=x0-q*x1; y=y0-q*y1;
        x0=x1; y0=y1;
        x1=x; y1=y;
        m=n; n=r; r=m%n;
        q=(m-r)/n;
    }
    return n;
}

//RSA初始化
void RSASimple::RSA_Initialize()
{
    //取出1000内素数保存在prime[]数组中
    int prime[5000];
    int count_Prime = ProducePrimeNumber(prime);

    //随机取两个素数p,q
    srand((unsigned)time(NULL));
    int ranNum1 = rand()%count_Prime;
    int ranNum2 = rand()%count_Prime;
    int p = prime[ranNum1], q = prime[ranNum2];

    n = p*q;

    int On = (p-1)*(q-1);


    //用欧几里德扩展算法求e,d
    for(int j = 3; j < On; j+=1331)
    {
        int gcd = Exgcd(j, On, d);
        if( gcd == 1 && d > 0)
        {
            e = j;
            break;
        }

    }

}

//RSA加密
int RSASimple::RSA_Encrypt()
{
    //cout<<"Public Key (e, n) : e = "<<e<<" n = "<<n<<'\n';
    //cout<<"Private Key (d, n) : d = "<<d<<" n = "<<n<<'\n'<<'\n';

    int i = 0;
    for(i = 0; i < m_len; i++)
        Ciphertext[i] = Modular_Exonentiation(Plaintext[i], e, n);

#if DEBUG
    cout<<"Use the public key (e, n) to RSASimple:"<<'\n';
    for(i = 0; i < m_len; i++)
        printf("%08X ", Ciphertext[i]);
    cout<<'\n'<<'\n';
#endif

    return i;
}

//RSA解密
int RSASimple::RSA_Decrypt()
{

    int i = 0;
    for(i = 0; i < m_len; i++)
        Ciphertext[i] = Modular_Exonentiation(Ciphertext[i], d, n);

#if DEBUG
    cout<<"Use private key (d, n) to decrypt:"<<'\n';
    for(i = 0; i < m_len; i++)
        printf("%08X ", Ciphertext[i]);
    cout<<'\n'<<'\n';
#endif
    return i;
}


void RSASimple::test()
{

    char in[1024]={0};

    char middle[1024]={0};

    sprintf(in, "%s", "hello world AS AW  wwqee  qwe ");

    setPublicKey("14cf21f1d4");
    setPrivateKey("62f21f1d3");

    setPlaintext(in, strlen(in));


    memcpy(middle, ciphertext(), cipherLen());


    int len = cipherLen();

    setCiphertext(middle, len);

    publicKey();
    privateKey();

    printf("RSA out:%s\n",  plaintext());


}


int  RSASimple::plainLen()
{
    return m_len;
}
int  RSASimple::cipherLen()
{
    return m_len*3;
}

void RSASimple::setPlaintext(char *data, int len)
{
    int i = 0;
    clearData();

    m_len = len;

    Plaintext = new int[m_len];
    Ciphertext = new long long[m_len];
    memset(Plaintext, 0, sizeof(int)*m_len);
    memset(Ciphertext, 0, sizeof(long long)*m_len);

    for(i = 0; i < m_len; i++)
    {
        Plaintext[i] =  data[i]&0xFF;
    }

#if DEBUG
    cout<<"Input Data:"<<'\n';
    for(i = 0; i < m_len; i++)
    {
        printf("%02x ", data[i]);

    }
    cout<<'\n'<<'\n';
#endif
}

void RSASimple::setCiphertext(char *data, int len)
{
    int i=0;
    clearData();

    m_len = len/3;

    Plaintext = new int[m_len];
    Ciphertext = new long long[m_len];
    memset(Plaintext, 0, sizeof(int)*m_len);
    memset(Ciphertext, 0, sizeof(long long)*m_len);


    for(i=0; i<m_len; i++)
    {
        Ciphertext[i]  = data[i*3+0]&0xFF;
        Ciphertext[i] |= (data[i*3+1]<<8)&0xFF00;
        Ciphertext[i] |= (data[i*3+2]<<16)&0xFF0000;
    }

#if DEBUG
    cout<<"Input RSASimple Data:"<<'\n';
    for(i = 0; i < m_len; i++)
        printf("%08X ", Ciphertext[i]);
    cout<<'\n'<<'\n';
#endif
}

char *RSASimple::ciphertext()
{
    int i = 0;
    RSA_Encrypt();

    if(m_mid_buffer == nullptr)
        m_mid_buffer = new char[m_len*3];
    else
        memset(m_mid_buffer, 0, m_len*3);

    for(i=0; i<m_len; i++)
    {
        m_mid_buffer[i*3+0] = Ciphertext[i]&0xFF;
        m_mid_buffer[i*3+1] = (Ciphertext[i]>>8)&0xFF;
        m_mid_buffer[i*3+2] = (Ciphertext[i]>>16)&0xFF;
    }

#if DEBUG
    cout<<"Encpty Data:"<<'\n';
    for(i = 0; i < m_len*3; i++)
        printf("%02X ", m_mid_buffer[i]&0xFF);
    cout<<'\n'<<'\n';
#endif

    return m_mid_buffer;
}
char *RSASimple::plaintext()
{
    RSA_Decrypt();

    if(m_mid_buffer == nullptr)
        m_mid_buffer = new char[m_len];
    else
        memset(m_mid_buffer, 0, m_len);

    for(int i=0; i<m_len; i++)
    {
        m_mid_buffer[i] = Ciphertext[i]&0xFF;
    }

#if DEBUG
    cout<<"un RSASimple data:"<<'\n';
    for(int i=0; i<m_len; i++)
    {
        printf("%02x ", m_mid_buffer[i]);
    }
    cout<<'\n'<<'\n';
#endif
    return m_mid_buffer;
}

void RSASimple::clearData()
{
    if(m_len>0)
        m_len = 0;
    if(m_mid_buffer != nullptr)
    {
        delete[] m_mid_buffer;
        m_mid_buffer = nullptr;
    }
    if(Plaintext != nullptr)
    {
        delete[] Plaintext;
        Plaintext = nullptr;
    }
    if(Ciphertext != nullptr)
    {
        delete[] Ciphertext;
        Ciphertext = nullptr;
    }
}

void RSASimple::setPublicKey(char *key)
{
    char se[12]={0};
    char sn[12]={0};
    int  num = 0, len = 0;

    len = strlen(key);
    num = key[len-1]-0x30;

    memcpy(se, key, num);
    memcpy(sn, key+num, len-num-1);

    this->e = strtol (se, nullptr, 16);
    this->n = strtol (sn, nullptr, 16);

    memset(pubkey, 0, sizeof(pubkey));
    sprintf(pubkey, "%s", key);
#if DEBUG
    printf("Set Public  Key (e, n):(%x, %x) key:%s\n", e, n, pubkey);
#endif
}
void RSASimple::setPrivateKey(char *key)
{
    char se[12]={0};
    char sd[12]={0};
    int  num = 0, len = 0;


    len = strlen(key);
    num = key[len-1]-0x30;

    memcpy(se, key, num);
    memcpy(sd, key+num, len-num-1);

    this->d = strtol (se, nullptr, 16);
    this->n = strtol (sd, nullptr, 16);

    memset(prikey, 0, sizeof(prikey));
    sprintf(prikey, "%s", key);
#if DEBUG
    printf("Set Private Key (d, n):(%x, %x) key:%s\n", d, n, prikey);
#endif
}

char *RSASimple::publicKey()
{
    //cout<<"Public  Key (e, n) : e = "<<e<<" n = "<<n<<'\n';
    //cout<<"Private Key (d, n) : d = "<<d<<" n = "<<n<<'\n'<<'\n';

    char se[12]={0};
    char sn[12]={0};

    memset(pubkey, 0, sizeof(pubkey));


    sprintf(se,"%x", e);
    sprintf(sn,"%x", n);

    sprintf(pubkey,"%x%x%d", e, n, strlen(se));
#if DEBUG
    printf("Get Public  Key (e, n):(%x, %x) key:%s\n", e, n, pubkey);
#endif
    return pubkey;
}
char *RSASimple::privateKey()
{
    char sd[12]={0};
    char sn[12]={0};

    memset(prikey, 0, sizeof(prikey));

    sprintf(sd,"%x", d);
    sprintf(sn,"%x", n);

    sprintf(prikey,"%x%x%d", d, n, strlen(sd));
#if DEBUG
    printf("Get Private Key (d, n):(%x, %x) key:%s\n", d, n, prikey);
#endif
    return prikey;
}

void RSASimple::generateKey()
{
    RSA_Initialize();
}

