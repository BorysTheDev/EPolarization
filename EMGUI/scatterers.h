#ifndef SCATTERERS
#define SCATTERERS

#include <QAbstractGraphicsShapeItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>

#include "axis.h"
#include "scatterersparam.h"


// scatterer coordinates are Cartesian coordinates

class IScatterer {
public:
     virtual void paint ( QGraphicsScene * scene, double xMin, double xMax, double yMin, double yMax ) = 0;
};


class BasicScatterer : public QGraphicsPathItem, public IScatterer {

public:
    BasicScatterer(QString name);
    BasicScatterer( QString name, QRectF &rect, double rotationAngle );
    virtual ~BasicScatterer();
    virtual void setRect( const QRectF & rect );
    virtual void setRotationAngle( double rotationAngle);
    virtual QRectF getRect();
    virtual void paint ( QGraphicsScene * scene, double xMin, double xMax, double yMin, double yMax ) = 0;

protected:
    virtual void setFormXY( double x, double y ) = 0;           //for drag mode
    virtual void setFormAngle( double deltaAngle ) = 0;         //for rotation mode
    virtual void formShow( ) = 0;
    virtual void mousePressEvent( QGraphicsSceneMouseEvent *event );
    virtual void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
    virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent *event );
    virtual void mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event );
    virtual void showLeftTop();
    virtual void showCenter();
    struct State;
    State * state;

};

class  EllipseScatterer : public QObject, public BasicScatterer {
    Q_OBJECT
public:
    EllipseScatterer(QString name, QRectF &rect, double startAngle, double spanAngle, double rotationAngle );
    virtual ~EllipseScatterer();
    virtual void paint ( QGraphicsScene * scene, double xMin, double xMax, double yMin, double yMax );
    virtual void setFormXY( double x, double y );
    virtual void setFormAngle( double deltaAngle );
    virtual void formShow( );
    void setStartAngle( double angle );
    void setSpanAngle( double angle);

private slots:
     virtual void setParamFromWidget( );
private:
    struct InnerState;
    InnerState * innerState;
};

class  LineScatterer : public QObject, public BasicScatterer {
    Q_OBJECT
public:
    LineScatterer( QString name, double x1, double y1 , double x2 , double y2 );
    virtual ~LineScatterer();
    virtual void paint ( QGraphicsScene * scene, double xMin, double xMax, double yMin, double yMax );
    virtual void setFormXY( double x, double y );
    virtual void setFormAngle( double deltaAngle );
    virtual void formShow( );

protected:
    void showCenter();
    void showLeftTop();

private slots:
     virtual void setParamFromWidget( );
private:
    struct InnerState;
    InnerState * innerState;
    QRectF getLineRect( double x1, double y1 , double x2 , double y2 );  // get Rect with parallel to axis sides which diagonal coincides with the line
    double calcAngle() ; // using x1,x2,y1,y2 get current inclination angle of the line
};

#endif // SCATTERERS

