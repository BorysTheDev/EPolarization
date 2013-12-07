#ifndef SINGLETON_H
#define SINGLETON_H

#include<mutex>

template <classt T>
class Singleton
{
public:
    static T* instance();

protected:
    ~Singleton() {delete singleton;}

private:
    static std::once_flag flag;
    static T* singleton = nullptr;
    Singleton(const singleton&) = delete;
    Singleton operator=(const singleton&) = delete;
};

template <classt T>
T* Singleton<T>::instance()
{
    if(singleton == 0)
        std::call_once(flag, [&](){ singleton = new T; });
    return singleton;
}


#endif // SINGLETON_H
