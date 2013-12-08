#ifndef POINT_H_
#define POINT_H_

#include <cmath>

namespace mth {

template<class T>
struct Point
{
  T x;
  T y;
};

template<class T>
T dist(const Point<T>& p1, const Point<T>& p2)
{
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

}

#endif /* POINT_H_ */
