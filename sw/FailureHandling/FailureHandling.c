#include "FailureHandling.h"

#include <stdlib.h>

void exitIfPreviousStepFailed(int previousStepFailed)
{
    if(previousStepFailed)
    {
        exit(1);
    }
}