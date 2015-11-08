#ifndef CALC_MANAGER_H_
#define CALC_MANAGER_H_

#include "given.h"

class CalcManager {
public:
    CalcManager(Given&& params): given(std::move(params)){}

	void run();
    void calcH();

private:
    Given&& given;
};


#endif /* CALC_MANAGER_H_ */
