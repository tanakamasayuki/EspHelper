#include "EspHelperBoardSettings.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    EspHelperBoardSettings::dump();
}

void loop()
{
    delay(1);
}
