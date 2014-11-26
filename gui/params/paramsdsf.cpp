#include "paramsdsf.h"
#include "ui_paramsdsf.h"

ParamsDSF::ParamsDSF(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsDSF)
{
    ui->setupUi(this);
}

ParamsDSF::~ParamsDSF()
{
    delete ui;
}
