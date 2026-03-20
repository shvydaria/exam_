#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int ft_scanf(const char *format, ...) {
    va_list args;
    int count = 0;
    int c;

    va_start(args, format);

    while (*format){
        if (isspace(*format)){
            while (isspace(c = fgetc(stdin)))
            if (c != EOF)
                ungetc(c, stdin);
            while (isspace(*format))
                format++;
            continue;
        }
        if (*format == '%' && (*(format + 1) == 'd' || *(format + 1) == 's' || *(format + 1) == 'c')){
            format++;
            if (*format == 'd')
            {
                int *n = va_arg(args, int *);
                int sign = 1;
                
                while (isspace(c = fgetc(stdin)));
                if (c == EOF) { if (count == 0) count = EOF; break; }
                
                if (c == '-' || c == '+') {
                    if (c == '-') sign = -1;
                    c = fgetc(stdin);
                }
                
                if (!isdigit(c)) { 
                    if (c != EOF) ungetc(c, stdin); 
                    break;
                }
                
                *n = 0;
                while (isdigit(c)) {
                    *n = (*n * 10) + (c - '0');
                    c = fgetc(stdin);
                }
                *n *= sign;
                if (c != EOF) ungetc(c, stdin);
                count++;
            }
            else if (*format == 's'){
                char *s = va_arg(args, char *);
                
                while (isspace(c = fgetc(stdin)));
                if (c == EOF) { if (count == 0) count = EOF; break; }
                
                int i = 0;
                while (c != EOF && !isspace(c)) {
                    s[i++] = c;
                    c = fgetc(stdin);
                }
                s[i] = '\0';
                if (c != EOF) ungetc(c, stdin);
                count++;
            }
            else if (*format == 'c'){
                char *ch = va_arg(args, char *);
                c = fgetc(stdin);
                if (c == EOF) { if (count == 0) count = EOF; break; }
                
                *ch = c;
                count++;
            }
        }
        else {
            c = fgetc(stdin);
            if (c == EOF && count == 0) {
                count = EOF;
                break;
            }
            if (c != *format) {
                if (c != EOF) ungetc(c, stdin);
                break; // Mismatch!
            }
        }
        format++;
    }

    va_end(args);
    return (count);
}