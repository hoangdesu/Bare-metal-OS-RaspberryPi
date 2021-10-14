/*
Author: Nguyen Quoc Hoang
Student ID: s3697305
Subject: EEET2490
Assignment 3: Screen Display and Application Developement for Bare Metal OS
*/

#include "uart.h"
#include "mbox.h"
#include "framebf.h"
#include "functions.h"
#include "colors.h"

void main()
{
	// initialize UART0
	uart_init();

	// console bootup message
	displayWelcomeMessage();

	// initialize colors
	colorsInit();

	// create a framebuffer at resolution 1024x768
	framebf_init(SCR_WIDTH, SCR_HEIGHT);

	// display menu in console
	displayMenu();

	// display on Qemu
	drawOnScreen();

	while (1)
	{
		uart_puts("\n\n");

		uart_puts("HoangOS>>> ");

		char command = uart_getc();

		uart_sendc(command);
		uart_sendc('\n');

		clearScreen(COLORS.BLACK);

		if (command == '1')
		{
			drawOnScreen();
		}
		else if (command == '2')
		{
			drawSmallImage();
		}
		else if (command == '3')
		{
			drawLargeImageScroll();
		}
		else if (command == '4')
		{
			playVideo();
		}
		else if (command == '5')
		{
			playGame();
		}
		else if (command == '0')
		{
			clearScreen(COLORS.BLACK);
			uart_puts("All cleared!");
		}
		else if (command == '9')
		{
			clearScreen(COLORS.WHITE);
			uart_puts("All cleared!");
		}
		else 
		{
			uart_puts("Invalid command. Please try again");
		}
	}
}
