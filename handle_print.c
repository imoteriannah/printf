#include "main.h"
/**
 * handle_print - function to Print an argument based on its type
 * @fmt: Formatted string in the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind pointer.
 * @buffer: Buffer to handle print
 * @flags:  Checks active flags in the arguments
 * @width: get width of arguments
 * @precision: Precision of the format specifier
 * @size: Size of the arguments
 *
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknown_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_c}, {'s', print_s}, {'%', print_per},
		{'i', print_i}, {'d', print_i}, {'b', print_b},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexade},
		{'X', print_hex_upper}, {'p', print_pointer}, {'S', print_non_print_char},
		{'r', print_rev}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknown_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknown_len += write(1, &fmt[*ind], 1);
		return (unknown_len);
	}
	return (printed_chars);
}

