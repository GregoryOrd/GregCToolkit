#include "ExternalProgramExecution.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#ifdef __WINDOWS__
#include <process.h>
#elif __unix__
#include <sys/wait.h>
#include <unistd.h>
#endif

int popenChildProcess(const char* pathToExecutable, int argc, char* const argv[])
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

   char commandText[255] = "";
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
   rd = popen(commandText, "r");
   if (strlen((char*)rd) > 0)
   {
      printf("%s\n", (char*)rd);
   }
   int status = pclose(rd);
   return WEXITSTATUS(status);
}

int forkAndRunChildProcess(const char* pathToExecutable, char* const argv[])
{
   int status;
#ifdef __WINDOWS__
   status = spawnv(P_WAIT, pathToExecutable, argv);
   if (WIFEXITED(status))
   {
      return WEXITSTATUS(status);
   }
#else
   pid_t pid = fork();
   if (pid == 0)
   { /* child process */
      execv(pathToExecutable, argv);
      exit(1); /* only if execv fails */
   }
   else
   { /* pid!=0; parent process */
      int status;
      waitpid(pid, &status, 0);
      if (WIFEXITED(status))
      {
         return WEXITSTATUS(status);
      }
   }
#endif
}
