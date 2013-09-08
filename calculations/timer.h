#ifndef TIMER_H_
#define TIMER_H_
#include <chrono>
#include <string>
#include <utility>
#include <list>



class Timer{
public:
	typedef std::chrono::time_point<std::chrono::system_clock> timePoint;
	void start();
	void stop();
	double interval();
private:
	timePoint start_, stop_;
};

void Timer::start(){
	start_ = std::chrono::system_clock::now();
}

void Timer::stop(){
	stop_ = std::chrono::system_clock::now();
}

double Timer::interval(){
	 return ((double)std::chrono::duration_cast<std::chrono::milliseconds>(stop_-start_).count()) / 1000;
}
#endif /* TIMER_H_ */
