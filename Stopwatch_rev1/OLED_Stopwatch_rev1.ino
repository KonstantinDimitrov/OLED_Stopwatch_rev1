/*

*/
#include <U8glib.h>     // OLED
#include <StopWatch.h>  // Stowatch library
/*********************************************/
int buttonA = 5;   // Physical
int buttonB = 6;   // push buttons
int buttonC = 7;   // for calling fuctions
/***************STOPWATCH*********************/
StopWatch sw_millis;                //

char swatchbuf[10];                 //
int frameRate = 100;                //   
long interval = (1000/frameRate);   //
long previousMillis = 0;            // 
long startTime ;                    // 
long elapsedTime ;                  //
int displayMillis;                  // 
int displaySecs;                    // 
int displayMins;                    // 
int elapsedFrames;                  // 
int elapsedSeconds;                 // 
int elapsedMinutes;                 //

int count = 0;                      //
int count1 = 0;                     //
/****************OLEDS*************************/

U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9, 8);  // CLK=13, DIN=11, CS=10, DC=9, RES=8
 //U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9, 8); // CLK=13, DIN=11, CS=10, DC=9, RES=8
 //U8GLIB_SSD1306_128X32 u8g(13, 11, 10, 9, 8); // CLK=13, DIN=11, CS=10, DC=9, RES=8
 
/*****************STOPWATCH********************/
 void draw_Stopwatch_Face(void){
      u8g.setFont(u8g_font_profont17r);  // select font
      u8g.setPrintPos(10, 10);           // set position
      u8g.print("stopwatch");            // name of page
      u8g.setFont(u8g_font_profont29r);  // select font
      u8g.setPrintPos(2, 50);            // set position
      u8g.print(swatchbuf);              // display time
    
}
/**********************************************/
void setup() {
    pinMode(buttonA, INPUT_PULLUP);        //
    pinMode(buttonB, INPUT_PULLUP);        //
    pinMode(buttonC, INPUT_PULLUP);        //
}
/**********************************************/
void loop() {
         static int button1_last = 0;
         int button1_state = digitalRead(buttonB);
     while (button1_state != button1_last)
  {
     count ++ ;
     button1_last = button1_state;
     if (count >= 5) {
       count = 1;
    }
  }
    switch (count) {
     case 3:
        
        sw_millis.stop();
        break;
     case 4:
        sw_millis.start();
        break;
     
  }if (digitalRead(buttonC) == LOW)
    {
        sw_millis.reset();
    }
    else
/**************************************************************************/
   elapsedTime =   sw_millis.elapsed();                 // store elapsed time
   elapsedMinutes = (elapsedTime / 60000L);
   elapsedSeconds = (elapsedTime / 1000L);              // divide by 1000 to convert to seconds - then cast to an int to print
   elapsedFrames = (elapsedTime / interval);            // divide by 100 to convert to 1/100 of a second - then cast to an int to print
   displayMillis = (int)(elapsedFrames % frameRate);    // use module operator to get fractional part of 100 Seconds
   displaySecs = (int)(elapsedSeconds % 60L);           // use module operator to get fractional part of 60 Seconds
   displayMins = (int)(elapsedMinutes % 60L);           // use module operator to get fractional part of 60 Minutes
   
   sprintf(swatchbuf, "%02d:%02d.%02d",displayMins, displaySecs, displayMillis);

}
