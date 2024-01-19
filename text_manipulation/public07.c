#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"

/******************************************************** 
 * Prints a pass or fail message for the specified test.* 
 ********************************************************/
void test_assert(int test_result, const char *test_name, int test_number) {
   if (test_result)  {
      printf("pass %s %d\n", test_name, test_number);
   } else {
      printf("fail %s %d\n", test_name, test_number);
   }
}

int main() {
   char result[MAX_STR_LEN + 1] = "";
   int word_count = 0;

   compact(result, &word_count);
   printf("%s%d\n", result, word_count);
   test_assert(strcmp(result, "tttttt") == 0 && word_count == 4, "compact", 1);

   return 0;
}


/*one space. two words, followed by 3 spaces*/