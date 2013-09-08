#ifndef BOX_H_
#define BOX_H_
#include <vector>
#include "prototype.h"
#include <list>

template<class T>
class Box {
public:
	virtual std::size_t size() const = 0;

	virtual const T& operator[](const std::size_t n) const = 0;

	virtual ~Box(){}
protected:
	Box(){}
private:
	Box(const Box&) = delete;
	const Box& operator=(const Box& f) = delete;
};

template<class T>
class DonationBox : public Box<T> {
public:
	DonationBox(){}
	std::size_t size() const override { return data.size(); }

	const T& operator[](const std::size_t n) const override { return *data[n]; }
	//T& operator[](std::size_t n) { return *data[n]; }

	DonationBox<T>& operator<<(T* donator);

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
class BlackBox : public Box<T> {
public:
	BlackBox(DonationBox<T>&);

	std::size_t size() const override { return data.size(); }
	const T& operator[](const std::size_t n) const override { return *data[n]; }

	~BlackBox();

private:
	std::vector<const T*> data;
	BlackBox(const BlackBox&) = delete;
	const BlackBox& operator=(const BlackBox& f) = delete;
};

template <class T>
BlackBox<T>::BlackBox(DonationBox<T>& d): data(d.size()) {
	for(std::size_t i = 0; i < d.size(); i++) {
		data[i] = d[i].clone();
	}
}

template<class T>
BlackBox<T>::~BlackBox() {
	for (auto& a : data)
		if (a) delete a;
}

#endif /* BOX_H_ */

