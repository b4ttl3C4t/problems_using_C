#include <algorithm>
#include <vector>
#include <map>

using namespace std;

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

// Internal function for function *most_common* .
template<typename T>
inline static bool complPairVector(pair<T, int> p1, pair<T, int> p2)
{
    return p1.second > p2.second;
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
    
    sort(counts.begin(), counts.end(), complPairVector);

    vector<T> result;

    for (auto &i: counts)
    {
        result.push_back(i.second);
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
    Counter<T> result;

    for(auto &each: *this)
    {
        ++result[each];
    }

    for(auto &each: c)
    {
        ++result[each];
    }

    return result;
}

template<typename T>
const Counter<T> Counter<T>::operator-(const Counter<T> &c)
{
    Counter<T> result;

    for(auto &each: *this)
    {
        ++result[each];
    }

    for(auto &each: c)
    {
        --result[each];
    }

    return result;
}

template<typename T>
const Counter<T> Counter<T>::operator+()
{
    Counter<T> positive_c;

    for(auto &each: *this)
    {
        if(each.second <= 0)
        {
            continue;
        }

        positive_c.insert(each);
    }

    return positive_c;
}

template<typename T>
const Counter<T> Counter<T>::operator-()
{
    Counter<T> negative_c;

    for(auto &each: *this)
    {
        if(each.second >= 0)
        {
            continue;
        }

        // As the note in sheet, 
        // you have to flip the sign on each count.
        each.second = -each.second;
        negative_c.insert(each);
    }

    return negative_c;
}