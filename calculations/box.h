#ifndef BOX_H_
#define BOX_H_
#include <vector>
#include "prototype.h"
#include <list>

template<class T>
class DonationBox {
public:
	//constructors
	explicit DonationBox(){}

	//functions
	size_t size() const {
		return data.size();
	}

	const T& operator[](const size_t n) const {
		return *data[n];
	}

	DonationBox<T>& operator<<(T* donator);

	//destructor
	~DonationBox();

private:
	std::vector<const T*> data;
	DonationBox(const DonationBox&) = delete;
	const DonationBox& operator=(const DonationBox& f) = delete;
};

template<class T>
DonationBox<T>& DonationBox<T>::operator<<(T* donator) {
	data.push_back(donator);
	return *this;
}

template<class T>
DonationBox<T>::~DonationBox() {
	for (auto& a : data)
		if (a) delete a;
}

template<class T>
class BlackBox {
public:
	//constructors
	//template <class Collection>
	BlackBox(DonationBox<T>&);

	//functions
	size_t size() const {
		return data.size();
	}

	const T& operator[](const size_t n) const {
		return *data[n];
	}

	//destructor
	~BlackBox();

private:
	std::vector<const T*> data;
	BlackBox(const BlackBox&) = delete;
	const BlackBox& operator=(const BlackBox& f) = delete;
};

template <class T>
BlackBox<T>::BlackBox(DonationBox<T>& d): data(d.size()) {
	for(size_t i = 0; i < d.size(); i++) {
		data[i] = d[i].clone();
	}
}

template<class T>
BlackBox<T>::~BlackBox() {
	for (auto& a : data)
		if (a) delete a;
}

#endif /* BOX_H_ */

