#include <iostream> // std::cout, std::cin
#include <fstream> // std::ofstream
#include <sstream>
#include <stdexcept> // runtime error.
#include <string>

#include "../../include/IEmoStateDLL.h"
#include "../../include/Iedk.h"
#include "../../include/IedkErrorCode.h"

void connectToEmoEngine();
void startLoggingMotionData();
void disconnectFromEmoEngine();

void logHeader();
void logMotionData();
void checkForKeyboardHits();

void printLine(std::string);

const char * FILE_NAME = "motionData.csv";
const std::string HEADER = "COUNTER, GYROX, GYROY, GYROZ, ACCX, ACCY, ACCZ, MAGX, MAGY, MAGZ, TIMESTAMP";

const float SECONDS = 1;
bool continueLogging = true;
std::ofstream outputFileStream;

EmoEngineEventHandle emoEngineEvent;
EmoStateHandle emoState;

// To compile g++ main.cpp -L/home/inspirecave/Documents/tallerEmotiv/bin/linux64/ -ledk
int main(int argc, char const *argv[]) {
  std::ofstream outputFileStream(FILE_NAME, std::ofstream::trunc);
  emoEngineEvent = IEE_EmoEngineEventCreate();
  emoState = IEE_EmoStateCreate();
  connectToEmoEngine();
  startLoggingMotionData();
  disconnectFromEmoEngine();
  outputFileStream.close();
  return 0;
}

void connectToEmoEngine() {
  if (IEE_EngineConnect() != EDK_OK){
    throw std::runtime_error("Cannot connect to Emotiv engine");
  }
}

void startLoggingMotionData() {
  printLine("Started logging motion data. Press Enter to stop");
  logHeader();
  while(continueLogging) {
    printLine("A");
    logMotionData();
    checkForKeyboardHits();
  }
}

void printLine(std::string line) {
  std::cout << line << std::endl;
  std::cout.flush();
}

void logHeader() {
  outputFileStream << HEADER << std::endl;
}

void logMotionData() {

}

void checkForKeyboardHits() {
  struct timeval tv;
  fd_set read_fd;
  tv.tv_sec=0;
  tv.tv_usec=0;

  FD_ZERO(&read_fd);
  FD_SET(0,&read_fd);

  if(select(1, &read_fd,NULL, NULL, &tv) == -1) {
    continueLogging = true;
  } else if(FD_ISSET(0,&read_fd)) {
    continueLogging = false;
    return;
  } else {
    continueLogging = true;
  }
}

// TODO:
void disconnectFromEmoEngine() {
  IEE_EngineDisconnect();
  IEE_EmoStateFree(emoState);
  IEE_EmoEngineEventFree(emoEngineEvent);
}
