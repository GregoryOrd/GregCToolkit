#ifndef EXTERNAL_PROGRAM_EXECUTION_H
#define EXTERNAL_PROGRAM_EXECUTION_H

#ifdef __cplusplus
extern "C" {
#endif  

int forkAndRunChildProcess(const char * pathToExecutable, int argc, char * const argv[]);

#ifdef __cplusplus
}
#endif  

#endif