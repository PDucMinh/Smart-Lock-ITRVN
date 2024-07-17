#include "string_recognize.h"
<<<<<<< HEAD
void check_string(char* input, int size)
{
  int checkpoint = 0;
  char* tmp = input;
  for (int i = 0; i < size; i++)
  {
    checkpoint = string_recognize_fsm(*(tmp+i));
  }
}
int main()
{
  char input[] = "110101";
  char input2[] = "010010110";
  char input3[] = "10110";
  check_string(input, sizeof(input) / sizeof(input[0]));
=======

int main()
{
    char input[] = "110101";
    char input2[] = "010010110";
    char input3[] = "10110";
>>>>>>> develop
}