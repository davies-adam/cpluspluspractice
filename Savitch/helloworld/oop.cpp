#include <iostream>

using namespace std;

enum Rating
{
    G, PG, PG13, R
};

class Movie
{
public:
    Movie(string n, Rating mpaa)
    {
        name = n;
        rating = mpaa;
    }
    string getName()
    {
        return name;
    }
    Rating getRating()
    {
        return rating;
    }
    void setName(string newname)
    {
        name = newname;
    }
    void setRating(Rating newrating)
    {
        rating = newrating;
    }
    void addReview(int newreview)
    {
        if(newreview > 0 && newreview < 6)
        {
            reviews[newreview - 1]++;
        }
    }
    double getAverage()
    {
        double piles = 0;
        for(int each : reviews)
        {
            if(each > 0)
            {
                piles++;
            }
        }
        return (reviews[0] + reviews[1]*2 + reviews[2]*3 + reviews[3]*4 + reviews[4]*5) / piles;
    }
    friend bool equal(Movie a, Movie b)
    {
        return (a.name == b.name) && (a.rating == b.rating);
    }
private:
    string name;
    Rating rating;
    int reviews[5] = {0, 0, 0, 0, 0};
};



class MyString
{
public:
    MyString(int length)
    {
        value = new char[length + 1];
        max = length;
    }
    MyString(const char a[])
    {
        value = new char[strlen(a) + 1];
        strcpy(value, a);
    }
    MyString(const MyString& other)
    {
        value = new char[other.length() + 1];
        strcpy(value, other.value);
    }
    ~MyString()
    {
        delete[] value;
    }
    void operator = (const MyString rightside)
    {
        
    }
    int length() const
    {
        return strlen(value);
    }
    void inputStream(istream& in)
    {
        in.getline(value, max + 1);
    }
    friend ostream& operator <<(ostream& out, const MyString& given)
    {
        if(strlen(given.value) == 0)
        {
            out << "<no value>" << endl;;
            return out;
        }
        out << given.value << endl;
        return out;
    }
private:
    char *value;
    int max;
};

class DecimalBookInfo
{
public:
    DecimalBookInfo(string title, double classification)
    {
        name = title;
        code = classification;
    }
    DecimalBookInfo(string title, int subject, int subcategory)
    {
        name = title;
        code = subject + subcategory/1000.0;
    }
    string getName()
    {
        return name;
    }
    double getCode()
    {
        return code;
    }
    friend bool operator <(DecimalBookInfo& left,  DecimalBookInfo& right)
    {
        return left.code < right.code;
    }
    friend bool operator >(DecimalBookInfo& left, DecimalBookInfo& right)
    {
        return left.code > right.code;
    }
    friend bool operator <=(DecimalBookInfo& left, DecimalBookInfo& right)
    {
        return left.code <= right.code;
    }
    friend bool operator >=(DecimalBookInfo& left, DecimalBookInfo& right)
    {
        return left.code >= right.code;
    }
    friend ostream& operator <<(ostream& out, DecimalBookInfo& book)
    {
        out << book.code;
        return out;
    }
private:
    string name;
    double code;
};



void conversation(int maxname)
{
    MyString in(maxname), fixed("Borg");
    in.inputStream(cin);
    cout << in;
}

class Money
{
public:
    Money(int dollars, int cents)
    {
        if (dollars * cents > 0)
        {
            allcents += dollars * 100;
            allcents += cents;
        }
    }
    Money(long cents)
    {
        allcents = cents;
    }
    Money(istream &in)
    {
        bool isNegative;
        char first, decimalpoint;
        long before, after;

        cout << "Enter value (in format -$20.42): ";

        in >> first;

        if (first == '$')
        {
            isNegative = false;
        }
        else if (first == '-')
        {
            char dollarsign;
            isNegative = true;
            in >> dollarsign;
        }
        in >> before >> decimalpoint >> after;

        allcents = before * 100 + after;

        if (isNegative)
        {
            allcents = -allcents;
        }
    }
    double toValue()
    {
        return allcents / 100.0;
    }
    int toCents()
    {
        return allcents;
    }
    const void output(ostream &out)
    {
        long dollars, cents;
        if (allcents < 0)
        {
            out << '-';
        }

        dollars = labs(allcents) / 100;
        cents = labs(allcents) % 100;
        out << '$' << dollars << '.';
        if (cents < 10)
        {
            out << '0';
        }
        out << cents;
    }
    Money operator ++ (int)
    {
        return Money(allcents++);
    }
    friend bool operator == (const Money& a, const Money& b)
    {
        return a.allcents == b.allcents;
    }
    friend bool operator !=(const Money& a, const Money& b)
    {
        return a.allcents != b.allcents;
    }
    friend Money operator +(const Money& a, Money& b)
    {
        return Money(a.allcents + b.allcents);
    }


private:
    long allcents = 0;
};

int main()
{
    Movie m = Movie("Star Wars", PG);
    cout << m.getName();
    m.addReview(5);
    m.addReview(1);
    m.addReview(4);
    cout << endl << m.getAverage();
    cout << endl << equal(m, Movie("Star Wars", PG));
}