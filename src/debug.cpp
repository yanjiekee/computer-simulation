#include "debug.h"

#ifndef DEBUG_ENABLE

void debugString(char* message) {
    return;
}

void debugPrintf(char* message, ...) {
    return;
}

#else

void debugString(char* message) {
	fprintf(STREAM_FILE, "%s", message);
    return;
}

void debugPrintf(char* message, ...) {
	bool message_has_args = false;
	for (uint8_t i = 0; true; i++) {
		if (message[i] == 0)
			break;
		if (message[i] == '%') {
			message_has_args = true;
			break;
		}
	}
	if (message_has_args) {
		va_list args;
		va_start(args, message);
		char buffer[256];
		vsprintf(buffer, message, args);
		va_end(args);
		debugString(buffer);
	} else {
		debugString(message);
	}
    return;
}

#endif
