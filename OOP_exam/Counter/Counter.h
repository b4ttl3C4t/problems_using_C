#ifndef COUNTER_H
#define COUNTER_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<typename T>
class Counter: public map<T, int>
{
public:
    Counter();
    Counter(vector<T> items);
    vector<T> most_common();
    vector<T> most_common(int n);
    int       total();
    void      subtract();
    void      subtract(T key);
    void      subtract(vector<T> keys);
    vector<T> operator+(const Counter &x);
    vector<T> operator-(const Counter &x);
    Counter   operator+();
    Counter   operator-();
private:
    Counter(const Counter &);
    Counter(const Counter &&);
    Counter& operator=(const Counter &);
    Counter& operator=(const Counter &&);
};

#endif