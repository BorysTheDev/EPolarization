#include "cubic_spline.h"

using namespace types;

static const double a = 8;
static const double b = 10;
static const double c = 2.5;
static const double d = 2;
static const double e = 0.5;
static const double f = 1;

static std::vector<double> diap = {
    0,                                                             //0
    b,                                                             //1
    a + b,                                                         //2
    a + 2 * b,                                                     //3
    a + 2 * b + c,                                                 //4
    a + 2 * b + c + d,                                             //5
    a + 2 * b + 2 * c + d - e,                                     //6
    a + 2 * b + 2 * c + d - e + f,                                 //7
    a + 2 * b + 3 * c + d - 2 * e + f,                             //8
    a + 2 * b + 3 * c + 2 * d - 2 * e + f,                         //9
    a + 2 * b + 4 * c + 2 * d - 3 * e + f,                         //10
    a + 3 * b + 4 * c - 4 * e,                                     //11
    2 * a + 3 * b + 4 * c - 6 * e,                                 //12
    2 * a + 4 * b + 4 * c - 2 * d - 7 * e - f,                     //13
    2 * a + 4 * b + 5 * c - 2 * d - 8 * e - f,                     //14
    2 * a + 4 * b + 5 * c - d - 8 * e - f,                         //15
    2 * a + 4 * b + 6 * c - d - 9 * e - f,                         //16
    2 * a + 4 * b + 6 * c - d - 9 * e,                             //17
    2 * a + 4 * b + 7 * c - d - 10 * e,                            //18
    2 * a + 4 * b + 7 * c - 10 * e,                                //19
    2 * a + 4 * b + 8 * c - 10 * e,                                //20
};

CubicSpline::CubicSpline()
{
}

double CubicSpline::x(real t) const
{
    double s = t / 2 / M_PI * diap.back();

    double x = 0, y = 0;
    if (diap[0] <= s && s < diap[1])
    {
        x = 0;
        y = s;
    }
    if (diap[1] <= s && s < diap[2])
    {
        x = s - b;
        y = b;
    }
    if (diap[2] <= s && s < diap[3])
    {
        x = a;
        y = diap[3] - s;
    }
    if (diap[3] <= s && s < diap[4])
    {
        x = 2 * a + 2 * b - s;
        y = 0;
    }
    if (diap[4] <= s && s < diap[5])
    {
        x = a - c;
        y = s - a - 2 * b - c;
    }
    if (diap[5] <= s && s < diap[6])
    {
        x = s - 2 * b - 2 * c - d;
        y = d;
    }
    if (diap[6] <= s && s < diap[7])
    {
        x = a - e;
        y = s - a - 2 * b - 2 * c + e;
    }
    if (diap[7] <= s && s < diap[8])
    {
        x = 2 * a - 2 * e + 2 * b + 2 * c + d + f - s;
        y = d + f;
    }
    if (diap[8] <= s && s < diap[9])
    {
        x = a - c;
        y = s - a - 2 * b - 3 * c + 2 * e;
    }
    if (diap[9] <= s && s < diap[10])
    {
        x = s - diap[9] + a - c;
        y = 2 * d + f;
    }
    if (diap[10] <= s && s < diap[11])
    {
        x = a - e;
        y = s - diap[10] + 2 * d + f;
    }
    if (diap[11] <= s && s < diap[12])
    {
        x = diap[12] - s + e;
        y = b - e;
    }
    if (diap[12] <= s && s < diap[13])
    {
        x = e;
        y = diap[13] + 2 * d + f - s;
    }
    if (diap[13] <= s && s < diap[14])
    {
        x = s - diap[13] + e;
        y = 2 * d + f;
    }
    if (diap[14] <= s && s < diap[15])
    {
        x = c;
        y = diap[15] + d + f - s;
    }
    if (diap[15] <= s && s < diap[16])
    {
        x = diap[16] + e - s;
        y = d + f;
    }
    if (diap[16] <= s && s < diap[17])
    {
        x = e;
        y = diap[17] + d - s;
    }
    if (diap[17] <= s && s < diap[18])
    {
        x = s - diap[17] + e;
        y = d;
    }
    if (diap[18] <= s && s < diap[19])
    {
        x = c;
        y = diap[19] - s;
    }
    if (diap[19] <= s && s < diap[20])
    {
        x = diap[20] - s;
        y = 0;
    }
    return x;
}

double CubicSpline::y(real t) const
{
    double s = t / 2 / M_PI * diap.back();

    double x = 0, y = 0;
    if (diap[0] <= s && s < diap[1])
    {
        x = 0;
        y = s;
    }
    if (diap[1] <= s && s < diap[2])
    {
        x = s - b;
        y = b;
    }
    if (diap[2] <= s && s < diap[3])
    {
        x = a;
        y = diap[3] - s;
    }
    if (diap[3] <= s && s < diap[4])
    {
        x = 2 * a + 2 * b - s;
        y = 0;
    }
    if (diap[4] <= s && s < diap[5])
    {
        x = a - c;
        y = s - a - 2 * b - c;
    }
    if (diap[5] <= s && s < diap[6])
    {
        x = s - 2 * b - 2 * c - d;
        y = d;
    }
    if (diap[6] <= s && s < diap[7])
    {
        x = a - e;
        y = s - a - 2 * b - 2 * c + e;
    }
    if (diap[7] <= s && s < diap[8])
    {
        x = 2 * a - 2 * e + 2 * b + 2 * c + d + f - s;
        y = d + f;
    }
    if (diap[8] <= s && s < diap[9])
    {
        x = a - c;
        y = s - a - 2 * b - 3 * c + 2 * e;
    }
    if (diap[9] <= s && s < diap[10])
    {
        x = s - diap[9] + a - c;
        y = 2 * d + f;
    }
    if (diap[10] <= s && s < diap[11])
    {
        x = a - e;
        y = s - diap[10] + 2 * d + f;
    }
    if (diap[11] <= s && s < diap[12])
    {
        x = diap[12] - s + e;
        y = b - e;
    }
    if (diap[12] <= s && s < diap[13])
    {
        x = e;
        y = diap[13] + 2 * d + f - s;
    }
    if (diap[13] <= s && s < diap[14])
    {
        x = s - diap[13] + e;
        y = 2 * d + f;
    }
    if (diap[14] <= s && s < diap[15])
    {
        x = c;
        y = diap[15] + d + f - s;
    }
    if (diap[15] <= s && s < diap[16])
    {
        x = diap[16] + e - s;
        y = d + f;
    }
    if (diap[16] <= s && s < diap[17])
    {
        x = e;
        y = diap[17] + d - s;
    }
    if (diap[17] <= s && s < diap[18])
    {
        x = s - diap[17] + e;
        y = d;
    }
    if (diap[18] <= s && s < diap[19])
    {
        x = c;
        y = diap[19] - s;
    }
    if (diap[19] <= s && s < diap[20])
    {
        x = diap[20] - s;
        y = 0;
    }
    return y;
}

double CubicSpline::dx(real t) const
{
    double s = t / 2 / M_PI * diap.back();

    double x = 0, y = 0;
    double dx = 2 * M_PI / diap.back();
    if (diap[0] <= s && s < diap[1])
    {
        x = 0;
        y = s;
        dx = 0;
    }
    if (diap[1] <= s && s < diap[2])
    {
        x = s - b;
        y = b;
    }
    if (diap[2] <= s && s < diap[3])
    {
        x = a;
        y = diap[3] - s;
        dx = 0;
    }
    if (diap[3] <= s && s < diap[4])
    {
        x = 2 * a + 2 * b - s;
        y = 0;
        dx = -dx;
    }
    if (diap[4] <= s && s < diap[5])
    {
        x = a - c;
        y = s - a - 2 * b - c;
        dx = 0;
    }
    if (diap[5] <= s && s < diap[6])
    {
        x = s - 2 * b - 2 * c - d;
        y = d;
    }
    if (diap[6] <= s && s < diap[7])
    {
        x = a - e;
        y = s - a - 2 * b - 2 * c + e;
        dx = 0;
    }
    if (diap[7] <= s && s < diap[8])
    {
        x = 2 * a - 2 * e + 2 * b + 2 * c + d + f - s;
        y = d + f;
        dx = -dx;
    }
    if (diap[8] <= s && s < diap[9])
    {
        x = a - c;
        y = s - a - 2 * b - 3 * c + 2 * e;
        dx = 0;
    }
    if (diap[9] <= s && s < diap[10])
    {
        x = s - diap[9] + a - c;
        y = 2 * d + f;
    }
    if (diap[10] <= s && s < diap[11])
    {
        x = a - e;
        y = s - diap[10] + 2 * d + f;
        dx = 0;
    }
    if (diap[11] <= s && s < diap[12])
    {
        x = diap[12] - s + e;
        y = b - e;
        dx = -dx;
    }
    if (diap[12] <= s && s < diap[13])
    {
        x = e;
        y = diap[13] + 2 * d + f - s;
        dx = 0;
    }
    if (diap[13] <= s && s < diap[14])
    {
        x = s - diap[13] + e;
        y = 2 * d + f;
    }
    if (diap[14] <= s && s < diap[15])
    {
        x = c;
        y = diap[15] + d + f - s;
        dx = 0;
    }
    if (diap[15] <= s && s < diap[16])
    {
        x = diap[16] + e - s;
        y = d + f;
        dx = -dx;
    }
    if (diap[16] <= s && s < diap[17])
    {
        x = e;
        y = diap[17] + d - s;
        dx = 0;
    }
    if (diap[17] <= s && s < diap[18])
    {
        x = s - diap[17] + e;
        y = d;
    }
    if (diap[18] <= s && s < diap[19])
    {
        x = c;
        y = diap[19] - s;
        dx = 0;
    }
    if (diap[19] <= s && s < diap[20])
    {
        x = diap[20] - s;
        y = 0;
        dx = -dx;
    }
    return dx;
}

double CubicSpline::dy(real t) const
{
    double s = t / 2 / M_PI * diap.back();

    double x = 0, y = 0;
    double dy = 2 * M_PI / diap.back();
    if (diap[0] <= s && s < diap[1])
    {
        x = 0;
        y = s;
    }
    if (diap[1] <= s && s < diap[2])
    {
        x = s - b;
        y = b;
        dy = 0;
    }
    if (diap[2] <= s && s < diap[3])
    {
        x = a;
        y = diap[3] - s;
        dy = -dy;
    }
    if (diap[3] <= s && s < diap[4])
    {
        x = 2 * a + 2 * b - s;
        y = 0;
        dy = 0;
    }
    if (diap[4] <= s && s < diap[5])
    {
        x = a - c;
        y = s - a - 2 * b - c;
    }
    if (diap[5] <= s && s < diap[6])
    {
        x = s - 2 * b - 2 * c - d;
        y = d;
        dy = 0;
    }
    if (diap[6] <= s && s < diap[7])
    {
        x = a - e;
        y = s - a - 2 * b - 2 * c + e;
    }
    if (diap[7] <= s && s < diap[8])
    {
        x = 2 * a - 2 * e + 2 * b + 2 * c + d + f - s;
        y = d + f;
        dy = 0;
    }
    if (diap[8] <= s && s < diap[9])
    {
        x = a - c;
        y = s - a - 2 * b - 3 * c + 2 * e;
    }
    if (diap[9] <= s && s < diap[10])
    {
        x = s - diap[9] + a - c;
        y = 2 * d + f;
        dy = 0;
    }
    if (diap[10] <= s && s < diap[11])
    {
        x = a - e;
        y = s - diap[10] + 2 * d + f;
    }
    if (diap[11] <= s && s < diap[12])
    {
        x = diap[12] - s + e;
        y = b - e;
        dy = 0;
    }
    if (diap[12] <= s && s < diap[13])
    {
        x = e;
        y = diap[13] + 2 * d + f - s;
        dy = -dy;
    }
    if (diap[13] <= s && s < diap[14])
    {
        x = s - diap[13] + e;
        y = 2 * d + f;
        dy = 0;
    }
    if (diap[14] <= s && s < diap[15])
    {
        x = c;
        y = diap[15] + d + f - s;
        dy = -dy;
    }
    if (diap[15] <= s && s < diap[16])
    {
        x = diap[16] + e - s;
        y = d + f;
        dy = 0;
    }
    if (diap[16] <= s && s < diap[17])
    {
        x = e;
        y = diap[17] + d - s;
        dy = -dy;
    }
    if (diap[17] <= s && s < diap[18])
    {
        x = s - diap[17] + e;
        y = d;
        dy = 0;
    }
    if (diap[18] <= s && s < diap[19])
    {
        x = c;
        y = diap[19] - s;
        dy = -dy;
    }
    if (diap[19] <= s && s < diap[20])
    {
        x = diap[20] - s;
        y = 0;
        dy = 0;
    }
    return dy;
}

double CubicSpline::d2x(real t) const
{
    return 0;
}

double CubicSpline::d2y(real t) const
{
    return 0;
}

double CubicSpline::length() const
{
    return diap.back();
}

CubicSpline* CubicSpline::clone() const
{
    return new CubicSpline;
}
