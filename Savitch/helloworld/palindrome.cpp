#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

string reverse(const string in)
{
   string result = "";
   for (int i = (in.length() - 1); i >= 0; i--)
   {
      result += in[i];
   }
   return result;
}

bool palindrome(const string first)
{
   string reversed = reverse(first);
   return reversed == first;
}

int main()
{
   while (true)
   {
      string input;
      cout << "Input: ";
      getline(cin, input);
      if (palindrome(input))
      {
         cout << "Palindrome!\n";
      }
   }
}
