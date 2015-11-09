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

typedef ParametricCurvePoint<double> const SPCPoint;
    
    
static double DL_dt_mul_sqr(const SPCPoint& pt, const SPCPoint& ptau)
{
    return (pt.x - ptau.x) * pt.d.x + (pt.y - ptau.y) * pt.d.y;
}

//DL_dtau is DL_dt(ptau, pt);
static double DL_dt(const SPCPoint& pt, const SPCPoint& ptau)
{
    return DL_dt_mul_sqr(ptau, pt) / dist(pt, ptau);
}

static double D2L_dt_d_tau(const SPCPoint& pt, const SPCPoint& ptau)
{
    double L = dist(pt, ptau);
    double temp1 = -(ptau.d.x * pt.d.x + ptau.d.y * pt.d.y) * L;
    double temp2 = DL_dt_mul_sqr(pt, ptau) * DL_dt_mul_sqr(ptau, pt) / L;
    return (temp1 - temp2) / sqr(L);
}

static types::complex D2H_tau_t(const SPCPoint& ptau, const SPCPoint& pt, double wN)
{
    double L = dist(pt,ptau);

    types::complex temp1 = -sqr(wN) * h2(wN * L);
    types::complex temp2 = (-wN) * h2(1, wN * L) / L;

    double dl_dt_x_dl_dtau = DL_dt(pt, ptau) * DL_dt(ptau, pt);

    double d2LdTdTau = D2L_dt_d_tau(pt, ptau);

    types::complex temp3 = wN * h2(1, wN * L) * d2LdTdTau;

    types::complex temp4 = (temp1 - temp2) * dl_dt_x_dl_dtau;
    return temp4 - temp3;
}

static types::complex A()
{
   return types::complex(0.0, 1.0) / 2.0 / M_PI;
}

static types::complex B(const SPCPoint& pt, double wN)
{
    return -sqr(wN) * ( sqr(pt.d.x) + sqr(pt.d.y) ) * types::complex(0, 1) / M_PI;
}

static types::complex Smooth(const SPCPoint& ptau, const SPCPoint& pt, double wN)
{
    types::complex d2HTauT = D2H_tau_t(ptau, pt, wN);
    types::complex H2 = h2( wN * dist(pt, ptau) );
    double sumD = ptau.d.x * pt.d.x + ptau.d.y * pt.d.y;
    double sin1 = sqr( sin( (pt.t - ptau.t) / 2 ) );
    types::complex b = B(ptau, wN);
    types::complex ln = log( std::fabs( sin( (pt.t - ptau.t) / 2 ) ) );

    return -d2HTauT + sqr(wN) * H2 * sumD - (A() / sin1) - b * ln;
}


static double Fi(int n, int col)
{
    n--;//needs to improve algorithm
    return 2 * M_PI * col / (n + 1);
}

static double Fi0(int n, int row)
{
    n--;
    return (2 * row + 1) * M_PI / (n + 1);
}

static double Hyper(const SPCPoint& pt0, const SPCPoint& pt, int n)
{
    double dif_fi = pt.t - pt0.t;
    double sin_dif_fi_div_2 = sin(dif_fi / 2);

    double sin1 = sqr( sin(n * dif_fi / 2) );
    double sin2 = sqr(sin_dif_fi_div_2);
    double sin3 = n * sin( (n + 0.5) * dif_fi );
    double sin4 = sin_dif_fi_div_2;

    double allSins = (sin1 / sin2) - (sin3 / sin4);

    return 4 * M_PI * allSins / (2 * n + 1);
}

static double Log(const SPCPoint& pt0, const SPCPoint& pt, int n)
{
    double dif_fi = pt0.t - pt.t;

    double sum = 0;
    for (int p = 1; p <= n; p++)
    {
        sum += cos(p * dif_fi) / p;
    }
    return -2 * M_PI / (2 * n + 1) * (log(2) + sum);
}

static types::complex H(const SPCPoint& ptau, const SPCPoint& pt, double wN, int n)
{
    return A() * Hyper(ptau, pt, n)
            + B(ptau, wN) * Log(ptau, pt, n)
            + 2 * M_PI * Smooth(ptau, pt, wN) / (2.0 * n + 1);

}

static types::complex ET(const SPCPoint& ptau, double wN, double alpha)
{
    double distance = nta::dist(ptau.d.x, ptau.d.y);
    types::complex e_arg( 0, wN * (sin(alpha) * ptau.x - cos(alpha) * ptau.y) );
    types::complex e = exp(e_arg) / distance;
    types::complex et = e * wN * ( ptau.d.x * cos(alpha) + ptau.d.y * sin(alpha));
    return 4 * distance * et;
}


}

#endif /* CORE_H_ */
