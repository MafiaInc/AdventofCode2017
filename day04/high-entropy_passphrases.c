#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define PASSPHRASE_LENGTH       350
#define MAX_WORDS_IN_PASSPHRASE 30

/* Return array of pointers as words[] and number of words
 * found in a given line up to the max_words set */
int getwords(int max_words, char *words[], char *line)
{
   int number_words = 0;
   char *lp = line;

   while (number_words < max_words)
   {
      /* Look for leading space just in case */
      while (isspace(*lp))
      {
         lp++;
      }

      /* if we managed to reach to the end of line we are done */
      if ((*lp == '\0') || (*lp == '\n'))
      {
         return number_words;
      }

      /* record the address of the word start in our words array
       * increment the number of words found */
      words[number_words++] = lp;

      /* look for non space characters not being end of string */
      while (!isspace(*lp) && *lp != '\0')
      {
         lp++;
      }

      /* if we managed to reach to the end of string we are done */
      if (*lp == '\0')
      {
         return number_words;
      }

      /* this should be a whitespace, change it to end of word */
      *lp++ = '\0';
   }

   return number_words;
}

void main()
{
   FILE *fp;
   char passphrase[PASSPHRASE_LENGTH];
   char *words[MAX_WORDS_IN_PASSPHRASE];
   int nwords;
   int valid_pass = 0;
   passphrase[0] = '\0';

   fp = fopen("high-entropy_passphrases_input.txt", "r");

LOOP:
   while (fgets(passphrase, (PASSPHRASE_LENGTH-1), fp) != NULL)
   {
      valid_pass++;
#ifdef DEBUG
      printf("For : %s", passphrase);
#endif
      nwords = getwords(MAX_WORDS_IN_PASSPHRASE, words, passphrase);
      for (int i = 0; i < nwords; i++)
      {
         for (int d = (nwords-1); d != i; d--)
         {
            if (strcmp(words[i], words[d]) == 0)
            {
               /* decrease the number of valid passphrases */
               valid_pass--;
#ifdef DEBUG
               printf("Word - %s-%d == %s-%d\n", words[i], i, words[d], d);
#endif
               /* We like to move it move it ... */
               goto LOOP;
            }
         }
      }
   }

   printf("Number of valid passphases found: %d\n", valid_pass);
}
