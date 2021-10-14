// ----------------------------------- framebf.h -------------------------------------

#define SCR_WIDTH 1024
#define SCR_HEIGHT 768

void physical_framebf_init(int w, int h);
void virtual_framebf_init(int w, int h);
void framebf_init(int w, int h);
void drawPixel(int x, int y, unsigned int attr);
void drawRect(int x1, int y1, int x2, int y2, unsigned int attr, int fill);
void drawLine(int x1, int y1, int x2, int y2, unsigned char attr);
void drawCircle(int x0, int y0, int radius, unsigned char attr, int fill);
void clearScreen(int color);
void drawImage(unsigned int image[], int x, int y, int w, int h);
void drawChar(unsigned char ch, int x, int y, unsigned char attr);
void drawString(int x, int y, char *s, unsigned char attr);
void drawOnScreen();


