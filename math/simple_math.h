#ifndef SIMPLE_MATH_H_
#define SIMPLE_MATH_H_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace mth {

template<class T>
inline T sqr(const T& base)
{
  return base * base;
}

//needs to change another dists to this dist
namespace nta
{
template<class T>
inline T dist(const T& x,const T& y )
{
  return sqrt( sqr(x) + sqr(y) );
}
}

}

#endif /* SIMPLE_MATH_H_ */
