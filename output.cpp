#include "output.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPushButton>
#include <QLineEdit>
#include "connection.h"

void onButtonClicked(QPushButton *button, QSerialPort *serial, QLineEdit *codeDisplay)
{
    QString buttonText = button->text();

    if (buttonText == "Enter") {
        QString enteredCode = codeDisplay->text();

        // Establish the database connection using the Connection class
        if (!Connection::getInstance().createConnect()) {
            QMessageBox::critical(nullptr, "Error", "Failed to connect to the database.");
            return;
        }

        QSqlQuery query;

        // Check if the code exists in the database
        query.prepare("SELECT park FROM vehicule WHERE code = :enteredCode");
        query.bindValue(":enteredCode", enteredCode);

        if (query.exec()) {
            if (query.next()) {
                int parkStatus = query.value(0).toInt();

                if (parkStatus == 0) {
                    // Update the park status to 1 (vehicle enters the parking lot)
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE vehicule SET park = 1 WHERE code = :enteredCode");
                    updateQuery.bindValue(":enteredCode", enteredCode);

                    if (updateQuery.exec()) {
                        QMessageBox::information(nullptr, "Success", "Code accepted! Gate is now open.");

                        // Send a signal to Arduino to activate the ultrasonic sensor
                        serial->write("1");  // Send '1' to Arduino (to activate sensor)
                    } else {
                        QMessageBox::critical(nullptr, "Error", "Failed to update park status: " + updateQuery.lastError().text());
                    }
                } else {
                    QMessageBox::warning(nullptr, "Error", "This vehicle is already in the parking lot!");
                }
            } else {
                QMessageBox::warning(nullptr, "Error", "Invalid code. Please try again.");

                // Send a signal to Arduino to flicker the red LED for wrong code
                serial->write("2");  // Send '2' to Arduino (to flicker red LED)
            }
        } else {
            QMessageBox::critical(nullptr, "Error", "Database query failed: " + query.lastError().text());
        }

        // Clear the display after checking
        codeDisplay->clear();
    }
}
