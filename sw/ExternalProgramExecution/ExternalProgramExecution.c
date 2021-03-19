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
   char commandText[255] = "";
   getCommandText(commandText, argc, argv);
   printf("%s\n", commandText);

   FILE* rd = NULL;
   rd = popen(commandText, "r");
   int status = pclose(rd);
   return WEXITSTATUS(status);
}

int popenChildProcess_NoCommandPrint(int argc, char* const argv[])
{
   char commandText[255] = "";
   getCommandText(commandText, argc, argv);

   FILE* rd = NULL;
   rd = popen(commandText, "r");
   int status = pclose(rd);
   return WEXITSTATUS(status);
}

int forkAndRunChildProcess(char* const argv[])
{
#ifdef __WINDOWS__
   return forkAndRunChildProcess_windows(argv);
#else
   return forkAndRunChildProcess_linux(argv);
#endif
}

#ifdef __WIDNOWS__
int forkAndRunChildProcess_windows(char* const argv[])
{
   int status = spawnv(P_WAIT, argv[0], argv);
   if (WIFEXITED(status))
   {
      return WEXITSTATUS(status);
   }
}
#else
int forkAndRunChildProcess_linux(char* const argv[])
{
   int status = 0;
   pid_t pid;
   int ret = 1;
   pid = fork();

   if (pid == 0)
   {
      // child process
      executeAndExit(argv);
   }
   else
   {
      // parent process
      return waitAndExit(pid, status);
   }
   return 1;
}
#endif

void getCommandText(char* commandText, int argc, char* const argv[])
{
   strcpy(commandText, argv[0]);
   for (int i = 1; i < argc; i++)
   {
      if (argv[i] != NULL)
      {
         strcat(commandText, " ");
         strcat(commandText, argv[i]);
      }
   }
}

void executeAndExit(char* const argv[])
{
   execvp(argv[0], argv);  // If execv returns, there was an error
   exit(0);
}

int waitAndExit(pid_t pid, int status)
{
   if (waitpid(pid, &status, 0) > 0)
   {
      if (WIFEXITED(status) && !WEXITSTATUS(status))
      {
         return WEXITSTATUS(status);
      }
   }
}
