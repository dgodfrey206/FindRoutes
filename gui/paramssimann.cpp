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
