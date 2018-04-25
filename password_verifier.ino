#include <Keypad.h>
#include <LiquidCrystal.h>

// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};
byte rowPins[ROWS] = {A0,A1,A2,A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11,10,9,8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

String password;

void setup(){
  digitalWrite(13,LOW);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //define password
  lcd.print("Set pass: ");
  password = getInputkeypad(4);
  lcd.setCursor(0,1);
  lcd.print("Successful.");
  delay(2000);
}

void loop(){
  lcd.clear();
  lcd.print("Verify pass");
  lcd.setCursor(0,1);
  if(verifyPass(password)){
    lcd.print("Successful.");
    digitalWrite(13,HIGH);
    delay(5000);
    digitalWrite(13,LOW);
  }else{
    lcd.print("wrong Password");
    delay(5000);
  }  
}

bool verifyPass(String pass){
  lcd.print("enter pass:");
  String enteredPass = getInputkeypad(pass.length());
  if(enteredPass == pass){
    return true;
  }
  else{
    return false;
  }
}

String getInputkeypad(int lenOfinput){
  String pas;
  bool active = true;
  while(active){
    char key = keypad.getKey();
    if (key) {
      lcd.print("*");
      pas += key;
    }
    if(pas.length() >= lenOfinput){
      active = false;
    }   
  }
  lcd.clear();
  return pas;
}
