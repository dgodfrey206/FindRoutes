#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QWidget>
#include <QTime>
#include <QFile>
#include <QTextStream>

#include <iostream>

namespace Ui {
class debugWindow;
}

class debugWindow : public QWidget
{
    Q_OBJECT

public:
    explicit debugWindow(QWidget *parent = 0);
    ~debugWindow();

    void append(const QString &str);

private:
    Ui::debugWindow *ui;

    QString getCurrentTime();
    QFile * file;
    QTextStream * stream;
private slots:
    void on_logIntoFile_pressed();
    void on_clear_pressed();
};

#endif // DEBUGWINDOW_H
