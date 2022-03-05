#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

const int PING_MSG = 0x2;
const int PONG_MSG = 0x3;
const int RINGRING_MSG = 0x1;
const int RASPI_ID = 100;
const int SENDER_ID = 101;
const int SENDER2_ID = 102;
const int BELL_ID = 103;

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
    int i;
    // Message with a good checksum received, dump it.
    String x = ((String)(char *)buf);
    String message = x.substring(0, int(buflen));
    String ping = "ping";
    Serial.println("rcv:'" + message + "'");
    if (ping == message)
    {
      delay(500);
      Serial.println("send pong");
      const char *msg1 = "pong";
      driver.send((uint8_t *)msg1, strlen(msg1));
      driver.waitPacketSent();
    }
  }
}
