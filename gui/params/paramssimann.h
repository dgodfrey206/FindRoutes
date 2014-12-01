#ifndef PARAMSSIMANN_H
#define PARAMSSIMANN_H

#include <QWidget>

namespace Ui {
class ParamsSimAnn;
}

class ParamsSimAnn : public QWidget
{
    Q_OBJECT

public:
    explicit ParamsSimAnn(QWidget *parent = 0);
    ~ParamsSimAnn();

    unsigned getT0();
    unsigned getTend();
    unsigned getIter();
    double getAlfa();

private:
    Ui::ParamsSimAnn *ui;
private slots:
    void updateAlphaBox();
    void updateAlphaSlider();
};

#endif // PARAMSSIMANN_H
