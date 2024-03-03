#include <iostream>
#include <vector>

using namespace std;

class Atoi
{
private:
    string beConverted;
public:
    Atoi()
    {
        ;
    } 
    Atoi(std::string s): beConverted(s)
    {
        ;
    }
    void SetString(std::string s)
    {
        beConverted = s;
    }
    std::string GetString()
    {
        if(beConverted[0] == '-')
            return beConverted.substr(1, beConverted.length());
        return beConverted;
    }
    int Length()
    {
        int result = beConverted.length();

        if(beConverted[0] == '-')
        {
            result -= 1;
        }
        
        return result;
    }
    bool IsDigital()
    {
        for(auto &each_number: beConverted)
        {
            if(!isdigit(each_number) && each_number != '-')
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
            if(beConverted[i] == '-')
            {
                result = -result;
                break;
            }
            result += (beConverted[i] ^ '0') * weight;
            weight *= 10;
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
