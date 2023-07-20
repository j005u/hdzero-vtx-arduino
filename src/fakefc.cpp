#include <Arduino.h>
#include <Piduino.h> 

#include <hdzero.h>

HDZero hdzero;

void setup() {
    // wait for serial to be ready
    Serial2.begin(115200);
    while (!Serial2)
        ;

    // setup and configure hdzero
    hdzero.begin(Serial2);
    hdzero.setFcVariant("INAV");
    hdzero.setResolution(SD_3016);

}

uint32_t lastRefreshTime = 0;

int8_t pointXDirection = 1;
uint8_t pointX = 0;

int8_t pointYDirection = 1;
uint8_t pointY = 0;

unsigned long armLoopStartTime = 0;

char loopTime[50];


void loop() {
    if (millis() - lastRefreshTime >= 500) {

        hdzero.clear();
        hdzero.writeString(0, 1, 10, "Tick tock!");
        hdzero.writeString(0, pointX, pointY, "AHHH");

        sprintf(loopTime, "%ld", millis()-armLoopStartTime);

        hdzero.writeString(0, 1, 11, loopTime);
        hdzero.writeString(0, 1, 12, hdzero.getArmed() ? "ARMED" : "DISARMED");

        pointX += pointXDirection;
        if (pointX + 4 >= 30 || pointX == 0) {
            pointXDirection = -pointXDirection;
        }
        pointY += pointYDirection;
        if (pointY >= 16 || pointY == 0) {
            pointYDirection = -pointYDirection;
        }

        // read this from bottom to top
        if (millis() - armLoopStartTime >= 439000) { // disarm and reset after 7 minutes
            hdzero.setArmed(false);
            armLoopStartTime = millis();
            //digitalWrite(LED_BUILTIN, 0);
        } else if (millis() - armLoopStartTime >= 19000) { // rearm after another 3 seconds
            hdzero.setArmed(true);
            //digitalWrite(LED_BUILTIN, 1);
        } else if (millis() - armLoopStartTime >= 16000) { // then disarm after a further 6
            hdzero.setArmed(false);
            //digitalWrite(LED_BUILTIN, 0);
        } else if (millis() - armLoopStartTime >= 10000) { // arm after ten seconds
            hdzero.setArmed(true);
            //digitalWrite(LED_BUILTIN, 1);
        }

        hdzero.draw();

        lastRefreshTime = millis();
    }

    hdzero.run();
}