#include <iostream>

#include "../../include/IEmoStateDLL.h"
#include "../../include/Iedk.h"
#include "../../include/IedkErrorCode.h"

void connectToEmoEngine();
void logMotionData();
void disconnectFromEmoEngine();

int main(int argc, char const *argv[]) {
  connectToEmoEngine();
  logMotionData();
  disconnectFromEmoEngine();
  return 0;
}

//TODO:
void connectToEmoEngine() {

}

//TODO:
void logMotionData() {

}

// TODO:
void disconnectFromEmoEngine() {
  
}
