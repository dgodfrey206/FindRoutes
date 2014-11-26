#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    this->loadAlgorithms();

    //connect(this->ui->algorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(updateParamsView()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::toggleVisibility()
{
    this->setVisible(!this->isVisible());
}

void Settings::loadAlgorithms()
{
    this->ui->algorithm->addItem("Wybierz algorytm");


    this->solvers.push_back(new SimAnnealingAlg());
    this->solvers.push_back(new BsfAlg());
    this->solvers.push_back(new DsfAlg());

    for(Solver * s: this->solvers)
    {
        this->ui->algorithm->addItem(QString::fromStdString(s->getName()));
    }

}

void Settings::updateParamsView(){

}

Solver * Settings::getCurrentSolver()
{
    const unsigned index = this->ui->algorithm->currentIndex();

    if(index == 0) return NULL;

    Solver * s = this->solvers[index - 1];

    if(index == 1)
    {
        //sim ann
    }
    if(index == 2)
    {
        //bsf
    }
    if(index == 3)
    {
        //dsf
    }

    return s;
}
