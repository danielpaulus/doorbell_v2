#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(2000, 4, 3); // 200bps, TX on D3 (pin 2), RX on D4 (pin 3)

void setup()
{
  //pinMode(13,1);
    Serial.begin(9600);  // Debugging only
   
    if (!driver.init())
         Serial.println("init failed");
         Serial.println("ready");
}

long start=0;
long current = 0;

void loop()
{
  long m = millis();
  if (m - start > 2000) {
    start = m;
    Serial.println("send ping");
    const char *msg1 = "ping";
    driver.send((uint8_t *)msg1, strlen(msg1));
    // driver.waitPacketSent();
   
    }
 return;
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    String x="";
    String y="Turn LED OFF";
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      x=((String)(char*)buf);
       String message  = x.substring(0, int(buflen));

      Serial.println("rcv:"+message);
   
       
          
    }
     
    
}
