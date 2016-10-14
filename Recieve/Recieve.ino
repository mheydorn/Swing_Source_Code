#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


RF24 radio(10,14
);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void)
{    
    pinMode(2, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(7,HIGH);
    digitalWrite(3, HIGH);
    Serial.begin(57600);
    Serial.println("Starting up");
    
    radio.begin();    
    radio.setRetries(15,15);       
    radio.openReadingPipe(1,pipes[1]);    
    radio.startListening();    
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
}
String command = "";
String prevCommand = "";
char c = '~';
int Location2 = 2400;

bool ok;
void loop(void){    
    c = '~';
    
    if ( radio.available() )
    {      
        char got_time = 'p';
      
        bool done = false;
       
        while (!done)
        {
            
            done = radio.read( &got_time, sizeof(char) );
           
        }
        radio.stopListening();
        Serial.print("Revieced a ");
        Serial.println(got_time);
        command.concat(got_time);
      
        c = got_time;         
        ok = c == 'e';
        if(ok){
            Serial.print("Ok and command is ");
            Serial.println(command);
            String tempCommand = "";
            bool hasNewLine = false;
            bool cont = true;
            for(int i = 0; i < command.length(); i++){
                if(cont){
                    if(command.charAt(i) == '\n'){
                        hasNewLine = true;
                    }
                    if(command.charAt(i) != '\n' && command.charAt(i) != 'e'){
                        tempCommand += command.charAt(i);
                    }
                    if(command.charAt(i) == '\n' || command.charAt(i) == 'e')    {
                        if(command.charAt(i) == 'e' && hasNewLine ){
                            cont = false;
                            }else{
                            proccess(tempCommand + 'e');
                            
                            tempCommand = "";
                        }
                    }
                }
            }
            Serial.println("Wiping command");
            command = "";
        }
       
        prevCommand = command;
        radio.startListening();
        
    }    
}
void proccess(String command){
    digitalWrite(2, HIGH);
    Serial.println("Proccessing command " + command);    
    
    if(command == ""){
        return;
    }
    if(command.charAt(0) == 'd'){
        String delayTime = "";
        for(int i = 1; i < command.length(); i++){
            delayTime += command.charAt(i);
            
        }
        delay(delayTime.toInt());
        digitalWrite(2, LOW);
        return;
    }
    
    if(command.charAt(0) == 's'){
        sendSnapShotSignal();
        digitalWrite(2, LOW);
        
        return;
    }
    if(command.charAt(0) == 'a'){
        
        String angle = "";
        for(int i = 2; i < command.length(); i++){
            angle += command.charAt(i);
        }
        if(angle.toInt() > 0){
            digitalWrite(7, HIGH);
        }
        if(angle.toInt() < 0){
            digitalWrite(7, LOW);
        }
        int turns = abs(AngleToSteps(angle.toInt()));
       
        moveMotor(turns);
    }
    if(command.charAt(0) == 'b'){
        String angle = "";
        for(int i = 2; i < command.length(); i++){
            angle += command.charAt(i);
        }
        
        if(command.charAt(1) == 'f'){
            digitalWrite(3, HIGH);
        }
        if(command.charAt(1) == 'r'){
            digitalWrite(3, LOW);
        }
        int Destination = AngleToDestination(angle.toInt());
        //check if positive or negative
        int turns = abs(Destination - Location2);
        if(Destination > Location2){
            
            }else{
            digitalWrite(3, LOW);
        }
        
        moveMotor2(turns);
        Location2 = Destination;
    }
    digitalWrite(2, LOW);
    // delay(1000);
    
}

void moveMotor(int moves){
    for(int i = 0 ; i < moves; i++){
                
        //if we're accelerating
        if(i < moves/2){
            
            if(i < 250*4){
                digitalWrite(8, HIGH);
                
                delayMicroseconds(400 - (i/4));
                digitalWrite(8, LOW);
                
                delayMicroseconds(400- (i/4));
                }else{
                digitalWrite(8, HIGH);
                
                delayMicroseconds(150);
                digitalWrite(8, LOW);
                
                delayMicroseconds(150);
            }
        }
        //if we're decelerating
        if(i >= moves/2){
            //return;
            if((moves - i) > 250*4){
                digitalWrite(8, HIGH);
                
                delayMicroseconds(150);
                digitalWrite(8, LOW);
                
                delayMicroseconds(150);
                
                }else{
                digitalWrite(8, HIGH);
                
                delayMicroseconds(400 + (i - moves)/4);
                digitalWrite(8, LOW);
                
                delayMicroseconds(400 + (i - moves)/4);
                
            }
        }                        
    }        
}

void moveMotor2(int moves){
    
    for(int i = 0 ; i < moves; i++){
        //if we're accelerating
        if(i < moves/2){
            
            if(i < 250*4){
                digitalWrite(4, HIGH);
                
                delayMicroseconds(400 - (i/4));
                digitalWrite(4, LOW);
                
                delayMicroseconds(400- (i/4));
                }else{
                digitalWrite(4, HIGH);
                
                delayMicroseconds(150);
                digitalWrite(4, LOW);
                
                delayMicroseconds(150);
            }
        }
        //if we're decelerating
        if(i >= moves/2){
            //return;
            if((moves - i) > 250*4){
                digitalWrite(4, HIGH);
                
                delayMicroseconds(150);
                digitalWrite(4, LOW);
                
                delayMicroseconds(150);
                
                }else{
                digitalWrite(4, HIGH);
                
                delayMicroseconds(400 + (i - moves)/4);
                digitalWrite(4, LOW);
                
                delayMicroseconds(400 + (i - moves)/4);
                
            }
        }                
    }
}

int AngleToDestination(int angle){
    return (int)((angle + 90)*26.66666666666666666);
    
}
//This function is for the rotation motor (motor 1)
int AngleToSteps(int angle){
    return (int)(71.111111111111111111111111 * angle);
}

void send(char c){
    bool ok = false;
    while(!ok){
        
        delay(8);
        ok = radio.write(&c, sizeof(char));
    }
}
void sendSnapShotSignal(){
    radio.stopListening();
    send('_');
    send('s');
    
    radio.startListening();
}
