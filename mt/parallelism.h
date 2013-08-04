#ifndef PARALLELISM_H_
#define PARALLELISM_H_
#include "thread.h"

namespace mt
{
  class RunnableFactory
  {
  public:
    RunnableFactory(int num) :num(num){}
    virtual Runnable&& produce(int pos);
    virtual ~RunnableFactory(){}
    int number() { return num;}

  protected:
    int num;
  };

  class Parallelism
  {
  public:
    Parallelism(RunnableFactory&& r);
  protected:
    std::vector<Thread> threads;
  };

  Parallelism::Parallelism(RunnableFactory&& r) :
      threads(r.number())
  {
    for (int i =0; i < threads.size(); i++) {
      threads[i] = Thread(r.produce(i));
    }
  }
}

#endif /* PARALLELISM_H_ */
