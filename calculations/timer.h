#ifndef TIMER_H_
#define TIMER_H_
#include <chrono>
#include <string>
#include <utility>
#include <list>

using namespace std;
using namespace chrono;

class Timer{

public:
	typedef time_point<std::chrono::system_clock> timePoint;
	void start();
	void stop();
	double interval();
private:
	timePoint start_, stop_;
};

void Timer::start(){
	start_ = system_clock::now();
}

void Timer::stop(){
	stop_ = system_clock::now();
}

double Timer::interval(){
	 return ((double)duration_cast<milliseconds>(stop_-start_).count()) / 1000;
}
#endif /* TIMER_H_ */
