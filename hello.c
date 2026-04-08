void terminal_write(const char *str, int len) {
    for (int i = 0; i < len; i++) {
        *(char*)(0x10000000) = str[i];
    }
}

/* Uncomment line11 - line39
 * when implementing formatted output
 */

#include <stdlib.h>  // for itoa() and utoa()
#include <string.h>  // for strlen() and strcat()
#include <stdarg.h>  // for va_start(), va_end(), va_arg() and va_copy()

void format_to_str(char* out, const char* fmt, va_list args) {
    for(out[0] = 0; *fmt != '\0'; fmt++) {
        if (*fmt != '%') {
            strncat(out, fmt, 1);
        } else {
            fmt++;
            if (*fmt == 's') {
                strcat(out, va_arg(args, char*));
            } else if (*fmt == 'd') {
                itoa(va_arg(args, int), out + strlen(out), 10);
            }
             else if (*fmt == 'l' && *(fmt + 1) == 'l' && *(fmt + 2) == 'u') {
                fmt+=2;
                unsigned long long c = va_arg(args, unsigned long long);
                char buf[21];
                buf[20] = '\0';
                int i = 19;
                while(c > 0) {
                    buf[i] = '0' + (c % 10);
                    c /= 10;
                    i--;
                }
                strcat(out, buf + i + 1);
            }
             else if (*fmt == 'c') {
                char c = (char)va_arg(args, int);
                strncat(out, &c, 1);
            }
             else if (*fmt == 'x') {
                int c = (int)va_arg(args, int);
                char buf[9];
                utoa(c, buf, 16);
                strcat(out, buf);
            }
             else if (*fmt == 'u') {
                unsigned int c = (unsigned int)va_arg(args, unsigned int);
                char buf[10];
                utoa(c, buf, 10);
                strcat(out, buf);
            }
             else if (*fmt == 'p') {
                void* c = va_arg(args, void*);
                char buf[19];
                utoa((unsigned long)c, buf, 16);
                strcat(out, "0x");
                strcat(out, buf);
            }
        }
    }
}

int printf(const char* format, ...) {
    char buf[512];
    va_list args;
    va_start(args, format);
    format_to_str(buf, format, args);
    va_end(args);
    terminal_write(buf, strlen(buf));

    return 0;
}


/* Uncomment line46 - line57
 * when implementing dynamic memory allocation
 */

extern char __heap_start, __heap_end;
static char* brk = &__heap_start;
char* _sbrk(int size) {
    if (brk + size > (char*)&__heap_end) {
        terminal_write("_sbrk: heap grows too large\r\n", 29);
        return NULL;
    }

    char* old_brk = brk;
    brk += size;
    return old_brk;
}


int main() {
    char* msg = "Hello, World!\n\r";
    terminal_write(msg, 15);

    /* Uncomment this line of code
     * when implementing formatted output
     */
     printf("%s-%d is awesome!\n\r", "egos", 2000);
     printf("%c is character $\n", '$');
     printf("%c is character 0\n", (char)48);
     printf("%x is integer 1234 in hexadecimal\n", 1234);
     printf("%u is the maximum of unsigned int\n", (unsigned int)0xFFFFFFFF);
     printf("%p is the hexadecimal address of the hello-world string\n", msg);
     printf("%llu is the maximum of unsigned long long\n", 0xFFFFFFFFFFFFFFFFULL);

    return 0;
}
