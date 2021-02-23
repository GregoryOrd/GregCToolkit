#ifndef EXTERNAL_PROGRAM_EXECUTION_H
#define EXTERNAL_PROGRAM_EXECUTION_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif  

//popenChildProcess() will print to our console the output for the external program.
//forkAndRunChildProcess() will not print out this output.

//If we do not expect any output, we should use forkAndRunChildProcess() because 
//popenChildProcess() will print out a garabage string if no printed text output is
//generated from the external program's execution.

//Expect the first element of argv to be the path to the executable program
int popenChildProcess(int argc, char * const argv[]);
int forkAndRunChildProcess(char* const argv[]);

#ifdef __WIDNOWS__
int forkAndRunChildProcess_windows(char* const argv[]);
#else
int forkAndRunChildProcess_linux(char* const argv[]);
#endif

void getCommandText(char* commandText, int argc, char* const argv[]);
void executeAndExit(char* const argv[]);
int waitAndExit(pid_t pid, int status);

#ifdef __cplusplus
}
#endif  

#endif