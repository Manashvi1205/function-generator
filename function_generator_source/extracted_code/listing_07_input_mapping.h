# pragma once
# include " input . h "
# include < Arduino .h >
// -------- Keypad size --------
# define INPUT_ROWS 4
# define INPUT_COLS 4
// -------- Row pins --------
static byte INPUT_ROW_PINS [ INPUT_ROWS ] = {32 , 33 , 25 , 26};
// -------- Column pins --------
static byte INPUT_COL_PINS [ INPUT_COLS ] = {27 , 14 , 12 , 13};
// -------- Key layout ( characters returned by keypad library ) --------
static char KEYPAD_KEYS [ INPUT_ROWS ][ INPUT_COLS ] =
{
{ ’1 ’ , ’2 ’ , ’3 ’ , ’A ’} ,
{ ’4 ’ , ’5 ’ , ’6 ’ , ’C ’} ,
{ ’7 ’ , ’8 ’ , ’9 ’ , ’B ’} ,
{ ’* ’ , ’0 ’ , ’# ’ , ’D ’}
};
.9.6 Signal Generation
