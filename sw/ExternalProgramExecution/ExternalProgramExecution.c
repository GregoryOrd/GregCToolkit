#include "ExternalProgramExecution.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#ifdef __WINDOWS__
#include <process.h>
#else
#include <sys/wait.h>
#include <unistd.h>
#endif

int popenChildProcess(int argc, char* const argv[])
{
   int sizeOfCommandText = strlen(argv[0]);
   for (int i = 1; i < argc; i++)
   {
      if (argv[i] != NULL)
      {
         sizeOfCommandText += (strlen(argv[i]) + 1);
      }
   }
   sizeOfCommandText++;

   char commandText[255] = "";
   strcpy(commandText, argv[0]);
   for (int i = 1; i < argc; i++)
   {
      if (argv[i] != NULL)
      {
         strcat(commandText, " ");
         strcat(commandText, argv[i]);
      }
   }
   printf("%s\n", commandText);

   FILE* rd = NULL;
   rd = popen(commandText, "r");
   int status = pclose(rd);
   return WEXITSTATUS(status);
}

int forkAndRunChildProcess(int argc, char* const argv[])
{
   int status;
#ifdef __WINDOWS__
   status = spawnv(P_WAIT, pathToExecutable, argv);
   if (WIFEXITED(status))
   {
      return WEXITSTATUS(status);
   }
#else
   pid_t pid;
   int ret = 1;
   pid = fork();

   if (pid == 0)
   {
      // child process
      execvp(argv[0], argv);

      // If execv returns, there was an error
      exit(0);
   }
   else
   {
      // parent process
      if (waitpid(pid, &status, 0) > 0)
      {
         if (WIFEXITED(status) && !WEXITSTATUS(status))
         {
            return WEXITSTATUS(status);
         }
      }
   }
   return 1;
#endif
}
