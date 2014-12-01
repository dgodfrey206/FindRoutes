#include "paramssimann.h"
#include "ui_paramssimann.h"

ParamsSimAnn::ParamsSimAnn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsSimAnn)
{
    ui->setupUi(this);

    connect(this->ui->alfabox, SIGNAL(valueChanged(double)), this, SLOT(updateAlphaSlider()));
    connect(this->ui->alfaslider, SIGNAL(valueChanged(int)), this, SLOT(updateAlphaBox()));
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

void ParamsSimAnn::updateAlphaBox()
{
    this->ui->alfabox->setValue(this->ui->alfaslider->value() / double(10000));
}

void ParamsSimAnn::updateAlphaSlider()
{
    this->ui->alfaslider->setValue(this->ui->alfabox->value() * 10000);
}
