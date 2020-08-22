// rf22_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_RF22 class. RH_RF22 class does not provide for addressing or
// reliability, so you should only use RH_RF22  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf22_client
// Tested on Duemilanove, Uno with Sparkfun RFM22 wireless shield
// Tested on Flymaple with sparkfun RFM22 wireless shield
// Tested on ChiKit Uno32 with sparkfun RFM22 wireless shield
// https://www.airspayce.com/mikem/arduino/RadioHead/rf22_server_8pde-example.html
#include <SPI.h>
#include <RH_RF22.h>
// Singleton instance of the radio driver
RH_RF22 rf22;

void InitRF()
{
  if (!rf22.init())
  {
    Serial.println("init failed");  
  }
  else
  {
      Serial.println("init successful");
      // https://www.sparkfun.com/datasheets/Wireless/General/RFM22B.pdf
      // Min frequency in 433Mhz band is 413. We use the minimum frequency to minimize path loss
      if(!rf22.setFrequency(915))
      {
        Serial.println("failed to set frequency!");
      }
      //rf22.setTxPower(RH_RF22_TXPOW_20DBM); // default is RH_RF22::RH_RF22_TXPOW_8DBM from RH_RF22.h
  }
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("beginning setup");
  InitRF();
}
void loop()
{
  if (rf22.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF22_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf22.recv(buf, &len))
    {
//      RF22::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf22.lastRssi(), DEC);
      
      // Send a reply
      /*uint8_t data[] = "And hello back to you";
      rf22.send(data, sizeof(data));
        Serial.println("attempting to send a reply");
      rf22.waitPacketSent();
      Serial.println("Sent a reply");*/
    }
    else
    {
      Serial.println("recv failed");
    }
    
    //Serial.println("Resetting rf22");
    //rf22.reset();
    //InitRF();
  }
  else
  {
     // Serial.println("rf22 message not available!");
  }
  delay(500);
}
