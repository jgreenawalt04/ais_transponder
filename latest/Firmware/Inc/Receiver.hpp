/*
  Copyright (c) 2016-2020 Peter Antypas

  This file is part of the MAIANA™ transponder firmware.

  The firmware is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>
*/


#ifndef RECEIVER_HPP_
#define RECEIVER_HPP_

#include "RXPacket.hpp"
#include "RadioState.hpp"
#include "RFIC.hpp"
#include "AISChannels.h"



class Receiver : public RFIC
{
public:
  Receiver(GPIO_TypeDef *sdnPort,
          uint32_t sdnPin,
          GPIO_TypeDef *csPort,
          uint32_t csPin,
          GPIO_TypeDef *dataPort,
          uint32_t dataPin,
          GPIO_TypeDef *clockPort,
          uint32_t clockPin);

  virtual ~Receiver();

  bool init();
  VHFChannel channel();
  virtual void startReceiving(VHFChannel channel);
  virtual void onBitClock();
  virtual void timeSlotStarted(uint32_t slot);
  void startListening(VHFChannel channel);
  void switchToChannel(VHFChannel channel);
private:
  bool addBit(uint8_t bit);
  void resetBitScanner();
  uint8_t reportRSSI();
  void pushPacket();
  void processNRZIBit(uint8_t level);
  virtual void configureGPIOsForRX();
protected:
  RXPacket mRXPacket;
  uint16_t mBitWindow;
  uint8_t mLastNRZIBit;
  uint32_t mBitCount;
  uint32_t mOneBitCount;
  BitState mBitState;
  uint8_t mRXByte;
  VHFChannel mChannel;
  uint16_t mSlotBitNumber;
  bool mSwitchAtNextSlot;
  VHFChannel mSwitchToChannel;
};

#endif /* RECEIVER_HPP_ */
