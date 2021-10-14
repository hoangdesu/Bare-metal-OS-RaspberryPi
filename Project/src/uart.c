#include "uart.h"
#include "gpio.h"

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
    register unsigned int r;

    /* initialize UART */
    *AUX_ENABLE |= 1;       //enable UART1, AUX mini uart (AUXENB)
    *AUX_MU_CNTL = 0;		//stop transmitter and receiver
    *AUX_MU_LCR  = 3;       //8-bit mode
    *AUX_MU_MCR  = 0;		//RTS (request to send)
    *AUX_MU_IER  = 0;		//disable interrupts
    *AUX_MU_IIR  = 0xc6;    //clear FIFOs
    *AUX_MU_BAUD = 270;    	// 115200 baud

    /* map UART1 to GPIO pins */
    r = *GPFSEL1;
    r &= ~( (7 << 12)|(7 << 15) ); //Clear bits 12-17 (gpio14, gpio15)
    r |=    (2 << 12)|(2 << 15);   //Set value 2 (select ALT5: UART1)
    *GPFSEL1 = r;

    /* enable GPIO 14, 15 */
    *GPPUD = 0;            //No pull up/down control
    r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
    *GPPUDCLK0 = (1 << 14)|(1 << 15); //enable clock for GPIO 14, 15
    r = 150; while(r--) { asm volatile("nop"); } //waiting 150 cycles
    *GPPUDCLK0 = 0;        // flush GPIO setup

    *AUX_MU_CNTL = 3;      //Enable transmitter and receiver (Tx, Rx)
}

/**
 * Send a character
 */
void uart_sendc(unsigned char c) {
    /* wait until transmitter is empty */
    do {
    	asm volatile("nop");
    } while ( !(*AUX_MU_LSR & 0x20) );

    /* write the character to the buffer */
    *AUX_MU_IO = c;
}

/**
 * Receive a character
 */
char uart_getc() {
    char c;

    /* wait until data is ready (one symbol) */
    do {
    	asm volatile("nop");
    } while ( !(*AUX_MU_LSR & 0x01) );

    /* read it and return */
    c = (char)(*AUX_MU_IO);

    /* convert carriage return to newline */
    return (c == '\r' ? '\n' : c);
}

/**
 * Display a string
 */
void uart_puts(char *s) {
    while (*s) {
        /* convert newline to carriage return + newline */
        if (*s == '\n')
            uart_sendc('\r');
        uart_sendc(*s++);
    }
}

/**
* Display a binary value in hexadecimal
*/
void uart_hex(unsigned int d) {
 unsigned int n;
 int c;
 uart_puts("0x");
 for (c = 28; c >= 0; c = c - 4) {
 // Get highest 4-bit nibble
	 n = (d >> c) & 0xF;
	 // 0-9 => '0'-'9', 10-15 => 'A'-'F'
	 n += (n > 9) ? (- 10 + 'A') : '0';
	 uart_sendc(n);
 }
}

/**
* Display a value in decimal by
*/
void uart_dec(int num)
{
		char str[33] = "";
		int i, rem, len = 0, n;
	 n = num;
	 while (n != 0){
		 len++;
		 n /= 10;
	 }
	 if (num == 0)
		 len = 1;

	 for (i = 0; i < len; i++){
		 rem = num % 10;
		 num = num / 10;
		 str[len - (i + 1)] = rem + '0';
	 }
	 str[len] = '\0';
	 uart_puts(str);
}


/**
* Comparing 2 strings.
*/
int string_compare(char *a,char *b)
{
   int flag=0;
    while(*a!='\0' && *b!='\0')  // while loop
    {
    	for (int i = 0; i < sizeof (a); i++) {
            if(*a!=*b)
            {
                flag=1;

            }
            a++;
			b++;
    	}
    }
    if(flag==0){
    	return 0;
    }
    else {
    	return 1;
    }
}


/**
* Substring.
*/
void substring(char s[], char sub[], int p, int l) {
   int c = 0;

   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}


/**
* String copy.
*/
void strcpy(char *src, char * dest)
{
    while (*src) {
        *(dest++) = *(src++);
    }
    *dest = '\0';
}


/**
* Set color for text.
*/
void set_text_color (char text[]){
	if (string_compare(text, "black") == 0) {
		uart_puts("\033[30;1m");
	}
	else if (string_compare(text, "red") == 0) {
		uart_puts("\033[31;1m");
	}
	else if (string_compare(text, "green") == 0) {
		uart_puts("\033[32;1m");
	}
	else if (string_compare(text, "yellow") == 0) {
		uart_puts("\033[33;1m");
	}
	else if (string_compare(text, "blue") == 0) {
		uart_puts("\033[34;1m");
	}
	else if (string_compare(text, "purple") == 0) {
		uart_puts("\033[35;1m");
	}
	else if (string_compare(text, "cyan") == 0) {
		uart_puts("\033[36;1m");
	}
	else if (string_compare(text, "white") == 0) {
		uart_puts("\033[37;1m");
	}
}


/**
* Set color for background.
*/
void set_background_color (char background[]){
	if (string_compare(background, "black") == 0) {
		uart_puts("\033[40;1m");
	}
	else if (string_compare(background, "red") == 0) {
		uart_puts("\033[41;1m");
	}
	else if (string_compare(background, "green") == 0) {
		uart_puts("\033[42;1m");
	}
	else if (string_compare(background, "yellow") == 0) {
		uart_puts("\033[43;1m");
	}
	else if (string_compare(background, "blue") == 0) {
		uart_puts("\033[44;1m");
	}
	else if (string_compare(background, "purple") == 0) {
		uart_puts("\033[45;1m");
	}
	else if (string_compare(background, "cyan") == 0) {
		uart_puts("\033[46;1m");
	}
	else if (string_compare(background, "white") == 0) {
		uart_puts("\033[47;1m");
	}
}



/**
* Convert string char to int.
*/
int convert(char s[])
{
	int i, n=0;

	for(i=0; s[i]>='0' && s[i]<='9'; i++)
		n = 10*n + (s[i] - '0');

	return n;
}



