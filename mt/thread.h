#ifndef THREAD_H_
#define THREAD_H_
#include <thread>

namespace mt {

struct Runnable {
	virtual void run() = 0;
	virtual ~Runnable() {}
};

namespace realization {

template<class T>
class Thread {
public:
	Thread(Runnable& r) : run(r){}
	void start();
	~Thread();

private:
	Runnable& run;
	T thread;
};

template<>
void Thread<std::thread>::start(){
	thread = std::thread(&Runnable::run, &run);
}

template<>
Thread<std::thread>::~Thread(){
	thread.join();
}

}
typedef realization::Thread<std::thread> Thread;
}

#endif /* THREAD_H_ */
