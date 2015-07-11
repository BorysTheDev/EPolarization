#include "emgraphicsview.h"
//#include "QsLog.h "

#include <QGraphicsItem>

struct EMgraphicsView::State {
    bool isMousePressed;
    double fixedX;
    double fixedY;
    State() {
        isMousePressed = false;
        fixedX = 0;
        fixedY = 0;
    }
};

EMgraphicsView::EMgraphicsView( QWidget *parent ) : QGraphicsView( parent ), state( new State ) {
    //QLOG_DEBUG() << " EMgraphicsView constructor";
    scale = 1;
    setCursor( Qt::SizeAllCursor );
    shiftSceneX = 0;
    shiftSceneY = 0;
    lower();
}

EMgraphicsView:: ~EMgraphicsView() {
    //QLOG_DEBUG() << " EMgraphicsView destructor";
}

void EMgraphicsView::wheelEvent( QWheelEvent *event ) {
    //QLOG_DEBUG() << " EMgraphicsView wheelEvent";
    int direction = event->angleDelta().y();
    //QLOG_INFO() << " direction = " << direction;
    ( direction > 0) ? scale*=2 : scale/=2;
    emit viewIsChanged();
}

void EMgraphicsView::mousePressEvent( QMouseEvent *event ) {
    QGraphicsView::mousePressEvent( event );
        if ( event->buttons() == Qt::LeftButton ) {
        //QLOG_DEBUG() << "EMgraphicsView::mousePressEvent : LeftButton";

        QPointF point = mapToScene( event->pos() );
        //QLOG_INFO() << " EMgraphicsView::mousePressEvent : point.x() = " << point.x();
        //QLOG_INFO() << " EMgraphicsView::mousePressEvent : point.y() = " <<  point.y();

        bool isItemUnderCursor = false;

        QGraphicsItem * item = scene()->itemAt( point, QTransform() );
       if ( item != nullptr ) {
          // if ( item->contains( point ) )  {

               //QLOG_INFO() << "item is under cursor";
               isItemUnderCursor = true;
          // }
       }
       if ( !isItemUnderCursor ) {
           state->isMousePressed = true;
           state->fixedX = event->pos().x();
           state->fixedY = event->pos().y();
       }
        //QLOG_INFO() << " state->isMousePressed = " <<  state->isMousePressed;
    }
}

void EMgraphicsView::mouseReleaseEvent( QMouseEvent *event ) {
    //QLOG_DEBUG() << "EMgraphicsView::mouseReleaseEvent";
    QGraphicsView::mouseReleaseEvent( event );
    state->isMousePressed = false;
}

void EMgraphicsView::mouseMoveEvent( QMouseEvent *event ) {
     QGraphicsView::mouseMoveEvent( event );
     if ( state->isMousePressed ) {
         shiftSceneX = event->pos().x() - state->fixedX;
         shiftSceneY = event->pos().y() - state->fixedY;
         //QLOG_INFO() << " EMgraphicsView:: shiftSceneX = " << shiftSceneX;
         //QLOG_INFO() << " EMgraphicsView:: shiftSceneY = " << shiftSceneY;
         emit viewIsChanged();
         state->fixedX = event->pos().x();
         state->fixedY = event->pos().y();
     }
}
