#ifndef EXTERNAL_PROGRAM_EXECUTION_H
#define EXTERNAL_PROGRAM_EXECUTION_H

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
int forkAndRunChildProcess(int argc, char* const argv[]);

#ifdef __cplusplus
}
#endif  

#endif