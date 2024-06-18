This LCD drivers was tested on STM32 F103 (blue pill) controller.

It can be configure and work with LCD with direct contol by port pins or with i2c-protocol.
Drivers supports 1-line, 2-lines and 4-lines displays with 5-dots symbol's width and configurable height in 8- or 10-dots.
All basic settings are "lcd_config.h" file.
For correct display cirillic symbols yuo need to connect the symbols table to the corresponding LCD-сontroller
via lcd_charTable_***.h-file after characters coding set.


Class public methods:

/****************************************************************************/
LCD& LCD::getInstance(void (*i2cWriteFunc) (uint16_t, uint8_t*))
-----------------------------------------------------------------------------
- static class method that initiates LCD instance with i2c-connecting, using masterWrite-function from i2c_lib-library/

masterWrite (uint16_t slaveAddr, uint8_t* buff, uint8_t dataSize = 1)
-----------------------------------------------------------------------------
- sets i2c-connection in master write mode. Sets connection with slave device on slaveAddr-address
and writes datasize bytes data from buff to slave device (without regAddr register address transfering).
The same regAddr = 0xffff. 
Runs in the current process thread, does not need to use interrupts

Parameters: 
*i2cWriteFunc - pointer to function masterWrite (uint16_t slaveAddr, uint8_t* buff, uint8_t dataSize = 1)* from i2c-library,
where 	int16_t slaveAddr - slave address
		uint8_t* buff - data source pointer				
Return:
LCD - LCD type entity.

	* - sets i2c-connection in master write mode. Sets connection with slave device on slaveAddr-address
		and writes 1 byte data from buff to slave device (without regAddr register address transfering).
		The same regAddr = 0xffff. Runs in the current process thread, does not need to use interrupts.
	
/****************************************************************************/
LCD& LCD::getInstance( )
-----------------------------------------------------------------------------
- static class method that initiates LCD instance with direct connection to port pins or used when instance already initiated
with i2c-connection parameteres and returns LCD-class instance

Parameters: void						
Return:
LCD - LCD type entity.
	
/****************************************************************************/
void backlightOn( )
-----------------------------------------------------------------------------
- turns on LCD-backlight

Parameters: void						
Return: void
	
/****************************************************************************/
void backlightOff( )
-----------------------------------------------------------------------------
- turns off LCD-backlight

Parameters: void						
Return: void
	
/****************************************************************************/
void on( )
-----------------------------------------------------------------------------
- turns on LCD-display and backlight.

Parameters: void						
Return: void
	
/****************************************************************************/
void off( )
-----------------------------------------------------------------------------
- turns off LCD-display and backlight.

Parameters: void						
Return: void
	
/****************************************************************************/
void clear( )
-----------------------------------------------------------------------------
- clear screen.

Parameters: void						
Return: void
	
/****************************************************************************/
void clearLine(uint8_t line)
-----------------------------------------------------------------------------
- clear screen on line of specified number and move cursour to begin of this line.

Parameters:
uint8_t line - number of erase line
Return: void
	
/****************************************************************************/
void home( )
-----------------------------------------------------------------------------
- move cursour to the begin LCD (first character cell) without clearing display

Parameters: void						
Return:
true - the corresponding mode is active
false - the corresponding mode is not active
	
/****************************************************************************/
void goTo(uint8_t lineNum, uint8_t position)
-----------------------------------------------------------------------------
- move cursour to the corresponding character position specified by lineNum and position parameters;
without clearing display, but with aligning display position if cursour ot of screen borders

Parameters:
uint8_t lineNum - number of line 
uint8_t position - horizontal pozition on line (min value is 0)				
Return:	void
	
/****************************************************************************/
void shiftCursorLeft (uint8_t pos)
void shiftCursorRight (uint8_t pos)
-----------------------------------------------------------------------------
- shift cursour to the left/right for corresponding cells specified by pos parameter with aligning display
position if cursour ot of screen borders

Parameters: 
uint8_t pos - number of cursour shifts				
Return:	void
	
/****************************************************************************/
void shiftCursorLeft ()
void shiftCursorRight ()
-----------------------------------------------------------------------------
- shift cursour to the left/right for 1 cell with aligning display position if cursour ot of screen borders

Parameters: void				
Return:	void
	
/****************************************************************************/
void shiftDisplayLeft (uint8_t pos)
void shiftDisplayRight (uint8_t pos)
-----------------------------------------------------------------------------
- shift display to the left/right for corresponding cells specified by pos parameter without aligning cursour
position

Parameters: 
uint8_t pos - number of display shifts				
Return:	void
	
/****************************************************************************/
void shiftDisplayLeft ()
void shiftDisplayRight ()
-----------------------------------------------------------------------------
- shift display to the left/right for 1 cell without aligning cursour
position

Parameters: void				
Return:	void
	
/****************************************************************************/
uint8_t getLine()
-----------------------------------------------------------------------------
- returns current line number

Parameters:	void
Return:
uint8_t - current line number

/****************************************************************************/
uint8_t getCursorPosition()
-----------------------------------------------------------------------------
- returns current cursour position in the current line (min value is 0)

Parameters: void
Return:
uint8_t - current cursour position
	
/****************************************************************************/
uint8_t getLineQuantity()
-----------------------------------------------------------------------------
- returns line quantity of used display. Gets LINE_QUANTITY value from configs in lcd_conf.h -file

Parameters:	void
Return:
uint8_t - line quantity of current LCD
	
/****************************************************************************/
uint8_t getCursorPositionMax()
-----------------------------------------------------------------------------
- returns maximal cursour position in line of current display. Gets CURSOR_POSITION_MAX value from
configs in lcd_conf.h -file

Parameters:	void
Return:
uint8_t - maximal cursour position in line of current LCD
	
/****************************************************************************/
uint8_t getDisplayWidth()
-----------------------------------------------------------------------------
- returns screen width of current LCD. Gets SCREEN_WIDTH value from configs in lcd_conf.h -file

Parameters:	void
Return:
uint8_t - screen width of current LCD
	
/****************************************************************************/
bool isEndOfLine()
-----------------------------------------------------------------------------
- checks whether the current cursor position has reached the end of the current display line.

Parameters:	void
Return:
true - has reached the end of line
false - hasn't reached the end of line

/****************************************************************************/
void loadCGROM(uint8_t position, uint8_t* charPattern)
-----------------------------------------------------------------------------
- loads custom 5x8 dot or 5x10 dot character patern from array with 8-bit character codes to 
character generator ROM (CGROM) of display.

Parameters:	
uint8_t position - position of stored character pattern in CGRAM of display/
					0..7 - for 8-dots height character pattern
					0..3 - for 10-dots height character 
uint8_t* charPattern - array with rows of character pattern. Every element of array corresponds
to each row of character. Therefor array length must be equal quantity dots of height. 
Return:	void

/****************************************************************************/
void printCGROM (uint8_t data)
-----------------------------------------------------------------------------
- unloads symbols onto the current cursour position on the screen from CGROM memory corresponding
to the symbol table in the facory datasheets. Custom character patterns from corresponding position
saved early by loadCGROM()-method can be unload too.
For correct uploading symbols for different LCD-grafic controllers need to inlude corresponding char_table_***.h-file.  

Parameters:	
uint8_t data - position of corresponding symbol in characters table CGROM of LCD-display.
Return:	void

/****************************************************************************/
void printCh (uint16_t data)
-----------------------------------------------------------------------------
- unloads character onto the current cursour position on the screen from CGROM memory corresponding
to the symbol table in the facory datasheets. 
For correct uploading symbols for different LCD-grafic controllers need to inlude corresponding char_table_***.h-file.  

Parameters:	
uint16_t data - character 16-bit code corresponding current character coding (must be suppots by char_table_***.h-file). 
Return:	void

/****************************************************************************/
void print(std::string data, uint8_t length)
void print(std::string data)
-----------------------------------------------------------------------------
- prints string on the screen.  
For correct uploading symbols for different LCD-grafic controllers need to inlude corresponding char_table_***.h-file.  

Parameters:	
std::string data - printable string
uint8_t length - printable length of the string
Return:	void

/****************************************************************************/
void print(int value, uint8_t digits)
void print(int value)
-----------------------------------------------------------------------------
- prints integer value.  
For correct uploading symbols for different LCD-grafic controllers need to inlude corresponding char_table_***.h-file.  

Parameters:	
int value - printable integer
uint8_t digits - number of printable digits
Return:	void

/****************************************************************************/
void print(double value, uint8_t digits)
void print(double value)
void print(float value, uint8_t digits)
void print(float value)
-----------------------------------------------------------------------------
- prints fractional value (double/float).  
For correct uploading symbols for different LCD-grafic controllers need to inlude corresponding char_table_***.h-file.  

Parameters:	
double value / float value - printable double/float value
uint8_t digits - number of decimal digits
Return:	void

/****************************************************************************/
void printHex(int data, uint8_t  digits)
-----------------------------------------------------------------------------
- prints data value into HEX-format.  
For correct uploading symbols for different LCD-grafic controllers need to inlude corresponding char_table_***.h-file.  

Parameters:	
int data - printable data
uint8_t digits - number of hexadecimal digits
Return:	void

/****************************************************************************/
void backspace()
-----------------------------------------------------------------------------
- erases one printed sign with cursor backshifting.  

Parameters:	void
Return:	void

/****************************************************************************/
void progressBar(float percentProgress, uint16_t symbol)
-----------------------------------------------------------------------------
- prints progressbar by symbols filling screen proportional percentProgress value. 

Parameters:
float percentProgress - percentage value in range 0..100
uint16_t symbol - filling symbol
Return:	void

/****************************************************************************/
void progressBar(float percentProgress)
-----------------------------------------------------------------------------
- prints progressbar by #-symbols filling screen proportional percentProgress value. 

Parameters:
float percentProgress - percentage value in range 0..100
Return:	void

/****************************************************************************/
