#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

const uint8_t PING_MSG = 0x2;
const uint8_t PONG_MSG = 0x3;
const uint8_t PONG_RESP[1] = {PONG_MSG};
const uint8_t RINGRING_MSG = 0x1;
const uint8_t RASPI_ID = 100;
const uint8_t SENDER_ID = 101;
const uint8_t SENDER2_ID = 102;
const uint8_t BELL_ID = 103;

RH_ASK driver(100, 4, 3); // 200bps, TX on D3 (pin 2), RX on D4 (pin 3)

void setup()
{
  // pinMode(13,1);
  Serial.begin(9600); // Debugging only

  if (!driver.init())
    Serial.println("init failed");
  driver.setThisAddress(15);
  Serial.println("ready");
}

void loop()
{
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    if (1 != int(buflen)) {
    Serial.println("invalid msg length");
    }
     uint8_t msg = buf[0];
    
    if (PING_MSG == msg)
    {
      Serial.println("PING received");
      delay(500);
      Serial.println("send pong");
      
      
      driver.send((uint8_t *)PONG_RESP, 1);
      driver.waitPacketSent();
      return;
    }
    Serial.println("unknown message:"+String(msg));
  }
}
