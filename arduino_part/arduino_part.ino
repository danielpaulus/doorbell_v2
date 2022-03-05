#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(100, 4, 3); // 200bps, TX on D3 (pin 2), RX on D4 (pin 3)
//https://github.com/bitblaster/pigpio/blob/master/EXAMPLES/Python/RADIO_HEAD/rh.py
void setup()
{
  //pinMode(13,1);
    Serial.begin(9600);  // Debugging only
   
    if (!driver.init())
         Serial.println("init failed");
    driver.setThisAddress(15);
    Serial.println("ready");
}

void loop()
{
  
    /*const char *msg1 = "ping";
    driver.send((uint8_t *)msg1, strlen(msg1));
     driver.waitPacketSent();
    delay(1000);*/
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    String x="";
    String y="Turn LED OFF";
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      
      int i;
      // Message with a good checksum received, dump it.
      
      x=((String)(char*)buf);
       String message  = x.substring(0, int(buflen));
String ping = "ping";
      Serial.println("rcv:'"+message+"'");
      if (ping == message){
        delay(500);
        Serial.println("send pong");
        const char *msg1 = "pong";
    driver.send((uint8_t *)msg1, strlen(msg1));
     driver.waitPacketSent();
        }
       
          
    }
    
}
