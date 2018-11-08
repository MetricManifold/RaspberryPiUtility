#include "control.h"


void(*__no_fn)() = []() {};
bool __queued = false;
std::thread __queue_thread([]() {});
std::mutex __mm;
