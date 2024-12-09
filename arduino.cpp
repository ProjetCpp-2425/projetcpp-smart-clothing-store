#include "arduino.h"
Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}
QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifÃ©e par  arduino_uno_vendor_id
    // est connectÃ©e
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( dÃ©bit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // dÃ©bit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des donnÃ©es : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de paritÃ© optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}
int Arduino::close_arduino()
{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}
 QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
         data=serial->readAll(); //rÃ©cupÃ©rer les donnÃ©es reÃ§ues

         return data;
    }
 }
int Arduino::write_to_arduino(QByteArray d) {
     if (serial->isWritable()) {
         qint64 bytesWritten = serial->write(d);
         if (bytesWritten == -1) {
             qDebug() << "Failed to write the data to serial port";
         } else if (bytesWritten != d.size()) {
             qDebug() << "Failed to write all the data to serial port";
         } else {
             qDebug() << "Data written to serial port";
         }
     } else {
         qDebug() << "Serial port not writable";
     }
 }
QByteArray Arduino::readRFIDCardID()
{
    QByteArray receivedData = read_from_arduino_2(); // Read data from Arduino
    int newlineIndex = receivedData.indexOf('\n'); // Find newline character
    if (newlineIndex != -1) {
        QByteArray rfidData = receivedData.left(newlineIndex); // Extract RFID data
        return rfidData.trimmed(); // Trim '\r' and '\n' characters and return
    }
    return QByteArray(); // Return empty QByteArray if no newline found
}
QByteArray Arduino::read_from_arduino_2()
{
    if(serial->waitForReadyRead(1000)) { // Wait for data with timeout of 1 second
         data = serial->readAll(); // Read data from serial port
         return data;
    }
    return QByteArray(); // Return empty QByteArray if no data available
}
