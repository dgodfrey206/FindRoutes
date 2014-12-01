#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "../src/algorithm/Solver.h"
#include "../src/algorithm/BSF.h"
#include "../src/algorithm/DSF.h"
#include "../src/algorithm/SimAnnealingAlg.h"


namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    Solver * getCurrentSolver();


private:

    void loadAlgorithms();

    Ui::Settings *ui;

    std::vector<Solver*> solvers;

public slots:
    void toggleVisibility();
};

#endif // SETTINGS_H
