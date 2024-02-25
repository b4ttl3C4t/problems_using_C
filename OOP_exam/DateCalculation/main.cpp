#include <iostream>

using namespace std;

static const int MONTH_TO_DAY[13] = 
{
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

class Date
{
public:
    int m_year;
    int m_month;
    int m_day;

    Date(void)
    : m_year(1), m_month(1), m_day(1)
    {
        ;
    }

    Date(int year, int month, int day)
    : m_year(year), m_month(month), m_day(day)
    {
        ;
    }

    bool check(void) const
    {
        if(m_year <= 2020 && (
            (m_month == 1 && m_day <= MONTH_TO_DAY[1]) || 
            (m_month == 2 && m_day <= MONTH_TO_DAY[2]) || 
            (m_month == 3 && m_day <= MONTH_TO_DAY[3]) || 
            (m_month == 4 && m_day <= MONTH_TO_DAY[4]) || 
            (m_month == 5 && m_day <= MONTH_TO_DAY[5]) || 
            (m_month == 6 && m_day <= MONTH_TO_DAY[6]) || 
            (m_month == 7 && m_day <= MONTH_TO_DAY[7]) || 
            (m_month == 8 && m_day <= MONTH_TO_DAY[8]) || 
            (m_month == 9 && m_day <= MONTH_TO_DAY[9]) || 
            (m_month == 10 && m_day <= MONTH_TO_DAY[10]) || 
            (m_month == 11 && m_day <= MONTH_TO_DAY[11]) || 
            (m_month == 12 && m_day <= MONTH_TO_DAY[12])
        ))
        {
            return true;
        }

        return false;
    }

    bool operator>(const Date& another) const
    {
        if(m_year > another.m_year)
        {
            return true;
        }
        else if(m_month > another.m_month)
        {
            return true;
        }
        else if(m_day > another.m_day)
        {
            return true;
        }
        return false;
    }

    bool operator<(const Date& another) const
    {
        if(m_year < another.m_year)
        {
            return true;
        }
        else if(m_month < another.m_month)
        {
            return true;
        }
        else if(m_day < another.m_day)
        {
            return true;
        }
        return false;
    }
    
    Date& operator=(const Date& another)
    {
        if(this != &another)
        {
            m_year = another.m_year;
            m_month = another.m_month;
            m_day = another.m_day;
        }

        return *this;
    }
};

int SumDate(const Date& date)
{
    int result = 0;

    for(int i = 1; i <= date.m_month; ++i)
    {
        result += MONTH_TO_DAY[i];
    }

    return date.m_year * 365 + result + date.m_day;
}

unsigned int operator-(const Date& date1, const Date& date2)
{
    return abs(SumDate(date1) - SumDate(date2));
}

unsigned int operator-(Date& date, int number)
{
    Date result;
    
    result.m_day = date.m_day - number;
    while(result.m_day <= 0)
    {

    }
}

unsigned int operator+(const Date& date, int number)
{
    ;
}

unsigned int operator+(int number, const Date& date)
{
    ;
}

int main(void) 
{
	enum COMMAND { GREATER = 1, SMALLER, BETWEEN, D_SUB_N, D_PLUS_N, N_PLUS_D };
	int command, y1, m1, d1, y2, m2, d2, num;
	cin >> command;
	while (command != 0) 
	{
		switch (command)
		{
		case GREATER:
		{
			cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
			Date date1(y1, m1, d1), date2(y2, m2, d2);
			if (date1.check() && date2.check())
				cout << (date1 > date2 ? "true" : "false") << endl;
			else 
				cout << "Error Input." << endl;
			break;
		}
		case SMALLER:
		{
			cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
			Date date1(y1, m1, d1), date2(y2, m2, d2);
			if (date1.check() && date2.check())
				cout << (date1 < date2 ? "true" : "false") << endl;
			else 
				cout << "Error Input." << endl;
			break;
		}
		case BETWEEN:
		{
			cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
			Date date1(y1, m1, d1), date2(y2, m2, d2);
			if (date1.check() && date2.check())
				cout << (date1 - date2) << endl;
			else 
				cout << "Error Input." << endl;
			break;
		}
		case D_SUB_N:
		{
			cin >> y1 >> m1 >> d1 >> num;
			Date date(y1, m1, d1);
			if (date.check()) 
			{
				Date ansDate = date - num;
				cout << ansDate.m_year << "/" << ansDate.m_month << "/" << ansDate.m_day << endl;
			}
			else 
				cout << "Error Input." << endl;
			break;
		}
		case D_PLUS_N:
		{
			cin >> y1 >> m1 >> d1 >> num;
			Date date(y1, m1, d1);
			if (date.check()) 
			{
				Date ansDate = date + num;
				cout << ansDate.m_year << "/" << ansDate.m_month << "/" << ansDate.m_day << endl;
			}
			else 
				cout << "Error Input." << endl;
			break;
		}
		case N_PLUS_D:
		{
			cin >> num >> y1 >> m1 >> d1;
			Date date(y1, m1, d1);
			if (date.check())
			{
				Date ansDate = num + date;
				cout << ansDate.m_year << "/" << ansDate.m_month << "/" << ansDate.m_day << endl;
			}
			else 
				cout << "Error Input." << endl;
			break;
		}
		}
		cin >> command;
	}
	return 0;
}
