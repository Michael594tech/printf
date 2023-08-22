#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Writes a single character to the buffer
 * @c: The character to be written.
 * @buffer: The buffer array to handle printing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}
/**
 * write_unsgnd - Writes an unsigned number to the buffer
 * @is_negative: Indicates if the number is negative (unused for unsigned numbers).
 * @ind: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle printing.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier (unused for unsigned numbers).
 *
 * Return: Number of characters written.
 */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
    int length = BUFF_SIZE - ind - 1, i = 0;
    char padd = ' ';

    UNUSED(is_negative);
    UNUSED(size);

    if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        return (0); /* printf(".0d", 0)  no character is printed */

    if (precision > 0 && precision < length)
        padd = ' ';

    while (precision > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    if (width > length)
    {
        for (i = 0; i < width - length; i++)
            buffer[i] = padd;

        buffer[i] = '\0';

        if (flags & F_MINUS) /* Assign extra character to the left of buffer [buffer>padd] */
        {
            return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
        }
        else /* Assign extra character to the left of padding [padd>buffer] */
        {
            return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
        }
    }

    return (write(1, &buffer[ind], length));
}
/**
 * write_pointer - Write a memory address to the buffer
 * @buffer: Buffer array of characters.
 * @ind: Index at which the address starts in the buffer.
 * @length: Length of the address.
 * @width: Width specifier.
 * @flags: Flags specifier.
 * @padd: Character representing the padding.
 * @extra_c: Character representing an extra character.
 * @padd_start: Index at which padding should start.
 *
 * Return: Number of written characters.
 */
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start)
{
    int i;

    if (width > length)
    {
        for (i = 3; i < width - length + 3; i++)
            buffer[i] = padd;
        buffer[i] = '\0';
        if (flags & F_MINUS && padd == ' ') /* Assign extra character to the left of buffer */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
        }
        else if (!(flags & F_MINUS) && padd == ' ') /* Extra character to the left of buffer */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
        }
        else if (!(flags & F_MINUS) && padd == '0') /* Extra character to the left of padding */
        {
            if (extra_c)
                buffer[--padd_start] = extra_c;
            buffer[1] = '0';
            buffer[2] = 'x';
            return (write(1, &buffer[padd_start], i - padd_start) +
                    write(1, &buffer[ind], length - (1 - padd_start) - 2));
        }
    }
    buffer[--ind] = 'x';
    buffer[--ind] = '0';
    if (extra_c)
        buffer[--ind] = extra_c;
    return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
