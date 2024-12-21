/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-rfid-mp3-player
 */

#include <SPI.h>
#include <MFRC522.h>


#include <YX5300_ESP32.h>

// *make sure the RX on the YX5300 goes to the TX on the ESP32, and vice-versa
#define RX 16
#define TX 17

YX5300_ESP32 mp3; // the mp3 object

#define SS_PIN    5  // ESP32 pin GPIO5 connected to the SS of the RFID reader
#define RST_PIN   27 // ESP32 pin GPIO27 connected to the RST of the RFID reader

#define SONG_NUM 12  // 3 songs + 3 RFID cards, change it as your need

MFRC522 rfid(SS_PIN, RST_PIN);

byte RFID_UIDs[SONG_NUM][4] = {
  { 0xF9, 0xF5, 0x55, 0x14 },  // song 1
  { 0xB1, 0xDF, 0x27, 0x1D },  // song 2
  { 0x37, 0x23, 0x27, 0x7B },  // song 3
  { 0xb8, 0x92, 0x1c, 0x33 },  // song 4
  { 0x07, 0x4b, 0x3a, 0x7b },  // song 5
  { 0xb7, 0x90, 0x2a, 0x7b },  // song 6
  { 0xf7, 0x3c, 0x28, 0x7b },  // song 7
  { 0xf7, 0x08, 0x2a, 0x7b },  // song 8
  { 0xa1, 0x8a, 0xec, 0x1d },  // song 9
  { 0x27, 0xa6, 0x91, 0x75 },  // song 10
  { 0xdf, 0x80, 0x54, 0x9e },  // song 11
  { 0xd3, 0x70, 0x1e, 0x19 }  // song 12

                               // ADD MORE IF NEEDED
};


void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(500);  // wait chip initialization is complete
  mp3 = YX5300_ESP32(Serial2, RX, TX);

  delay(200);                        // wait for 200ms

  SPI.begin();      // init SPI bus
  rfid.PCD_Init();  // init MFRC522

  Serial.println("Tap RFID Tag on reader");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {  // new tag is available
    if (rfid.PICC_ReadCardSerial()) {  // NUID has been readed
      Serial.print("Tag UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      for (int index = 0; index < SONG_NUM; index++) {
        if (rfid.uid.uidByte[0] == RFID_UIDs[index][0] && rfid.uid.uidByte[1] == RFID_UIDs[index][1] && rfid.uid.uidByte[2] == RFID_UIDs[index][2] && rfid.uid.uidByte[3] == RFID_UIDs[index][3]) {
          Serial.print("Playing song ");
          Serial.println(index);
          mp3.playTrack(index+1);
          
          // mp3_command(CMD_PLAY_W_INDEX, index);  // Play mp3
        }
      }

      rfid.PICC_HaltA();       // halt PICC
      rfid.PCD_StopCrypto1();  // stop encryption on PCD
    }
  }
}



