#ifndef PARAMSDSF_H
#define PARAMSDSF_H

#include <QWidget>

namespace Ui {
class ParamsDSF;
}

class ParamsDSF : public QWidget
{
    Q_OBJECT

public:
    explicit ParamsDSF(QWidget *parent = 0);
    ~ParamsDSF();

private:
    Ui::ParamsDSF *ui;
};

#endif // PARAMSDSF_H
