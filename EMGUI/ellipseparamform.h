#ifndef ELLIPSEPARAMFORM_H
#define ELLIPSEPARAMFORM_H

#include "scatterersparam.h"

#include <QWidget>

namespace Ui {
class EllipseParamForm;
}

class EllipseParamForm : public QWidget
{
    Q_OBJECT

public:
    explicit EllipseParamForm(QWidget *parent = 0);
    ~EllipseParamForm();
    void setName ( QString name );
    void setXleftTop( double xLeftTop );
    void setYleftTop( double yLeftTop );
    void setWidth( double width );
    void setHeight( double height );
    void setStartAngle( double startAngle );
    void setSpanAngle( double spanAngle );
    virtual void setRotationAngle( double rotationAngle );
    void setParam ( double xLeftTop, double yLeftTop, double width, double height, double startAngle, double spanAngle , double rotationAngle );
    EllipseParam getParam();
    int precision = 4;
private slots:
    void on_lineEditStartAngle_editingFinished();
    void on_lineEditSpanAngle_editingFinished();

    void on_lineEditXleftTop_editingFinished();

    void on_lineEditYleftTop_editingFinished();

    void on_lineEditWidth_editingFinished();

    void on_lineEditHeight_editingFinished();

    void on_lineEditRotationAngle_editingFinished();

signals:
    void paramIsChanged();

private:
    Ui::EllipseParamForm *ui;
};

#endif // ELLIPSEPARAMFORM_H
