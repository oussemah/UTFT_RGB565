/* Function    :    rgb565Draw
 * Description : 	Draws a part of a bigger picture on the myGLCD UTFT object
 * Remarqs     :	code works successfully on 5" 800x480 LCD using a 800x480 picture
 * 			   :    picture file is in raw format (i.e. no image file header, just the pixel description buffer)
 */
 
/* the following function can be inserted into original library in UTFT.cpp file
 *  the original version gives inverted picture and inverted color values
 * 
void UTFT::drawPixelLineInverted(int x, int y, int width, uint16_t* buf)
{
	uint16_t* temp = (uint16_t* )buf + width;
	cbi(P_CS, B_CS);
	setXY(x, y, x+width, y);
	for (int i=width; i>0; i--)
	{
		fcl = ((*temp) >> 8) & 0xFF;
		fch = (*temp) & 0xFF ;
		temp--;
		LCD_Write_DATA(fch, fcl);
	}
	sbi(P_CS, B_CS);
	clrXY();
}

 */
 
#define BUFFER_SIZE 40 /* how many lines we can read */
 
boolean rgb565Draw(char *filename, uint8_t x, uint8_t y, uint16_t w, uint16_t h, uint16_t picWidth)
{
  File picFile;
  uint32_t rowSize;
  uint8_t line[2 * picWidth * BUFFER_SIZE];
  uint16_t row;
  uint8_t tempH = BUFFER_SIZE, i;
  
  picFile = SD.open(filename);
  
  rowSize = picWidth * 2 * BUFFER_SIZE;
 
  uint32_t startTime = millis(); 
  picFile.seek(y * picWidth * 2);
  
  for (row = 0; row < h;) {
        if (row > h-tempH-1) 
        {
          tempH = h-row-1;
          rowSize = 2 * picWidth * tempH; 
        }
        picFile.read( line, rowSize);
        for (i=0; i < tempH; i++)
        {
          myGLCD.drawPixelLineInverted(x, y+row+i, w, (uint16_t *)line+ i * picWidth);
        }
             
        row += BUFFER_SIZE;
  }
  
  Serial.print("Done in :");
  Serial.print(millis() - startTime);
  Serial.println(" ms"); 
  picFile.close(); 
}
