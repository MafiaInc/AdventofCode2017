#include <stdio.h>
#define ROW_SIZE 16

/* --- Day 2: Corruption Checksum ---

As you walk through the door, a glowing humanoid shape yells in your direction. "You there! Your state appears to be idle. Come help us repair the corruption in this spreadsheet - if we take another millisecond, we'll have to display an hourglass cursor!"

The spreadsheet consists of rows of apparently-random numbers. To make sure the recovery process is on the right track, they need you to calculate the spreadsheet's checksum. For each row, determine the difference between the largest value and the smallest value; the checksum is the sum of all of these differences.

For example, given the following spreadsheet:

5 1 9 5
7 5 3
2 4 6 8

    The first row's largest and smallest values are 9 and 1, and their difference is 8.
    The second row's largest and smallest values are 7 and 3, and their difference is 4.
    The third row's difference is 6.

In this example, the spreadsheet's checksum would be 8 + 4 + 6 = 18.

What is the checksum for the spreadsheet in your puzzle input?

Your puzzle answer was 48357.
--- Part Two ---

"Great work; looks like we're on the right track after all. Here's a star for your effort." However, the program seems a little worried. Can programs be worried?

"Based on what we're seeing, it looks like all the User wanted is some information about the evenly divisible values in the spreadsheet. Unfortunately, none of us are equipped for that kind of calculation - most of us specialize in bitwise operations."

It sounds like the goal is to find the only two numbers in each row where one evenly divides the other - that is, where the result of the division operation is a whole number. They would like you to find those numbers on each line, divide them, and add up each line's result.

For example, given the following spreadsheet:

5 9 2 8
9 4 7 3
3 8 6 5

    In the first row, the only two numbers that evenly divide are 8 and 2; the result of this division is 4.
    In the second row, the two numbers are 9 and 3; the result is 3.
    In the third row, the result is 2.

In this example, the sum of the results would be 4 + 3 + 2 = 9.

What is the sum of each row's result in your puzzle input?
 */

void main() {
   FILE *fp;
   int number = 0;
   int index = 0;
   int array[ROW_SIZE];
   int min_val = 0;
   int max_val = 0;
   int hash_value = 0;
   int hash_mod_value = 0;

   fp = fopen("corruption_checksum_input.txt", "r");

   if (fp != NULL) {
      // read all the number from the file opened
      while(fscanf(fp, "%d", &number) == 1)
      {
         array[index] = number;
#ifdef DEBUG
         printf("Index : %d , val : %d\n", index, array[index]);
#endif

         // if we reached the defined row size
         if(index == (ROW_SIZE - 1))
         {
            // find min and max values of current row
            max_val = min_val = array[0];
            for (int i = 0; i < ROW_SIZE; i++)
            {
              if (array[i] < min_val)
              {
                 min_val = array[i];
              }

              if (array[i] > max_val)
              {
                 max_val = array[i];
              }

              /* Part Two requirements */
              for (int j = i+1; j < ROW_SIZE; j++)
              {
                 if (array[i] % array[j] == 0)
                 {
                    hash_mod_value += (array[i] / array[j]);
                 }
                 else if (array[j] % array[i] == 0)
                 {
                    hash_mod_value += (array[j] / array[i]);
                 }
              }
              /* end of Part Two */
            }

            // add to the hash value
            hash_value += (max_val - min_val);

            // restart the index
            index = 0;
            continue;
         }
         index++;
      }
      printf("MIN-MAX HASH: %d\n", hash_value);
      printf("MOD HASH: %d\n", hash_mod_value);
   } else {
      printf("Can't open input file: 'corruption_checksums_input.txt'!\n");
   }
}
