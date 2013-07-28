#ifndef MT_DISCRETIZATION_H_
#define MT_DISCRETIZATION_H_

using namespace mt;

class RunnableFactory{
public:
	RunnableFactory(int num) : num(num){}
	virtual Runnable&& produce(int pos);
	virtual ~RunnableFactory(){}

	int number() {return num;}

protected:
	int num;
};

class Parallelism {
public:
	Parallel(RunnableFactory&& r);
protected:
	std::vector<Thread> threads;
};

Parallelism::Parallelism(RunnableFactory&& r) :
		threads(r.number()) {
	for (auto& i : threads) {
		i = Thread(r.init(num, i));
	}
}

#endif /* MT_DISCRETIZATION_H_ */
