#ifndef FSM_H__
#define FSM_H__
#include <variant>
#include <optional>
#include <string_view>
#include <FSM/AnimStates.h>


template <typename Derived, typename StateVariant>
class FSM
{
protected:
	StateVariant state_;
public:
	template<typename Event>
	void dispatch(Event&& event)
	{
		Derived& child = static_cast<Derived&>(*this);
		auto new_state = std::visit(
			[&](auto& s) -> std::optional<StateVariant>
			{
				return child.On_Event(s, std::forward<Event>(event));
			}, state_);
		if (new_state)
		{
			state_ = *std::move(new_state);
		}
	}

	StateVariant& getStateVariant() {
		return state_;
	}

	std::string_view getStateName() const
	{
		return toString(getStateEnum(state_));
	}

	void setInitialState(StateVariant&& newstate)
	{
		state_ = std::move(newstate);
	}

	

};

// duck folding
template<typename Fsm, typename... Events>
void dispatch(Fsm& fsm, Events&&... events)
{
	(fsm.dispatch(std::forward<Events>(events)), ...);
}

#endif