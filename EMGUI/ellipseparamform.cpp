#include "ellipseparamform.h"
#include "ui_ellipseparamform.h"
//#include "QsLog.h "

EllipseParamForm::EllipseParamForm( QWidget *parent ) :
  //  QWidget(parent),
    ui(new Ui::EllipseParamForm) {
    ui->setupUi(this);
    //QLOG_DEBUG() << "EllipseParamForm constructor";
}

EllipseParamForm::~EllipseParamForm() {
    delete ui;
}

void EllipseParamForm::setName ( QString name ) {
    ui->lineEditName->setText( name );
}

void EllipseParamForm::setXleftTop( double xLeftTop ) {
    ui->lineEditXleftTop->setText( QString::number( xLeftTop, 'g', precision ) );
}

void EllipseParamForm::setYleftTop( double yLeftTop ) {
    ui->lineEditYleftTop->setText( QString::number( yLeftTop, 'g', precision ) );
}

void EllipseParamForm::setWidth( double width ) {
    ui->lineEditWidth->setText( QString::number( width, 'g', precision ) );
}

void EllipseParamForm::setHeight( double height ) {
    ui->lineEditHeight->setText( QString::number( height, 'g', precision ) );
}

void EllipseParamForm::setStartAngle( double startAngle ) {
    ui->lineEditStartAngle->setText( QString::number( startAngle, 'g', precision ) );
}

void EllipseParamForm::setSpanAngle( double spanAngle ) {
    ui->lineEditSpanAngle->setText( QString::number( spanAngle, 'g', precision ) );
}

void EllipseParamForm::setRotationAngle( double rotationAngle ) {
    ui->lineEditRotationAngle->setText( QString::number( rotationAngle, 'g', precision ) );
}

void EllipseParamForm::setParam (double xLeftTop, double yLeftTop, double width, double height, double startAngle, double spanAngle, double rotationAngle ) {
    //QLOG_DEBUG() << "EllipseParamForm::setParam";
    setXleftTop( xLeftTop );
    setYleftTop( yLeftTop );
    setWidth( width );
    setHeight( height );
    setStartAngle( startAngle );
    setSpanAngle( spanAngle );
    setRotationAngle( rotationAngle );
}

EllipseParam EllipseParamForm::getParam() {
    //QLOG_DEBUG() << "EllipseParamForm::getParam()";
    EllipseParam param;
    double x = ui->lineEditXleftTop->text().toDouble();
    double y = ui->lineEditYleftTop->text().toDouble();
    double width = ui->lineEditWidth->text().toDouble();
    double height = ui->lineEditHeight->text().toDouble();
    param.rect = QRectF ( x, y, width, height );
    param.startAngle = ui->lineEditStartAngle->text().toDouble();
    param.spanAngle = ui->lineEditSpanAngle->text().toDouble();
    param.rotationAngle = ui->lineEditRotationAngle->text().toDouble();
    return param;
}

void EllipseParamForm::on_lineEditStartAngle_editingFinished() {
    //QLOG_DEBUG() << "EllipseParamForm::on_lineEditStartAngle_editingFinished()";
    emit paramIsChanged();
}

void EllipseParamForm::on_lineEditSpanAngle_editingFinished() {
    //QLOG_DEBUG() << "EllipseParamForm::on_lineEditSpanAngle_editingFinished()";
    emit paramIsChanged();
}

void EllipseParamForm::on_lineEditXleftTop_editingFinished() {
    //QLOG_DEBUG() << "EllipseParamForm::on_lineEditXleftTop_editingFinished()";
    emit paramIsChanged();
}

void EllipseParamForm::on_lineEditYleftTop_editingFinished() {
    //QLOG_DEBUG() << "EllipseParamForm::on_lineEditYleftTop_editingFinished()";
    emit paramIsChanged();
}

void EllipseParamForm::on_lineEditWidth_editingFinished() {
    //QLOG_DEBUG() << "EllipseParamForm::on_lineEditWidth_editingFinished()";
    emit paramIsChanged();
}

void EllipseParamForm::on_lineEditHeight_editingFinished() {
    //QLOG_DEBUG() << "EllipseParamForm::on_lineEditHeight_editingFinished()";
    emit paramIsChanged();
}

void EllipseParamForm::on_lineEditRotationAngle_editingFinished() {
    //QLOG_DEBUG() << "EllipseParamForm::on_lineEditRotationAngle_editingFinished()";
    emit paramIsChanged();
}
