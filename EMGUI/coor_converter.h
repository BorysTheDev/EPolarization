#ifndef COOR_CONVERTER_H
#define COOR_CONVERTER_H

double getXscene( double x, double xMin, double xMax, double sceneWidth );

double getYscene( double y, double yMin, double yMax, double sceneHeight );

double getX( double xScene, double xMin, double xMax, double sceneWidth );

double getY( double yScene, double yMin, double yMax, double sceneHeight );

double getWidthOnScene( double width, double xMin, double xMax, double sceneWidth );

double getHeightOnScene( double height, double yMin, double yMax, double sceneHeight );

double getWidth( double widthOnScene, double xMin, double xMax, double sceneWidth);

double getHeight(double heightOnScene, double yMin, double yMax, double sceneHeight);


#endif // COOR_CONVERTER_H
