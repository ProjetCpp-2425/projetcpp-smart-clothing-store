#ifndef MAILWINDOW_H
#define MAILWINDOW_H

#include <QWidget>

namespace Ui {
class MailWindow;
}

class MailWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MailWindow(QWidget *parent = nullptr);
    ~MailWindow();

private slots:
    void onSendMailButtonClicked();
    void onAttachmentBrowseButtonClicked();

private:
    Ui::MailWindow *ui;
};

#endif // MAILWINDOW_H
