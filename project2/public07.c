#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Loading Document ";
   const char *target = "b";
   const char *replacement = "hello";
   int data_lines = 8;
   char data[20][MAX_STR_SIZE + 1] = {
        "bb"
   };

   init_document(&doc, doc_name);
   load_document(&doc, data, data_lines);
   print_document(&doc);
   printf("----------------\n----------------\n----------------\n");
   replace_text(&doc, target, replacement);
   print_document(&doc);

   return 0;
}
