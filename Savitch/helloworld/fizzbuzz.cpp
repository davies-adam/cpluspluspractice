#include <iostream>

using namespace std;

int iterativefactorial(int n)
{
   int result = 1;
   for (int i=n; i>0; i--)
   {
      result *= i;
   }
   return result;
}

int main()
{
   int counter = 100;
   while(counter > 1)
   {
      bool divisible_by_five = (counter % 5) == 0;
      bool divisibe_by_three = (counter % 3) == 0;
      if(divisibe_by_three && divisible_by_five) 
      {
         cout << "Fizzbuzz \n";
      }
      else if (divisible_by_five)
      {
         cout << "Fizz \n";
      }
      else if (divisibe_by_three)
      {
         cout << "Buzz \n";
      }
      else
      {
         cout << counter << endl;
      }
      counter = counter - 1;
   }
}
