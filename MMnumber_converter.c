#include "main.h"

/**
 * convert - Converts a number into a string representation using a given base.
 * @num: The input number.
 * @base: The input base.
 * @lowercase: Flag to indicate whether hex values should be lowercase.
 * Return: The resulting string.
 */
char *convert(unsigned long int num, int base, int lowercase)
{
	static char *rep;
	static char buffer[50];
	char *ptr;

	rep = (lowercase)
		? "0123456789abcdef"
		: "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num != 0);

	return (ptr);
}

