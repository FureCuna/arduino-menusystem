/*
 * lcd_nav.ino - Example code using the menu system library
 *
 * This example shows using the menu system with a 16x2 LCD display
 * (controled over serial).
 *
 * Copyright (c) 2015 arduino-menusystem
 * Licensed under the MIT license (see LICENSE)
 *
 * You also need to have the GLCD library for this to work
 */

#include <MenuSystem.h>
#include <glcd.h>
#include "fonts/allFonts.h"
#include "bitmaps/allBitmaps.h"

Image_t icon;

gText textArea;              // a text area to be defined later in the sketch
gText textAreaArray[3];      // an array of text areas  
gText countdownArea =  gText(GLCD.CenterX, GLCD.CenterY,1,1,Arial_14); // text area for countdown digits

unsigned long startMillis;
unsigned int  loops = 0;
unsigned int  iter = 0;
         int  theDelay = 20; 
// Menu variables
MenuSystem ms;
 Menu mm("Hoofd Menu");
  MenuItem mm_mi1("Level 1 - Item 1 (Item)");
 Menu mu1("Level 1 - Item 2 (menu)");
  MenuItem mu1_mi1("Level 2 - Item 1 (Item)");
 ooMenu mu2("Level 1 - Item 3 (Menu)");
  MenuItem mu2_mi1("Level 2 - Item 1 (Item)");



// Menu callback function
// In this example all menu items use the same callback.

void on_item1_selected(MenuItem* p_menu_item)
{
  GLCD.ClearScreen();

GLCD.CursorToXY (9,6);//putting the cursor at coordinates 9;6 so it wont be completely in the corner
GLCD.print("Item1 Selected");

  delay(1500); // so we can look the result on the GLCD
}

void on_item2_selected(MenuItem* p_menu_item)
{
  GLCD.ClearScreen();

GLCD.CursorToXY (9,6);//putting the cursor at coordinates 9;6 so it wont be completely in the corner
GLCD.print("Item2 Selected");


  delay(1500); // so we can look the result on the LCD
}

void on_item3_selected(MenuItem* p_menu_item)
{
  GLCD.ClearScreen();

GLCD.CursorToXY (9,6);//putting the cursor at coordinates 9;6 so it wont be completely in the corner
GLCD.print("Item3 Selected");

  delay(1500); // so we can look the result on the LCD
}

// Standard arduino functions

void setup()
{
  Serial.begin(9600);
   GLCD.Init();   // initialise the library, non inverted writes pixels onto a clear screen
  if(GLCD.Height >= 64)   
    icon = ArduinoIcon64x64;  // the 64 pixel high icon
  else
    icon = ArduinoIcon64x32;  // the 32 pixel high icon

  GLCD.ClearScreen(); 

  GLCD.SelectFont(System5x7, BLACK); // font for the default text area
  

  // Menu setup
  /*
  Menu Structure:
   -Item1
   -Item2
   -Item3
   --Item1
   
   */
  mm.add_item(&mm_mi1, &on_item1_selected);
  
  mm.add_menu(&mu1);
  mu1.add_item(&mu1_mi1, &on_item2_selected);
  mm.add_menu(&mu2);
  mu2.add_item(&mu2_mi1, &on_item3_selected);
  ms.set_root_menu(&mm);
  Serial.println("Menu setted.");
  displayMenu();
}

void loop()
{
  // Handle serial commands
  serialHandler();

  // Wait for two seconds so the output is viewable
  //delay(2000);
}

void displayMenu() {
  GLCD.ClearScreen();
  GLCD.GotoXY(0,0);
  // Display the menu
  Menu const* cp_menu = ms.get_current_menu();

  //lcd.print("Current menu name: ");
  GLCD.print(cp_menu->get_name());
  
  GLCD.GotoXY(0,20);
  
  GLCD.print(cp_menu->get_selected()->get_name());
}

void serialHandler() {
  char inChar;
  if((inChar = Serial.read())>0) {
    switch (inChar) {
    case 'w': // Previus item
      ms.prev();
      displayMenu();
      break;
    case 's': // Next item
      ms.next();
      displayMenu();
      break;
    case 'a': // Back presed
      ms.back();
      displayMenu();
      break;
    case 'd': // Select presed
      ms.select();
      displayMenu();
      break;
    case '?':
    case 'h': // Display help
      serialPrintHelp();
      break;
    default:
      break;
    }
  }
}

void serialPrintHelp() {
  Serial.println("***************");
  Serial.println("w: go to previus item (up)");
  Serial.println("s: go to next item (down)");
  Serial.println("a: go back (right)");
  Serial.println("d: select \"selected\" item");
  Serial.println("?: print this help");
  Serial.println("h: print this help");
  Serial.println("***************");

}
