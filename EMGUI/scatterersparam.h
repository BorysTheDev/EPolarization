#ifndef SCATTERERSPARAM
#define SCATTERERSPARAM

#include "QRectF"


struct ICurveParam {
    double rotationAngle;
};

struct EllipseParam : ICurveParam  {
    QRectF rect;
    double startAngle;
    double spanAngle;
};

struct LineParam : ICurveParam {
    double x1;
    double y1;
    double x2;
    double y2;
};

#endif // SCATTERERSPARAM

