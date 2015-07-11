#include "scatterers.h"
#include "coor_converter.h"
//#include "QsLog.h "
#include "ellipseparamform.h"
#include "lineparamform.h"


#include <QStyle>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

//----------------------------------------------BASIC-------------------------------------------------------------

struct BasicScatterer::State {
    QString name;
    double rotationAngle;
    QRectF rect;
    QPen defaultPen;
    QPen dragPen;
    bool isAdded;
    int posX;       //for drag mode
    int posY;       //for drag mode
    bool rotationMode;  // rotation if right buttom is pressed and mouse is moved up-down
    State() {
        defaultPen = QPen( Qt::black, 3 );
        dragPen = QPen( Qt::red, 3 );
        isAdded = false;
        posX = 0;
        posY = 0;
        rotationMode = false;
    }
    QGraphicsScene * scene;
    QRectF boundingRectBeforeDrag;
    double xMin;
    double yMin;
    double xMax;
    double yMax;
    QGraphicsEllipseItem * mark;
};

BasicScatterer::BasicScatterer( QString name ) : state ( new State ) {
    //QLOG_DEBUG() << "BasicScatterer constructor";
    state->name = name;
    setPen( state->defaultPen );
    setFlag(QGraphicsItem::ItemIsMovable);
    setCursor(Qt::OpenHandCursor);
}

BasicScatterer::BasicScatterer( QString name, QRectF &rect, double rotationAngle ) : BasicScatterer( name ) {
    //QLOG_DEBUG() << "BasicScatterer constructor";
    state->name = name;
    state->rotationAngle = rotationAngle;
    state->rect = rect;

}

BasicScatterer::~BasicScatterer( ) {
    delete state;
}

void BasicScatterer::setRect( const QRectF & rect ) {
    state->rect = rect;
}


void BasicScatterer::setRotationAngle( double rotationAngle) {
    state->rotationAngle = rotationAngle;
}

QRectF BasicScatterer::getRect() {
    return state->rect;
}

void BasicScatterer::mousePressEvent( QGraphicsSceneMouseEvent * event ) {
    //QLOG_DEBUG() << "BasicScatterer::mousePressEvent";
    state->mark = new QGraphicsEllipseItem( );
    state->mark->setPen( QPen( Qt::red ) );
    state->scene->addItem( state->mark );

    if ( event->buttons() == Qt::LeftButton ) {
        //QLOG_INFO() << "EllipseScatterer::mousePressEvent : LeftButton";
        setPen( state->dragPen );
        setCursor( Qt::ClosedHandCursor );
        showLeftTop();
    }
    else if ( event->buttons() == Qt::RightButton ) {
        setCursor( Qt::SizeVerCursor );
        //QLOG_INFO() << "EllipseScatterer::mousePressEvent : RightButton";
        state->rotationMode = true;
        showCenter();
    }
}

// after mouse is released we calc coordinates of the arc using scene coordinates (in pixels)
// the main problem is 1)knowing only relative shift ( parebt is the path in initial position)
//                     2)knowing only rect bounding arc not full ellipse
void BasicScatterer::mouseReleaseEvent( QGraphicsSceneMouseEvent *event ) {
    //QLOG_DEBUG() << "BasicScatterer::mouseReleaseEvent";
    QAbstractGraphicsShapeItem::mouseReleaseEvent( event );
    setPen( state->defaultPen );
    setCursor( Qt::OpenHandCursor );

    if ( state->mark != nullptr ) {
        delete state->mark;
        state->mark = nullptr;
    }
    state->rotationMode = false;
}

void BasicScatterer::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
     QAbstractGraphicsShapeItem::mouseMoveEvent( event );
     //QLOG_DEBUG() << " BasicScatterer::mouseMoveEvent" ;
     if ( event->buttons() == Qt::LeftButton ) {
         //QLOG_INFO() << " EllipseScatterer::mouseMoveEvent : LeftButton" ;
         QRectF boundingRectAfterDrag = sceneBoundingRect();

        // state->scene->addRect( state->boundingRectBeforeDrag );
        // state->scene->addRect( boundingRectAfterDrag );

         double shiftWidthScene =  boundingRectAfterDrag.x() - state->boundingRectBeforeDrag.x();
         double shiftHeightScene = - boundingRectAfterDrag.y() + state->boundingRectBeforeDrag.y();
         double shiftWidth = getWidth( shiftWidthScene, state->xMin, state->xMax, state->scene->width() );
         double shiftHeight = getHeight( shiftHeightScene, state->yMin, state->yMax, state->scene->height() );
         double newX = state->rect.x() + shiftWidth;
         double newY = state->rect.y() + shiftHeight;

         //QLOG_INFO() << "newX = " << newX;
         //QLOG_INFO() << "newY = " << newY;

         state->rect = QRectF( newX, newY, state->rect.width(), state->rect.height() );
         state->posX =  pos().x();
         state->posY =  pos().y();
         state->boundingRectBeforeDrag = sceneBoundingRect();

         setFormXY( newX, newY );

         showLeftTop();
     }
     else if ( event->buttons() == Qt::RightButton ) {
        //QLOG_INFO() << " EllipseScatterer::mouseMoveEvent : RightButton" ;

        if ( state->rotationMode ) {
            //QLOG_INFO() << "event->scenePos().y() = " << event->scenePos().y();
            //QLOG_INFO() << "event->lastScenePos().y() = " << event->lastScenePos().y();

            double deltaAngle = event->scenePos().y() - event->lastScenePos().y();
            //state->rotationAngle += event->scenePos().y() - event->lastScenePos().y();
            paint( state->scene, state->xMin, state->xMax, state->yMin, state->yMax );
           // setFormAngle(  state->rotationAngle );
            setFormAngle(  deltaAngle );
            showCenter();
        }
     }
}

void BasicScatterer::mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event ) {
    //QLOG_DEBUG() << "BasicScatterer::mouseDoubleClickEvent";
    formShow();
}

void BasicScatterer::showLeftTop() {
    double leftTopXscene = getXscene( state->rect.x(), state->xMin, state->xMax, state->scene->width() );
    double leftTopYscene = getYscene( state->rect.y(), state->yMin, state->yMax, state->scene->height() );
    double rad = 3;
    state->mark->setRect( leftTopXscene - rad, leftTopYscene - rad, 2*rad, 2*rad );
}

void BasicScatterer::showCenter() {
    double centerXscene = getXscene( state->rect.x() + state->rect.width()/2, state->xMin, state->xMax, state->scene->width() );
    double centerYscene = getYscene( state->rect.y() - state->rect.height()/2, state->yMin, state->yMax, state->scene->height() );
    double rad = 3;
    state->mark->setRect( centerXscene - rad, centerYscene - rad, 2*rad, 2*rad );
}


//----------------------------------------------ELLIPSE-------------------------------------------------------------

struct EllipseScatterer::InnerState {
    double startAngle;
    double spanAngle;
    EllipseParamForm form;
};

EllipseScatterer::EllipseScatterer( QString name, QRectF &rect, double startAngle, double spanAngle, double rotationAngle ) :
    BasicScatterer( name, rect, rotationAngle ), innerState( new InnerState ) {
    //QLOG_DEBUG() << "EllipseScatterer2 constructor";
    innerState->form.setName( name );
    innerState->startAngle = startAngle;
    innerState->spanAngle = spanAngle;
    innerState->form.setWindowFlags( Qt::WindowStaysOnTopHint );
    innerState->form.setParam( rect.x(), rect.y(), rect.width(), rect.height(), startAngle, spanAngle, rotationAngle );

    QObject::connect( &innerState->form, SIGNAL( paramIsChanged() ), this, SLOT( setParamFromWidget() ) );
}

EllipseScatterer::~EllipseScatterer() {
    //QLOG_DEBUG() << "EllipseScatterer2 deconstructor";
    delete innerState;
}

void EllipseScatterer::paint ( QGraphicsScene * scene, double xMin, double xMax, double yMin, double yMax ) {
    //QLOG_DEBUG() << "EllipseScatterer::paint";
    innerState->form.show();
    state->xMax = xMax;
    state->yMax = yMax;
    state->xMin = xMin;
    state->yMin = yMin;
    state->scene = scene;

    double x = getXscene( state->rect.x(), xMin, xMax, scene->width() );
    double y = getYscene( state->rect.y(), yMin, yMax, scene->height() );
    double width = getWidthOnScene( state->rect.width(), xMin, xMax, scene->width() );
    double height = getHeightOnScene( state->rect.height(),  yMin, yMax, scene->height() );

    QRectF rectScene( x - state->posX, y - state->posY, width, height ); // if we drug on ( delta_x, delta_y ) then  origin shift on ( delta_x, delta_y ) - I DON'T KNOW WHY!
    QPainterPath path_;
    path_.arcMoveTo( rectScene, innerState->startAngle );
    path_.arcTo( rectScene, innerState->startAngle , innerState->spanAngle );
    setPath( path_ );

    setTransformOriginPoint( x + width/2 - state->posX, y + height/2 - state->posY );  //posX, posY - because of mouse drag
    setRotation( state->rotationAngle );

    if ( !state->isAdded ) {
        scene->addItem( this );
        state->isAdded = true;
    }
    state->boundingRectBeforeDrag = sceneBoundingRect();

}
void EllipseScatterer::setParamFromWidget( ) {
    //QLOG_DEBUG() << "EllipseScatterer::setParamFromWidget";
    EllipseParam param = innerState->form.getParam();
    setRect( param.rect );
    setStartAngle( param.startAngle );
    setSpanAngle( param.spanAngle );
    setRotationAngle( param.rotationAngle );
    paint( state->scene, state->xMin, state->xMax, state->yMin, state->yMax );
}

void EllipseScatterer::setFormXY( double x, double y ) {
    innerState->form.setXleftTop( x );
    innerState->form.setYleftTop( y );
}

void EllipseScatterer::setFormAngle( double deltaAngle ) {
    state->rotationAngle += deltaAngle;
    innerState->form.setRotationAngle( state->rotationAngle );
}
void EllipseScatterer::formShow ( ) {
    innerState->form.close();
    innerState->form.show();
}

void EllipseScatterer::setStartAngle( double angle ) {
    innerState->startAngle = angle;
}

void EllipseScatterer::setSpanAngle( double angle) {
    innerState->spanAngle = angle;
}


//----------------------------------------------LINE-------------------------------------------------------------

struct LineScatterer::InnerState {
    double x1;
    double y1;
    double x2;
    double y2;
    LineParamForm form;
};

LineScatterer::LineScatterer( QString name, double x1, double y1, double x2, double y2 ) : BasicScatterer( name ), innerState( new InnerState ) {
    //QLOG_DEBUG() << "LineScatterer constructor";
    innerState->form.setWindowFlags( Qt::WindowStaysOnTopHint );
    innerState->x1 = x1;
    innerState->y1 = y1;
    innerState->x2 = x2;
    innerState->y2 = y2;
    innerState->form.setParam( x1, y1, x2, y2 );
    innerState->form.setName( name );
    state->rect = getLineRect( x1, y1, x2, y2 );
    QObject::connect( &innerState->form, SIGNAL( paramIsChanged() ), this, SLOT( setParamFromWidget() ) );
}

LineScatterer::~LineScatterer() {
    //QLOG_DEBUG() << "LineScatterer deconstructor";
    delete innerState;
}

void LineScatterer::paint ( QGraphicsScene * scene, double xMin, double xMax, double yMin, double yMax ) {
    //QLOG_DEBUG() << "LineScatterer::paint";
    innerState->form.show();
    state->xMax = xMax;
    state->yMax = yMax;
    state->xMin = xMin;
    state->yMin = yMin;
    state->scene = scene;

    double x1Scene = getXscene( innerState->x1, xMin, xMax, scene->width() ) - state->posX;
    double y1Scene = getYscene( innerState->y1, yMin, yMax, scene->height() ) - state->posY;
    double x2Scene = getXscene( innerState->x2, xMin, xMax, scene->width() ) - state->posX;
    double y2Scene = getYscene( innerState->y2,  yMin, yMax, scene->height() ) - state->posY;

    QPainterPath path_;
    path_.moveTo( x1Scene, y1Scene );
    path_.lineTo( x2Scene, y2Scene );

    setPath( path_ );

    setTransformOriginPoint( (x1Scene + x2Scene) / 2, ( y1Scene + y2Scene ) / 2 );  //posX, posY - because of mouse drag
   // setRotation( state->rotationAngle );

    double angle = calcAngle();
    //QLOG_INFO() << "angle = " << angle;

    if ( !state->isAdded ) {
        scene->addItem( this );
        state->isAdded = true;
    }
    state->boundingRectBeforeDrag = sceneBoundingRect();
}

void LineScatterer::setParamFromWidget( ) {
    //QLOG_DEBUG() << "EllipseScatterer::setParamFromWidget";
    LineParam param = innerState->form.getParam();
    innerState->x1 = param.x1;
    innerState->y1 = param.y1;
    innerState->x2 = param.x2;
    innerState->y2 = param.y2;
    state->rect = getLineRect( param.x1, param.y1, param.x2, param.y2 );

    //setRect()
//    setRect( param.rect );
//    setRotationAngle( param.rotationAngle );
    paint( state->scene, state->xMin, state->xMax, state->yMin, state->yMax );
}

void LineScatterer::setFormXY( double x, double y ) {  //in addition we change innerState->x1,x2,,y1,y2 here
    LineParam param = innerState->form.getParam();
    QRectF oldRect = getLineRect( param.x1, param.y1, param.x2, param.y2 );
    double xDelta = x - oldRect.x();
    double yDelta = y - oldRect.y();
    double newX1 =  param.x1 + xDelta;
    double newY1 = param.y1 + yDelta;
    double newX2 = param.x2 + xDelta;
    double newY2 =  param.y2 + yDelta;
    innerState->form.setX1(  newX1 );
    innerState->form.setY1( newY1 );
    innerState->form.setX2(  newX2 );
    innerState->form.setY2( newY2 );
    innerState->x1 = newX1;
    innerState->y1 = newY1;
    innerState->x2 = newX2;
    innerState->y2 = newY2;
    //QLOG_INFO() << "LineScatterer innerState->x1 = " << innerState->x1;
    //QLOG_INFO() << "LineScatterer innerState->y1 = " << innerState->y1;
}
double LineScatterer::calcAngle() {
    double pi = 3.14159265358979323846  ;
    double x = innerState->x2 - innerState->x1;
    double y = innerState->y2 - innerState->y1;
    double eps = 10E-10;
    if ( std::abs( x ) <= eps ) {
        if ( y > 0 ) return 90;
        else return -90;
    }
    else {
        if ( x > 0 ) return atan( y / x ) * 180 / pi;
        if ( x < 0 ) return ( pi - atan( y / (-x) ) ) * 180 / pi;
    }
}

void LineScatterer::setFormAngle( double deltaAngle ) {

    //QLOG_INFO() << "deltaAngle = " << deltaAngle;
    //state->boundingRectBeforeDrag = sceneBoundingRect();
    double pi = 3.14159265358979323846  ;
    state->rotationAngle += deltaAngle;
    double alpha = deltaAngle * pi / 180;
    double xC = ( innerState->x1 + innerState->x2 ) / 2;
    double yC = ( innerState->y1 + innerState->y2 ) / 2;
    double oldX = innerState->x1 - xC;
    double oldY = innerState->y1 - yC;
    double x = oldX * cos( alpha ) + oldY * sin( alpha );
    double y = -oldX * sin( alpha ) + oldY * cos( alpha );
    innerState->x1 = xC + x;
    innerState->y1 = yC + y;
    innerState->x2 = xC - x;
    innerState->y2 = yC - y;
    state->rect = getLineRect( innerState->x1, innerState->y1, innerState->x2, innerState->y2 );
    innerState->form.setParam( innerState->x1, innerState->y1, innerState->x2, innerState->y2 );
    paint( state->scene, state->xMin, state->xMax, state->yMin, state->yMax );



    ////QLOG_INFO() << "angle after rotation = " << prevAngle + deltaAngle;
   // innerState->form.setRotationAngle( state->rotationAngle );
}
void LineScatterer::formShow ( ) {
    innerState->form.close();
    innerState->form.show();
}

QRectF LineScatterer::getLineRect( double x1, double y1 , double x2 , double y2 ) {
    return QRectF( std::min( x1, x2 ), std::min( y1, y2 ), std::abs( x2 - x1 ), std::abs( y2 - y1 ) );
}

void LineScatterer::showCenter() {
    double x1Scene = getXscene( innerState->x1, state->xMin, state->xMax, state->scene->width() ) ;
    double y1Scene = getYscene( innerState->y1, state->yMin, state->yMax, state->scene->height() ) ;
    double x2Scene = getXscene( innerState->x2, state->xMin, state->xMax, state->scene->width() ) ;
    double y2Scene = getYscene( innerState->y2,  state->yMin, state->yMax, state->scene->height() ) ;
    double rad = 3;
    double x = ( x1Scene + x2Scene ) / 2;
    double y = ( y1Scene + y2Scene ) / 2;
    state->mark->setRect( x - rad, y - rad, 2*rad, 2*rad );
}

void LineScatterer::showLeftTop() {
    showCenter();
}


