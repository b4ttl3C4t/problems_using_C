#ifndef MONTH_H
#define MONTH_H

class Month
{
public:
    Month();
    Month(char first, char second, char third);
    Month(int monthInt);
    void inputInt();
    void inputStr();
    void outputInt();
    void outputStr();
    int  nextMonth();
    const Month operator=(int monthInt);
private:
    int compareStr(char first, char second, char third);
    int month;
};

#endif