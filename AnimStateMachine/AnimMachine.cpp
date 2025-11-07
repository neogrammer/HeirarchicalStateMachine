#include "AnimMachine.h"

#include "all_anim_states.h"

#include "../all_object_types.h"


std::unique_ptr<AnimState> AnimMachine::buildState(anim::CompoundStateType stateType_)
{
	std::unique_ptr<AnimState> state{ nullptr };

	using c = anim::CompoundStateType;
	switch (stateType_)
	{
	case c::Idle: { return std::make_unique<IdleState>(&stateStack.top()->getOwner()); } break;
	case c::Dead: { return std::make_unique<DeadState>(&stateStack.top()->getOwner()); } break;
	case c::Hit: { return std::make_unique<HitState>(&stateStack.top()->getOwner()); } break;
	case c::Running: { return std::make_unique<RunningState>(&stateStack.top()->getOwner()); } break;
	case c::Landing: { return std::make_unique<LandingState>(&stateStack.top()->getOwner()); } break;
	case c::Rising: { return std::make_unique<RisingState>(&stateStack.top()->getOwner()); } break;
	case c::Falling: { return std::make_unique<FallingState>(&stateStack.top()->getOwner()); } break;
	case c::Launching: { return std::make_unique<LaunchingState>(&stateStack.top()->getOwner()); } break;

	default: break;
	}

	return nullptr;
}

AnimMachine::AnimMachine(Obj* owner_, std::unique_ptr<AnimState>& state_)
{

	stateStack.push(std::move(state_));
}

AnimMachine::~AnimMachine()
{
}

void AnimMachine::setFacingRight(bool cond_) { facingRight = cond_; }
bool AnimMachine::getFacingRight() { return facingRight; }
std::string AnimMachine::getCurrAnim()
{
	std::string tmp = stateToString();
	if (facingRight)
		tmp.append("_Right");
	else
		tmp.append("_Left");
	return tmp;
}
std::string AnimMachine::stateToString()
{
	using c = anim::CompoundStateType;
	switch (stateStack.top()->getCompoundType())
	{
	case c::Idle: { return "Idle"; } break;
	case c::Hit: { return "Hit"; } break;
	case c::Dead: { return "Dead"; } break;
	case c::Running: { return "Running"; } break;
	case c::Landing: { return "Landing"; } break;
	case c::Rising: { return "Rising"; } break;
	case c::Falling: { return "Falling"; } break;
	case c::Launching: { return "Launching"; } break;

	default: 
	{
		throw std::runtime_error("No State");
	}
		break;
	};
}
void AnimMachine::update(float dt_)
{
	stateStack.top()->update(dt_);
	if (stateStack.top()->isReadyToTransition())
	{
		if (stateStack.top()->isStateTransient() && stateStack.top()->isFinished() && stateStack.top()->lastInSequence())
		{
			// does not have a next, pop off transient stack and take state under it
			do {
				stateStack.pop();
			} while (stateStack.top()->partOfTransStack());
		}
		auto next = stateStack.top()->getNextState();
		std::unique_ptr<AnimState> tmp{ std::move(buildState(next)) };
		if (stateStack.top()->getType() != anim::StateType::Idle &&
			!tmp->isStateTransient())
		{
			stateStack.pop();
			stateStack.push(std::move(tmp));
		}
		else
		{
			stateStack.push(std::move(tmp));
		}
	}
}