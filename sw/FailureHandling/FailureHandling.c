#include "FailureHandling.h"

#include <stdlib.h>

void exitIfError(int error)
{
   if (error)
   {
      exit(1);
   }
}
