#ifndef EMGRAPHICSVIEW_H
#define EMGRAPHICSVIEW_H

#include "QGraphicsView"
#include "QWheelEvent"

class EMgraphicsView : public QGraphicsView {

       Q_OBJECT

public:
    EMgraphicsView( QWidget *parent = 0 );
    virtual ~EMgraphicsView();
    double scale;
    double shiftSceneX;
    double shiftSceneY;
protected:
    void wheelEvent( QWheelEvent *event );
    void mousePressEvent( QMouseEvent * event );
    void mouseReleaseEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event);

signals:
    void viewIsChanged();

private:
    struct State;
    State * state;
};

#endif // EMGRAPHICSVIEW_H
