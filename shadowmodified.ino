
 */

#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wtv020sd16p.h>


#define TX             0
#define RX             1
#define resetPin       2
#define clock          3
#define data           4
#define busy           5
#define button         6

#define clearMemory          0
#define total          20   //the total number of prohibited statements has been limited to 20

#define State          11    //the state pin of the HC 05 module
#define rs             12
#define en              7
#define d4              8
#define d5              9
#define d6             10
#define d7             13

int address;
int VoiceAddress;
int RandomNumber;
int memory;
int last_Memory;
int State1;
int never[total] = {};
int minNo;
int maxNo;
String voice;


Wtv020sd16p module(resetPin, clock, data, busy);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial BT(TX, RX);


// The characters to be displayed on the screen
byte neutral_part[8] = {

  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111

};

byte blink_part[8] = {

  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111

};

byte Glee_left[8] = {

  0b00000,
  0b00000,
  0b00111,
  0b01111,
  0b11111,
  0b11111,
  0b11100,
  0b11000
};

byte Glee_right[8] = {

  0b00000,
  0b00000,
  0b11100,
  0b11110,
  0b11111,
  0b11111,
  0b00111,
  0b00001

};

byte Sad_left[8] = {

  0b00000,
  0b00000,
  0b10000,
  0b11000,
  0b11111,
  0b11111,
  0b01111,
  0b00111
};

byte Sad_right[8] = {

  0b00000,
  0b00000,
  0b00001,
  0b00011,
  0b11111,
  0b11111,
  0b11110,
  0b11100
};

byte Squint_left[8] = {

  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01111,
  0b11111,
  0b00000

};

byte Squint_right[8] = {

  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11110,
  0b11111,
  0b00000

};


void setup() {


  pinMode (button, INPUT);                         //set the button as an input
  pinMode(State, INPUT);
  BT.begin(9600);                                  //set the bluetooth bandwith to 9600
  lcd.begin(16, 2);                                //initialize the lcd to have 16 columns and 2 rows
  memory = clearMemory;                            //clear the memory


  //create the characters
  lcd.createChar(0, neutral_part);
  //neutral is set as 0
  lcd.createChar(1, blink_part);
  //blink as 1
  lcd.createChar(2, Glee_left);
  //glee left as 2
  lcd.createChar(3, Glee_right);
  //glee right as 3
  lcd.createChar(4, Sad_left);
  //sad left as 4
  lcd.createChar(5, Sad_right);
  //sad right as 5
  lcd.createChar(6, Squint_left);
  //squint left as 6
  lcd.createChar(7, Squint_right);
  //squint right as 7
  module.reset();                                  //reset the wtv020sd16p module
  module.playVoice(262);                           //say hello to everyone
  delay(40);                                       //delay added to make things stable
  Neutral();

}

void loop() {

  if (State == LOW) {                 //check and inform if Eve is not connected through Bluetooth
    RandomNumber = random(1);         //create Random Numbers from 0 to 1
    Squint();                         //make up the angry-squinting expression
    if (RandomNumber == 1)
      module.playVoice(0);
    else
      module.playVoice(1);
  }

  while (BT.available()) {            //while Serial data is available over bluetooth
    delay(10);                        //delay added to make things stable
    char c = BT.read();               //conduct a Serial reading of the Bluetooth data
    voice += c;                       //build the strings
  }











  
  
  

  
  if (voice.indexOf("your name") > -1) {                     //starting from the most common question of introduction
    Neutral();                                     
    RandomNumber = random(2, 4);                   //generate random numbers from the range 2 to 4
    minNo = 2;
    maxNo = 4;
    playBack();
  }

  else if ((voice.indexOf("address") > -1) || (voice.indexOf("stay") > -1)) { //asking address
    Neutral();
    RandomNumber = random(5, 7);
    minNo = 5;
    maxNo = 7;
    playBack();
 
  }
   else if ((voice.indexOf("address") > -1) || (voice.indexOf("stay") > -1))
   { 
    Neutral();
    RandomNumber = random(5, 7);
    minNo = 5;
    maxNo = 7;
    playBack();
   }

   
else if ((voice.indexOf("Machine learning software") > -1) || (voice.indexOf("Artifcial intelligent") > -1 ))
{
Squint();
module.playVoice(514);

}
else if ((voice.indexOf("shadow") > -1))
{
  Neutral();
  module.playVoice(513);
}
else if ((voice.indexOf("why were you made") > -1) ||(voice.indexOf("reason for your creation") > -1))
{Neutral();
module.playVoice(500);
}

else if ((voice.indexOf("sentinel") > -1) || (voice.indexOf("guard me") > -1))
{Neutral();
module.playVoice(501);
}

else if ((voice.indexOf("reminders") > -1) || (voice.indexOf("remind") > -1))
{
  module.playVoice(502);
}

else if ((voice.indexOf("goodbye") > -1) ||  (voice.indexOf("see you") > -1))
{
  RandomNumber = random(503,504) ;
  minNo = 503 ;
  maxNo = 504 ;
  playBack();
}

else if(voice.indexOf("what am I forgeting") > -1)
{
  module.playVoice(505);
}

else if(voice.indexOf("promises") > -1)
{
  module.playVoice(506);
}


else if(voice.indexOf("hard work") > -1)
{
  module.playVoice(507);
}


else if(voice.indexOf("about rules") > -1)
{
  module.playVoice(508);
}



else if ((voice.indexOf("algorithim dead man") > -1) || (voice.indexOf("protocol dead man") > -1))
{
  module.playVoice(509);
}



else if ((voice.indexOf("deploy") > -1) || (voice.indexOf("initiate") > -1) || (voice.indexOf("launch") > -1))
{
  module.playVoice(510);
}



else if ((voice.indexOf("self destruct") > -1) || (voice.indexOf("erase data") > -1))
{
  module.playVoice(511);
}


else if(voice.indexOf("feeling today") > -1)
{
  module.playVoice(512);
}




  

  else if (voice.indexOf("phone number") > -1) {
    Neutral();
    RandomNumber = random(8, 10);
    minNo = 8;
    maxNo = 10;
    playBack();
  }

  else if (voice.indexOf("who asked you") > -1) {
    Squint();           //set up the squint face
    RandomNumber = random(11, 13);
    minNo = 11;
    maxNo = 13;
    playBack();
  }

  else if ((voice.indexOf("gender") > -1) || (voice.indexOf("male") > -1) || (voice.indexOf("female") > -1)) { //asking the gender
    Squint();
    RandomNumber = random(14, 16);
    minNo = 14;
    maxNo = 16;
    playBack();
  }

  else if (voice.indexOf("read") > -1) {
    Neutral();
    RandomNumber = random(17, 19);
    minNo = 17;
    maxNo = 19;
    playBack();
  }


  else if ((voice.indexOf("yes") > -1) || (voice.indexOf("of course") > -1) || (voice.indexOf("surely") > -1)) {
    Glee();                       //set up the happy cute little face
    RandomNumber = random(20, 22);
    minNo = 20;
    maxNo = 22;
    playBack();

  }

  else if ((voice.indexOf("beautiful") > -1) || (voice.indexOf("cute") > -1)) {
    Glee();
    RandomNumber = random(23, 25);
    minNo = 23;
    maxNo = 25;
    playBack();
  }
  else if ((voice.indexOf("married") > -1) || (voice.indexOf("maritial status") > -1)) {
    Glee();
    RandomNumber = random(26, 28);
    minNo = 26;
    maxNo = 28;
    playBack();
  }


  else if (voice.indexOf("friend") > -1) {
    Neutral();
    RandomNumber = random(29, 31);
    minNo = 27;
    maxNo = 29;
    playBack();

  }

  else if (voice.indexOf("google now") > -1) {
    Glee();
    module.playVoice(32);
    memory = 32;
  }

  else if (voice.indexOf("siri") > -1) {
    Glee();
    module.playVoice(33);
    memory = 33;
  }

  else if ((voice.indexOf("game") > -1) || (voice.indexOf("sport") > -1)) {
    Glee();
    RandomNumber = random(34, 36);
    minNo = 34;
    maxNo = 36;
    playBack();
  }


  else if ((voice.indexOf("depressed") > -1) || (voice.indexOf("sad") > -1) || ((voice.indexOf("not") > -1) && (voice.indexOf("good") > -1)) > -1) {
    Sad();          
    RandomNumber = random(37, 41);
    minNo = 37;
    maxNo = 41;
    playBack();

  }


  else if ((voice.indexOf("sing") > -1) && (voice.indexOf("song") > -1)) {
    Glee();         //Robots should always sing with a happy mood
    RandomNumber = random(45, 46);
    minNo = 45;
    maxNo = 46;
    playBack();
  }

  else if ((voice.indexOf("you") > -1) && (voice.indexOf("human") > -1)) {
    Neutral();
    RandomNumber = random(47, 59);
    minNo = 49;
    maxNo = 51;
    playBack();

  }

  else if (voice.indexOf("shut up") > -1) {
    Squint();
    RandomNumber = random(50, 52);
    minNo = 52;
    maxNo = 54;
    playBack();

  }
  else if (voice.indexOf("bore") > -1) {
    Neutral();
    RandomNumber = random(54, 55);
    minNo = 54;
    maxNo = 55;
    playBack();
  }

  else if ((voice.indexOf("fact") > -1) || (voice.indexOf("interesting") > -1) || (voice.indexOf("some") > -1)) {
    Glee();     //it is uninteresting to learn without being happy
    RandomNumber = random(58, 67);
    minNo = 56;
    maxNo = 67;
    playBack();
  }
  else if (voice.indexOf("joke") > -1) {
    Glee();       //jokes are not tolerable without a smiling face
    RandomNumber = random(68, 72);
    minNo = 68;
    maxNo = 72;
    playBack();
  }

  else if ((voice.indexOf("age") > -1) || (voice.indexOf("old") > -1)) {
    Neutral();
    RandomNumber = random(73, 75);
    minNo = 73;
    maxNo = 75;
    playBack();
  }

  else if (voice.indexOf("story") > -1) {
    Glee();
    RandomNumber = random(76, 79);
    minNo = 76;
    maxNo = 79;
    playBack();
  }

  else if ((voice.indexOf("how are you") > -1) || (voice.indexOf("how do you do") > -1)) {
    Glee();
    RandomNumber = random(79, 81);
    minNo = 70;
    maxNo = 82;
    playBack();
  }

  else if (voice.indexOf("thank") > -1) {
    Glee();
    module.playVoice(83);
    memory = 83;
  }

  else if ((voice.indexOf("sibling") > -1) || (voice.indexOf("brother") > -1) || (voice.indexOf("sister") > -1)) {
    Neutral();
    RandomNumber = random(84, 86);
    minNo = 84;
    maxNo = 86;
    playBack();
  }

  else if (voice.indexOf("introduc") > -1) { //introduction
    Glee();     //we should always introduce ourselves with a smiling face
    RandomNumber = random(87, 88);
    minNo = 87;
    maxNo = 88;
    playBack();
  }

  else if (voice.indexOf("love") > -1) {
    Glee();
    RandomNumber = random(89, 91);
    minNo = 89;
    maxNo = 91;
    playBack();
  }
  else if ((voice.indexOf("mean") > -1) && (voice.indexOf("Eve") > -1)) {
    Neutral();
    RandomNumber = random(92, 94);
    minNo = 92;
    maxNo = 94;
    playBack();
  }

  else if ((voice.indexOf("boring") > -1) || (voice.indexOf("stupid") > -1) || (voice.indexOf("annoying") > -1)) {
    Neutral();
    module.playVoice(95);
    memory = 95;
  }

  else if ((voice.indexOf("owner") > -1) || (voice.indexOf("inventor") > -1) || (voice.indexOf("creat") > -1)) {
    Glee();         //say the name of the creator with a smile on the face
    module.playVoice(96);
    memory = 96;
  }

  else if (voice.indexOf("hate") > -1) {
    Sad();
    module.playVoice(97);
    memory = 97;
  }

  else if (((voice.indexOf("my") > -1) || (voice.indexOf("we") > -1)) && (voice.indexOf("friend") > -1)) {
    Glee();
    module.playVoice(98);
    memory = 98;
  }





  //The commands from Eliza Ai that makes the distinction in the software

  else if (voice.indexOf("can you") > -1) {
    Squint();
    RandomNumber = random(100, 102);
    minNo = 100;
    maxNo = 102;
    playBack();
  }

  else if (voice.indexOf("can i") > -1) {
    Neutral();
    RandomNumber = random(103, 105);
    minNo = 103;
    maxNo = 105;
    playBack();
  }

  else if ((voice.indexOf("you are") > -1) || (voice.indexOf("you're") > -1)) {
    Squint();
    RandomNumber = random(106, 110);
    minNo = 106;
    maxNo = 110;
    playBack();
  }

  else if (voice.indexOf("i dont") > -1) {
    Neutral();
    RandomNumber = random(111, 114);
    minNo = 111;
    maxNo = 114;
    playBack();
  }
  //////////
  else if (voice.indexOf("i feel") > -1) {
    Squint();
    RandomNumber = random(115, 117);
    minNo = 115;
    maxNo = 117;
    playBack();
  }////

  else if ((voice.indexOf("why don't you") > -1) || (voice.indexOf("why do not you") > -1) || (voice.indexOf("why dont you") > -1)) {
    Squint();
    RandomNumber = random(118, 120);
    minNo = 118;
    maxNo = 120;
    playBack();
  }// I have a doubt in this block of the program

  else if (voice.indexOf("why can't i") > -1) {
    Neutral();
    RandomNumber = random(121, 125);
    minNo = 121;
    maxNo = 125;
    playBack();
  }

  else if (voice.indexOf("are you") > -1) {
    Squint();
    RandomNumber = random(126, 128);
    minNo = 126;
    maxNo = 128;
    playBack();
  }
  //wrong
  else if (voice.indexOf("i can't") > -1) {

    RandomNumber = random(129, 131);
    minNo = 129;
    maxNo = 131;
    playBack();
  }

  else if ((voice.indexOf("i am") > -1) || (voice.indexOf("i'm") > -1)) {
    RandomNumber = (132, 135);
    minNo = 132;
    maxNo = 135;
    playBack();//
  }

  else if (voice.indexOf("you ") > -1) {
    RandomNumber = random(136, 138);
    minNo = 136;
    maxNo = 138;
    playBack();
  }//

  else if ((voice.indexOf("what") > -1) || (voice.indexOf("how") > -1) || (voice.indexOf("where") > -1)) {
    RandomNumber = random(139, 148);
    minNo = 139;
    maxNo = 148;
    playBack();//
  }

  else if (voice.indexOf("i want") > -1) {
    RandomNumber = random(149, 153);
    minNo = 149;
    maxNo = 153;
    playBack();
  }



  else if (voice.indexOf("name") > -1) {
    RandomNumber = random(154, 156);
    minNo = 154;
    maxNo = 156;
    playBack();
  }

  else if (voice.indexOf("cause") > -1) {
    RandomNumber = random(157, 160);
    minNo = 157;
    maxNo = 160;
    playBack();
  }

  else if (voice.indexOf("sorry") > -1) {
    RandomNumber = random(161, 163);
    minNo = 161;
    maxNo = 163;
    playBack();
  }

  else if (voice.indexOf("dream") > -1) {
    RandomNumber = random(164, 167);
    minNo = 164;
    maxNo = 167;
    playBack();
  }


  else if (voice.indexOf("always") > -1) {
    RandomNumber = random(168, 171);
    minNo = 168;
    maxNo = 171;
    playBack();
  }

  else if (voice.indexOf("think") > -1) {
    RandomNumber = random(172, 175);
    minNo = 172;
    maxNo = 175;
    playBack();
  }

  else if (voice.indexOf("alike") > -1) {
    RandomNumber = random(176, 181);
    minNo = 176;
    maxNo = 172;
    playBack();
  }

  else if (voice.indexOf("friend") > -1) {
    RandomNumber = random(182, 186);
    minNo = 182;
    maxNo = 186;
    playBack();
  }

  else if (voice.indexOf("computer") > -1) {
    RandomNumber = random(187, 192);
    minNo = 187;
    maxNo = 192;
    playBack();
  }

  else if (voice.indexOf("car") > -1) {
    minNo = 192;
    maxNo = 198;
    RandomNumber = random(minNo, maxNo);
    playBack();
  }


  else if ((voice.indexOf("yes") > -1) || (voice.indexOf("yeah") > -1)) {
    RandomNumber = random(199, 202);
    minNo = 199;
    maxNo = 202;
    playBack();
  }

  else if (voice.indexOf("maybe") > -1) {
    RandomNumber = random(201, 207);
    minNo = 201;
    maxNo = 207;
    playBack();
  }

  else if (voice.indexOf("your") > -1) {
    RandomNumber = random(208, 210);
    minNo = 208;
    maxNo = 210;
    playBack();
  }

  else if (voice.indexOf("no") > -1) {
    RandomNumber = random(211, 214);
    minNo = 211;
    maxNo = 214;
    playBack();
  }

  else if ((voice.indexOf("hello") > -1) || (voice.indexOf("hi ") > -1)) {
    RandomNumber = random(257, 259);
    minNo = 257;
    maxNo = 259;
    playBack();
  }

  else if ((voice.indexOf("last") > -1) || (voice.indexOf("say") > -1)) {

    if (memory == clearMemory)                  //if nothing is stored in the memory
      module.playVoice(254);              //say that nothing was said before
    else {
      RandomNumber = random(250, 252);
      module.playVoice(RandomNumber);     // I just said that
      module.playVoice(memory);           //say the last thing stored in the memory
    }
  }

  else if ((voice.indexOf("not") > -1) || (voice.indexOf("don't") > -1) || (voice.indexOf("never") > -1)) {     //the prohibition command
    module.playVoice(255);
    EEPROM_write();

  }

  else if ((voice.indexOf("are allowed to") > -1) || (voice.indexOf("can say") > -1) || (voice.indexOf("can tell") > -1)) {//the permission command
    module.playVoice(256);
    EEPROM_UndoWrite();
  }

  else { //this part is under the experimentation process to make sure it works fine
    RandomNumber = random(214, 222);
    minNo = 214;
    maxNo = 223;
    playBack();
  }

  if (button == HIGH) {                 //if reset prohibition button is pressed
    module.playVoice(253);              //inform that Eve has been resetted of all prohibitions
    Memory_clear();                     //clear all the data in the EEPROM
  }

  voice = "";
}



//the playback functions
void checkProhibition() {

  if (RandomNumber == memory)                 //check if the playback is the same as the previous one
    RandomNumber = ((RandomNumber >= minNo) && (RandomNumber < maxNo)) ? RandomNumber++ : RandomNumber--;

  for (int i; i <= total; i++) {              //conduct a reading of all the prohibited values
    if (RandomNumber  == never[i]) {           //if robot is going to say the prohibited thing
      RandomNumber = ((RandomNumber >= minNo) && (RandomNumber < maxNo)) ? RandomNumber++ : RandomNumber--;
      break;
    }
  }
}


void playBack() {           //the playback function plays the required voice files and stores in the memory
  checkProhibition();
  module.playVoice(RandomNumber);
  memory = RandomNumber;
}

/*
  void Introduction() {

  while (State1 == 0) {         //unless no one has started talking with Eve
    if (BT.available()) {
      module.playVoice(260);    //may I ask whom I am speaking to?
      if (BT.available()) {
        module.playVoice(261);  //OK so hello, let's start talking
        State1 = 1;             //store in memory that Eve has been introduced
        break;
      }
    }
  }
  }
*/

//the prohibition functions
void Memory_clear() {
  //this function clears all the values stored in the EEPROM and the prohibition array
  //function is executed when the reset_prohibition button is pressed

  for (int i; i <= total; i++)
    EEPROM.write(i, clearMemory);
  for (int i; i <= total; i ++)
    never[i] = clearMemory;
}

void EEPROM_read() {                          //reads the values stored in the EEPROM
  for (int i; i <= total; i++) {
    never[i] = EEPROM.read(i);          //store the prohibited statement number in the memory from the EEPROM
  }
}

//EEPROM functions that store prohibited statements in the EEPROM
void EEPROM_write() {

  //there are a particular number of prohibited statements
  //firstly we determine which address is clear
  //then we write the prohibited statement value at the free address

  for (int i; i <= total; i++) {           //search for the addresses for free memory
    if (never[i] == 0) {                   //if a particular address is clear,
      EEPROM.write(never[i], memory);      //store the prohibited statement in the EEPROM
      last_Memory = never[i];              //store the address of the last prohibited statement so that we might undo it later
    }
  }
  EEPROM_read();                            //store the new value in the prohibition array
}

void EEPROM_UndoWrite() {

  //make the last prohibited statement executable
  //firstly search for the address of the last prohibited statement
  //when found, delete the contents of that address

  for (int i; i <= total; i++) {
    if (never[i] == last_Memory)
      EEPROM.write(never[i], clearMemory);
  }
  EEPROM_read();
}

void blink() {

  lcd.clear();                //clear the lcd screen
  delay(40);
  for (int i; i <= 15; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(1));             //print the blink character unless the it covers the whole screen
  }
  delay(400);                 //wait for 400 micro seconds so that the blink becomes prominent to the human eye
}

void Neutral() {

  blink();
  lcd.clear();  //clear the previous lcd values
  delay(200);
  lcd.setCursor(6, 0);
  lcd.write(byte(0));
  lcd.setCursor(6, 1);
  lcd.write(byte(0));
  lcd.setCursor(7, 0);
  lcd.write(byte(0));
  lcd.setCursor(7, 1);
  lcd.write(byte(0));

  lcd.setCursor(9, 0);
  lcd.write(byte(0));
  lcd.setCursor(9, 1);
  lcd.write(byte(0));
  lcd.setCursor(10, 0);
  lcd.write(byte(0));
  lcd.setCursor(10, 1);
  lcd.write(byte(0));

}

void Glee() {

  blink();//blink before the robot is in the glee mood
  lcd.clear();  //clear the lcd screen
  delay(200);
  lcd.setCursor(6, 0);
  lcd.write(byte(2));
  lcd.setCursor(7, 0);
  lcd.write(byte(3));

  lcd.setCursor(9, 0);
  lcd.write(byte(2));
  lcd.setCursor(10, 0);
  lcd.write(byte(3));
}


void Sad() {

  blink();//blink before the robot sets in the mood
  lcd.clear();    //clear the screen
  delay(200);
  lcd.setCursor(6, 0);
  lcd.write(byte(4));
  lcd.setCursor(7, 0);
  lcd.write(byte(5));

  lcd.setCursor(9, 0);
  lcd.write(byte(4));
  lcd.setCursor(10, 0);
  lcd.write(byte(5));
}

void Squint() {

  blink();//blink before the robot sets in the mood
  lcd.clear();    //clear the screen for the current display
  delay(200);
  lcd.setCursor(6, 0);
  lcd.write(byte(6));
  lcd.setCursor(7, 0);
  lcd.write(byte(7));

  lcd.setCursor(9, 0);
  lcd.write(byte(6));
  lcd.setCursor(10, 0);
  lcd.write(byte(7));
}
