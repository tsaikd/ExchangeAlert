/**
 * @file Debug.cpp
 * @see Debug.h
 **/

#include "Debug.h"

#ifdef DEBUG

char g_debugBuf[DEBUG_BUFSIZE];
char g_debugBuf2[DEBUG_BUFSIZE];
FILE* g_fpDebugLog;

#endif//DEBUG
