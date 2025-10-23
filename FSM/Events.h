#ifndef EVENTS_H__
#define EVENTS_H__

#include <variant>
#include <string>
#include <unordered_map>
class FSMEvent
{
public:
	std::string name{ "none" };

	inline void setName(std::string name_) { name = name_; }
	inline std::string getName() { return name; }
	virtual ~FSMEvent() = 0;
};


struct EventStartedShooting : FSMEvent { EventStartedShooting() : FSMEvent() { setName("StartedShooting"); } };
struct EventStoppedShooting : FSMEvent { EventStoppedShooting() : FSMEvent() { setName("StoppedShooting"); } };
struct EventStartedMoving : FSMEvent { EventStartedMoving() : FSMEvent() { setName("StartedMoving"); } };
struct EventStoppedMoving : FSMEvent { EventStoppedMoving() : FSMEvent() { setName("StoppedMoving"); } };
struct EventFell : FSMEvent { EventFell() : FSMEvent() { setName("Fell"); } };
struct EventHit : FSMEvent { EventHit() : FSMEvent() { setName("Hit"); } };
struct EventJumped : FSMEvent { EventJumped() : FSMEvent() { setName("Jumped"); } };
struct EventLanded : FSMEvent { EventLanded() : FSMEvent() { setName("Landed"); } };
struct EventRecovered : FSMEvent { EventRecovered() : FSMEvent() { setName("Recovered"); } };
struct EventDied : FSMEvent { EventDied() : FSMEvent() { setName("Died"); } };
struct EventTransEnd : FSMEvent { EventTransEnd() : FSMEvent() { setName("TransEnd"); } };

using PlayerEventVar = std::variant<EventStartedShooting, EventJumped, EventDied, EventStartedMoving , EventStoppedMoving, EventFell, EventHit, EventLanded, EventStoppedShooting, EventRecovered, EventTransEnd>;

enum class EventEnum {
	StartedShooting,
	StoppedShooting,
	StartedMoving,
	StoppedMoving,
	Fell,
	Hit,
	Jumped,
	Landed,
	Recovered,
	Died,
	TransEnd,
	Count,
	None
};


static const std::string_view evtToString(EventEnum s)
{
	switch (s)
	{
	case EventEnum::StartedShooting: return "StartedShooting";
	case EventEnum::StoppedShooting: return "StoppedShooting";
	case EventEnum::StartedMoving: return "StartedMoving";
	case EventEnum::StoppedMoving: return "StoppedMoving";
	case EventEnum::Fell: return "Fell";
	case EventEnum::Hit: return "Hit";
	case EventEnum::Jumped: return "Jumped";
	case EventEnum::Landed: return "Landed";
	case EventEnum::Recovered: return "Recovered";
	case EventEnum::Died: return "Died";
	case EventEnum::TransEnd: return "TransEnd";
	case EventEnum::None: return "None";
	}
	return "None"; // fallback
}

static EventEnum strToEvt(const std::string& evtStr_)
{
	static const std::unordered_map<std::string, EventEnum> eventMap = {
		{"StartedShooting", EventEnum::StartedShooting},
		{"StoppedShooting", EventEnum::StoppedShooting},
		{"StartedMoving", EventEnum::StartedMoving},
		{"StoppedMoving", EventEnum::StoppedMoving},
		{"Fell", EventEnum::Fell},
		{"Hit", EventEnum::Hit},
		{"Jumped", EventEnum::Jumped},
		{"Landed", EventEnum::Landed},
		{"Recovered", EventEnum::Recovered},
		{"Died",EventEnum::Died},
		{"TransEnd", EventEnum::TransEnd},
		{"None",EventEnum::None},


	};

	auto it = eventMap.find(evtStr_);
	return (it != eventMap.end()) ? it->second : EventEnum::None;
};


template <typename EventVar>
constexpr EventEnum getEventEnum(EventVar state_)
{
	if (std::holds_alternative<EventStartedShooting>(state_)) return EventEnum::StartedShooting;
	else if (std::holds_alternative<EventJumped>(state_)) return EventEnum::Jumped;
	else if (std::holds_alternative<EventDied>(state_)) return EventEnum::Died;
	else if (std::holds_alternative<EventStartedMoving>(state_)) return EventEnum::StartedMoving;
	else if (std::holds_alternative<EventStoppedMoving>(state_)) return EventEnum::StoppedMoving;
	else if (std::holds_alternative<EventFell>(state_)) return EventEnum::Fell;
	else if (std::holds_alternative<EventHit>(state_)) return EventEnum::Hit;
	else if (std::holds_alternative<EventLanded>(state_)) return EventEnum::Landed;
	else if (std::holds_alternative<EventStoppedShooting>(state_)) return EventEnum::StoppedShooting;
	else if (std::holds_alternative<EventRecovered>(state_)) return EventEnum::Recovered;
	else if (std::holds_alternative<EventTransEnd>(state_)) return EventEnum::TransEnd;
	else return EventEnum::None;
};


#endif