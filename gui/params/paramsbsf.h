#ifndef PARAMSBSF_H
#define PARAMSBSF_H

#include <QWidget>

namespace Ui {
class ParamsBSF;
}

class ParamsBSF : public QWidget
{
    Q_OBJECT

public:
    explicit ParamsBSF(QWidget *parent = 0);
    ~ParamsBSF();

private:
    Ui::ParamsBSF *ui;
};

#endif // PARAMSBSF_H
