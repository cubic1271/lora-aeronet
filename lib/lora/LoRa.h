#ifndef LORA_H
#define LORA_H

#include <Arduino.h>
#include <SPI.h>

#define LORA_DEFAULT_SS_PIN     18
#define LORA_DEFAULT_RESET_PIN  14
#define LORA_DEFAULT_DIO0_PIN   26

#define PA_OUTPUT_PA_BOOST_PIN  1
#define PA_OUTPUT_RFO_PIN       0

#define LORA_STATUS_MODEM_CLR   (0x10)
#define LORA_STATUS_HDR_VALID   (0x08)
#define LORA_STATUS_CURR_RX     (0x04)
#define LORA_STATUS_SIG_SYNC    (0x02)
#define LORA_STATUS_SIG_DET     (0x01)

#if defined (__STM32F1__)
inline unsigned char  digitalPinToInterrupt(unsigned char Interrupt_pin) { return Interrupt_pin; } //This isn't included in the stm32duino libs (yet)
#define portOutputRegister(port) (volatile byte *)( &(port->regs->ODR) ) //These are defined in STM32F1/variants/generic_stm32f103c/variant.h but return a non byte* value
#define portInputRegister(port) (volatile byte *)( &(port->regs->IDR) ) //These are defined in STM32F1/variants/generic_stm32f103c/variant.h but return a non byte* value
#endif

class LoRaClass : public Stream {
public:
  LoRaClass();

  int begin(long frequency,bool PABOOST);
  void end();

  int beginPacket(int implicitHeader = false);
  int endPacket();

  int parsePacket(int size = 0);
  int packetRssi();
  float packetSnr();

  // from Print
  virtual size_t write(uint8_t byte);
  virtual size_t write(const uint8_t *buffer, size_t size);

  // from Stream
  virtual int available();
  virtual int read();
  virtual int peek();
  virtual void flush();

  int status();

  void onReceive(void(*callback)(int));

  void receive(int size = 0);
  void idle();
  void sleep();

  int getFrequency();
  int getTxPower();
  int getSpreadingFactor();
  long getSignalBandwidth();
  int getCodingRate4();
  long getPreambleLength();
  int getSyncWord();

  void setTxPower(int level, int outputPin = PA_OUTPUT_PA_BOOST_PIN);
  void setFrequency(long frequency);
  void setSpreadingFactor(int sf);
  void setSignalBandwidth(long sbw);
  void setCodingRate4(int denominator);
  void setPreambleLength(long length);
  void setSyncWord(int sw);
  void enableCrc();
  void disableCrc();

  // deprecated
  void crc() { enableCrc(); }
  void noCrc() { disableCrc(); }

  byte random();

  void setPins(int ss = LORA_DEFAULT_SS_PIN, int reset = LORA_DEFAULT_RESET_PIN, int dio0 = LORA_DEFAULT_DIO0_PIN);
  void setSPIFrequency(uint32_t frequency);

  void dumpRegisters(Stream& out);
  uint8_t readRegister(uint8_t address);

private:
  void explicitHeaderMode();
  void implicitHeaderMode();

  void handleDio0Rise();

  void writeRegister(uint8_t address, uint8_t value);
  uint8_t singleTransfer(uint8_t address, uint8_t value);

  static void onDio0Rise();

private:
  SPISettings _spiSettings;
  int _ss;
  int _reset;
  int _dio0;
  int _frequency;
  int _packetIndex;
  int _implicitHeaderMode;
  void (*_onReceive)(int);
};

extern LoRaClass LoRa;

#endif
