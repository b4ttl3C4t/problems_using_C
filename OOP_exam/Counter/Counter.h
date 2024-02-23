#ifndef COUNTER_H
#define COUNTER_H

#include <algorithm>
#include <vector>
#include <map>

using namespace std;

template<typename T>
class Counter: public map<T, int>
{
public:
    Counter();
    Counter(vector<T> items);
    Counter(const Counter &);
    vector<T>  most_common();
    vector<T>  most_common(int n = -1);
    int        total();
    void       subtract();
    void       subtract(T key);
    void       subtract(vector<T> keys);
    const Counter<T> operator+(const Counter<T> &x);
    const Counter<T> operator-(const Counter<T> &x);
    const Counter<T> operator+();
    const Counter<T> operator-();
    Counter<T> &     operator=(const Counter<T> &x);
private:
};

template<typename T>
inline Counter<T>::Counter()
{
    ;
}

template<typename T>
inline Counter<T>::Counter(vector<T> items)
{
    for(auto i: items)
    {
        ++(*this)[i];
    }
}

template<typename T>
inline Counter<T>::Counter(const Counter &c): map<T, int>(c)
{
    ;
}

template<typename T>
vector<T> Counter<T>::most_common(int n)
{
    // There is no way to sort data for non-linear data structure as map.
    // So, we need to restruct the data to vector with pair.
    vector<pair<T, int>> counts;

    for (auto i: *this)
    {
        counts.push_back({i.first, i.second});
    }

    sort(counts.begin(), counts.end(), [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
                      return a.second > b.second || (a.second == b.second && a.first < b.first);
                  });

    vector<T> result;

    for (auto &i: counts)
    {
        result.push_back(i.first);
    }

    if(n >= 0)
    {
        result.resize(n);
    }

    return result;
}

template<typename T>
int Counter<T>::total()
{
    int summation = 0;

    for(auto &each: *this)
    {
        summation += each.second;
    }

    return summation;
}

template<typename T>
inline void Counter<T>::subtract()
{
    for(auto &each: *this)
    {
        --each.second;
    }
}

template<typename T>
inline void Counter<T>::subtract(T key)
{
    for(auto &each: *this)
    {
        if(each.first == key)
        {
            --each.second;
            break;
        }
    }
}

template<typename T>
inline void Counter<T>::subtract(vector<T> keys)
{
    for(auto &each: keys)
    {
        --(*this)[each];
    }
}

template<typename T>
const Counter<T> Counter<T>::operator+(const Counter<T> &c)
{
    Counter<T> result = *this;

    for(auto &each: c)
    {
        result[each.first] += each.second;
    }

    return result;
}

template<typename T>
const Counter<T> Counter<T>::operator-(const Counter<T> &c)
{
    Counter<T> result;

    for(auto &each: c)
    {
        result[each.first] -= each.second;
    }

    return result;
}

template<typename T>
Counter<T> & Counter<T>::operator=(const Counter<T> &c)
{
    if(&c != this)
    {
        map<T, int>::operator=(*this, c);
    }

    return this;
}

template<typename T>
const Counter<T> Counter<T>::operator+()
{
    Counter<T> positive_c;

    for(auto &each: *this)
    {
        if(each.second > 0)
        {
            positive_c.insert(each);
        }
    }

    return positive_c;
}

template<typename T>
const Counter<T> Counter<T>::operator-()
{
    Counter<T> negative_c;

    for(auto &each: *this)
    {
        if(each.second < 0)
        {
            each.second = -each.second;
            negative_c.insert(each);
        }
    }

    return negative_c;
}

#endif