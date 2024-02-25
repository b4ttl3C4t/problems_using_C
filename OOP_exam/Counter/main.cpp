#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

template <typename T>
class Counter: public map<T, int>
{
public:
    Counter()
    {
        ;
    }
    
    Counter(vector<T> &items)
    {
        for(auto &item: items)
        {
            ++(*this)[item];
        }
    }

    vector<T> most_common(int n = -1)
    {
        vector<pair<T, int>> buffer;

        for(auto &each: *this)
        {
            buffer.push_back({each.first, each.second});
        }

        sort(buffer.begin(), buffer.end(), [](pair<T, int> x, pair<T, int> y)
        {
            return x.second > y.second;
        });

        vector<T> result;

        if(n <= 0)
        {
            n = buffer.size();
        }

        for(int i = 0; i < n; ++i)
        {
            result.push_back(buffer[i].first);
        }

        return result;
    }

    void subtract()
    {
        for(auto &each: *this)
        {
            --each.second;
        }
    }

    void subtract(T key)
    {
        --(*this)[key];
    }

    void subtract(vector<T> keys)
    {
        for(auto &key: keys)
        {
            --(*this)[key];
        }
    }

    const Counter<T> operator+(const Counter<T> & inputs)
    {
        Counter<T> result = *this;

        for(auto &input: inputs)
        {
            result[input.first] += input.second;

            if(result[input.first] <= 0)
            {
                result.erase(input.first);
            }
        }

        return result;
    }

    const Counter<T> operator-(const Counter<T> & inputs)
    {
        Counter<T> result = *this;

        for(auto &input: inputs)
        {
            result[input.first] -= input.second;

            if(result[input.first] <= 0)
            {
                result.erase(input.first);
            }
        }

        return result;
    }
    
    const Counter<T> operator+()
    {
        Counter<T> result;
        
        for(auto &each: *this)
        {
            if(each.second > 0)
            {
                result[each.first] = each.second;
            }
        }

        return result;
    }

    const Counter<T> operator-()
    {
        Counter<T> result;

        for(auto &each: *this)
        {
            if(each.second < 0)
            {
                result[each.first] = -each.second;
            }
        }

        return result;
    }

    const Counter<T> operator=(const Counter<T> & x)
    {
        if(this != &x)
        {
            map<T, int>::operator=(*this, x);
        }

        return this;
    }
};

int main(void)
{
    vector<int> v  = {1, 2, 3, 4, 5, 5, 2, 1, 1, 0, 3, 2};
    vector<int> v2 = {2, 2, 1, 4, 0, 1, 2, 1, 2, 0, 3, 2};
    Counter<int> c1(v);
    Counter<int> c2(v2);
    Counter<int> c3 = -c1;

    for(auto &each: c1)
    {
        cout << each.first << " " << each.second << endl;
    }
    cout << endl;

    for(auto &each: c2)
    {
        cout << each.first << " " << each.second << endl;
    }
    cout << endl;

    for(auto &each: c3)
    {
        cout << each.first << " " << each.second << endl;
    }
    cout << endl;

    return 0;
}