#ifndef MINWINDOW_H
#define MINWINDOW_H
#include <QObject>
#include "rsa.h"
#include "rsa_simple.h"

class QQmlApplicationEngine;

class MainWinwow : public QObject{
    Q_OBJECT
public:
    explicit MainWinwow(QObject* parent = nullptr);
    Q_INVOKABLE QString doSendRsa(int nbits,int ebits);
    Q_INVOKABLE QString doEncypt(QString);
    Q_INVOKABLE QString doDecypt(QString);

private:
    void init();


private:
    QQmlApplicationEngine* m_pEnger = nullptr;
    RSA*                   m_pRsa = nullptr;
    RSASimple*             m_pRsa_simple = nullptr;
    string                 pub_e, pub_n, pri_d, pri_n;

};

#endif // MINWINDOW_H
