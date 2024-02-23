#ifndef COUNTER_H
#define COUNTER_H

#include <vector>
#include <map>

using namespace std;

template<typename T>
class Counter: public map<T, int>
{
public:
    Counter();
    Counter(vector<T> items);
    vector<T>  most_common();
    vector<T>  most_common(int n = -1);
    int        total();
    void       subtract();
    void       subtract(T key);
    void       subtract(vector<T> keys);
    const Counter<T> operator+(const Counter &x);
    const Counter<T> operator-(const Counter &x);
    const Counter<T> operator+();
    const Counter<T> operator-();
private:
    Counter(const Counter &);
    Counter(const Counter &&);
    Counter& operator=(const Counter &);
    Counter& operator=(const Counter &&);
};

#include "Counter.cpp"

#endif