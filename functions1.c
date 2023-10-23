#include "myheader.h"

void flush_buffer(char text[], int *text_index);

/**
 * my_printf - Custom printf function
 * @fmt: The format string.
 * Return: Number of characters printed.
 */
int my_printf(const char *fmt, ...)
{
    int i, chars_printed = 0, total_printed = 0;
    int flags, width, precision, size, text_index = 0;
    va_list args;
    char text[TEXT_SIZE];

    if (fmt == NULL)
        return -1;

    va_start(args, fmt);

    for (i = 0; fmt && fmt[i] != '\0'; i++)
    {
        if (fmt[i] != '%')
        {
            text[text_index++] = fmt[i];
            if (text_index == TEXT_SIZE)
                flush_buffer(text, &text_index);
            chars_printed++;
        }
        else
        {
            flush_buffer(text, &text_index);
            flags = custom_flags(fmt, &i);
            width = custom_width(fmt, &i, args);
            precision = custom_precision(fmt, &i, args);
            size = custom_size(fmt, &i);
            i++;
            int printed = custom_print(fmt, &i, args, text,
                flags, width, precision, size);
            if (printed == -1)
            {
                va_end(args);
                return -1;
            }
            chars_printed += printed;
        }
    }

    flush_buffer(text, &text_index);

    va_end(args);

    return chars_printed;
}

/**
 * flush_buffer - Writes the text buffer to the standard output and resets the index.
 * @text: Array of characters to be printed.
 * @text_index: Index at which to add the next character, representing the length.
 */
void flush_buffer(char text[], int *text_index)
{
    if (*text_index > 0)
        write(1, &text[0], *text_index);

    *text_index = 0;
}

