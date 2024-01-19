/*Zachary Meyers
  UID 120279096 */

#include <stdio.h>

/*Prototypes: */
int draw_rectangle(int width, int length, char c);
int draw_triangle(int size, char c);
int valid_character(char c);

/**********************************************/
/* The program prompts the user for a shape */
/* and shape parameters. It then generates  */
/* a shape or states the parameters aren't valid.  */
/***************************************************/

int main() {
  int input = -1;
  int width, length, size;
  char c;

  /* Main program loop */
  while(input != 0) {
    printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
    scanf("%d", &input);
    
    /* Check for invalid input or shape type */
    if(input != 0 && input != 1 && input != 2 && input != 3) {
      printf("Invalid choice.\n");
    } else if(input == 1) {
      /* Prompt for rectangle parameters */
      printf("Enter character, width and length: ");
      scanf(" %c %d %d", &c, &width, &length);
      if(draw_rectangle(width, length, c) == 0) {
	printf("Invalid data provided.\n");
      }
    } else if(input == 2) {
      /* Prompt for triangle parameters */
      printf("Enter character and size: ");
      scanf(" %c %d", &c, &size);
      if(draw_triangle(size, c) == 0) {
	printf("Invalid data provided.\n");
      }
    }
  }
  /* End program */
  printf("Bye Bye.\n");
  return 0;
}

/* Draw a rectangle using provided width, length, and char */
int draw_rectangle(int width, int length, char c) {
  int i, j;
  /* Check for validity */
  if(width <= 0 || length <= 0 || !valid_character(c)) {
    return 0;
  }
  /* Embedded for loop draws rectangle */
  for(i = 0; i < width; i++) {
    for(j = 0; j < length; j++) {
      printf("%c",c);
    }
    printf("\n");
  }
  return 1;

}

/* Draw a triangle using provided size and char */
int draw_triangle(int size, char c) {
  /* Variables to keep track of the triangle line-by-line */
  int line_length = (size * 2) - 1;
  int start_char_index = size - 1;
  int end_char_index = size;
  int i, j,k,l;
  /* Check for validity */
  if(size <= 0 || !valid_character(c)) {
    return 0;
  }
  /* Iterate through each line to draw apppriate */
  /* number of spaces and characters */
  for(i = 0; i < size; i++) {
    for(j = 0; j < start_char_index; j++) {
      printf(" ");
    }
    for(k = start_char_index; k < end_char_index; k++) {
      printf("%c",c);
    }
    for(l = end_char_index; l < line_length; l++) {
      printf(" ");
    }
    printf("\n");
    start_char_index--;
    end_char_index++;
  }
  return 1;
}

/* Check for character validity */
int valid_character(char c) {
  return (c == '%' || c == '*' || c == '#');
}
