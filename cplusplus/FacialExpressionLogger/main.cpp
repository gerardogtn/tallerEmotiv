// Copyright 2016 Gerardo Teruel

#include <unistd.h>  // Para la funcion usleep(). Solo sirve en UNIX.
#include <iostream>
#include <stdexcept>  // Para runtime_error

#include "../../include/IEmoStateDLL.h"
#include "../../include/Iedk.h"
#include "../../include/IedkErrorCode.h"

const char * FILE_NAME = "facialExpression.csv";

EmoEngineEventHandle emotivEngineEvent;
EmoStateHandle emotivEngineState;
IEE_Event_t currentEventType;
unsigned int userId = 0;

void initializeEmotivEngine();
void terminateEmotivEngine();
bool isThereNewEvent();

void updateCurrentEvent();
void updateCurrentEventType();

void logFacialExpressionData();
void logHeader();
void logCurrentFacialExpressionData();

void logTimeFromStart();
void logFacialBooleanData();
void logFacialPowerData();
void logUpperFaceExpressionData(IEE_FacialExpressionAlgo_t, float);
void logLowerFaceExpressionData(IEE_FacialExpressionAlgo_t, float);

int main(int argc, char const *argv[]) {
    initializeEmotivEngine();
    logFacialExpressionData();
    terminateEmotivEngine();
    return 0;
}

void initializeEmotivEngine() {
    if (IEE_EngineConnect() != EDK_OK) {
        throw std::runtime_error("Cannot connect to emotiv engine");
    }
    emotivEngineEvent = IEE_EmoEngineEventCreate();
    emotivEngineState = IEE_EmoStateCreate();
}


void logFacialExpressionData() {
    logHeader();
    while (true) {
        if (isThereNewEvent()) {
            updateCurrentEventType();
            // IEE_EmoStateUpdated means that there is new detection
            // results from EmotivEngine.
            if (currentEventType == IEE_EmoStateUpdated) {
                updateCurrentEvent();
                logCurrentFacialExpressionData();
                std::cout << "\n";
            }
        }
        sleep(1);
    }
}

void logHeader() {
    std::cout << "Time, Blink, Wink left, " <<  "Wink right, Eyes Open,"  <<
            " Eyes closed, Surprise, Frown, Smile, Clench\n";
}

bool isThereNewEvent() {
    int state = IEE_EngineGetNextEvent(emotivEngineEvent);
    if (state == EDK_OK) {
        return true;
    } else if (state == EDK_NO_EVENT) {
        return false;
    } else {
        throw std::runtime_error("Emotiv engine error");
    }
}

void updateCurrentEventType() {
    currentEventType =  IEE_EmoEngineEventGetType(emotivEngineEvent);
}

void updateCurrentEvent() {
    IEE_EmoEngineEventGetEmoState(emotivEngineEvent, emotivEngineState);
}

void logCurrentFacialExpressionData() {
    logTimeFromStart();
    logFacialBooleanData();
    logFacialPowerData();
    return;
}

void logTimeFromStart() {
    // GetTimeFromStart regresa un float con el numero de segundos desde que el
    // emotiv engine se conecto al dispositivo.
    std::cout << IS_GetTimeFromStart(emotivEngineState) << ", ";
}

void logFacialBooleanData() {
    std::cout << IS_FacialExpressionIsBlink(emotivEngineState) << ", ";
    std::cout << IS_FacialExpressionIsLeftWink(emotivEngineState) << ", ";
    std::cout << IS_FacialExpressionIsRightWink(emotivEngineState) << ", ";
    std::cout << IS_FacialExpressionIsEyesOpen(emotivEngineState) << ", ";
    std::cout << IS_FacialExpressionIsLookingUp(emotivEngineState) << ", ";
    std::cout << IS_FacialExpressionIsLookingDown(emotivEngineState) << ", ";
}

// Power es una medida de 0-1 que indica con que tanto "poder" se esta
// esta realizando una accion.
void logFacialPowerData() {
    IEE_FacialExpressionAlgo_t lowerFaceExpression = IS_FacialExpressionGetLowerFaceAction(emotivEngineState);
    IEE_FacialExpressionAlgo_t upperFaceExpression = IS_FacialExpressionGetUpperFaceAction(emotivEngineState);
    float lowerFaceExpressionPower = IS_FacialExpressionGetLowerFaceActionPower(emotivEngineState);
    float upperFaceExpressionPower = IS_FacialExpressionGetUpperFaceActionPower(emotivEngineState);

    logUpperFaceExpressionData(upperFaceExpression, upperFaceExpressionPower);
    logLowerFaceExpressionData(lowerFaceExpression, lowerFaceExpressionPower);
}

void logUpperFaceExpressionData(IEE_FacialExpressionAlgo_t type, float value) {
    if (type == FE_SURPRISE) {
        std::cout << value << ", " << 0;
    } else if (type == FE_FROWN) {
        std::cout << "0, " << value;
    } else {
        std::cout << "0, 0";
    }
}

void logLowerFaceExpressionData(IEE_FacialExpressionAlgo_t type, float value) {
    if (type == FE_SMILE) {
        std::cout << value << ", 0";
    } else if (type == FE_CLENCH) {
        std::cout << "0, " << value;
    } else {
        std::cout << "0, 0";
    }
}

void terminateEmotivEngine() {
    IEE_EngineDisconnect();
    IEE_EmoStateFree(emotivEngineState);
    IEE_EmoEngineEventFree(emotivEngineEvent);
}
