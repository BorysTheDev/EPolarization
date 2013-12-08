#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

template<class T> class Prototype;

template<class T>
class ProtoPtr
{
public:
  ProtoPtr(Prototype<T>* ptr) : protoPtr(ptr) {}
  ProtoPtr(const ProtoPtr& ptr) : protoPtr(ptr->clone().release()) {}
  ProtoPtr& operator=(const ProtoPtr& ptr);

  T* operator->() const { return (T*)protoPtr; }
  T& operator*()  const { return *(T*)protoPtr; }
  operator T*()   const { return (T*)protoPtr; }

  T* release();

  ~ProtoPtr() { if (protoPtr) delete protoPtr; }
private:
  Prototype<T>* protoPtr;
};

template<class T>
class Prototype
{
public:
  virtual ProtoPtr<T> clone() const = 0;
  virtual ~Prototype() {}
};

template<class T>
ProtoPtr<T>& ProtoPtr<T>::operator=(const ProtoPtr& ptr)
{
  if (protoPtr)
    delete protoPtr;
  protoPtr = ptr->clone();
  return *this;
}

template<class T>
T* ProtoPtr<T>::release()
{
  T* tmp = (T*)protoPtr;
  protoPtr = nullptr;
  return tmp;
}



#endif /* PROTOTYPE_H_ */
