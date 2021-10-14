#include "functions.h"
#include "colors.h"
#include "pictures.h"
#include "video.h"
#include "uart.h"
#include "mbox.h"
#include "framebf.h"

// -------------------------------------------------------------- //
void displayWelcomeMessage()
{

    static const char message[15][100] = {

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
        "\n"};

    uart_puts("\n");
    set_text_color("cyan");

    for (int i = 0; i < (sizeof(message) / sizeof(*message)); i++)
    {
        uart_puts(message[i]);
        uart_sendc('\n');
    }
    set_text_color("yellow");
    uart_puts("\tDeveloped by <Hoang Nguyen> - <s3697305>\n\n");
}

// -------------------------------------------------------------- //
void displayMenu()
{
    set_text_color("blue");
    uart_puts(
        "\n\n\tEnter a number to choose command:\n"
        "\t1.\tDisplay text on screen\n"
        "\t2.\tDisplay a small image\n"
        "\t3.\tDisplay a scrollable large image\n"
        "\t4.\tDisplay a video\n"
        "\t5.\tPlay game\n"
        "\t0.\tClear the screen\n");
    set_text_color("green");
}

// -------------------------------------------------------------- //
const char *readUserInput()
{
    int count = 0;
    static char command[str_size];
    while (1)
    {
        //read each char
        char c = uart_getc();

        // if user presses ENTER, break the loop and do a command
        if (c == 10)
        {
            uart_puts("\n");
            return command;
        }

        //add each character into the string
        else if (c != 8)
        {
            uart_sendc(c);
            command[count] = c;
            count++;
        }

        //delete each character when user press BackSpace each time
        else if (c == 8 && count > 0)
        {
            uart_sendc(c);
            uart_sendc(32);
            uart_sendc(8);
            count--;
            command[count] = 0; //make the element at that index in the string to be whitespace
        }
    }
}

// -------------------------------------------------------------- //
void set_text_color(char text[])
{
    if (string_compare(text, "black") == 0)
    {
        uart_puts("\033[30;1m");
    }
    else if (string_compare(text, "red") == 0)
    {
        uart_puts("\033[31;1m");
    }
    else if (string_compare(text, "green") == 0)
    {
        uart_puts("\033[32;1m");
    }
    else if (string_compare(text, "yellow") == 0)
    {
        uart_puts("\033[33;1m");
    }
    else if (string_compare(text, "blue") == 0)
    {
        uart_puts("\033[34;1m");
    }
    else if (string_compare(text, "purple") == 0)
    {
        uart_puts("\033[35;1m");
    }
    else if (string_compare(text, "cyan") == 0)
    {
        uart_puts("\033[36;1m");
    }
    else if (string_compare(text, "white") == 0)
    {
        uart_puts("\033[37;1m");
    }
}

void set_background_color(char background[])
{
    if (string_compare(background, "black") == 0)
    {
        uart_puts("\033[40;1m");
    }
    else if (string_compare(background, "red") == 0)
    {
        uart_puts("\033[41;1m");
    }
    else if (string_compare(background, "green") == 0)
    {
        uart_puts("\033[42;1m");
    }
    else if (string_compare(background, "yellow") == 0)
    {
        uart_puts("\033[43;1m");
    }
    else if (string_compare(background, "blue") == 0)
    {
        uart_puts("\033[44;1m");
    }
    else if (string_compare(background, "purple") == 0)
    {
        uart_puts("\033[45;1m");
    }
    else if (string_compare(background, "cyan") == 0)
    {
        uart_puts("\033[46;1m");
    }
    else if (string_compare(background, "white") == 0)
    {
        uart_puts("\033[47;1m");
    }
}

// -------------------------------------------------------------- //
void clearTerminal()
{
    uart_puts("\033[H\033[J");
}

// -------------------------------------------------------------- //
void wait_ms(unsigned int n)
{
    register unsigned long f, t, r;

    // Get the current counter frequency
    asm volatile("mrs %0, cntfrq_el0"
                 : "=r"(f));
    // Read the current counter
    asm volatile("mrs %0, cntpct_el0"
                 : "=r"(t));
    // Calculate expire value for counter
    t += ((f / 1000) * n) / 1000;
    do
    {
        asm volatile("mrs %0, cntpct_el0"
                     : "=r"(r));
    } while (r < t);
}

void drawSmallImage()
{
    drawImage(small_img, 0, 0, 564, 700);
    uart_puts("Programmer's best friends 😂");
}

void drawLargeImageScroll()
{
    uart_puts("Use WASD to scroll. Press Enter to quit scroll mode ");
    int y = 0;
    int x = 0;
    drawImage(large_img, x, y, 1920, 1080);

    while (1)
    {
        char c = uart_getc();

        if (c == 'w')
        {
            y -= 20;
        }
        else if (c == 's')
        {
            y += 20;
        }
        else if (c == 'd')
        {
            x += 20;
        }
        else if (c == 'a')
        {
            x -= 20;
        }
        else if (c == '\n')
        {
            break;
        }
        clearScreen(COLORS.BLACK);

        drawImage(large_img, x, y, 1920, 1080);
    }
}

void playVideo()
{
    uart_puts("Playing video ►\n");
    uart_puts("Press Enter to stop ");
    char c = uart_get_char();
    int i = 0;
    while (c != '\n')
    {
        if (i > 7)
            i = 0;
        // printf("%d\n", i);
        drawImage(video_frames[i], 0, 0, 453, 421);
        wait_ms(60000);
        i++;
        c = uart_get_char();
    }
    uart_puts("\nVideo stopped ■");
}

struct Box
{
    int x1, y1, x2, y2, w, h, velocity;
} player, box1, box2, box3;

enum state {welcome, play, win};

void playGame()
{
    enum state gameState;
    gameState = welcome;

    // player
    player.x1 = 50;
    player.y1 = 768/2 - 10;
    player.w = 20;
    player.h = 20;
    player.x2 = player.x1 + player.w;
    player.y2 = player.y1 + player.h;
    player.velocity = 20;

    // box 1
    box1.x1 = 200;
    box1.y1 = 20;
    box1.w = 50;
    box1.h = 150;
    box1.x2 = box1.x1 + box1.w;
    box1.y2 = box1.y1 + box1.h;
    box1.velocity = 30;

    // box 2
    box2.x1 = 500;
    box2.y1 = 500;
    box2.w = 40;
    box2.h = 180;
    box2.x2 = box2.x1 + box2.w;
    box2.y2 = box2.y1 + box2.h;
    box2.velocity = -50;

    // box 3
    box3.x1 = 700;
    box3.y1 = 169;
    box3.w = 55;
    box3.h = 250;
    box3.x2 = box3.x1 + box3.w;
    box3.y2 = box3.y1 + box3.h;
    box3.velocity = -80;
    
    char c;

    while (1)
    {
        if (gameState == welcome)
        {
            drawString(SCR_WIDTH / 2 - 70, 262, "Rescue the Pink-cess", 0xe);
            drawString(SCR_WIDTH / 2 - 72, 300, "Press Enter to play", 0xf);
            char c = uart_getc();
            if (c == '\n')
            {
                gameState = play;
            }
        }
        else if (gameState == play)
        {
            // revert direction if boxes touch top or bottom edge
            if (box1.y2 > 768 || box1.y1 < 0) box1.velocity = -box1.velocity;
            if (box2.y2 > 768 || box2.y1 < 0) box2.velocity = -box2.velocity;
            if (box3.y2 > 768 || box3.y1 < 0) box3.velocity = -box3.velocity;

            // player movement
            c = uart_get_char();
            if (c == '\r') c = '\0';
            if (c == 'w')
            {
                if (player.y1 > 0) player.y1 -= player.velocity;
            }
            else if (c == 'd')
            {
                if (player.x2 < 1024) player.x1 += player.velocity;
            }
            else if (c == 's')
            {
                if (player.y2 < 768) player.y1 += player.velocity;   
            }
            else if (c == 'a')
            {
                if (player.x1 > 0) player.x1 -= player.velocity;
            }
            else if (c == 'r') // ultimate hack =)))
            {
                player.x1 = 890;
                player.x2 = 910;
                player.y1 = 270;
                player.y2 = 290;
            }
            else if (c == 'q') 
            {
                uart_puts("Game quit");
                break;
            }
            
            // update the other edge of the player and the boxes
            player.x2 = player.x1 + player.w;
            player.y2 = player.y1 + player.h;

            box1.y1 += box1.velocity;
            box1.y2 = box1.y1 + box1.h;
                    
            box2.y1 += box2.velocity;
            box2.y2 = box2.y1 + box2.h;
        
            box3.y1 += box3.velocity;
            box3.y2 = box3.y1 + box3.h;

            // detect collision with pink-cess
            if ((player.y1 > 264 && player.y2 < 304) && (player.x1 > 880 && player.x2 < 920))
            {
                gameState = win;
            }

            // draw the elements
            drawCircle(900, SCR_HEIGHT/2 - 100, 20, 0x36, 1); // pink-cess

            drawRect(player.x1, player.y1, player.x2, player.y2, 0xd, 1); // player

            drawRect(box1.x1, box1.y1, box1.x2, box1.y2, 0x6, 1); // boxbox
            drawRect(box2.x1, box2.y1, box2.x2, box2.y2, 0x9, 1);
            drawRect(box3.x1, box3.y1, box3.x2, box3.y2, 0xa, 1);

            wait_ms(50000); // delay = less flickering = more bugs :/

            clearScreen(COLORS.BLACK);
        }
        else if (gameState == win)
        {
            uart_puts("YOU WIN!!");
            drawString(SCR_WIDTH / 2 - 50, 400, "YOU WIN!!", 0xe);
            if (uart_getc() == '\n') break;
        }
    }
}