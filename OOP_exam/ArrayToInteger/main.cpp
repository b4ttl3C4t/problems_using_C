#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Atoi
{
private:
    string beConverted;
public:
    Atoi() :beConverted("")
    {
        ;
    }

    Atoi(string s) :beConverted(s)
    {
        ;
    }

    void SetString(string s)
    {
        beConverted = s;
    }

    string GetString()
    {
        string result(beConverted);
        result.erase(remove(result.begin(), result.end(), '-'), result.end());

        return result;
    }

    int Length()
    {
        if(beConverted[0] == '-')
            return beConverted.length() - 1;
        return beConverted.length();
    }
    
    bool IsDigital()
    {
        for(auto &i: beConverted)
        {
            if(!isdigit(i) && i != '-')
            {
                return false;
            }
        }
        return true;
    }

    int StringToInteger()
    {
        int result = 0, weight = 1;

        for(int i = beConverted.length() - 1; i >= 0; --i)
        {
            if(!isdigit(beConverted[i])) break;
            result += (beConverted[i] ^ '0') * weight;
            weight *= 10;
        }

        if(beConverted[0] == '-')
        {
            result *= -1;
        }

        return result;
    }
};

int main() {
	string beConverted;

	while (cin >> beConverted) {
		Atoi atoi(beConverted + "20");
		if (atoi.IsDigital()) {
			cout << atoi.Length() << endl;
			cout << atoi.StringToInteger() << endl;
			cout << atoi.GetString() << endl;
			cout << sizeof(atoi.StringToInteger()) << endl;
		}

		atoi.SetString(beConverted);
		if (atoi.IsDigital()) {
			cout << atoi.Length() << endl;
			cout << atoi.StringToInteger() << endl;
			cout << atoi.GetString() << endl;
			cout << sizeof(atoi.StringToInteger()) << endl;
		}
	}

	return 0;
}
