#ifndef LINEPARAMFORM_H
#define LINEPARAMFORM_H

#include <QWidget>

#include "scatterersparam.h"

namespace Ui {
class LineParamForm;
}

class LineParamForm : public QWidget
{
    Q_OBJECT

public:
    explicit LineParamForm(QWidget *parent = 0);
    ~LineParamForm();
    void setName ( QString name );
    void setX1( double x1 );
    void setY1( double y1 );
    void setX2( double x2 );
    void setY2( double y2 );
    void setParam ( double x1, double y1, double x2, double y2 );
    LineParam getParam();
    int precision = 4;
private:
    Ui::LineParamForm *ui;

signals:
    void paramIsChanged();

private slots:
    void on_lineEditX1_editingFinished();
    void on_lineEditX2_editingFinished();
    void on_lineEditY1_editingFinished();
    void on_lineEditY2_editingFinished();
};

#endif // LINEPARAMFORM_H
