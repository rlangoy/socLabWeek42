/*
  This program uses the HIVE Led/Switch shield for arduino uno.
  The program sends state of the switches over RS232 and
  Can set/clear the leds
  This example code is in the public domain.
 */

#include <stdio.h>  // Use the sprinf to generate strings

#define MAX_RECV_LINE_LENGTH 200
#define MAX_COMMANDS 10

String strIncompleteLine = "";   // a string to hold incoming data
String strInputLine = "";        // a string to the recieved line
boolean bStrComplete = false;    // whether the string is complete

String strCommands[MAX_COMMANDS];

// Give names to the input pins
int sw0 = 14;
int sw1 = 15;
int sw2 = 16;

// Give names to the output pins
int led0 = 8;
int led1 = 9;
int led2 = 10;

int i=0;
char msg[100];
int statusSw0 = 0;
int statusSw1 = 0;
int statusSw2 = 0;

void setup() {
    // make the Leds output width pulup  
  pinMode(led0,  OUTPUT );
  pinMode(led1,  OUTPUT );
  pinMode(led2,  OUTPUT );

  // make the switches input width pulup
  pinMode(sw0,  INPUT_PULLUP);
  pinMode(sw1,  INPUT_PULLUP);
  pinMode(sw2,  INPUT_PULLUP);

  //Save Initial status
  statusSw0 = digitalRead(sw0);
  statusSw1 = digitalRead(sw1);
  statusSw2 = digitalRead(sw2);

  //Turn Leds off
  digitalWrite(led0,1);
  digitalWrite(led1,1);
  digitalWrite(led2,1);
   
  // initialize serial:
  Serial.begin(9600);
  // reserve MAX_RECV_LENGTH bytes for the inputString:
  strIncompleteLine.reserve(MAX_RECV_LINE_LENGTH);
  strInputLine.reserve(MAX_RECV_LINE_LENGTH);  
}

//  strCommands - input string that contains a CVS string ($LED,1,0,1,0,1)
//  strTab - has the splited input (strTab[0]="$LED",strTab[1]="1",strTab[2]="0")
//  maxItems -  the maximum commands to parse
//  Return the number of read items
int SplitCommands(String  strCommands, String strTab[],int maxItems)
{
  //Start position looking for ','
  int fisrtCommaPosition=0; 
  int lastCommaPosition=0;
  int iItems=0;
  do
    { //Get the position of the next item
        lastCommaPosition = strCommands.indexOf(',',fisrtCommaPosition);
        if(lastCommaPosition != -1)
        {   strTab[iItems]= strCommands.substring(fisrtCommaPosition,lastCommaPosition);
            fisrtCommaPosition=lastCommaPosition+1;             
        }
        else
            //Prints the last element
            strTab[iItems]= strCommands.substring(fisrtCommaPosition,strInputLine.length()-1);
      
       iItems++; 

     } while((lastCommaPosition >=0) & (iItems<maxItems));    

  return iItems;
}

//Main loop do the work :)
void loop() 
{
     //Check if the state of the switches has changed
    if ( (statusSw0!=digitalRead(sw0)) |
         (statusSw1!=digitalRead(sw1)) |
         (statusSw2!=digitalRead(sw2)) )
      { //Transfer the new switch walues      

       //Store the new values
       statusSw0 = digitalRead(sw0);
       statusSw1 = digitalRead(sw1);
       statusSw2 = digitalRead(sw2);

       //Make the string to transfer
       sprintf(msg,"$SW,%d,%d,%d",
        digitalRead(sw0),digitalRead(sw1),
        digitalRead(sw2));
       
       //Transfer the serial data
       Serial.println(msg);
      }//end if
    
    // print the string when a newline arrives:
    if (bStrComplete) 
    { bStrComplete=false;
      // Splits the incoming string into strCommands[0] .. [MAX_COMMANDS]
      int nCommands=SplitCommands(strInputLine,strCommands,MAX_COMMANDS); // Parses the CVS string
      // if cmd = $LED send the values to the leds
      if (strCommands[0]=="$LED")
        {    digitalWrite(led0,1);
             digitalWrite(led1,1);
             digitalWrite(led2,1);
             
             if (strCommands[1]=="1")
                digitalWrite(led0,0);
             if (strCommands[2]=="1")
                digitalWrite(led1,0);
             if (strCommands[3]=="1")
                digitalWrite(led2,0);
        }//end of $LED
  
    }//end of bStrComplete
}// end Loop

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    strIncompleteLine += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if ((inChar == '\n') || (inChar == '\r') ) {
      strInputLine=strIncompleteLine;
      bStrComplete = true;  
      strIncompleteLine="";      
    }
  }
}
