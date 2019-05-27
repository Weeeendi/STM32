#ifndef __LCD_CONFIG_H
#define __LCD_CONFIG_H

/*---------------------- Graphic LCD orientation configuration ---------------*/
#ifndef LCD_MIRROR_X
#define LCD_MIRROR_X   0               /* Mirror X axis = 1:yes, 0:no */
#endif
#ifndef LCD_MIRROR_Y
#define LCD_MIRROR_Y   1               /* Mirror Y axis = 1:yes, 0:no */
#endif
#ifndef LCD_SWAP_XY
#define LCD_SWAP_XY    1               /* Swap X&Y axis = 1:yes, 0:no */
#endif

/*--------------------- Graphic LCD physical definitions --------------------*/
#define LCD_SIZE_X     240             /* Screen size X (in pixels) */
#define LCD_SIZE_Y     320             /* Screen size Y (in pixels) */
#define LCD_BPP        16              /* Bits per pixel            */

#if    (LCD_SWAP_XY)
#define LCD_WIDTH      LCD_SIZE_Y     /* Screen Width  (in pixels) */
#define LCD_HEIGHT     LCD_SIZE_X     /* Screen Height (in pixels) */
#else
#define LCD_WIDTH      LCD_SIZE_X     /* Screen Width  (in pixels) */
#define LCD_HEIGHT     LCD_SIZE_Y     /* Screen Height (in pixels) */
#endif

/*---------------------- Graphic LCD color definitions -----------------------*/
/* Color coding (16-bit):
     15..11 = R4..0 (Red)
     10..5  = G5..0 (Green)
      4..0  = B4..0 (Blue)
*/

/* LCD RGB color definitions                            */
#define LCD_COLOR_BLACK        0x0000  /*   0,   0,   0 */
#define LCD_COLOR_NAVY         0x000F  /*   0,   0, 128 */
#define LCD_COLOR_DARK_GREEN   0x03E0  /*   0, 128,   0 */
#define LCD_COLOR_DARK_CYAN    0x03EF  /*   0, 128, 128 */
#define LCD_COLOR_MAROON       0x7800  /* 128,   0,   0 */
#define LCD_COLOR_PURPLE       0x780F  /* 128,   0, 128 */
#define LCD_COLOR_OLIVE        0x7BE0  /* 128, 128,   0 */
#define LCD_COLOR_LIGHT_GREY   0xC618  /* 192, 192, 192 */
#define LCD_COLOR_DARK_GREY    0x7BEF  /* 128, 128, 128 */
#define LCD_COLOR_BLUE         0x001F  /*   0,   0, 255 */
#define LCD_COLOR_GREEN        0x07E0  /*   0, 255,   0 */
#define LCD_COLOR_CYAN         0x07FF  /*   0, 255, 255 (À¶ÂÌÉ«)*/
#define LCD_COLOR_RED          0xF800  /* 255,   0,   0 */
#define LCD_COLOR_MAGENTA      0xF81F  /* 255,   0, 255 */
#define LCD_COLOR_YELLOW       0xFFE0  /* 255, 255, 0   */
#define LCD_COLOR_WHITE        0xFFFF  /* 255, 255, 255 */

#endif /* __GLCD_CONFIG_H */
