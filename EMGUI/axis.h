#ifndef AXIS_H
#define AXIS_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>

class Axis {
public:
    Axis ();
    virtual ~Axis();
    void paint( QGraphicsScene * scene, double xMin, double xMax, double yMin, double yMax );
    void setGrid( bool isGrid);
    void clear();
    int stepX;
    int stepY;

private:
    struct State;
    State * state;
    void addXdivider( double x, double y, double len, double min, double max, double width );
    void addYdivider(double x, double y, double len, double min, double max, double height );
    void addGrid( QGraphicsScene * scene );
};

#endif // AXIS_H
