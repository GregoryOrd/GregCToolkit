#include "ExternalProgramExecution.h"

#include <errno.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> /* for pid_t */

int forkAndRunChildProcess(const char* pathToExecutable, int argc, char* const argv[])
{
   int sizeOfCommandText = strlen(pathToExecutable);
   for (int i = 1; i < argc; i++)
   {
      if (argv[i] != NULL)
      {
         sizeOfCommandText += (strlen(argv[i]) + 1);
      }
   }
   sizeOfCommandText++;

   char* commandText = calloc(sizeOfCommandText, sizeof(char));
   strcpy(commandText, pathToExecutable);
   for (int i = 1; i < argc; i++)
   {
      if (argv[i] != NULL)
      {
         strcat(commandText, " ");
         strcat(commandText, argv[i]);
      }
   }
   printf("%s\n", commandText);

   FILE* rd;
   char buffer[4080];
   rd = popen(commandText, "r");
   if (strlen((char*)rd) > 0)
   {
      printf("%s\n", rd);
   }
   int status = pclose(rd);
   free(commandText);
   return WEXITSTATUS(status);
}