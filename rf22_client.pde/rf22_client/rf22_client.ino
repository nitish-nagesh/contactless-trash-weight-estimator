// rf22_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_RF22 class. RH_RF22 class does not provide for addressing or
// reliability, so you should only use RH_RF22 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf22_server
// Tested on Duemilanove, Uno with Sparkfun RFM22 wireless shield
// Tested on Flymaple with sparkfun RFM22 wireless shield
// Tested on ChiKit Uno32 with sparkfun RFM22 wireless shield
// https://www.airspayce.com/mikem/arduino/RadioHead/rf22_client_8pde-example.html
#include <SPI.h>
#include <RH_RF22.h>
// Singleton instance of the radio driver
RH_RF22 rf22;

/* Power levels available
 * // For RFM22B:
#define RH_RF22_TXPOW_1DBM                         0x00
#define RH_RF22_TXPOW_2DBM                         0x01
#define RH_RF22_TXPOW_5DBM                         0x02
#define RH_RF22_TXPOW_8DBM                         0x03
#define RH_RF22_TXPOW_11DBM                        0x04
#define RH_RF22_TXPOW_14DBM                        0x05 
#define RH_RF22_TXPOW_17DBM                        0x06 
#define RH_RF22_TXPOW_20DBM                        0x07 
 */
 /* Actual transmit power
  * Program power           Measured Power
   dBm                         dBm
   1                           -5.6
   2                           -3.8
   5                           -2.2
   8                           -0.6
   11                           1.2
   14                           11.6
   17                           14.4
   20                           18.0
  */
static const float MAX_PULL_IN_RANGE = 0.159375; //RH_RF22.h setFrequency

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
      // We have a quarter wavelength antenna, at 413Mhz the wavelength = speed of light / frequency, 72 centimeters
      if(!rf22.setFrequency(915))
      {
        Serial.println("failed to set frequency!");
      }
      rf22.setTxPower(RH_RF22_TXPOW_20DBM); // default is RH_RF22::RH_RF22_TXPOW_8DBM from RH_RF22.h
  }
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("Setting up");
  InitRF();
}
void loop()
{
  Serial.println("Sending to rf22_server");
  // Send a message to rf22_server
  uint8_t data[] = "Hello World!";
  rf22.send(data, sizeof(data));
  //rf22.sleep();

  //rf22.waitPacketSent(); // unreliable
  // Now wait for a reply
  /*uint8_t buf[RH_RF22_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf22.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf22.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      //RSSI Resolution RESRSSI — ±0.5 — dB
      //https://www.sparkfun.com/datasheets/Wireless/General/RFM22B.pdf
      Serial.print("RSSI: ");
      Serial.println(rf22.lastRssi(), DEC);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf22_server running?");
    rf22.reset();
    InitRF();
  }*/
  delay(5000);

   rf22.reset();
   InitRF();
}
