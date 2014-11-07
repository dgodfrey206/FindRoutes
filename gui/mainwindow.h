#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QWindow>
#include <QFileDialog>
#include <QTime>
#include <QDate>
#include <QWebView>

#include "debugwindow.h"

#include "../src/graph/Network.h"
=======
>>>>>>> aadf5d30... QT GUI init commit

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
<<<<<<< HEAD

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
=======
    Ui::MainWindow *ui;
>>>>>>> aadf5d30... QT GUI init commit
};

#endif // MAINWINDOW_H
