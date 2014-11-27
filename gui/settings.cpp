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

    if(index == 1)
    {
        SimAnnealingAlg * s = reinterpret_cast<SimAnnealingAlg *>(this->solvers[index -1]);
        s->setParams(this->ui->simann->getT0(),
                     this->ui->simann->getTend(),
                     this->ui->simann->getIter(),
                     this->ui->simann->getAlfa());

        return s;
    }
    if(index == 2)
    {
        BsfAlg * s = reinterpret_cast<BsfAlg *>(this->solvers[index - 1]);


        return s;
    }
    if(index == 3)
    {
        DsfAlg * s = reinterpret_cast<DsfAlg *>(this->solvers[index - 1]);


        return s;
    }
}
