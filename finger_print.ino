#include <Adafruit_Fingerprint.h>

#include <Key.h>
#include <Keypad.h>
const int numButtons = 6;
 
int buttonCounters[numButtons] = {0};
int buttonStates[numButtons] = {HIGH};
int lastButtonStates[numButtons] = {HIGH};

const int buttonPins[numButtons] = {10, 11, 12 , A0, A1, A2}; 
char k[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};


 
byte rpins[4]={2,3,4,5};
byte cpins[4]={6,7,8,9};
char mykey;
Keypad mypad (makeKeymap(k),rpins,cpins,4,4);
char pass[]={'1','3','4','5'};
byte counter=0,j=0;

void resetlcd(){
 lcd.home();
 lcd.clear();
 lcd.print("Enter password");
 lcd.setCursor(0,1);
}

void setup() {
  pinMode(13,OUTPUT);
  pinMode(10,INPUT_PULLUP);
 lcd.init();
 lcd.backlight();
 for (int i = 0; i < numButtons; ++i) {
 pinMode(buttonPins[i], INPUT_PULLUP);
   }
   
 resetlcd();

}
void loop() {
  mykey=mypad.getKey();
  if(mykey=='D'){
    lcd.clear();  
    lcd.home();
    for(j=0;j<sizeof(upass);j++){
      break;}
  if((j==sizeof(pass))&&(counter==0)){
  counter=-1;
  lcd.clear();
  lcd.home();
  lcd.print("User authorized");
  digitalWrite(13,1);
  delay(1000);
  digitalWrite(13,0);
  resetlcd();
  }
  else {
  counter=-1;
  lcd.clear();
  lcd.home();
  lcd.print("Wrong password");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter your finger");
  delay(2000);
  resetlcd();
  }  
  }
  else if(mykey){
    *(pass+counter)=mykey;
    lcd.print("*");
    counter=(counter>=3)?-1:counter;
   counter++; 
  }
    for (int i = 0; i < numButtons; ++i) {
    buttonStates[i] = digitalRead(buttonPins[i]);

    if (buttonStates[i] == LOW && lastButtonStates[i] == HIGH) {
      buttonCounters[i]++;
      updateLCD(i);
    }

    lastButtonStates[i] = buttonStates[i];
  }
}

void updateLCD(int buttonIndex) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The ID is :");
  lcd.print(buttonIndex + 1);  
  delay(1000);
}
