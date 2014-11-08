#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QFileDialog>
#include <QTime>
#include <QDate>

#include "debugwindow.h"

#include "../src/Network.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void setupActions();

    void prepareGUI();//called after loading from file

    Ui::MainWindow *ui;

    debugWindow * debug;

    Network * network;

private slots:
    void manageDebugWindow();
    void loadFromFile();
    void showHelp();

    void findRoute();
};

#endif // MAINWINDOW_H
