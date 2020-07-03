#include "mainwindow.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

MainWinwow::MainWinwow(QObject *parent)
{
    init();
}

QString MainWinwow::doSendRsa(int nbits, int ebits)
{
    m_pRsa->generateKey(nbits, ebits);
    m_pRsa->getKey(RSA::PublicKey,  pub_e, pub_n);
    m_pRsa->getKey(RSA::PrivateKey, pri_d, pri_n);

    QString str = QString("%1,\n%2&%3,\n%4")
                      .arg(QString(pub_e.c_str()))
                      .arg(QString(pub_n.c_str()))
                      .arg(QString(pri_d.c_str()))
                      .arg(QString(pri_n.c_str()));
    return str;
}

QString MainWinwow::doEncypt(QString text)
{
    m_pRsa->setKey(RSA::PrivateKey, pri_d, pri_n);
    QByteArray hex;
    QString strhex = hex.append(text).toHex();
    string enc = m_pRsa->Encrypt(strhex.toStdString(), 16);
    return QString::fromStdString(enc);

}

QString MainWinwow::doDecypt(QString text)
{
    m_pRsa->setKey(RSA::PublicKey,pub_e,pub_n);
    string enc = m_pRsa->Decrypt(text.toStdString(), 16);
    //将16进制字符串转为字符串
    QString strhex = QString::fromStdString(enc);
    QByteArray hex;
    hex.append(strhex);
    QByteArray str = QByteArray::fromHex(hex);
    return str;
}


void MainWinwow::init()
{
    m_pEnger = new QQmlApplicationEngine(this);

    m_pEnger->rootContext()->setContextProperty("MainWindow",this);
    m_pEnger->load(QUrl(QStringLiteral("qrc:/main.qml")));

    m_pRsa = new RSA;
    m_pRsa_simple = new RSASimple;
}

