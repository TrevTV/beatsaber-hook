#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string_view>
#include <vector>
#include <unistd.h>
#include <unwind.h>

// logs the function, file and line, sleeps to allow logs to flush, then terminates program
__attribute__((noreturn)) inline void safeAbort() {
    // we REALLY want this to appear at least once in the log (for fastest fixing)
    for (int i = 0; i < 2; i++) {
        usleep(100000L);  // 0.1s
    }
    usleep(100000L);   // 0.1s
    std::terminate();  // cleans things up and then calls abort
}

// sets "file" and "line" to the file and line you call this macro from
#ifndef SUPPRESS_MACRO_LOGS
#define SAFE_ABORT() safeAbort()
#else
#define SAFE_ABORT() safeAbort()
#endif

#ifndef SUPPRESS_MACRO_LOGS
#define SAFE_ABORT_MSG(...) safeAbort()
#else
#define SAFE_ABORT_MSG(...) safeAbort()
#endif

struct Il2CppString;
#ifndef __cplusplus
bool = uchar8_t;
#endif /* __cplusplus */


// Dumps the 'before' bytes before and 'after' bytes after the given pointer to log
void dump(int before, int after, void* ptr);
// Reads all of the text of a file at the given filename. If the file does not exist, returns an empty string.
std::string readfile(std::string_view filename);
// Reads all bytes from the provided file at the given filename. If the file does not exist, returns an empty vector.
std::vector<char> readbytes(std::string_view filename);
// Writes all of the text to a file at the given filename. Returns true on success, false otherwise
bool writefile(std::string_view filename, std::string_view text);
// Deletes a file at the given filename. Returns true on success, false otherwise
bool deletefile(std::string_view filename);
// Returns if a file exists and can be written to / read from
bool fileexists(std::string_view filename);
// Returns if a directory exists and can be written to / read from
bool direxists(std::string_view dirname);

/// @brief Get the buildId from a file
/// @returns The buildId if found
std::optional<std::string> getBuildId(std::string_view filename);

/// @brief Get the size of the libil2cpp.so file
/// @returns The size of the .so
uintptr_t getLibil2cppSize();

namespace backtrace_helpers {
    struct BacktraceState {
        void **current;
        void **end;
        uint16_t skip;
    };
    _Unwind_Reason_Code unwindCallback(struct _Unwind_Context *context, void *arg);
    size_t captureBacktrace(void **buffer, uint16_t max, uint16_t skip = 0);
}

#endif /* UTILS_FUNCTIONS_H */
