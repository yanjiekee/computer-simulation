// Adapted from Steve Gunn's debug.h, which was licensed under the Creative Commons Attribution License

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdbool.h>
#include <stdarg.h>

#define DEBUG_ENABLE 1
#define STREAM_FILE stderr

#define DEBUG_MESSAGE(message, ...) do{debugPrintf("%s:%d:%s() ", __FILE__+4, __LINE__, __FUNCTION__); debugPrintf(message, ##__VA_ARGS__); debugString("\n");break;} while (true)

void debugPrintf(char* message, ...);
void debugString(char* message);