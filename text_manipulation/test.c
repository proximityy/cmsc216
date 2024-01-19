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
   char result[MAX_STR_LEN + 1] = " t reps !";
   int word_count = 0, num_result;
    printf("initial strlen: %lu\n", strlen(result));
   num_result = compact(result, &word_count);
   printf("string: [%s] word count: [%d] result: [%d] strlen: [%lu]\n", result, word_count, num_result, strlen(result));
   test_assert(strcmp(result, "treps!") == 0 && word_count == 3 && num_result == SUCCESS, "compact", 1);

   return 0;
}
