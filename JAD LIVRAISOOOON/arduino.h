#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>


class Arduino
{
public:     //mÃ©thodes de la classe Arduino
    Arduino();
    int connect_arduino(); // permet de connecter le PC Ã  Arduino
    int close_arduino(); // permet de femer la connexion
    int write_to_arduino( QByteArray ); // envoyer des donnÃ©es vers arduino
    QByteArray read_from_arduino();  //recevoir des donnÃ©es de la carte Arduino
    QSerialPort* getserial();   // accesseur
    QString getarduino_port_name();
    QByteArray readRFIDCardID();
    QByteArray read_from_arduino_2();
private:
QSerialPort * serial; //Cet objet rassemble des informations (vitesse, bits de donnÃ©es, etc.)
//et des fonctions (envoi, lecture de rÃ©ception,â€¦) sur ce quâ€™est une voie sÃ©rie pour Arduino.
static const quint16 arduino_uno_vendor_id=9025;
static const quint16 arduino_uno_producy_id=67;
QString arduino_port_name;
bool arduino_is_available;
QByteArray data;  // contenant les donnÃ©es lues Ã  partir d'Arduino
};



#endif // ARDUINO_H
