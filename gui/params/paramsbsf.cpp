#include "paramsbsf.h"
#include "ui_paramsbsf.h"

ParamsBSF::ParamsBSF(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsBSF)
{
    ui->setupUi(this);
}

ParamsBSF::~ParamsBSF()
{
    delete ui;
}
