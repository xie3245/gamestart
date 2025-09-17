#include "thread.h"

namespace this_thread {
void sleep(std::chrono::milliseconds duration) noexcept { SDL_Delay(duration.count()); }
}  // namespace this_thread