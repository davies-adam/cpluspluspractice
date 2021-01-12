#include <iostream>

using namespace std;

const int WIDTH = 4;
const int HEIGHT = 4;

//const int WIDTH = 80;
//const int HEIGHT = 22;

void render(bool const generation[][HEIGHT])
{
   for (int i = 0; i < WIDTH; i++)
   {
      for (int j = 0; j < HEIGHT; j++)
      {
         if(generation[i][j])
         {
            cout << '*';
         }
         else
         {
            cout.put(' ');
         }
      }
      cout << endl;
   }
   cout << endl;
}

//chunk is 3x3
bool apply_rule(const bool chunk[][3])
{
   int count = chunk[0][0] + chunk[0][1] + chunk[0][2] + chunk[1][0] + chunk[1][2] + chunk[2][0] + chunk[2][1] + chunk[2][1];

   if (chunk[1][1] && ((count == 2) || (count == 3)))
   {
      return true;
   }
   else if (!chunk[1][1] && count == 3)
   {
      return true;
   }
   else
   {
      return false;
   }
}

// initial[WIDTH][HEIGHT], RESULTS[3][3]
void get_neighbors(const bool initial[][HEIGHT], int row, int column, bool results[][3])
{
   bool not_top = row != 0;
   bool not_left = column != 0;
   bool not_bottom = row != HEIGHT - 1;
   bool not_right = row != WIDTH - 1;

   results[1][1] = initial[row][column];

   if (not_top)
   {
      results[0][1] == initial[row - 1][column];
      if (not_left)
      {
         results[0][0] = initial[row - 1][column - 1];
      }
      if (not_right)
      {
         results[0][2] = initial[row - 1][column + 1];
      }
   }
   if (not_left)
   {
      results[1][0] = initial[row][column - 1];
   }
   if (not_right)
   {
      results[1][2] = initial[row][column + 1];
   }
   if (not_bottom)
   {
      results[2][1] = initial[row + 1][column];
      if (not_left)
      {
         results[2][0] = initial[row + 1][column - 1];
      }
      if (not_right)
      {
         results[2][2] = initial[row + 1][column + 1];
      }
   }
}

void tick(bool old[][HEIGHT],  bool *next[][HEIGHT])
{
   for (int i = 0; i < WIDTH; i++)
   {
      for (int j = 0; j < HEIGHT; j++)
      {
         bool results[3][3] = {};
         get_neighbors(old, i, j, results);

         bool result = apply_rule(results);
         *next[i][j] = apply_rule(results);
      }
   }
}

int main()
{
   bool init[WIDTH][HEIGHT] = {};
   bool second[WIDTH][HEIGHT] = {};

   for (int i = 0; i < WIDTH; i++)
   {
      init[i][0] = true;
   }
   init[0][2] = 1;
   render(init);

   while (true)
   {
      if (cin.get() == '\n')
      {
         render(second);
         tick(init, &second);
         render(second);
      }
   }
}
