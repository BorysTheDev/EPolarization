#ifndef CORE_H_
#define CORE_H_

#include "curves/discretize_curve.h"
#include "math/hankel.h"
#include "math/simple_math.h"

namespace hpl {
using namespace mth;
//DComplex core(const crv::ParametricCurvePoint&,
//    const crv::ParametricCurvePoint&, double wn);

//DComplex smoothCore(const crv::ParametricCurvePoint& t,
//    const crv::ParametricCurvePoint& t1, double wn);

typedef ParametricCurvePoint<double> SPCPoint;
    
    
double DL_dt_mul_sqr(SPCPoint& pt, SPCPoint& ptau)
{
    return (pt.x - ptau.x) * pt.d.x - (pt.y - ptau.y) * pt.d.y;
}

//DL_dtau is DL_dt(ptau, pt);
double DL_dt(SPCPoint& pt, SPCPoint& ptau)
{
    return DL_dt_mul_sqr(ptau, pt) / dist(pt, ptau);
}

double D2L_dt_d_tau(SPCPoint& pt, SPCPoint& ptau)
{
    return ( (-ptau.d.x * pt.d.x - ptau.d.y * pt.d.y) * dist(pt, ptau)
             - DL_dt(ptau, pt) * DL_dt_mul_sqr(pt, ptau)
             ) / sqr( dist(pt, ptau) );
}

types::complex D2H_tau_t(SPCPoint& pt, SPCPoint& ptau, double wN)
{
    double L = dist(pt,ptau);

    types::complex temp1 = -sqr(wN) * h2(wN * L);
    types::complex temp2 = (-wN) * h2(1, wN * L) / L;

    double dl_dt_x_dl_dtau = DL_dt(pt, ptau) * DL_dt(ptau, pt);

    types::complex temp3 = (-wN) * h2(1, wN * L) * D2L_dt_d_tau(pt, ptau);

    return (temp1 - temp2) * dl_dt_x_dl_dtau - temp3;
}

types::complex A()
{
   return types::complex(0.0, 1.0) / 2.0 / M_PI;
}

types::complex B(SPCPoint& pt, double wN)
{
    return -sqr(wN) * ( sqr(pt.d.x) + sqr(pt.d.y) ) * types::complex(0, 1) / M_PI;
}

types::complex Smooth(SPCPoint& pt, SPCPoint& ptau, double wN)
{
    return -D2H_tau_t(pt, ptau, wN)
            + sqr(wN) * h2( wN * dist(pt, ptau) ) * (ptau.d.x * pt.d.x + ptau.d.y * pt.d.y)
            - A() / sqr( sin( (pt.t - ptau.t) / 2 ) )
            - B(ptau, wN) * log( std::fabs( sin( (pt.t - ptau.t) / 2 ) ) );

}


double Fi(int col, int n)
{
    return 2 * M_PI * col / (2 * n + 1);
}

double Fi0(int row, int n)
{
    return (2 * row + 1) * M_PI / (2 * n + 1);
}

double Hyper(int row, int col, int n)
{
    double dif_fi = Fi0(row, n) - Fi(col, n);
    double sin_dif_fi_div_2 = sin(dif_fi / 2);

    return sqr( sin(n * dif_fi / 2) ) / sqr(sin_dif_fi_div_2)
            - n * sin( (n + 0.5) * dif_fi ) / sin_dif_fi_div_2;
}

double Log(int row, int col, int n)
{
    double dif_fi = Fi0(row, n) - Fi(col, n);

    double sum = 0;
    for (int p = 1; p <= n; p++)
    {
        sum += cos(p * dif_fi) / p;
    }
    return -2 * M_PI / (2 * n + 1) * (log(2) + sum);
}

types::complex H(SPCPoint& pt, SPCPoint& ptau, double wN, int n)
{
    return A() * Hyper(ptau.t, pt.t, n)
            + B(ptau, wN) * Log(ptau.t, pt.t, n)
            + 2 * M_PI * Smooth(ptau, pt, wN) / (2.0 * n + 1);

}




}

#endif /* CORE_H_ */
