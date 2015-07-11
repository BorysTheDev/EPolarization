#include <iostream>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <windows.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scatterers.h"
//#include "QsLog.h "


struct MainWindow::State {
    int calc = 1;
    Axis * axis;
    QGraphicsScene * scene;
    std::vector< IScatterer* > scatterers;
    double shiftX ;
    double shiftY ;
    double scale;
    double pixelPerUnit;
    double xMin = -10;
    double yMin = -10;
    double xMax = 10;
    double yMax = 10;
    int ellipseCalc;
    int lineCalc;
    State() {
        ellipseCalc = 0;
        lineCalc = 0;
        scale = 1;
        shiftX = 2;
        shiftY = 0;
        pixelPerUnit = 30;
    }

};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    state( new State ) {

    //QLOG_DEBUG() <<"MainWindow constructor";
    ui->setupUi(this);
    state->scene = new QGraphicsScene;
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();
    QRect sceneRect( 0, 0, width, height );
    state->scene->setSceneRect( sceneRect );
    ui->graphicsView->setScene( state->scene );

    ui->graphicsView->setSceneRect( sceneRect );

    recalcSceneParam();

    state->axis = new Axis();

    QObject::connect( ui->graphicsView, SIGNAL( viewIsChanged() ), this, SLOT( changeSceneParam() ) );
    repaintScene();
    //showMaximized();   // QGraphicsView width =100. If I resize, or click on graphicsView - width became adequate
                         // emulate click on graphicsView??

}

MainWindow::~MainWindow() {
    delete ui;
    delete state->scene;
    delete state;
}

void MainWindow::changeSceneParam() {
    state->scale = ui->graphicsView->scale;
    state->shiftX += -2*( ui->graphicsView->shiftSceneX / ( state->pixelPerUnit * state->scale ) );
    state->shiftY += 2*( ui->graphicsView->shiftSceneY / ( state->pixelPerUnit * state->scale ) );

    repaintScene();
}


void MainWindow::mousePressEvent( QMouseEvent *event ){
    //QLOG_DEBUG() << "MainWindow::mousePressEvent";
}

void MainWindow::resizeEvent( QResizeEvent *event ) {
    //QLOG_DEBUG() << "MainWindow::resizeEvent";
    QMainWindow::resizeEvent( event );
    repaintScene();
}

void MainWindow::on_pushButtonArc_clicked() {
    //QLOG_DEBUG() <<"MainWindow::on_pushButtonArc_clicked()";
    state->ellipseCalc++;
    QRectF rect( -2, 1, 2, 2);
    EllipseScatterer * scatterer = new EllipseScatterer( "EllipseArcScatterer" + QString::number( state->ellipseCalc ), rect, 0.0, 180.0, 0 );
    state->scatterers.push_back( scatterer );
    recalcSceneParam();
    scatterer->paint( state->scene, state->xMin, state->xMax, state->yMin, state->yMax );
    //state->scene->addItem( scatterer );
    // QGraphicsPathItem item;

}

void MainWindow::on_pushButtonLine_clicked() {
    //QLOG_DEBUG() <<"MainWindow::on_pushButtonLine_clicked()";
    state->lineCalc++;
    LineScatterer * scatterer = new LineScatterer( "LineScatterer" + QString::number( state->lineCalc ), -1, -1, 1, 1 );
    state->scatterers.push_back( scatterer );
    recalcSceneParam();
    scatterer->paint( state->scene, state->xMin, state->xMax, state->yMin, state->yMax );
}

void MainWindow::recalcSceneParam() {
    //QLOG_DEBUG() <<"MainWindow::recalcSceneParam()";
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();

    state->xMin = -0.5*width / ( state->pixelPerUnit*state->scale ) + state->shiftX/2;
    state->xMax = 0.5*width / ( state->pixelPerUnit*state->scale ) + state->shiftX/2;
    state->yMin = -0.5*height / ( state->pixelPerUnit*state->scale ) + state->shiftY/2;
    state->yMax = 0.5*height / ( state->pixelPerUnit*state->scale ) + state->shiftY/2;
}

void MainWindow::repaintScene() {
    //QLOG_DEBUG() <<"MainWindow::repaintScene()";
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();
    //QLOG_INFO() << "width = " << width;
    QRect sceneRect( 0, 0, width, height );
    state->scene->setSceneRect( sceneRect );
    ui->graphicsView->setSceneRect( sceneRect );

    recalcSceneParam();

    state->axis->stepX = state->pixelPerUnit;
    state->axis->stepY = state->pixelPerUnit;
    state->axis->clear();
    state->axis->paint( state->scene, state->xMin, state->xMax, state->yMin, state->yMax );
    for ( IScatterer * scatterer : state->scatterers ) {
        scatterer->paint( state->scene, state->xMin, state->xMax, state->yMin, state->yMax );
    }
}

void MainWindow::on_checkBoxGrid_clicked() {
    //QLOG_DEBUG() << "MainWindow::on_checkBoxGrid_clicked()";
    if ( ui->checkBoxGrid->isChecked() ) {
        state->axis->setGrid( true );
        repaintScene();
    }
    else {
        state->axis->setGrid( false );
        repaintScene();
    }
}

