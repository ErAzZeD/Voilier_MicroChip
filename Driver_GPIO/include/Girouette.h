#include "Driver_Timer.h"
#include "stm32f10x.h"
#include "Driver_GPIO.h"

void initGirouette(void);
float getAngle(void);
float calculDuty(float angle);