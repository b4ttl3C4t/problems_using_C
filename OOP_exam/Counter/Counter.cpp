#include "Counter.h"

/*
template<typename T>
class Counter: public map
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
*/

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
inline vector<T> Counter<T>::most_common(int n)
{
    vector<pair<T, int>> count;

    for (auto i: this)
    {
        count.push_back(pair<T, int>(i->first, i->second));
    }
    
}