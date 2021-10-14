#include "uart.h"
#include "mbox.h"
#include "framebf.h"

void displayWelcomeMessage();

void main()
{

	// set up serial console
	uart_init();

	displayWelcomeMessage();

	// echo everything back
	while (1)
	{

		uart_puts("\n\n");

		// declaring variables
		int count = 0;
		char str[40];		// char array to store user inputs
		char split[40][40]; // char array for storing color commands
		char split1[40][40];

		int y = 0;
		int z = 0;
		int y1 = 0;
		int z1 = 0;

		char set_color[40];
		char set_type1[40];
		char color1[40];
		char set_type2[40];
		char color2[40];

		char set_screen[40];
		char width[40];
		char height[40];
		char screen_type1[40];

		// Taking input commands
		uart_puts("Hoang OS >>> ");
		while (1)
		{
			//read each char
			char c = uart_getc();

			// if user presses ENTER, break the loop and execute a command
			if (c == 10)
			{
				uart_puts("\n");
				break;
			}

			//add each character into the string
			else if (c != 8)
			{
				uart_sendc(c);
				str[count] = c;
				count++;
			}

			//delete each character when user press BackSpace each time
			else if (c == 8 && count > 0)
			{
				uart_sendc(c);
				uart_sendc(32);
				uart_sendc(8);
				count--;
				str[count] = 0; //make the element at that index in the string to be whitespace
			}
		}

		uart_puts("Execute command: ");
		uart_puts(str);
		uart_puts("\n");

		for (int x = 0; x <= sizeof(str); x++)
		{
			// if space or NULL found, assign NULL into split[z]
			if (str[x] == ' ' || str[x] == '\0')
			{
				split[z][y] = '\0';
				z++;   //for next word
				y = 0; //for next word, init index to 0
			}
			else
			{
				split[z][y] = str[x];
				y++;
			}
		}

		strcpy(split[0], set_color);
		strcpy(split[1], set_type1);
		strcpy(split[2], color1);
		strcpy(split[3], set_type2);
		strcpy(split[4], color2);

		for (int x1 = 0; x1 <= sizeof(str); x1++)
		{
			// if space or NULL found, assign NULL into split[z]
			if (str[x1] == ' ' || str[x1] == '\0')
			{
				split1[z1][y1] = '\0';
				z1++;	//for next word
				y1 = 0; //for next word, init index to 0
			}
			else
			{
				split1[z1][y1] = str[x1];
				y1++;
			}
		}

		strcpy(split1[0], set_screen);
		strcpy(split1[1], screen_type1);
		strcpy(split1[2], width);
		strcpy(split1[3], height);

		// uart_puts(split);

		// ----- COMMANDS -----//
		if (str[0] == '\0')
		{
			uart_puts("");
		}

		// command 1: help <command>
		else if (string_compare(str, "help") == 0)
		{
			uart_puts(
				"For more information on a specific command, type HELP command-name \n"
				"HELP\t\tShow brief information of all commands 				  \n"
				"SETCOLOR\tSet text color, and/or background color 	 		  \n"
				"CLS\t\tClear screen										  \n"
				"BRDREV\t\tShow board revision									  \n"
				"SCRSIZE\t\tSet screen size 									  \n"
				"ARMFREQ\t\tDisplay ARM frequency 							  \n"
				"UARTFREQ\tDisplay UART frequency 							  \n"
				"BRDMODEL\tDisplay board model 							  \n"
				"FIRMWARE\tDisplay the current firmware						  \n"
				"DRAW\t\tDisplay a picture 									  \n");
		}

		else if (string_compare(str, "help setcolor") == 0)
		{
			uart_puts("SETCOLOR\tSet text color, and/or background color of the 	\n"
					  "\t\tconsole to one of the following color: BLACK, RED, 	\n"
					  "\t\tGREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE 			\n"
					  "\t\tExample: setcolor -b yellow");
		}

		else if (string_compare(str, "help cls") == 0)
		{
			uart_puts("CLS\t\tClear screen (the terminal will scroll down to current position of the cursor). \n"
					  "\t\tExample: cls");
		}

		else if (string_compare(str, "help brdrev") == 0)
		{
			uart_puts("BRDREV\t\tShow board revision \n"
					  "\t\tExample: brdrev \n");
		}

		else if (string_compare(str, "help scrsize") == 0)
		{
			uart_puts("SCRSIZE\t\tSet screen size 				  \n"
					  "\t\tMust have options to set physical screen size (-p)\n"
					  "\t\tor virtual screen size (-v), or both (by default) \n"
					  "\t\tExample: scrsize -p 1024 768 (set physical screen) \n"
					  "\t\tscrsize -v 1024 768 (set virtual screen)\n"
					  "\t\tscrsize -b 1024 768 (set both physical and virtual screens)\n");
		}

		else if (string_compare(str, "help armfreq") == 0)
		{
			uart_puts("ARMFREQ\t\tDisplay information of ARM frequency \n"
					  "\t\tExample: armfreq \n");
		}

		else if (string_compare(str, "help uartfreq") == 0)
		{
			uart_puts("UARTFREQ\tDisplay information of UART frequency \n"
					  "\t\tExample: uartfreq \n");
		}

		else if (string_compare(str, "help brdmodel") == 0)
		{
			uart_puts("BRDMODEL\tDisplay board model \n"
					  "\t\tExample: brdmodel \n");
		}

		else if (string_compare(str, "help firmware") == 0)
		{
			uart_puts("FIRMWARE\tDisplay a version of current firmware \n"
					  "\t\tExample: firmware \n");
		}

		else if (string_compare(str, "help draw") == 0)
		{
			uart_puts("DRAW\t\tDisplay a picture \n"
					  "\t\tExample: draw \n");
		}

		// command 2: setcolor <options>
		else if (string_compare(set_color, "setcolor") == 0 && string_compare(set_type1, "-t") == 0 && string_compare(color1, '\0') != 0)
		{
			if (string_compare(set_type2, "-b") == 0 && string_compare(color2, '\0') != 0)
			{
				set_text_color(color1);
				set_background_color(color2);
			}
			set_text_color(color1);
		}

		else if (string_compare(set_color, "setcolor") == 0 && string_compare(set_type1, "-b") == 0 && string_compare(color1, '\0') != 0)
		{
			set_background_color(color1);
		}

		// command 3: cls
		else if (string_compare(str, "cls") == 0)
		{
			uart_puts("\033[H\033[J");
		}

		// command 4: brdrev
		else if (string_compare(str, "brdrev") == 0)
		{
			mbox[0] = 7 * 4;		// Message Buffer Size in bytes (9 elements * 4 bytes (32 bit) each)
			mbox[1] = MBOX_REQUEST; // Message Request Code (this is a request message)

			mbox[2] = 0x00010002; // TAG Identifier: Get clock rate
			mbox[3] = 4;		  // Value buffer size in bytes (max of request and response lengths)
			mbox[4] = 0;		  // REQUEST CODE = 0
			mbox[5] = 0;		  // clear output buffer
			mbox[6] = MBOX_TAG_LAST;

			if (mbox_call(ADDR(mbox), MBOX_CH_PROP))
			{
				uart_puts("Board revision: ");
				uart_hex(mbox[5]);
			}
			else
			{
				uart_puts("Unable to query!\n");
			}
		}

		// command 5: scrsize <options>
		else if (string_compare(set_screen, "scrsize") == 0 && string_compare(screen_type1, "-p") == 0 && string_compare(width, '\0') != 0 && string_compare(height, '\0') != 0)
		{
			int w = convert(width);
			int h = convert(height);
			physical_framebf_init(w, h);
		}

		else if (string_compare(set_screen, "scrsize") == 0 && string_compare(screen_type1, "-v") == 0 && string_compare(width, '\0') != 0 && string_compare(height, '\0') != 0)
		{
			int w = convert(width);
			int h = convert(height);
			virtual_framebf_init(w, h);
		}

		else if (string_compare(set_screen, "scrsize") == 0 && string_compare(screen_type1, "-b") == 0 && string_compare(width, '\0') != 0 && string_compare(height, '\0') != 0)
		{
			int w = convert(width);
			int h = convert(height);
			default_framebf_init(w, h);
		}

		// command 6: armfreq
		else if (string_compare(str, "armfreq") == 0)
		{
			// mailbox data buffer: Read ARM frequency
			mbox[0] = 8 * 4;		// Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
			mbox[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
			mbox[2] = 0x00030002;	// TAG Identifier: Get clock rate
			mbox[3] = 8;			// Value buffer size in bytes (max of request and response lengths)
			mbox[4] = 0;			// REQUEST CODE = 0
			mbox[5] = 3;			// clock id: ARM system clock
			mbox[6] = 0;			// clear output buffer (response data are mbox[5] & mbox[6])
			mbox[7] = MBOX_TAG_LAST;

			if (mbox_call(ADDR(mbox), MBOX_CH_PROP))
			{
				uart_puts("ARM clock rate: ");
				uart_dec(mbox[6]);
				uart_puts(" Hz");
			}
			else
			{
				uart_puts("Unable to query!\n");
			}
		}

		// command 7: uartfreq 
		else if (string_compare(str, "uartfreq") == 0)
		{
			mbox[0] = 8 * 4;		// Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
			mbox[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
			mbox[2] = 0x00030002;	// TAG Identifier: Get clock rate
			mbox[3] = 8;			// Value buffer size in bytes (max of request and response lengths)
			mbox[4] = 0;			// REQUEST CODE = 0
			mbox[5] = 2;			// clock id: UART clock rate
			mbox[6] = 0;			// clear output buffer (response data are mbox[5] & mbox[6])
			mbox[7] = MBOX_TAG_LAST;

			if (mbox_call(ADDR(mbox), MBOX_CH_PROP))
			{
				uart_puts("UART clock rate ");
				uart_dec(mbox[6]);
				uart_puts(" Hz");
			}
			else
			{
				uart_puts("Unable to query!\n");
			}
		}

		// command 8: brdmodel 
		else if (string_compare(str, "brdmodel") == 0)
		{
			mbox[0] = 7 * 4;		// Message Buffer Size in bytes (9 elements * 4 bytes (32 bit) each)
			mbox[1] = MBOX_REQUEST; // Message Request Code (this is a request message)

			mbox[2] = 0x00010001; // TAG Identifier: Get clock rate
			mbox[3] = 4;		  // Value buffer size in bytes (max of request and response lengths)
			mbox[4] = 0;		  // REQUEST CODE = 0
			mbox[5] = 0;		  // clear output buffer
			mbox[6] = MBOX_TAG_LAST;

			if (mbox_call(ADDR(mbox), MBOX_CH_PROP))
			{
				uart_puts("Board model: ");
				uart_hex(mbox[5]);
			}
			else
			{
				uart_puts("Unable to query!\n");
			}
		}

		// command 9: firmware 
		else if (string_compare(str, "firmware") == 0)
		{
			mbox[0] = 7 * 4;		// Message Buffer Size in bytes (9 elements * 4 bytes (32 bit) each)
			mbox[1] = MBOX_REQUEST; // Message Request Code (this is a request message)

			mbox[2] = 0x00000001; // TAG Identifier: Get clock rate
			mbox[3] = 4;		  // Value buffer size in bytes (max of request and response lengths)
			mbox[4] = 0;		  // REQUEST CODE = 0
			mbox[5] = 0;		  // clear output buffer
			mbox[6] = MBOX_TAG_LAST;

			if (mbox_call(ADDR(mbox), MBOX_CH_PROP))
			{
				uart_puts("Board's firmware: ");
				uart_hex(mbox[5]);
			}
			else
			{
				uart_puts("Unable to query!\n");
			}
		}

		// command 10: draw 
		else if (string_compare(str, "draw") == 0)
		{
			unsigned int red, green, blue, yellow;
			red = 0x00AA0000;
			green = 0x0000BB00;
			yellow = 0x00FFFF00;
			blue = 0x000000CC;
			default_framebf_init(1024, 800);
			drawRectARGB32(660, 420, 750, 650, blue, 1);
			drawRectARGB32(320, 130, 700, 400, yellow, 1);
			drawRectARGB32(450, 500, 600, 600, green, 1);
			drawRectARGB32(100, 100, 300, 400, red, 1);
			drawPixelARGB32(300, 300, red);
		}

		/* Task 1c: printf() function implementation */
		else if (string_compare(str, "printf") == 0)
		{
			printf("String: %s\n", "Wazzup!");
			printf("Character: %c\n", 69);
			printf("Percentage sign: %%\n");
			printf("Decimal/integer number: %d\n", 262);
			printf("This is a float number: %f \n", (float)6 / 9);
			printf("Hexadecimal: %x\n", 195);
		}

		// Invalid command
		else
		{
			uart_puts("'");
			uart_puts(str);
			uart_puts("'");
			uart_puts(" is an invalid command. Please check again. \n");
		}

		// reset string arrays
		for (int k = 0; k < 40; k++)
		{
			//Reset string input
			str[k] = '\0';

			// Reset strings for command setcolor
			split[k][k] = '\0';
			set_color[k] = '\0';
			set_type1[k] = '\0';
			color1[k] = '\0';
			set_type2[k] = '\0';
			color2[k] = '\0';

			//Reset strings for command scrsize
			split1[k][k] = '\0';
			set_screen[k] = '\0';
			screen_type1[k] = '\0';
			width[k] = '\0';
			height[k] = '\0';
		}
	}
}

void displayWelcomeMessage()
{

	static const char message[16][100] = {

		"d88888b d88888b d88888b d888888b   .d888b.   j88D  .d888b.  .d88b.",
		"88'     88'     88'     `~~88~~'   VP  `8D  j8~88  88' `8D .8P  88. ",
		"88ooooo 88ooooo 88ooooo    88         odD' j8' 88  `V8o88' 88  d'88",
		"88~~~~~ 88~~~~~ 88~~~~~    88       .88'   V88888D    d8'  88 d' 88",
		"88.     88.     88.        88      j88.        88    d8'   `88  d8' ",
		"Y88888P Y88888P Y88888P    YP      888888D     VP   d8'     `Y88P'  ",
		"\n",
		"#     #                                 #######  ##### ",
		"#     #  ####    ##   #    #  ####      #     # #     #",
		"#     # #    #  #  #  ##   # #    #     #     # #       ",
		"####### #    # #    # # #  # #          #     #  #####  ",
		"#     # #    # ###### #  # # #  ###     #     #       # ",
		"#     # #    # #    # #   ## #    #     #     # #     # ",
		"#     #  ####  #    # #    #  ####      #######  #####  ",
		"\n",
		"\tDeveloped by <Hoang Nguyen> - <s3697305>\n"

	};

	uart_puts("\n\n");
	char color[] = "\033[33;1m";
	uart_puts(color);

	for (int i = 0; i < (sizeof(message) / sizeof(*message)); i++)
	{
		uart_puts(message[i]);
		uart_sendc('\n');
	}
}
