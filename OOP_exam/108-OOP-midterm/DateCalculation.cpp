#include <iostream>
#include <vector>

using namespace std;

static const unsigned char MONTH[] =
{
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static inline const int fromDateToDay(const Date& date)
{
    int result = 0;
    
    result += date.m_year * 365;

    for(int i = 1; i < date.m_month; ++i)
    {
        result += MONTH[i];
    }

    result += date.m_day;

    return result;
}

static inline const Date fromDayToDate(int day)
{
    int temp;
    Date result;

    result.m_year = day / 365;
    day %= 365;

    result.m_month = 1;
    for(int i = 1; i <= 11; ++i)
    {
        if(day < MONTH[i])
        {
            break;
        }

        day -= MONTH[i];
        result.m_month += 1;
    }

    result.m_day = day;

    return result;
}

class Date
{
public:
    int m_year;
    int m_month;
    int m_day;
public:
    Date(int y, int m, int d)
    : m_year(y), m_month(m), m_day(d)
    {
        ;
    }
    Date(void)
    : m_year(0), m_month(0), m_day(0)
    {
        ;
    }
    Date& operator=(const Date& object)
    {
        m_year  = object.m_year;
        m_month = object.m_month;
        m_day   = object.m_day;
    }
    bool check()
    {
        if(m_year > 2020)
        {
            return false;
        }
        if(m_day > MONTH[m_month])
        {
            return false;
        }
        return true;
    }
    bool operator>(const Date& object)
    {
        if(fromDateToDay(*this) > fromDateToDay(object))
        {
            return true;
        }
        return false;
    }
    bool operator<(const Date& object)
    {
        if(fromDateToDay(*this) < fromDateToDay(object))
        {
            return true;
        }
        return false;
    }
    
5.	Define operator – :
5.1	Date – Date : Return the number of days between the first and the second arguments (operands). For example, the number of days between 2020/1/1 and 2020/1/2 is 1, and the number of days between 2020/1/2 and 2020/1/1 is also 1.)
5.2	Date – N days : Return the date that is N days before the input date.
6.	Define operator + :
6.1	Date + N days : Return the date that is N days after the input date.
6.2	N days + Date : Return the date that is N days after the input date.
};

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
