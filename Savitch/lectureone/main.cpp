#include <iostream>

using namespace std;

int main()
{
    int year_now, month_now, age_years, month_born, another_year, another_month;

    cout << "Enter the current year then press RETURN.\n";
    cin >> year_now;

    cout << "Enter the current month (in 1-12)\n";
    cin >> month_now;

    if(month_now > 12 || month_now < 1)
    {
        cout << "Not a valid month! \n";
        return 1;
    }

    cout << "Enter your current age in years.\n";
    cin >> age_years;

    cout << "Enter your month of birth\n";
    cin >> month_born;
    if(month_born > 12 || month_born < 1)
    {
        cout << "Not a valid month! \n";
        return 1;
    }

    cout << "Enter the year for which you wish to know your age.\n";
    cin >> another_year;

    cout << "Enter the month of that year\n";
    cin >> another_month;
    if(another_month > 12 || another_month < 1)
    {
        cout << "Not a valid month! \n";
        return 1;
    }

    int gap_between_now_and_next_months = (another_year*12 + another_month) - ((year_now * 12) + month_now);
    int new_age = (age_years*12 + (month_now - month_born)) + gap_between_now_and_next_months;

    int new_months = new_age % 12;
    int new_year = (new_age - new_months) / 12;

    if (new_year > 150)
    {
        cout << "Sorry, but you'll probably be dead by the time you're " << new_year << "years old." << endl;
    }
    else if (new_age >= 0)
    {
        cout << "Your age in " << another_month << "/" << another_year << " will be: ";
        if(new_year == 1)
        {
            cout << new_year << " year and ";
        }
        else
        {
            cout << new_year << " years and ";
        }
        if(new_months == 1)
        {
            cout << new_months << " month old.";
        }
        else
        {
            cout << new_months << " months old.";
        }
        cout << endl;
    }
    else    
    {
        cout << "You weren't even born in ";
        cout << another_year << "!\n";
    }

    return 0;
}