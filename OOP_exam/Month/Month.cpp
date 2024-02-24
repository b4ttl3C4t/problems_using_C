#include <iostream>
#include <string>

#include "Month.h"

using namespace std;

Month::Month() :month(1)
{
    ;
}

Month::Month(char first, char second, char third)
{
    month = compareStr(first, second, third);
}

Month::Month(int monthInt) :month(1)
{
    if(1 <= monthInt && monthInt <= 12)
    {
        month = monthInt;
    }
}

void Month::inputInt()
{
    int monthInt = 0;

    cin >> monthInt;

    month = 1;

    if(1 <= monthInt && monthInt <= 12)
    {
        month = monthInt;
    }
}

void Month::inputStr()
{
    char first, second, third;

    cin >> first >> second >> third;

    month = compareStr(first, second, third);
}

void Month::outputInt()
{
    cout << month;
}

void Month::outputStr()
{
    switch(month)
    {
    case 1:
        cout << "Jan";
        break;
    case 2:
        cout << "Feb";
        break;
    case 3:
        cout << "Mar";
        break;
    case 4:
        cout << "Apr";
        break;
    case 5:
        cout << "May";
        break;
    case 6:
        cout << "Jun";
        break;
    case 7:
        cout << "Jul";
        break;
    case 8:
        cout << "Aug";
        break;
    case 9:
        cout << "Sep";
        break;
    case 10:
        cout << "Oct";
        break;
    case 11:
        cout << "Nov";
        break;
    case 12:
        cout << "Dec";
        break;
    }
}

int Month::nextMonth()
{
    ++month;

    if(month > 12)
    {
        month = 1;
    }

    return month;
}

const Month Month::operator=(int monthInt)
{
    month = monthInt;

    return *this;
}

int Month::compareStr(char first, char second, char third)
{
    int result = 1;
    string temp;
    
    temp += first;
    temp += second;
    temp += third;
    
    if(temp == "Jan")
    {
        result = 1;
    }
    else if (temp == "Feb")
    {
        result = 2;
    }
    else if (temp == "Mar")
    {
        result = 3;
    }
    else if (temp == "Apr")
    {
        result = 4;
    }
    else if (temp == "May")
    {
        result = 5;
    }
    else if (temp == "Jun")
    {
        result = 6;
    }
    else if (temp == "Jul")
    {
        result = 7;
    }
    else if (temp == "Aug")
    {
        result = 8;
    }
    else if (temp == "Sep")
    {
        result = 9;
    }
    else if (temp == "Oct")
    {
        result = 10;
    }
    else if (temp == "Nov")
    {
        result = 11;
    }
    else if (temp == "Dec")
    {
        result = 12;
    }

    return result;
}
