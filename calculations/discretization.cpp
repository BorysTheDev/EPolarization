#include "discretization.h"
#include <functional>
#include <list>
#include <thread>
#include <stdexcept>
#include <algorithm>
#include <hpolarization/h_core.h>
#include "math/hankel.h"
#include "iostream"

using namespace mth;

Discretization::Discretization(const CurvesList& sCurves, const CurvesList& sCurvesFi0,
    const IncidentFields& fields) : fields(fields), curvesFi(sCurves), curvesFi0(sCurvesFi0),
    wN(fields.waveNumber()), borders(sCurves.size())
{
  for (size_t i = 0; i < sCurves.size(); i++) {
    size += sCurves[i]->size();
    borders[i] = size;
  }
}

MatrixPtr<types::complex> Discretization::createMatrix(int threads) {
  if (threads < 1) throw std::logic_error("threads can't be less then 1");
  Matrix<types::complex> *matrix = new Matrix<types::complex>(size);
  auto cn = curvesFi.size();

  std::function<void(int, int, int)> fillBlocks =
      [&](int start, int step, int th) {
    for (size_t m = start; m < cn; m += step)
      for (size_t n = 0; n < cn; n++){
        fillMatrixBlock(*matrix, m, n, th);
      }
  };

  int tt = std::min(threads, (int)cn);
  std::list<std::thread> tasks;

  for (int i = 0; i < tt; i++)
    tasks.push_back(std::thread(fillBlocks, i, tt, threads / tt + 1));

  for (auto& t : tasks)
    t.join();
  return MatrixPtr<types::complex>(matrix);
}

std::vector<types::complex> Discretization::createArray() {
  std::vector<types::complex> f(size);
  int ii = 0;
  for (size_t i = 0; i < curvesFi.size(); i++) {
    for (size_t j = 0; j < curvesFi[i]->size(); j++, ii++)
      f[ii] = -fields((*curvesFi[i])[j].x, (*curvesFi[i])[j].y);
  }
  return f;
}

void Discretization::fillMatrixBlock(Matrix<types::complex>& matr,
    size_t ci1, size_t ci2, int threads)
{
  if (threads < 1) throw std::logic_error("threads can't be less then 1");
  int i = leftBorderOf(ci1);
  int j = leftBorderOf(ci2);
  const DiscretizeCurve& c1 = *curvesFi[ci1];
  const DiscretizeCurve& c2 = *curvesFi[ci2];

  //not diagonal blocks
  std::function<void(int, int)> block =
      [&](int start, int step) {
        if (i != j) {
          for (size_t ii = start; ii < c1.size(); ii += step) {
            for (size_t jj = 0; jj < c2.size(); jj++) {
              matr[i + ii][j + jj] = (M_PI / c2.size()) * h2(wN * dist(c1[ii] ,c2[jj]));
            }
          }
        } else {
          for (size_t ii = start; ii < c1.size(); ii += step) {
            for (size_t jj = 0; jj < c2.size(); jj++) {
              types::complex temp = ii != jj ? h2(wN * dist(c1[ii], c2[jj]))
              - epol::asymp(c1[ii].t, c1[jj].t) : epol::lim(c1[ii].d, wN);
              matr[i + ii][j + jj] = (M_PI / c1.size()) * (temp - types::complex(0, 2)
                  * epol::Ln(c1[ii].t, c1[jj].t, c1.size()) / M_PI);
            }
          }
        }
      };

  std::list<std::thread> tasks;
  for (int i = 0; i < threads; i++)
    tasks.push_back(std::thread(block, i, threads));

  for (auto& t : tasks)
    t.join();
}

MatrixPtr<types::complex> Discretization::createHMatrix()
{
    using namespace hpl;
    auto matrix = new Matrix<types::complex>(size);
    Matrix<types::complex>& matr = *matrix;

    SPCPoint& pt = (*curvesFi[0])[1];
    SPCPoint& pt0 = (*curvesFi0[0])[1];
    int n = curvesFi[0]->size() / 2;
    std::cout << "B     " << B(pt, wN) << std::endl
              << "Hyper " << Hyper(pt0, pt, n) << std::endl
              << "Log   " << Log(pt, pt0, n) << std::endl
              << "Smooth" << Smooth(pt, pt0, wN) << std::endl
              << "H     " << hpl::H((*curvesFi[0])[1], (*curvesFi0[0])[1], wN, n) << std::endl;

    for (size_t row = 0; row < curvesFi0[0]->size(); row++)
    {
        for (size_t col = 0; col < curvesFi[0]->size(); col++)
        {
            matr[row][col] = hpl::H((*curvesFi0[0])[row], (*curvesFi[0])[col], wN, n);
        }
    }
    return MatrixPtr<types::complex>(matrix);
}

std::vector<types::complex> Discretization::createHArray() {
  std::vector<types::complex> f(size);
  int ii = 0;
  for (size_t i = 0; i < curvesFi.size(); i++)
  {
    for (size_t j = 0; j < curvesFi[i]->size(); j++, ii++)
    {
      f[ii] = hpl::ET((*curvesFi0[i])[j], wN, 3 * M_PI / 2);
    }
  }
  return f;
}
