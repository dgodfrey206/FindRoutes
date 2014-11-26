#include "paramssimann.h"
#include "ui_paramssimann.h"

ParamsSimAnn::ParamsSimAnn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsSimAnn)
{
    ui->setupUi(this);
}

ParamsSimAnn::~ParamsSimAnn()
{
    delete ui;
}

unsigned ParamsSimAnn::getT0()
{
    return this->ui->t0box->value();
}

unsigned ParamsSimAnn::getTend()
{
    return this->ui->tkbox->value();
}

unsigned ParamsSimAnn::getIter()
{
    return this->ui->iterbox->value();
}

double ParamsSimAnn::getAlfa()
{
    return this->ui->alfabox->value();
}
