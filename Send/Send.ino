
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(10,14);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void)
{
    pinMode(9 , OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(5, OUTPUT);
    Serial.begin(57600);
    Serial.println("Starting up");

    radio.begin();
    radio.setRetries(15,15);
    radio.openReadingPipe(1,pipes[1]);
    radio.startListening();
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
}

bool alt = false;
void loop(void)
{
    String content = "";
    char character;
    while(Serial.available()) {
        character = Serial.read();
        content.concat(character);
        String car = "";
        car.concat(character);
        if(((character< '0' || character > 'z') && character != '-')){
        }
    }
    if (content != "") {
        Serial.print("Sending ");
        Serial.println(content);
        Serial.print("Size is ");
        Serial.println(content.length());
        content.concat('e');
        digitalWrite(9, HIGH);
        for(int i = 0; i < content.length(); i++){
            send(content.charAt(i));        
        }   
        digitalWrite(9, LOW);
    }
    //check if we need to take a picture
    if ( radio.available() )
    {
        char got_time = 'p';
        bool done = false;
        while (!done)
        {
            done = radio.read( &got_time, sizeof(char) );
        }
        if(got_time == 's'){
            digitalWrite(5, HIGH);
            delay(50);
            digitalWrite(5, LOW);
        }
    }
}
void signal(){
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(7, LOW);
    delay(500);
}
void signalFast(){
    while(true){
        digitalWrite(7, HIGH);
        delay(100);
        digitalWrite(7, LOW);
        delay(100);
    }
}
void send(char c){
    radio.stopListening();
    bool ok = false;
    while(!ok){
        char  time2 = c;
        delay(10);
        ok = radio.write( &time2, sizeof(char));
    }
    radio.startListening();
}
char listen(){
    char c = 'p';
    if(radio.available()){
        bool done = false;
        while(!done){
            done = radio.read(&c, sizeof(char));
        }
        return c;
    }
    return c;
}
