#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QFileDialog>
#include <QTime>
#include <QDate>
#include <QWebView>

#include "debugwindow.h"

#include "../src/graph/Network.h"

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
    void prepareMap();//loads api key from API_KEY file and prepares map of city
    void updateMap();//refreshes map
    Ui::MainWindow *ui;

    debugWindow * debug;

    Network * network;

    QString apiKey;

private slots:
    void manageDebugWindow();
    void loadFromFile();
    void showHelp();

    void findRoute();
};

#endif // MAINWINDOW_H
