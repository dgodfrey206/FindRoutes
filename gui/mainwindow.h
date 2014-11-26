#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QFileDialog>
#include <QTime>
#include <QDate>
#include <QWebView>

#include "debugwindow.h"
#include "settings.h"

#include "../src/graph/Network.h"
#include "debugwindow.h"

#include "../src/Network.h"
#include "../src/db/DataBase.h"

#include "../src/algorithm/Solver.h"
#include "../src/algorithm/BSF.h"
#include "../src/algorithm/DSF.h"
#include "../src/algorithm/SimAnnealingAlg.h"

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

    Settings * settings;

    Network * network;

    QString apiKey;

private slots:
    void manageDebugWindow();
    void loadFromFile(DataBase::LoadMethod m);
    void showHelp();

    void findRoute();
    Ui::MainWindow *ui;

    Ui::MainWindow *ui;

    debugWindow * debug;

    Network * network;

private slots:
    void manageDebugWindow();
    void loadFromFile();
    void showHelp();

    void findRoute();

    void loadGTFS();
    void loadJSON();
    void loadMulJSON();
    void loadSavedDB();

    void showRouteOnMap(Route * r);
};

#endif // MAINWINDOW_H
