#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int print_int(int num) {
  int remainder = 0;
  int chars[1024];
  int i = 0;

  while (num > 0) {
    remainder = num % 10;
    remainder += 48;
    chars[i] = remainder;
    num = num / 10;
    i++;
  }

  for (int j = i; j >= 0; j--) {
    int character = chars[j];
    write(1, &character, 1);
  }
  return i;
}

int print_float(float num) {
  int decimal_part = (int)(num);
  int n_digits_decimal = 0;

  int temp = decimal_part;
  while (temp > 0) {
    temp = temp / 10;
    n_digits_decimal++;
  }
  float rational_part = num - decimal_part;
  int decimal_rational_part =
      (int)(rational_part * pow(10.0, n_digits_decimal));

  print_int(decimal_part);
  int ascii_comma = 44;
  write(1, &ascii_comma, 1);
  print_int(decimal_rational_part);

  return 0;
}

int ft_printf(const char *str, ...) {
  int i = 0;
  va_list list;
  va_start(list, str);
  while (str[i]) {
    if (str[i] == '%') {
      switch (str[i + 1]) {
      case 's':
        char *arg1 = va_arg(list, char *);
        write(1, arg1, strlen(arg1));
        break;
      case 'c':
        int arg2 = va_arg(list, int);
        write(1, &arg2, 1);
        break;
      case 'd':
        int arg3 = va_arg(list, int);
        print_int(arg3);
        break;
      case 'f':
        double arg4 = va_arg(list, double);
        print_float(arg4);
        break;
      default:
        break;
      }
    }

    if (str[i] == '\n') {
      char newline = '\n';
      write(1, &newline, 1);
    } else if (str[i] == '\t') {
      char tab = '\t';
      write(1, &tab, 1);
    }
    i++;
  }
  va_end(list);
  return 0;
}

int main(void) {
  float num = 932.34;
  ft_printf("\t%f\n", num);
  return 0;
}
