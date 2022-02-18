#ifndef _FSM__MACHINE_H_
#define _FSM__MACHINE_H_

#include <type_traits>
#include "fsm_base_types.h"
#include "machine_type.h"

namespace fsm {
    class StateMachine;

    template<typename M, typename... Args,
            class = typename std::enable_if<std::is_base_of<StateMachine, typename std::decay<M>::type>::value>::type>
    [[maybe_unused]] std::shared_ptr<typename std::decay<M>::type> GenerateStateMachine(Args &&... args) {
        using RealType = typename std::decay<M>::type;
        std::shared_ptr<RealType> machine = std::make_shared<RealType>(std::forward<Args>(args)...);
        if (machine) { machine->Initialize(); }
        return machine;
    }

    class MachineBase {
    public:
        __VIRTUAL_ATTR_READER__(uint64_t, 0, timeout)

        __VIRTUAL_ATTR_READER__(bool, false, TimedOut)

        __ATTR_READER_REF__(type_, type)

        __ATTR_READER_REF__(name_, name)

        explicit MachineBase(std::string name)
                : type_(name),
                  name_(std::move(name)) {}

        virtual ~MachineBase() = default;

        virtual bool Process(EventSharedPtr) = 0;

        virtual void SetTimeout(uint64_t timeout) = 0;

        virtual void Initialize() = 0;

    protected:
        MachineType type_;
        std::string name_;
    };

    class StateMachine : public MachineBase {
        friend class State;

    public:
        __ATTR_READER_REF__(current_state_, current_state)

        __ATTR_READER_REF__(previous_state_, previous_state)

        explicit StateMachine(std::string name)
                : MachineBase(std::move(name)),
                  timeout_(0) {}

        StateMachine &operator=(const StateMachine &) = delete;

        ~StateMachine() override = default;

        [[maybe_unused]] bool ForceState(const StateSharedPtr &state);

        [[maybe_unused]] bool SetStartState(const StateSharedPtr &state);

        [[maybe_unused]] bool SetMetaState(const StateSharedPtr &state);

        [[maybe_unused]] void ClearMetaState();

        void SetTimeout(uint64_t timeout) override;

        [[nodiscard]] uint64_t timeout() const override;

        [[nodiscard]] bool TimedOut() const override;

        bool Process(EventSharedPtr) override;

    private:
        bool ProcessNormalStateTransition(const EventSharedPtr &event);

        bool ProcessMetaStateTransition(const EventSharedPtr &event);

        template<bool is_meta_state>
        bool InternalSetState(const StateSharedPtr &state);

    protected:
        StateMachine(const StateMachine &state_machine)
                : MachineBase(state_machine),
                  timeout_(state_machine.timeout_) {
        }

        uint64_t timeout_;
        StateSharedPtr current_state_;
        StateSharedPtr previous_state_;

        typedef std::vector<StateSharedPtr> StateListType;
        StateListType states_;

        StateSharedPtr meta_state_;
    };

    class ActionMachine : public MachineBase {
        friend class NonTransitiveAction;

    public:
        explicit ActionMachine(std::string name)
                : MachineBase(std::move(name)) {}

        bool Process(EventSharedPtr) override;

    protected:
        typedef std::vector<NonTransitiveActionSharedPtr> ActionListType;
        ActionListType non_transitive_actions_;
    };
}

#endif  // _FSM__MACHINE_H_
