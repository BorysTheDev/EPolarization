#include "discretization.h"
#include <functional>
#include <list>
#include <thread>
#include <stdexcept>
#include <algorithm>


Discretization::Discretization(const CurvesList& sCurves,
    const IncidentFields& fields) : fields(fields), curves(sCurves),
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
  auto cn = curves.size();

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
  for (size_t i = 0; i < curves.size(); i++) {
    for (size_t j = 0; j < curves[i]->size(); j++, ii++)
      f[ii] = -fields((*curves[i])[j].x, (*curves[i])[j].y);
  }
  return f;
}

void Discretization::fillMatrixBlock(Matrix<types::complex>& matr,
    size_t ci1, size_t ci2, int threads)
{
  if (threads < 1) throw std::logic_error("threads can't be less then 1");
  int i = leftBorderOf(ci1);
  int j = leftBorderOf(ci2);
  const DiscretizeCurve& c1 = *curves[ci1];
  const DiscretizeCurve& c2 = *curves[ci2];

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
