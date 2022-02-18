#ifndef _FSM__EVENT_H_
#define _FSM__EVENT_H_

#include "fsm_base_types.h"

namespace fsm {
    class MachineBase;

    class MachineSet;

    class Event {
        friend class MachineSet;

        friend class StateMachine;

        friend class ActionMachine;

    public:
        __VIRTUAL_ATTR_READER__(MachineSetSharedPtr, machine_set_.lock(), machine_set)

        virtual std::ostream &ToStream(std::ostream &str) const = 0;

        [[nodiscard]] virtual std::string ToString() const = 0;

        explicit Event(const MachineSetSharedPtr &machine_set)
                : machine_set_(machine_set) {}

        virtual ~Event() = default;

    protected:
        MachineSetWeakPtr machine_set_;
        MachineBaseWeakPtrVec target_machines_;
    };

    template<class EventType,
            class = typename std::enable_if<std::is_enum<EventType>::value>::type>
    class EventTemplate : public Event {
        friend class MachineSet;

        friend class StateMachine;

        friend class ActionMachine;

    public:
        typedef EventType Type;

        __ATTR_READER_REF__(type_, type)

        explicit EventTemplate(Type type)
                : Event(MachineSetSharedPtr()),
                  type_(type) {
        }

        [[maybe_unused]] EventTemplate(Type type, const MachineBaseWeakPtrVec &target_machines)
                : Event(MachineSetSharedPtr()),
                  type_(type) {
            target_machines_ = target_machines;
        }

        [[maybe_unused]] EventTemplate(Type type, const MachineBaseSharedPtr &target_machine)
                : Event(MachineSetSharedPtr()),
                  type_(type) {
            if (target_machine)
                target_machines_.emplace_back(target_machine);
        }

        EventTemplate(Type type, const MachineSetSharedPtr &machine_set)
                : Event(machine_set),
                  type_(type) {
        }

        ~EventTemplate() override = default;

    protected:
        Type type_;
    };

    inline std::ostream &operator<<(std::ostream &str, const Event &event) { return event.ToStream(str); }
}

#endif  // _FSM__EVENT_H_
