#ifndef _FSM__TIMER_H_
#define _FSM__TIMER_H_

#include <sys/time.h>

namespace fsm {
    uint64_t GetTime() {
        struct timeval now{};
        gettimeofday(&now, nullptr);

        return (now.tv_sec * 1000000 + now.tv_usec) / 1000;
    }
}

#endif  // _FSM__TIMER_H_
