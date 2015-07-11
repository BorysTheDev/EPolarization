#include "coor_converter.h"

double getXscene( double x, double xMin, double xMax, double sceneWidth ) {
    return ( x - xMin ) * sceneWidth / ( xMax - xMin );

}

double getYscene( double y, double yMin, double yMax, double sceneHeight ) {
    return sceneHeight - ( y - yMin ) * sceneHeight / ( yMax - yMin );
}

double getX( double xScene, double xMin, double xMax, double sceneWidth ) {
    return xMin + (xMax - xMin ) / sceneWidth * (double)xScene;
}

double getY( double yScene, double yMin, double yMax, double sceneHeight ) {
    return 0 + ( yMax - ( yMax - yMin ) / sceneHeight * (double)yScene );
}

double getWidthOnScene( double width, double xMin, double xMax, double sceneWidth ) {
    return sceneWidth * width / ( xMax - xMin );
}

double getHeightOnScene( double height, double yMin, double yMax, double sceneHeight ) {
    return sceneHeight * height / ( yMax - yMin );
}

double getWidth( double widthOnScene, double xMin, double xMax, double sceneWidth) {
    return ( xMax - xMin ) * widthOnScene / sceneWidth ;
}

double getHeight( double heightOnScene, double yMin, double yMax, double sceneHeight) {
    return ( yMax - yMin ) * heightOnScene / sceneHeight ;
}
