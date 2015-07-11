#include "lineparamform.h"
#include "ui_lineparamform.h"
//#include "QsLog.h "

LineParamForm::LineParamForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineParamForm) {
    ui->setupUi(this);
}

LineParamForm::~LineParamForm() {
    delete ui;
}

void LineParamForm::setName ( QString name ) {
    ui->lineEditName->setText( name );
}

void LineParamForm::setX1( double x1 ) {
    ui->lineEditX1->setText( QString::number( x1, 'g', precision ) );
}

void LineParamForm::setY1( double y1 ) {
     ui->lineEditY1->setText( QString::number( y1, 'g', precision ) );
}

void LineParamForm::setX2( double x2 ) {
     ui->lineEditX2->setText( QString::number( x2, 'g', precision ) );
}

void LineParamForm::setY2( double y2 ) {
     ui->lineEditY2->setText( QString::number( y2, 'g', precision ) );
}

void LineParamForm::setParam ( double x1, double y1, double x2, double y2 ) {
    //QLOG_DEBUG() << "LineParamForm::setParam";
    setX1( x1 );
    setX2( x2 );
    setY1( y1 );
    setY2( y2 );
}

LineParam LineParamForm::getParam() {
    //QLOG_DEBUG() << "LineParamForm::getParam()";
    LineParam param;
    param.x1 = ui->lineEditX1->text().toDouble();
    param.y1 = ui->lineEditY1->text().toDouble();
    param.x2 = ui->lineEditX2->text().toDouble();
    param.y2 = ui->lineEditY2->text().toDouble();
    return param;
}

void LineParamForm::on_lineEditX1_editingFinished() {
    //QLOG_DEBUG() << "on_lineEditX1_editingFinished";
    emit paramIsChanged();
}

void LineParamForm::on_lineEditX2_editingFinished() {
    //QLOG_DEBUG() << "on_lineEditX2_editingFinished";
    emit paramIsChanged();
}

void LineParamForm::on_lineEditY1_editingFinished() {
    //QLOG_DEBUG() << "on_lineEditY1_editingFinished";
    emit paramIsChanged();
}

void LineParamForm::on_lineEditY2_editingFinished() {
    //QLOG_DEBUG() << "on_lineEditY2_editingFinished";
    emit paramIsChanged();
}
