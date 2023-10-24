#include "main.h"

/**
 * print_pointer - Outputs the value of a pointer variable
 * @types: List a of arguments
 * @param output_buffer: Buffer for printing
 * @param formatting_flags: formatting flags
 * @param output_width: width specifier
 * @param output_precision: Precision specification
 * @param output_size: Size specifier
 * Return: Number of characters printed.
 */
int print_pointer(va_list types, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int output_size)
	char extra_char = 0, padd = ' ';
	int buffer_index = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long address_value;
	char hex_map[] = "0123456789abcdef";
	void *pointer = va_arg(types, void *);

	UNUSED(output_width);
	UNUSED(output_size);

	if (pointer == NULL)
		return (write(1, "(nil)", 5));

	output_buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(output_precision);

	address_value = (unsigned long)pointer;

	while (address_value > 0)
	{
		output_buffer[ind--] = hex_map[num_addrs % 16];
		address_value /= 16;
		output_length++;
	}

	if ((formatting_flags & F_ZERO) && !(formatting_flags & F_MINUS))
		padding_char = '0';
	if (formatting_flags & F_PLUS)
		extra_char = '+', output_length++;
	else if (formatting_flags & F_SPACE)
		extra_char = ' ', output_length++;

	buffer_index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(output_buffer, buffer_index, output_length,
		output_width, formatting_flags, padding_char, extra_char, padding_start));
}

/**
 * print_non_printable - Prints non printable chars
 * @param args: List of arguments
 * @param output_buffer: Buffer array to handle print
 * @param output_flags:  Calculates active flags
 * @param output_width: get width
 * @param output_precision: Precision specification
 * @param output_size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list args, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int output_size)
{
	int i = 0, offset = 0;
	char *text = va_arg(args, char *);

	UNUSED(formatting_flags);
	UNUSED(output_width);
	UNUSED(output_precision);
	UNUSED(output_size);

	if (text == NULL)
		return (write(1, "(null)", 6));

	while (text[i] != '\0')
	{
		if (is_printable(text[i]))
			output_buffer[i + offset] = text[i];
		else
			offset += append_hexa_code(text[i], output_buffer, i + offset);

		i++;
	}

	output_buffer[i + offset] = '\0';

	return (write(1, output_buffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @param args: List of arguments
 * @param output_buffer: Buffer array to handle print
 * @param formatting_flags:  Calculates active flags
 * @param output_width: get width
 * @param output_precision: Precision specification
 * @param output_size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list args, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int output_size)
{
	char *input_string;
	int i, count = 0;

	UNUSED(output_buffer);
	UNUSED(formatting_flags);
	UNUSED(output_width);
	UNUSED(output_size);

	input_string = va_arg(args, char *);

	if (input_string == NULL)
	{
		UNUSED(output_precision);

		input_string = ")Null(";
	}
	for (i = 0; input_string[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = input_string[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @param args: Lists of arguments
 * @param output_buffer: Buffer array to handle print
 * @param formatting_flags:  Calculates active flags
 * @param output_width: get width
 * @param output_precision: Precision specification
 * @param output_size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list args, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int output_size)
{
	char x;
	char *text;
	unsigned int i, j;
	int count = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	text = va_arg(args, char *);
	UNUSED(output_buffer);
	UNUSED(formatting_flags);
	UNUSED(output_width);
	UNUSED(output_precision);
	UNUSED(output_size);

	if (text == NULL)
		text = "(AHYY)";
	for (i = 0; text[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (input[j] == text[i])
			{
				x = output[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!input[j])
		{
			x = text[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
