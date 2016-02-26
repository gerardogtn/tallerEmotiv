// Copyright 2016 Gerardo Teruel

#include <unistd.h>  // Para la funcion usleep(). Solo sirve en UNIX.
#include <iostream>
#include <stdexcept>  // Para runtime_error

#include "../../include/IEmoStateDLL.h"
#include "../../include/Iedk.h"
#include "../../include/IedkErrorCode.h"

void initializeEmotivEngine();
void startLoggingMotionData();
void disconnectFromEmoEngine();

void logHeader();
void logMotionData();

IEE_MotionDataChannel_t motionDataChannels[] = {IMD_COUNTER, IMD_GYROX, IMD_GYROY,
        IMD_GYROZ, IMD_ACCX, IMD_ACCY, IMD_ACCZ, IMD_MAGX, IMD_MAGY, IMD_MAGZ,
        IMD_TIMESTAMP};

const int NUMBER_OF_CHANNELS = 11;
const char * HEADER = "COUNTER, GYROX, GYROY, GYROZ, ACCX, ACCY, ACCZ, MAGX, MAGY, MAGZ, TIMESTAMP";
const float SECONDS = 1;

DataHandle motionDataHandle;

int main(int argc, char const *argv[]) {
  initializeEmotivEngine();
  startLoggingMotionData();
  disconnectFromEmoEngine();
  return 0;
}

void initializeEmotivEngine() {
    if (IEE_EngineConnect() != EDK_OK) {
        throw std::runtime_error("Cannot connect to emotiv engine");
    }
    motionDataHandle = IEE_MotionDataCreate();
    IEE_MotionDataSetBufferSizeInSec(SECONDS);
}

void startLoggingMotionData() {
  logHeader();
  while (true) {
    logMotionData();
    sleep(1);
  }
}

void logHeader() {
    std::cout << HEADER << std::endl;
}

void logMotionData() {
    IEE_MotionDataUpdateHandle(0, motionDataHandle);

    unsigned int samplesTaken = 0;
    IEE_MotionDataGetNumberOfSample(motionDataHandle, & samplesTaken);

    for (int i = samplesTaken; i > 0; i--) {
        for (int j = 0; j < NUMBER_OF_CHANNELS; j++) {
            double * data = new double[samplesTaken];
            IEE_MotionDataGet(motionDataHandle, motionDataChannels[j], data, samplesTaken);
            std::cout << data[i] << ", ";
            delete[] data;
        }
        std::cout << "\n";
    }
}

void disconnectFromEmoEngine() {
  IEE_MotionDataFree(motionDataHandle);
  IEE_EngineDisconnect();
}
