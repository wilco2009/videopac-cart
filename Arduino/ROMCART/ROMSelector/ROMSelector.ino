#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include "videopacdisplay.h"
#include "ROMLIST.h"
#include "ROMSET0.h"
#include "ROMSET1.h"
#include "ROMSET2.h"
#include "ROMSET3.h"

// #define INIT

#define WAITING_KEY 0
#define WAITING_REPEAT 1
#define REPEATING_KEY 2
#define CHECKING_BUTTON_CONFIG 3

#define BUTTON_NOTHING 0
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_ENTER 3
#define BUTTON_ESCAPE 4
#define BUTTON_CONFIG 5
#define BUTTON_FACTORY_SETTINGS 6

#define FS(x) (__FlashStringHelper*)(x)

#define MAX_CUSTOM_NAME 14

#define ROMSET_POS(k) k*32*4
#define CUSTOM_NAME_POS(n) 512+n*MAX_CUSTOM_NAME
#define ROMSET_NAME_POS(n) 960+n*MAX_ROMSET_NAME

#define BYTE_TO_BINARY_PATTERN "%c %c %c %c %c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x01 ? '_' : '-'), \
  (byte & 0x02 ? '_' : '-'), \
  (byte & 0x04 ? '_' : '-'), \
  (byte & 0x08 ? '_' : '-'), \
  (byte & 0x10 ? '_' : '-')
  
byte selected = 0;
byte ROMselected = 0;

//#define FACT_ROMSET_3 "OTHERS2"
//const unsigned long int PROGMEM ROMSET_CRC_3[32] = {   
//  0x280D08F4,
//  0x11FF50AD,
//  0x825976A9,
//  0x9451BE1E,
//  0x2C9D1715,
//  0x1C750349,
//  0x0B2DEB61,
//  0x9C9DDDF9,
//  0x45E62222,
//  0x69893F7F,
//  0x58FA6766,
//  0x2122012C,
//  0x9E5EE195,
//  0xE7B26A56,
//  0x6CB1DE16,
//  0xA29F0FD4,
//  0x24D53E2C,
//  0xD3B09FEC,
//  0x2247405E,
//  0xF4C2075E,
//  0x4F73B44C,
//  0x5C8708AC,
//  0x19947048,
//  0xA5ABFD39,
//  0x07685850,
//  0xC97268DC,
//  0xBE26212B,
//  0xA2C6750E,
//  0x88D7CE72,
//  0x0009965B,
//  0xEB61888F,
//  0xC06A3880
//};
//
//#define FACT_ROMSET_2 "WAR&OTH"
//const unsigned long int PROGMEM ROMSET_CRC_2[32] = {   
//  0x1EEB88F5,
//  0x71AE8533,
//  0xDDBA0ED2,
//  0x45EF459C,
//  0x5AE57A8C,
//  0xA7344D1F,
//  0xFC5A7F08,
//  0x9D72D4E9,
//  0xFB83171E,
//  0xFD179F6D,
//  0xAFC093FD,
//  0x2A5F0B2B,
//  0x9BFC3E01,
//  0x2DCB77F0,
//  0x54736B74,
//  0x65E5A779,
//  0x17BE749B,
//  0x39E31BF0,
//  0xA6909A8B,
//  0x4E2CC6D3,
//  0x335481F1,
//  0x655FDF57,
//  0xD03EFA86,
//  0x7BE6F1EF,
//  0xA69C2C93,
//  0x6CB1DE16,
//  0x5C4F35D3,
//  0xDF36683F,
//  0x9487C920,
//  0x44D1A8A5,
//  0x95936B07,
//  0x395629E1
//};
//
//
//#define FACT_ROMSET_1 "LOG&SPOR"
//const unsigned long int PROGMEM ROMSET_CRC_1[32] = {   
//  0x7C747245,
//  0xD158EEBA,
//  0x9D2C45DC,
//  0x3B9D30C4,
//  0x193F3855,
//  0xBB6E7135,
//  0x11EDF25B,
//  0x7810BAD5,
//  0x69D21F8F,
//  0x1C8368E7,
//  0x85DFCDD7,
//  0xC8F36C28,
//  0xBBF276A0,
//  0xDC5AFAA2,
//  0xECCD03BE,
//  0xA030B990,
//  0x4663C4B6,
//  0xB07748E7,
//  0x084EE035,
//  0x14B6CC76,
//  0x89C6DE2C,
//  0xF9084AA3,
//  0x39989464,
//  0xA5ABFD39,
//  0x07685850,
//  0xA2C6750E,
//  0x2122012C,
//  0xDAAE02DC,
//  0x798E10BB,
//  0x6EF2471A,
//  0xC06A3880,
//  0x881CEAE4
//};
//
////#define FACT_ROMSET_0 "BEN"
////unsigned long int ROMSET_CRC[32] = {   
////  0x3BFEF56B,
////  0xD158EEBA,
////  0x1EEB88F5,
////  0x5AE57A8C,
////  0xA7344D1F,
////  0xFC5A7F08,
////  0x07685850,
////  0x0F870806,
////  0x193F3855,
////  0xA2C6750E,
////  0xD0BC4EE6,
////  0x4A3E2DC8,
////  0x39E31BF0,
////  0xFEE664F3,
////  0x3B9D30C4,
////  0x0C2E4811,
////  0xEB61888F,
////  0xA69C2C93,
////  0x6CB1DE16,
////  0xC06A3880,
////  0x5216771A,
////  0x0F46CF66,
////  0xEF9E9C3B,
////  0x67069924,
////  0x4EDA4917,
////  0x3E5F71F3,
////  0x11FF50AD,
////  0x825976A9,
////  0x9451BE1E,
////  0x1C750349,
////  0x0B2DEB61,
////  0xD3B09FEC
////};
//
//#define FACT_ROMSET_0 "QUICKIE"
//unsigned long int ROMSET_CRC[32] = {   
//  0x313547EB,
//  0x202F2749,
//  0x4A3E2DC8,
//  0x67069924,
//  0x9585D511,
//  0x95936B07,
//  0x11FF50AD,
//  0x825976A9,
//  0x9451BE1E,
//  0x2C9D1715,
//  0x1C750349,
//  0x2B1E9E19,
//  0x71AE8533,
//  0x4663C4B6,
//  0x5AE57A8C,
//  0xFC5A7F08,
//  0xFB83171E,
//  0xA57E1724,
//  0x17BE749B,
//  0xFD179F6D,
//  0x0F870806,
//  0xAFC093FD,
//  0xF4C2075E,
//  0x9BFC3E01,
//  0xDC30AD3D,
//  0x3BFEF56B,
//  0x54736B74,
//  0xD0BC4EE6,
//  0x39E31BF0,
//  0x5216771A,
//  0x874F36A4,
//  0x0CA8C961
//};
////#define FACT_ROMSET_0 "ONLYFJ"
////unsigned long int ROMSET_CRC[32] = {   
////  0xDDBA0ED2,
////  0x4663C4B6,
////  0x764894A1,
////  0xFB83171E,
////  0x82996B1F,
////  0xBE4FF48E,
////  0x14B6CC76,
////  0x6FABCB7E,
////  0x7A006985,
////  0x0CA8C961,
////  0x9884EF36,
////  0x32AAC006,
////  0x1931F5C5,
////  0xD0BC4EE6,
////  0x5C8708AC,
////  0x65E5A779,
////  0x17BE749B,
////  0x4F73B44C,
////  0x4E2CC6D3,
////  0xDEE70B33,
////  0xB2F0F0B4,
////  0xB932D584,
////  0x26B0FF5B,
////  0x569E4249,
////  0x81C20196,
////  0x3C949A57,
////  0xABE9B016,
////  0x25057C11,
////  0x2DA28C17,
////  0x95936B07,
////  0x0A2F0F58,
////  0xB4735E6B
////};
//
////#define FACT_ROMSET_0 "OTHERS"
////unsigned long int ROMSET_CRC[32] = {   
////  0x45EF459C,
////  0x0CA8C961,
////  0xA57E1724,
////  0xD0BC4EE6,
////  0x5F663FFC,
////  0x4A3E2DC8,
////  0xA6909A8B,
////  0xB096654E,
////  0x9C9DDDF9,
////  0xCA23F40C,
////  0x655FDF57,
////  0x07685850,
////  0x88D7CE72,
////  0xFEE664F3,
////  0xA767508B,
////  0xABE9B016,
////  0x72674ADB,
////  0x313547EB,
////  0xDAAE02DC,
////  0x239DF97D,
////  0xD62814A3,
////  0x5216771A,
////  0x3351FEDA,
////  0x202F2749,
////  0x0F46CF66,
////  0xEF9E9C3B,
////  0x7394E82C,
////  0xDF36683F,
////  0x9487C920,
////  0x1B9F2F16,
////  0x4EDA4917,
////  0x9585D511
////};

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

const byte UpPin = 2;     
const byte DnPin = 3;     
const byte EnterPin = 4; 
const byte pinA14 = 5;
const byte pinA15 = 6;
const byte pinA16 = 7;
const byte pinA17 = 8;
const byte pinA18 = 9;
unsigned NUM_ROMS; 
const byte EscPin = 10; 

 void setup(void) {
   Serial.begin(9600);
   u8g2.begin();
   pinMode(UpPin, INPUT_PULLUP);
   pinMode(DnPin, INPUT_PULLUP);
   pinMode(EnterPin, INPUT_PULLUP);
   pinMode(EscPin, INPUT_PULLUP);
   pinMode(pinA14, OUTPUT);
   pinMode(pinA15, OUTPUT);
   pinMode(pinA16, OUTPUT);
   pinMode(pinA17, OUTPUT);
   pinMode(pinA18, OUTPUT);
   delay(1000);
}

int counter = 0;

int statUp, statDn, statEnter, statEsc;
byte key = BUTTON_NOTHING;
unsigned long starttime;
unsigned long ahora;
unsigned long starttime_roll;
byte roll_pos = 0;
char str1[MAX_NAME_LEN+1];
char str2[MAX_NAME_LEN+1];
byte state = WAITING_KEY;
//bool printed = false;
//bool printed1 = false;
//bool printed2 = false;
unsigned int w,dw;
unsigned int wait_roll = 1000;

byte i;

void init_rollname(void) {
    roll_pos = 0;
    starttime_roll = millis();
    wait_roll = 1000;
}

signed int search(unsigned long int CRC){
unsigned int i;
unsigned long int t;
 
  for (i=0; i<NUM_ROMS; i++){
    t = pgm_read_dword(&(CRCList[i]));
    if (t==CRC){
        return i; 
    }
  }
  return -1;
}

void readCustomName(char* s, int n){
unsigned short int i;
  for (i=0;i<MAX_CUSTOM_NAME;i++){
    s[i] = EEPROM.read(CUSTOM_NAME_POS(n)+i);
  }
}

void writeCustomName(char* s, int n){
unsigned short int i;
  for (i=0;i<MAX_CUSTOM_NAME;i++){
    EEPROM.write(CUSTOM_NAME_POS(n)+i, s[i]);
  }  
}

void printCustomName(char* s, int j, byte pos){
byte i, x;
char s2[2];
    sprintf_P(str1, PSTR("%02X?"), j);
    sprintf_P(str2, PSTR("Custom Name "));
    u8g2.clearBuffer();          
    u8g2.setFont(u8g2_font_fur11_tr);
    u8g2.drawStr(1,13,strcat(str2,str1)); 
    x = 1;
    s2[1]='\0';
    for (i=0;(i<MAX_CUSTOM_NAME) || (s[i]=='\0');i++){   
      s2[0] = s[i];
      u8g2.setDrawColor(1);
      if (i==pos){
        u8g2.drawBox(x,30,u8g2.getStrWidth(s2)+1,2);
        u8g2.setDrawColor(1);
      }
      u8g2.drawStr(x,30,s2);  
      x+= u8g2.getStrWidth(s2);
    }
   u8g2.sendBuffer();         // transfer internal memory to the display
}
void ModifyCustomName(int i){
char s[MAX_CUSTOM_NAME+1];
int k;
bool fin;
byte len, pos;
//  shiftOut(10, 11, LSBFIRST, 1);
  wait_no_key();
  pos = 0;
  fin = false;
  readCustomName(s, i);
  s[MAX_CUSTOM_NAME]='\0';
  len = strlen(s);
  if (len == 0){
    len++;
  }
  while (not fin) {
    s[len] = '\0';
    if (s[pos]<32) s[pos]=' ';
    k = ReadButtons();
    switch (k) {
      case BUTTON_UP:
        if (s[pos]<255)
          s[pos]++;
        break;
      case BUTTON_DOWN:
        if (s[pos]>32)
          s[pos]--;
        break;
      case BUTTON_ENTER:
        if (pos < MAX_CUSTOM_NAME) 
          pos++;
        break;
      case BUTTON_CONFIG:
        fin = true;
        writeCustomName(s, i);
        break;
      case BUTTON_ESCAPE:
        fin = true;
        break;
    }
    printCustomName(s, i, pos);
  }
  wait_no_key();
}

void printROM_FromList(int i, int ROMNum) {

    sprintf_P(str1, PSTR("%02X?"), ROMNum);
    sprintf_P(str2, PSTR("Name of ROM "));
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_fur11_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
//    strcat(str2, "?");
    u8g2.drawStr(1,13,strcat(str2,str1)); // write something to the internal memory
    if (i < NUM_ROMS){
      if (i>=0) {
        strcpy_P(str1,(char*)pgm_read_word(&(ROMNameList[i])));
        memcpy( str2, &str1[roll_pos], MAX_NAME_LEN-1);
        str2[MAX_NAME_LEN-1]='\0';
      } else
        str2[0]='\0'; //????
    } else {
      sprintf_P(str1, PSTR("%02X"), i);
      strcpy(str2, "CUSTOM ");
      strcat(str2, str1);
      u8g2.drawLine(0,31,128,31); 
      readCustomName(str1, i-NUM_ROMS);
      str1[MAX_CUSTOM_NAME]='\0';
      if (str1[0] != '\0')
        strcpy(str2, str1);
    }
    if (millis()-starttime_roll > wait_roll) {
      w = u8g2.getStrWidth(str2);
      dw = u8g2.getWidth();
      if (w > dw) {
        roll_pos++;
        starttime_roll = millis();
        wait_roll = 200;
      } else {
          init_rollname();
      }
   }
   
   u8g2.drawStr(1,29,str2); // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
}



void printROM_FromSet(int i, int selected) {

  signed int k;

    sprintf_P(str1, PSTR("%02X"), i);
    sprintf(str2, " "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(i));
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_fur11_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(1,13,strcat(str1,str2)); // write something to the internal memory
    if (i==selected)
      u8g2.drawFrame(0,0,128,32);
    k = search(ROMSET_CRC[i]);
    if (ROMSET_CRC[i]<32){
      readCustomName(str1, ROMSET_CRC[i]);
      str1[MAX_CUSTOM_NAME]='\0';
      if (str1[0] != '\0')
        strcpy(str2, str1);
    } else {
      if (k>=0) {
        strcpy_P(str1,(char*)pgm_read_word(&(ROMNameList[k])));
        memcpy( str2, &str1[roll_pos], MAX_NAME_LEN-1);
        str2[MAX_NAME_LEN-1]='\0';
      } else
        str2[0]='\0';
    }
    if (millis()-starttime_roll > wait_roll) {
      w = u8g2.getStrWidth(str2);
      dw = u8g2.getWidth();
      if (w > dw) {
        roll_pos++;
        starttime_roll = millis();
        wait_roll = 200;
      } else {
          init_rollname();
      }
   }
   
   u8g2.drawStr(1,29,str2); // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
}

int check_buttons(void){
  statUp = digitalRead(UpPin);
  statDn = digitalRead(DnPin);
  statEnter = digitalRead(EnterPin);
  statEsc = digitalRead(EscPin);
  if (statUp==0 && statDn==0 && statEnter==0)
    key = BUTTON_FACTORY_SETTINGS;
  else if ((statUp==0 && statDn==0) || (statEsc==0)){
    key = BUTTON_ESCAPE;
    starttime = millis();
  } else if (statUp == 0){
    starttime = millis();
    key = BUTTON_UP;
  } else if (statDn == 0) {
    starttime = millis();
    key = BUTTON_DOWN;
  } else if (statEnter == 0){
    key = BUTTON_ENTER;
  } else key = BUTTON_NOTHING;
  delay(1);
  return key;
}

void pause(unsigned long ms){
  starttime = millis();
  while ((millis()-starttime < ms) && (digitalRead(EnterPin)==1)) { }
}

void wait_no_key() {
  while (check_buttons() != BUTTON_NOTHING) {
  }
}

byte ReadButtons(void){
  byte key;
    key = 0;
    switch (state) {
    case WAITING_KEY:
        key = check_buttons();
        if (key == BUTTON_ESCAPE)
          key = BUTTON_ESCAPE;
        else if (key == BUTTON_ENTER) {
            starttime = millis();
            state = CHECKING_BUTTON_CONFIG;
            key = BUTTON_NOTHING;
         } else if (key != BUTTON_NOTHING) {
            state = WAITING_REPEAT;
       }
        break;
    case WAITING_REPEAT:
        key = BUTTON_NOTHING;
        ahora = millis()-starttime;
        if (ahora > 300) {
          state = REPEATING_KEY;
        }
        break;
    case REPEATING_KEY:
      ahora = millis()-starttime;
      if (ahora > 100) {
        key = check_buttons();
        if (key == BUTTON_NOTHING) {
            state = WAITING_KEY;
        }
      }
      break;
    case CHECKING_BUTTON_CONFIG:
      key = check_buttons();
      if (key == BUTTON_ENTER){
          ahora = millis()-starttime;
          if (ahora > 1000)  {
            key = BUTTON_CONFIG;
            state = WAITING_KEY;
          } else key = BUTTON_NOTHING;
      } else { 
        key = BUTTON_ENTER;
        state = WAITING_KEY;
      }
      break;
  }
  return key;
}

int getROM(int ROMNum){
int k;
static int counter = 0;
  printROM_FromList(counter, ROMNum);
  wait_no_key();
  k = -2;
  do {
      printROM_FromList(counter, ROMNum);
      key = ReadButtons();
      switch (key) {
        case BUTTON_UP:
          if (counter <  NUM_ROMS+31){
            init_rollname();
            counter++;
          } else counter = 0;
          break;
        case BUTTON_DOWN:
          if (counter > 0x00){
            init_rollname();
            counter--;
          } else counter = NUM_ROMS+31;
          break;
        case BUTTON_ESCAPE:
          k = -1;
          break;
        case BUTTON_ENTER:
           k = counter;
          break;
        case BUTTON_CONFIG:
           ModifyCustomName(counter-NUM_ROMS);
           key = BUTTON_NOTHING;
           break;
      }
  } while(k==-2);
  wait_no_key();
  return k;
}

void readROMSetName(char* s, int num){
byte i;
  for (i=0;i<MAX_ROMSET_NAME;i++){
    s[i] = EEPROM.read(ROMSET_NAME_POS(num)+i);
  }
}

void writeROMSetName(char* s, int num){
byte i;
  s[8]='\0';
  for (i=0;i<MAX_ROMSET_NAME;i++){
    EEPROM.write(ROMSET_NAME_POS(num)+i, s[i]);
  }
}

void printROMSetName(int x, int y, int num){
byte i;
char s[MAX_ROMSET_NAME+1];
    readROMSetName(s, num);
    s[MAX_ROMSET_NAME]='\0';
    u8g2.drawStr(x,y,s);  
}

void printROMSetScr(byte num, int pos, char* name){
char S[2];
byte i, x;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_fur11_tr);  
    u8g2.setDrawColor(1);
    u8g2.drawBox(0,0,128,14);
    u8g2.setDrawColor(0);
    u8g2.drawStr(1,13,"SELECT ROMSET"); 
    u8g2.setDrawColor(1);  
    for (i=0; i<4;i++){
      if (i == num){
        u8g2.setDrawColor(1);
        u8g2.drawBox(i*12,16,13,15);
        u8g2.setDrawColor(0);
      } else
        u8g2.setDrawColor(1);
      sprintf(S, "%d", i);
      u8g2.drawStr(1+i*12,30,S); 
    }
    u8g2.setDrawColor(1);
    if (name==0)
      printROMSetName(51,30,num);
    else {
      x = 51;
      for (i=0;i<MAX_ROMSET_NAME;i++){
        S[0]=name[i];
        u8g2.drawStr(x,30,S); 
        if (i==pos){
          u8g2.drawBox(x,30,u8g2.getStrWidth(S)+1,2);
        }
        x+=u8g2.getStrWidth(S);
      }
    }
      
    u8g2.sendBuffer();         
}

void modifyROMSetName(int i){
char s[MAX_ROMSET_NAME+1];
int k;
bool fin;
byte len, pos;
  wait_no_key();
  pos = 0;
  fin = false;
  readROMSetName(s, i);
  s[MAX_ROMSET_NAME]='\0';
  len = strlen(s);
  if (len == 0){
    len++;
  }
  while (not fin) {
    s[len] = '\0';
    if (s[pos]<' ') s[pos]=' ';
    k = ReadButtons();
    switch (k) {
      case BUTTON_UP:
        if (s[pos]<255)
          s[pos]++;
        break;
      case BUTTON_DOWN:
        if (s[pos]>' ')
          s[pos]--;
        break;
      case BUTTON_ENTER:
        if (pos < MAX_ROMSET_NAME-1) //--
          pos++;
        break;
      case BUTTON_CONFIG:
        fin = true;
        writeROMSetName(s, i);
        break;
      case BUTTON_ESCAPE:
        if (pos > 0) pos--;
        break;
    }
    printROMSetScr(i, pos, s);         
  }
  wait_no_key();
}

int selectROMSet(void){
byte k;
byte num=0;
  if (selected > 3)
    selected = 0;
  num = selected;
  do {
    k = ReadButtons();
    switch (k){
      case BUTTON_UP:
        if (num < 3) num++;
        break;
      case BUTTON_DOWN:
        if (num > 0) num--;
        break;
      case BUTTON_ESCAPE:
        return -1;
    }
    printROMSetScr(num, -1, 0);          
  } while (k != BUTTON_ENTER);  
  return num;
}

void do_saveROMSet(int k){
int i;
  for (i=0;i<=31;i++){
    EEPROM.put(ROMSET_POS(k)+i*4,ROMSET_CRC[i]);
  }
}

signed short int SaveROMSet(void){
int k, j;
  k = selectROMSet();

  if (k >= 0) {
    modifyROMSetName(k);
    do_saveROMSet(k);
  }
  return k;
}

void do_loadROMSet(int k){
int i;
  for (i=0;i<=31;i++){
    EEPROM.get(ROMSET_POS(k)+i*4,ROMSET_CRC[i]);
  }
}

signed short int LoadROMSet(void){
signed short int k, j;
unsigned short int i;  
  k = selectROMSet();
  if (k>=0)
    do_loadROMSet(k);
  return k;
}

void storeSetSelected(byte set){
byte j;
  EEPROM.get(1023,j);
  if (set != j)
    EEPROM.put(1023,set);
}

void storeROMSelected(byte set){
byte j;
  EEPROM.get(1022,j);
  if (set != j)
    EEPROM.put(1022,set);
}

byte loadSetSelected(void){
byte j;
  EEPROM.get(1023,j);
  if (j > 3) j = 0;
  return j;
}

byte loadROMSelected(void){
byte j;
  EEPROM.get(1022,j);
  if (j > 31) j = 0;
  return j;
}


#define firmes 0
#define izq1 1
#define izq2 2
#define der1 3
#define der2 4

#define SCR_MAXX 95
#define SCR_MAXY 31
#define MAX_X SCR_MAXX-8
#define MAX_Y 200-8
#define paso 1
#define PRESET_TIMER1 2000

#define PARADO    0
#define ARRIBA    1
#define ABAJO     2
#define DERECHA   3
#define IZQUIERDA 4

bool fin = false;
byte scrx = 0;
byte scry = 37;
signed char hx = 47;
byte hy = 46;
byte h_dir = 0;
signed char fx[4] = {47,47,47,47};
signed char fy[4] = {37,37,37,37};
unsigned long int timer1=0;
byte direccion = PARADO;
byte direccion_fantasma[4] = {PARADO,PARADO,PARADO,PARADO};
bool moviendo_fantasma[4] = {false,false,false,false};
int puntuacion = 0;
byte cocos_counter = 0;
byte vidas = 3;

byte maze[][3] = {
  {0b11010111, 0b01110111,0b01010110},
  {0b10010100, 0b10001100,0b01010010},
  {0b10010110, 0b01000011,0b00010110},
  {0b11010000, 0b11000100,0b11010010},
  {0b01010001, 0b00101001,0b00010100},
  {0b11011001, 0b10010011,0b00010110},
  {0b10010010, 0b01010100,0b10010010},
  {0b01010101, 0b01010101,0b01010100}
};

byte cocos[][2] = {
  {0b11111111, 0b11100000},
  {0b11111111, 0b11100000},
  {0b11111111, 0b11100000},
  {0b11111111, 0b11100000},
  {0b00100000, 0b10000000},
  {0b11110001, 0b11100000},
  {0b11111111, 0b11100000},
};

bool come_coco(byte px, byte py){
  byte i, n,k,x,y;
  x=(px+6)/9;
  y=(py+6)/9;
  i = x / 8;
  n = cocos[y][i];
  k = ~(1 << (7-(x % 8)));
//  Serial.println(x);
//  Serial.println(y);
//  Serial.println(i);
//  Serial.println(n);
//  Serial.println(k);
  cocos[y][i] = cocos[y][i] & k;
  return n != cocos[y][i];
}

bool hay_coco(byte x, byte y){
  byte i, n;
  i = x / 8;
  n = cocos[y][i];
//  Serial.println(x);
//  Serial.println(y);
//  Serial.println(i);
//  Serial.println(n);
//  Serial.println((8-(x % 8)+1));
//  return true;
  return (n >> (7-(x % 8))) & 1;
}

void display_fantasma(signed char x, signed char y){
  u8g2.drawXBMP(x-scrx, y-scry, 8, 8, fantasma);
}
void display_hombre(byte hx, byte hy, int h_dir){
  switch (h_dir){
    case firmes:
      u8g2.drawXBMP(hx, hy, 8, 8, Hombre_8);
      break;
    case der1:
      u8g2.drawXBMP(hx, hy, 8, 8, Hombre_der1_8);
      break;
    case der2:
      u8g2.drawXBMP(hx, hy, 8, 8, Hombre_der2_8);
      break;
    case izq1:
      u8g2.drawXBMP(hx, hy, 8, 8, Hombre_izq1_8);
      break;
    case izq2:
      u8g2.drawXBMP(hx, hy, 8, 8, Hombre_izq2_8);
      break;
  };
}

bool arriba(byte px, byte py){
  byte n,m,d,x,y;
  x = (px+6)/9;
  y = (py+6)/9;
  m = x % 4;
  d = x /4;
  n = maze[y][d] >> 8-(m+1)*2;
//  Serial.println(x);
//  Serial.println(y);
//  Serial.println(px);
//  Serial.println(py);
//  Serial.println(m);
//  Serial.println(d);
//  Serial.println(n);
//  Serial.println("-------");
  return ((n & 0b01) != 0) || ((px % 9) != 1);  
//  return false;  
}

bool izquierda(byte px, byte py){
  byte n,m,d,x,y;
  x = (px+6)/9;
  y = (py+6)/9;
  m = x % 4;
  d = x /4;
  n = maze[y][d] >> 8-(m+1)*2;
//  Serial.println(x);
//  Serial.println(y);
//  Serial.println(px);
//  Serial.println(py);
//  Serial.println(m);
//  Serial.println(d);
//  Serial.println(n);
//  Serial.println("-------");
  
  return ((n & 0b10) != 0) || ((py % 9) != 1);
}
bool derecha(byte x, byte y){
  return izquierda(x+3,y);
}

bool abajo(byte x, byte y){
  return arriba(x,y+2);
}

void draw_maze(void){
  byte i,j,x1,y1,x2,y2,n,m,d;
  for (j=0;j<=7;j++){
    for (i=0;i<=11;i++){
        m = i % 4;
        d = i /4;
        n = maze[j][d] >> 8-(m+1)*2;
        if ((n & 0b01) != 0){
          // linea superior
          x1 = (i*9)-scrx; x2 = x1+9;
          y1 = (j*9)-scry; y2 = y1;
          if ((y1>=0) && (y2 <= SCR_MAXY))
            u8g2.drawHLine(x1,y1,9);
        }
        if ((n & 0b10) != 0){
          // linea izquierda
          x1 = (i*9)-scrx; x2 = x1;
          y1 = (j*9)-scry; y2 = y1+9;
          if ((y1>=0) && (y2 <= SCR_MAXY))
            u8g2.drawVLine(x1,y1,9);
        }
    }
  }
  for (j=0;j<=6;j++){
    for (i=0;i<=10;i++) {
      if (hay_coco(i,j)){
        x1=i*9-scrx+1;
        y1=j*9-scry+1;
        y2 = y1+8;
        if ((y1>=0) && (y2 <= SCR_MAXY))
          u8g2.drawXBMP(x1, y1, 8, 8, coco);
      }
    }
  }
  for (i=1; i<=vidas;i++)
    display_hombre(90+i*10,20,firmes);

  sprintf(str1, "%03d", puntuacion);
  u8g2.drawStr(102,12,str1); 
}

void mueve_abajo(void){
  hy+=paso;
  if (hy >= 16) scry+=paso;
  switch (h_dir){
    case der1:
    case firmes: h_dir = der2;
    break;
    case der2: h_dir = der1;
    break;
    case izq1: h_dir = izq2;
    break;
    case izq2: h_dir = izq1;
    break;
  }
}

void mueve_arriba(void){
  hy-=paso;
  if (scry > 0) scry-=paso;
  switch (h_dir){
    case der1:
    case firmes: h_dir = der2;
    break;
    case der2: h_dir = der1;
    break;
    case izq1: h_dir = izq2;
    break;
    case izq2: h_dir = izq1;
    break;
  }
}

void mueve_izquierda(void){
  hx-=paso;
//  if (hx > SCR_MAXX-8) scrx-=paso;
  if (h_dir != izq1)
    h_dir = izq1;
  else
    h_dir = izq2;
}

void mueve_derecha(void){
  hx+=paso;
//  if (hx > SCR_MAXX-8) scrx+=paso;
  if (h_dir != der1)
    h_dir = der1;
  else
    h_dir = der2;
}

void mueve_hombre(void){
  display_hombre(hx-scrx,hy-scry,h_dir);
  
  if ((digitalRead(UpPin)==LOW) && ((hy-paso) >= 0)&& !arriba(hx,hy)) { 
    direccion = ARRIBA;
    mueve_arriba();
    timer1 = millis();
  }
  if ((digitalRead(DnPin)==LOW) && ((hy+paso) <= MAX_Y)&& !abajo(hx,hy)) {
    direccion = ABAJO;
    mueve_abajo();
    timer1 = millis();
  }
  if ((digitalRead(EscPin)==LOW) && !izquierda(hx,hy)) {
      direccion = IZQUIERDA;
      mueve_izquierda();
      timer1 = millis();
  }
  if ((digitalRead(EnterPin)==LOW) && !derecha(hx,hy)) {
      direccion = DERECHA;
      mueve_derecha();
      timer1 = millis();
  }
  switch (direccion){
    case ARRIBA: 
      if (hy % 9 != 1) mueve_arriba();
      else {
        direccion = PARADO;
        if (come_coco(hx,hy)){
          puntuacion++;
          cocos_counter++;
        }
      }
      break;
    case ABAJO: 
      if (hy % 9 != 1) mueve_abajo();
      else {
        direccion = PARADO;
        if (come_coco(hx,hy)){
          puntuacion++;
          cocos_counter++;
        }
      }
      break;
    case DERECHA: 
      if (hx % 9 != 1) mueve_derecha();
      else {
        direccion = PARADO;
        if (come_coco(hx,hy)){
          puntuacion++;
          cocos_counter++;
        }
        if (hx > MAX_X+6){
          hx = 1;
        }
      }
      break;
    case IZQUIERDA: 
      if ((hx % 9 != 1) && (hx >=0)) mueve_izquierda();
      else {
        direccion = PARADO;
        if (come_coco(hx,hy)){
          puntuacion++;
          cocos_counter++;
        }
        if (hx < 0){
          hx = MAX_X-1;
        }
      }
      break;
  }
  if (millis()-timer1 >= PRESET_TIMER1) h_dir = firmes;
  delay(1);
}

void nueva_direccion(byte j){
  byte prob[5];
  byte i;
  int s, total, r;
  prob[IZQUIERDA] = !izquierda(fx[j], fy[j])*10;
  prob[DERECHA] = !derecha(fx[j], fy[j])*10;
  prob[ARRIBA] = !arriba(fx[j], fy[j])*10;
  prob[ABAJO] = !abajo(fx[j], fy[j])*10;
  switch (direccion_fantasma[j]){
    case IZQUIERDA: 
      prob[DERECHA]/=10;
      break;
    case DERECHA: 
      prob[IZQUIERDA]/=10;
      break;
    case ARRIBA: 
      prob[ABAJO]/=10;
      break;
    case ABAJO: 
      prob[ARRIBA]/=10;
      break;
  }
  if (hx > fx[j]) prob[DERECHA]*=3;
  if (hx < fx[j]) prob[IZQUIERDA]*=3;
  if (hy < fy[j]) prob[ABAJO]*=3;
  if (hy > fy[j]) prob[ARRIBA]*=3;
  total = prob[1]+prob[2]+prob[3]+prob[4];
  r = rand() % total;
  s = 0;
//  Serial.println(hx);
//  Serial.println(hy);
//  Serial.println(fx[i]);
//  Serial.println(fy[i]);
//  Serial.println(izquierda(fx[i],fy[i]));
//  Serial.println(derecha(fx[i],fy[i]));
//  Serial.println(arriba(fx[i],fy[i]));
//  Serial.println(abajo(fx[i],fy[i]));
//  Serial.println(prob[1]);
//  Serial.println(prob[2]);
//  Serial.println(prob[3]);
//  Serial.println(prob[4]);
//  Serial.println(r);
  for (i=1;i<=4;i++){
    s = s + prob[i];
//    Serial.println(s);
    if (r+1 <= s){
      direccion_fantasma[j] = i;
      break;
    }
  }
//  Serial.println("------");
//  delay(3000);
  
}

void mueve_fantasma(byte i){
  display_fantasma(fx[i], fy[i]);
  if (!moviendo_fantasma[i]) {
    nueva_direccion(i);
    moviendo_fantasma[i] = true;
  }
  switch (direccion_fantasma[i]) {
    case PARADO:
       direccion_fantasma[i] = ARRIBA; 
       break;
    case IZQUIERDA:   
       fx[i]-=paso;
       if ((fx[i] % 9) == 1) 
        moviendo_fantasma[i] = false;
        if (fx[i] < 0){
          fx[i] = MAX_X-1;
        }
       break;
    case DERECHA:   
       fx[i]+=paso;
       if ((fx[i] % 9) == 1) 
        moviendo_fantasma[i] = false;
        if (fx[i] > MAX_X+6){
          fx[i] = 1;
        }
        break;
    case ARRIBA:   
       fy[i]-=paso;
       if ((fy[i] % 9) == 1) 
        moviendo_fantasma[i] = false;
       break;
    case ABAJO:   
       fy[i]+=paso;
       if ((fy[i] % 9) == 1) 
        moviendo_fantasma[i] = false;
       break;
  }
}

void init_sprites(void){
  scrx = 0;
  scry = 37;
  hx = 47;
  hy = 46;
  h_dir = 0;
  for (i=0;i<=3;i++){
    fx[i] = 47;
    fy[i] = 37;
    direccion_fantasma[i] = PARADO;
    moviendo_fantasma[i] = false;
  }
  timer1=0;
  direccion = PARADO;
}

void init_maze(void){
  cocos_counter = 0;
  cocos[0][0]=0b11111111; cocos[0][1]=0b11100000;
  cocos[1][0]=0b11111111; cocos[1][1]=0b11100000;
  cocos[2][0]=0b11111111; cocos[2][1]=0b11100000;
  cocos[3][0]=0b11111111; cocos[3][1]=0b11100000;
  cocos[4][0]=0b00100000; cocos[4][1]=0b10000000;
  cocos[5][0]=0b11110001; cocos[5][1]=0b11100000;
  cocos[6][0]=0b11111111; cocos[6][1]=0b11100000;
  init_sprites();
}

void game(void){

  vidas = 3;
  puntuacion = 0;
  fin = false;
  u8g2.setFont(u8g2_font_fur11_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  init_maze();
  while (not fin){
    if (cocos_counter==65) {
      init_maze();
    }
    u8g2.clearBuffer();          // clear the internal memory
    draw_maze();
    for (i=0;i<=3;i++){
      mueve_fantasma(i);
      if (((hx+6)/9 == (fx[i]+6)/9) && ((hy+6)/9 == (fy[i]+6)/9)) { // pillado
        wait_no_key();
        delay(3000);
        init_sprites();
        if (vidas>0) 
          vidas--;
        else
          fin = true;
      }
    }
    mueve_hombre();
    u8g2.sendBuffer();         // transfer internal memory to the display
  }
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.drawStr(20,22,"GAME OVER"); 
  u8g2.sendBuffer();         // transfer internal memory to the display
  delay(5000);
}

void do_menu(void){
signed short int option = 0;
int s;
byte k;
    wait_no_key();
    while (true){
      k = ReadButtons();
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_fur11_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
      u8g2.setDrawColor(1);
      u8g2.drawBox(0,0,40,14);
      u8g2.setDrawColor(0);
      u8g2.drawStr(1,13,"Menu"); 
//      u8g2.drawStr(84,13,"Exit"); 
      u8g2.setDrawColor(1);
      u8g2.drawStr(1,29,"Save  Load Game"); 
      switch (k){
        case BUTTON_UP:
          option++;
          if (option > 2) option = 0;
          break;
        case BUTTON_DOWN:
          option--;
          if (option < 0) option = 2;
          break;
        case BUTTON_ENTER:
          if (option == 0) {
            s = SaveROMSet();
            if (s >= 0){
              selected = s;
              storeSetSelected(selected);
            }
          }
          else if (option == 1) {
            s = LoadROMSet();
            if (s >= 0) {
              selected = s;
              storeSetSelected(selected);
            }
          }
          else if (option == 2) 
            game();
          break;
        case BUTTON_ESCAPE:
          goto exit_label;
          break;
      }
      switch (option){
        case 0: 
          u8g2.drawFrame(0,16,42,16);
          break;
        case 1:
          u8g2.drawFrame(42,16,40,16);
          break;
        case 2:
          u8g2.drawFrame(84,16,44,16);
          break;
      }
       u8g2.sendBuffer();         // transfer internal memory to the display
   }
exit_label:
    wait_no_key();
}

void activeROMpins(byte selected){
    digitalWrite(pinA14, (selected & 0b00000001) !=0?HIGH:LOW);
    digitalWrite(pinA15, (selected & 0b00000010) !=0?HIGH:LOW);
    digitalWrite(pinA16, (selected & 0b00000100) !=0?HIGH:LOW);
    digitalWrite(pinA17, (selected & 0b00001000) !=0?HIGH:LOW);
    digitalWrite(pinA18, (selected & 0b00010000) !=0?HIGH:LOW);
}

void SelectROM(void){
  int k;
  while(true){
      activeROMpins(ROMselected);
      printROM_FromSet(counter, ROMselected);
      key = ReadButtons();
      switch (key) {
        case BUTTON_UP:
          if (counter < 0x1F){
            init_rollname();
            counter++;
          }
          break;
        case BUTTON_DOWN:
          if (counter > 0x00){
            init_rollname();
            counter--;
          }
          break;
        case BUTTON_ENTER:
            ROMselected = counter;
            storeROMSelected(ROMselected);
          break;
        case BUTTON_CONFIG:
          k = getROM(counter);
          printROM_FromSet(counter, ROMselected);
          wait_no_key();
          if (k >= 0) {
            if (k < NUM_ROMS)
              ROMSET_CRC[counter] = pgm_read_dword(&(CRCList[k]));
            else
              ROMSET_CRC[counter] = k-NUM_ROMS;
          }
          break;
        case BUTTON_ESCAPE:
//            Serial.println("MENU");
            do_menu();
          break;
      }
      key = BUTTON_NOTHING;
  }
}

void printStartScr(byte i){

    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_fur11_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawXBMP(0, 0, 16, 16, Hombre1_16x16);
//    u8g2.drawXBMP(22, 0, 16, 16, Hombre_der1_16x16);
//    u8g2.drawXBMP(45, 0, 16, 16, Hombre_der2_16x16);
//    u8g2.drawXBMP(68, 0, 16, 16, Hombre_izq1_16x16);
//    u8g2.drawXBMP(90, 0, 16, 16, Hombre_izq2_16x16);
    strcpy_P(str2, PSTR("version 1.1"));
    u8g2.drawStr(25,15,str2);
    u8g2.drawXBMP(112, 0, 16, 16, Hombre1_16x16);
    if ((i % 2) == 0)
      u8g2.drawXBMP(i,16, 16, 16, Hombre_der1_16x16);
    else
      u8g2.drawXBMP(i,16, 16, 16, Hombre_der2_16x16);
    strcpy_P(str2, PSTR("2018-wilco2009"));
    w = u8g2.getStrWidth(str2);
    if ((i+w > u8g2.getWidth()) && (strlen(str2)>0))
      str2[strlen(str2)-1] = '\0';
    
    u8g2.drawStr(i+15,32,str2);
    u8g2.sendBuffer();         // transfer internal memory to the display
}

void copyROMSet(int k){
byte i;
  for (i=0; i<=31; i++){
    if (k==1)
      ROMSET_CRC[i] = pgm_read_dword(&(ROMSET_CRC_1[i]));
    else if (k==2)
      ROMSET_CRC[i] = pgm_read_dword(&(ROMSET_CRC_2[i]));
    else if (k==3)
      ROMSET_CRC[i] = pgm_read_dword(&(ROMSET_CRC_3[i]));
  }
}

void init_selections(void){
  char s[] = "             ";
   if ((digitalRead(EscPin)==LOW)&&(digitalRead(EnterPin)==LOW)){
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_fur11_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    strcpy_P(str2, PSTR("Restoring"));
    u8g2.drawStr(0,16,str2);
    strcpy_P(str2, PSTR("Fact. settings"));
    u8g2.drawStr(0,32,str2);
    u8g2.sendBuffer();         // transfer internal memory to the display
    selected = 0;
    ROMselected = 0;
    
    storeSetSelected(selected);
    storeROMSelected(ROMselected);

    // clearing custom names
    for (i=0;i<=31;i++)
      writeCustomName(s, i);  

    strcpy_P(str2, PSTR(FACT_ROMSET_0));  
    writeROMSetName(str2, 0);
    do_saveROMSet(0);

    copyROMSet(1);
    strcpy_P(str2, PSTR(FACT_ROMSET_1));  
    writeROMSetName(str2, 1);
    do_saveROMSet(1);

    copyROMSet(2);
    strcpy_P(str2, PSTR(FACT_ROMSET_2));  
    writeROMSetName(str2, 2);
    do_saveROMSet(2);

    copyROMSet(3);
    strcpy_P(str2, PSTR(FACT_ROMSET_3));  
    writeROMSetName(str2, 3);
    do_saveROMSet(3);

    delay(3000);
  } else {
    selected = loadSetSelected();
    ROMselected = loadROMSelected();
  }
  do_loadROMSet(selected);
  
}

void loop(void) {

  NUM_ROMS = sizeof(CRCList) / 4;

  u8g2.clearBuffer();          // clear the internal memory
  u8g2.drawXBMP(0, 0, 128, 32, videopacdisplay);
  u8g2.sendBuffer();         // transfer internal memory to the display
  delay(1000);
  pause(2000);
  init_selections();
  
  printStartScr(0);
  pause(1000);

  for (i=0; i<120; i+=3){
    printStartScr(i);
    if (digitalRead(EnterPin)==0) break;
    delay(1);
  }
  delay(1000);

  while (true) {
    SelectROM();
  }
}
