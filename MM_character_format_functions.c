#include "main.h"

/**
 * print_string - Prints a string character by character.
 * @l: va_list arguments from _printf.
 * @f: Pointer to the struct flags that determines if a flag is passed to _printf.
 *
 * Description: This function takes a string as input and prints each character
 * in the string. If the string is NULL, it prints "(null)".
 *
 * Return: The number of characters printed.
 */
int print_string(va_list l, flags_t *f)
{
    char *s = va_arg(l, char *);

    (void)f;

    if (!s)
        s = "(null)";

    return (_puts(s));
}

/**
 * print_char - Prints a single character.
 * @l: va_list arguments from _printf.
 * @f: Pointer to the struct flags that determines if a flag is passed to _printf.
 *
 * Description: This function takes a character as input and prints it.
 *
 * Return: Always returns 1 as it prints a single character.
 */
int print_char(va_list l, flags_t *f)
{
    (void)f;
    _putchar(va_arg(l, int));
    return (1);
}
