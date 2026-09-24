#include "pid.h"

static int lastError = 0;

void resetPID() {
  lastError = 0;
}

int calculatePID(int currentPosition, int targetPosition, float dt) {
  int error = currentPosition - targetPosition;

  float pTerm = Kp * error;
  float dTerm = Kd * ((error - lastError) / dt);

  lastError = error;

  int output = (int)(pTerm + dTerm);
  return output;
}
