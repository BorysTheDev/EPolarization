#include "axis.h"

#include <iostream>
#include <coor_converter.h>

struct Axis::State {
    QGraphicsLineItem * xAxis;
    QGraphicsLineItem * yAxis;

    std::vector<QGraphicsLineItem*> xDividers;
    std::vector<QGraphicsLineItem*> yDividers;
    std::vector<QGraphicsTextItem*> xDividersNum;
    std::vector<QGraphicsTextItem*> yDividersNum;
    std::vector<QGraphicsLineItem*> gridX;
    std::vector<QGraphicsLineItem*> gridY;
    QPen pen;
    QFont font;
    QPen gridPen;
    bool isGrid;
    int dividersNumPrecision;
    int dividerLen;
    State() {
        font.setFamily( "Times" );
        font.setWeight( QFont::Bold );
        font.setPixelSize( 12 );
        dividerLen = 10;
        pen.setColor(Qt::black);
        pen.setWidth( 3 );
        gridPen.setColor( Qt::green );
        gridPen.setStyle( Qt::DashLine );
        isGrid = false;
        dividersNumPrecision = 4;
    }


};

Axis::Axis() : state( new State ) {
    //QLOG_DEBUG() << "Axis constructor";
    state->xAxis = new QGraphicsLineItem();
    state->yAxis = new QGraphicsLineItem();
    //paint( scene, xMin, xMax, yMin, yMax );
}

void Axis::setGrid( bool isGrid) {
    state->isGrid = isGrid;
}

void Axis::paint( QGraphicsScene * scene, double xMin, double xMax, double yMin, double yMax ) {
    double xCartesian = 0;
    double yCartesian = 0;
    double width = scene->width();
    double height = scene->height();
    double xC = getXscene( xCartesian, xMin, xMax, width );
    double yC = getYscene( yCartesian, yMin, yMax, height );

    //QLOG_INFO() << "xC =" << xC << " yC =" << yC;
    state->xAxis = new QGraphicsLineItem( 0, yC, width, yC );
    state->yAxis = new QGraphicsLineItem( xC, 0, xC, height );

    state->xAxis->setPen( state->pen );
    state->yAxis->setPen( state->pen );

    scene->addItem( state->xAxis );
    scene->addItem( state->yAxis );
    double x_ = stepX;    // space between dividers on axis X
    double y_ = stepY;   // space between dividers on axis Y
    double x = xC;                               // divider x for positive value
    double y = yC;                               // divider y for positive value
    double w = width / 60;                       // divider Width


    QGraphicsTextItem * text = new QGraphicsTextItem( "0" );
    text->setPos( xC + state->dividerLen, yC + state->dividerLen) ;

    text->setFont( state->font );
    state->xDividersNum.push_back( text );

    // draw x dividers
    while ( x + x_ < width ) {
        x += x_;
        addXdivider( x, yC, state->dividerLen, xMin, xMax, width );
    }
    x = xC;
    while ( x - x_  > 0 ) {
        x -= x_;
        addXdivider( x, yC, state->dividerLen, xMin, xMax, width );
    }
    for ( int i = 0; i < state->xDividers.size(); i++ ) {
        scene->addItem( state->xDividers[i] );
    }
    for ( int i = 0; i < state->xDividersNum.size(); i++ ) {
        scene->addItem( state->xDividersNum[i] );
    }

    // draw y dividers
    while ( y + y_ < height ) {
        y += y_;
        addYdivider( xC, y, state->dividerLen, yMin, yMax, height );
    }
    y = yC;
    while ( y - y_  > 0 ) {
        y -= y_;
        addYdivider( xC, y, state->dividerLen, yMin, yMax, height );
    }

    for ( int i = 0; i < state->yDividers.size(); i++ ) {
        scene->addItem( state->yDividers[i] );
    }

    for ( int i = 0; i < state->yDividersNum.size(); i++ ) {
        scene->addItem( state->yDividersNum[i] );
    }

    if ( state->isGrid ) {
        addGrid( scene );
    }

}

void Axis::addXdivider( double x, double y, double len, double min, double max, double width ) {
    QGraphicsLineItem * divider = new QGraphicsLineItem( x, y - len, x, y + len );
    divider->setPen( state->pen );
    state->xDividers.push_back( divider );
    double xNum = getX( x, min, max, width );

    QGraphicsTextItem * text = new QGraphicsTextItem( QString::number( xNum, 'g', state->dividersNumPrecision ) );
    text->setPos( x, y + len );
    text->setFont( state->font );
    state->xDividersNum.push_back( text );
}

void Axis::addYdivider( double x, double y, double len, double min, double max, double height ) {
    QGraphicsLineItem * divider = new QGraphicsLineItem( x - len, y, x + len, y );
    divider->setPen( state->pen );
    state->yDividers.push_back( divider );
    double yNum = getY( y, min, max, height );
    QGraphicsTextItem * text = new QGraphicsTextItem( QString::number( yNum, 'g', state->dividersNumPrecision ) );
    text->setPos( x + len, y );
    text->setFont( state->font );
    state->yDividersNum.push_back( text );
}

void Axis::addGrid( QGraphicsScene * scene ) {
    //QLOG_DEBUG() << "Axis::addGrid";
    if ( state->xDividers.size() > 0 ) {
        for ( int i = 0; i < state->xDividers.size(); i++ ) {
            QLineF line = state->xDividers[i]->line();
            double x = line.x1();
            QGraphicsLineItem * gridLineY = new QGraphicsLineItem( x, 0, x , scene->height() );
            gridLineY->setPen( state->gridPen );
            state->gridY.push_back( gridLineY );
            scene->addItem( gridLineY );
        }
    }
    if ( state->yDividers.size() > 0 ) {
        for ( int i = 0; i < state->yDividers.size(); i++ ) {
            QLineF line = state->yDividers[i]->line();
            double y = line.y1();
            QGraphicsLineItem * gridLineX = new QGraphicsLineItem( 0, y, scene->width(), y );
            gridLineX->setPen( state->gridPen );
            state->gridX.push_back( gridLineX );
            scene->addItem( gridLineX );
        }
    }
}

void Axis::clear() {
    //QLOG_DEBUG() << "Axis::clear()";
    if ( state->xAxis != nullptr ) {
        delete state->xAxis;
        state->xAxis = nullptr;
    }
    if ( state->yAxis != nullptr ) {
        delete state->yAxis;
        state->yAxis = nullptr;
    }
    if ( state->xDividers.size() > 0 ) {
        for ( int i = 0; i < state->xDividers.size(); i++ ) {
            delete state->xDividers[i];
        }
        state->xDividers.clear();
    }
    if ( state->yDividers.size() > 0 ) {
        for ( int i = 0; i < state->yDividers.size(); i++ ) {
            delete state->yDividers[i];
        }
        state->yDividers.clear();
    }
    if ( state->xDividersNum.size() > 0 ) {
        for ( int i = 0; i < state->xDividersNum.size(); i++ ) {
            delete state->xDividersNum[i];
        }
        state->xDividersNum.clear();
    }
    if ( state->yDividersNum.size() > 0 ) {
        for ( int i = 0; i < state->yDividersNum.size(); i++ ) {
            delete state->yDividersNum[i];
        }
        state->yDividersNum.clear();
    }
    if ( state->gridX.size() > 0 ) {
        for ( int i = 0; i < state->gridX.size(); i++ ) {
            delete state->gridX[i];
        }
        state->gridX.clear();
    }
    if ( state->gridY.size() > 0 ) {
        for ( int i = 0; i < state->gridY.size(); i++ ) {
            delete state->gridY[i];
        }
        state->gridY.clear();
    }
}

Axis::~Axis() {
    clear();
    delete state;
}





