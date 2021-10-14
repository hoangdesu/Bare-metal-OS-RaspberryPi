#include "printf.h"
#include "uart.h"

#define MAX_PRINT_SIZE 256


void printf(char *string,...) {

	va_list ap;
	va_start(ap, string);

	char buffer[MAX_PRINT_SIZE];
	int buffer_index = 0;

	char temp_buffer[MAX_PRINT_SIZE];

	while(1) {
		if (*string == 0)
			break;

		if (*string == '%') {

			string++;

			if (*string == 'd') {
				string++;
				int x = va_arg(ap, int);
				int temp_index = MAX_PRINT_SIZE - 1;

				do {
					temp_buffer[temp_index] = (x % 10) + '0';
					temp_index--;
					x /= 10;
				} while(x != 0);

				for(int i = temp_index + 1; i < MAX_PRINT_SIZE; i++) {
					buffer[buffer_index] = temp_buffer[i];
					buffer_index++;
				}
			}

			else if (*string == 's') {
				string++;

				char *s = va_arg(ap, char*);
				while ( *s != '\0') {
					buffer[buffer_index] = *s++;
					buffer_index++;
				}
			}

			else if (*string == 'c') {
				string++;

				int c = va_arg(ap, int);
				buffer[buffer_index] = c;
				buffer_index++;

			}

			else if (*string == 'x') {
				string++;
				int x = va_arg(ap, int);
				int temp_index = MAX_PRINT_SIZE - 1;

				while (x != 0) {
					if ((x % 16) < 10) {
						temp_buffer[temp_index] = 48 + (x % 16);
					}
					else {
						temp_buffer[temp_index] = 55 + (x % 16);
					}
					temp_index--;
					x /= 16;
				}

				for(int i = temp_index + 1; i < MAX_PRINT_SIZE; i++) {
					buffer[buffer_index] = temp_buffer[i];
					buffer_index++;
				}
			}

			else if (*string == '%') {
				string++;
				int x = va_arg(ap, int);

				buffer[buffer_index] = 37;
				buffer_index++;

			}
			else if (*string == 'f') {
				string++;
				double f = va_arg(ap, double);
				int int_f = (double)f;
				int dot_position = 0;
				int number_after_dot = 10000;
				while (int_f != 0) {
					dot_position++;
					int_f /= 10;
				}

				int x = (int)(f * number_after_dot + 5);
				x /= 10;

				int temp_index = MAX_PRINT_SIZE - 1;

				do {
					temp_buffer[temp_index] = (x % 10) + 48;
					temp_index--;
					x /= 10;
				} while(x != 0);

				for(int i = temp_index + 1; i < MAX_PRINT_SIZE; i++) {
					if (i == (dot_position + temp_index + 1)) {
						buffer[buffer_index] = '.';
						buffer_index++;
					}
					buffer[buffer_index] = temp_buffer[i];
					buffer_index++;

				}

			}
		}

		else {
			buffer[buffer_index] = *string;
			buffer_index++;
			string++;
		}

		if (buffer_index == MAX_PRINT_SIZE - 1)
			break;
	}

	va_end(ap);


	//Print out formated string
	uart_puts(buffer);
}






