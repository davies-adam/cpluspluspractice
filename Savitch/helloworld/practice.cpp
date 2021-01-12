#include <iostream>

using namespace std;

void print_array(int array[], int size);
void selection_sort(int array[], int size);
void insertion_sort(int array[], int size);
void bubble_sort(int array[], int size);

int main()
{
   const int LENGTH = 5;
   int list[LENGTH] = {10, 4, 8, 2, 6};
   print_array(list, LENGTH);
   insertion_sort(list, LENGTH);
   print_array(list, LENGTH);
}

void print_array(int array[], int size)
{
   for (int i = 0; i < size; i++)
   {
      cout << array[i] << " ";
   }
   cout << endl;
}

void selection_sort(int array[], int size)
{
   for (int i = 0; i < size; i++)
   {
      int index_of_smallest = i;
      for (int j = i; j < size; j++)
      {
         if (array[j] < array[index_of_smallest])
         {
            index_of_smallest = j;
         }
      }

      int temp = array[i];
      array[i] = array[index_of_smallest];
      array[index_of_smallest] = temp;
   }
}

void bubble_sort(int array[], int size)
{
   for (int i = size - 1; i > 0; i--)
   {
      for (int j = 0; j < i; j++)
      {
         int next = array[j + 1];
         if (array[j] > next)
         {
            array[j + 1] = array[j];
            array[j] = next;
         }
      }
   }
}

void insertion_sort(int array[], int size)
{
   for (int i = 1; i < size; i++)
   { 
      int current = array[i];
      int j = i - 1;
      while(current < array[j] && j>=0)
      {
         array[j+1] = array[j];
         j--;
      }

      array[j+1] = current;
   }
}