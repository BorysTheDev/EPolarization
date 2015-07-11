#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonArc_clicked();
    void on_pushButtonLine_clicked();
    void on_checkBoxGrid_clicked(); 
private:
    Ui::MainWindow *ui;
    struct State;
    State * state;

private slots:
    void recalcSceneParam();
    void repaintScene();
    void changeSceneParam();

protected:
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent( QResizeEvent *event);

signals:

};

#endif // MAINWINDOW_H
