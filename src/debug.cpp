#include "debug.h"

#ifndef DEBUG_ENABLE

void debugString(const char* message) {
    return;
}

void debugPrintf(const char* message, ...) {
    return;
}

#else

void debugString(const char* message) {
	fprintf(STREAM_FILE, "%s", message);
    return;
}

void debugPrintf(const char* message, ...) {
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
