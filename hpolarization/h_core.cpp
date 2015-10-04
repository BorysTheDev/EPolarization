#include "h_core.h"
//#include "hankel.h"
#include "simple_math.h"

//using namespace tps;
//using namespace crv;

//typedef crv::ParametricCurvePoint pcp;

//namespace hpl {

//DComplex core(const pcp& tau, const pcp& t, double wn)
//{
//  double difx = t.x - tau.x;
//  double dify = t.y - tau.y;
//  double z2 = difx * difx + dify * dify;
//  double z = std::sqrt(z2);
//  double zdzdt = difx * t.d.x + dify * t.d.y;
//  double zdzdtau = -difx * tau.d.x - dify * tau.d.y;
//  //double dzdt   = zdzdt / z;
//  //double dzdtau = zdzdtau / z;
//  double dzdtdtau = ((-t.d.x * tau.d.x - t.d.y * tau.d.y) * z - zdzdt * zdzdtau) / z2;
//  complex h2_1 = mth::h2(1, z);
//  return wn * ((mth::h2(2, z) - h2_1 / z) * (zdzdt * zdzdtau) / z - h2_1 * dzdtdtau);
//}

//DComplex smoothCore(const pcp& tau, const pcp& t, double wn)
//{
//  double p       = std::hypot(t.d.x, t.d.y);
//  double dp      = 2 * (t.d.x * t.d2.x + t.d.y * t.d2.y);
//  double tmtau   = std::abs(t.t - tau.t);
//  double lntmtau = std::log(tmtau);
//  complex sm1(0, 2.0 / M_PI / mth::sqr(tmtau));
//  complex sm2(0, (2.0 / M_PI) * 2 * wn * p * lntmtau);
//  complex sm3(0, (2.0 / M_PI) * 2 * wn * tmtau * dp * lntmtau);
//  return core(t, tau, wn) - sm1 - (sm2 + sm3) / complex(4, 0);
//}

//}
