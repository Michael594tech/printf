#include "main.h"

void print_buffer(char output_buffer[], int *output_index);

/**
 * custom_printf - Custom Printf function
 * @format_string: Format string.
 * Return: Number of printed characters.
 */
int custom_printf(const char *format_string, ...)
{
	int i, printed_count = 0, total_printed_chars = 0;
int custom_flags, cust_width, custom_precision, custom_size, output_index = 0;
	va_list args_list;
	char output_buffer[BUFF_SIZE];

	if (format_string == NULL)
		return (-1);

	va_start(args_list, format_string);

	for (i = 0; format_string && format_string[i] != '\0'; i++)
	{
		if (format_string[i] != '%')
		{
			output_buffer[output_index++] = format_string[i];
			if (output_index == BUFF_SIZE)
				print_buffer(output_buffer, &output_index);
			printed_count++;
		}
		else
		{
			print_buffer(output_buffer, &output_index);
			custom_flags = get_custom_flags(format_string, &i);
			custom_width = get_custom_width(format_string, &i, args_list);
			custom_precision = get_custom_precision(format_string, &i, args_list);
			custom_size = get_custom_size(format_string, &i);
			++i;
			printed_count = handle_print(format_string, &i, args_list, output_buffer,
					custom_flags, custom_width, custom_precision, custom_size);
			if (printed_count == -1)
				return (-1);
			total_printed_chars += printed_count;
		}
	}

	print_buffer(output_buffer, &output_index);

	va_end(args_list);

	return (total_printed_chars);
}

/**
 * print_buffer - Prints the contents of the output buffer if it exists
 * @output_buffer: Array of characters
 * @output_index:Index at which to add the next character,represents the length
 */
void print_buffer(char output_buffer[], int *output_index)
{
	if (*output_index > 0)
		write(1, &output_buffer[0], *output_index);

	*output_index = 0;
}
