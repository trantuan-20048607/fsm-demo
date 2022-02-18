#ifndef _FSM__MACHINE_OPERATION_EVENT_H_
#define _FSM__MACHINE_OPERATION_EVENT_H_

#include <sstream>
#include "event.h"

namespace fsm {
    class MachineBase;

    enum class MachineOperator {
        kAdd,
        kRemove,
    };

    class MachineOperationEvent : public EventTemplate<MachineOperator> {
    public:
        __ATTR_READER__(machine_, machine)

        MachineOperationEvent(MachineOperator type, MachineBaseSharedPtr machine)
                : EventTemplate<MachineOperator>(type),
                  machine_(std::move(machine)) {}

        ~MachineOperationEvent() override = default;

        [[maybe_unused]] std::ostream &ToStream(std::ostream &ostream) const override;

        [[nodiscard]] std::string ToString() const override;

    private:
        MachineBaseSharedPtr machine_;
    };
}

#endif  // _FSM__MACHINE_OPERATION_EVENT_H_
