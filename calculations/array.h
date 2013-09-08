#ifndef ARRAY_H_
#define ARRAY_H_
#include "stdint.h"

template<class T>
class Array{
	typedef uint32_t size_t;
public:
	//constructors
	explicit Array(size_t size);
	Array(const Array& a){init(a.size(), a.array);}
	//functions
	inline T& operator[](const size_t pos){return array[pos];}
	inline const T& operator[](const size_t pos)const {return array[pos];}
	Array operator=(const Array& a){init(a.size(), a.array); return *this;}
	size_t size()const {return size_;}
	//destructor
	~Array(){reset();}
private:
	void init(size_t size_, T* array_ = nullptr);
	size_t size_;
	void reset();
	T* array;
};


template<class T>
Array<T>::Array(size_t size_){
	init(size_);
}

template<class T>
void Array<T>::reset(){
	delete[] array;
	size_ = 0;
}

template<class T>
void Array<T>::init(size_t size_, T* array_){
	this->size_ = size_;
	array = new T[size_];
	if (array_ != nullptr){
		for(size_t i = 0; i < size(); i++)
			array[i] = array_[i];
	}
}

#endif /* ARRAY_H_ */
