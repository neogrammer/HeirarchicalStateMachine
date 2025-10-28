#include "AnimState.h"
#include <stdexcept>
std::function<bool()>* AnimState::getCondFn(anim::StateType type_)
{
	if (condMap.find(type_) == condMap.end())
	{
		throw std::runtime_error("Whoa, anim::stateType does not exist in the condMap!  Bye Felecia!");
	}
	return
}

bool AnimState::checkCondition()
{
	return false;
}

AnimState::AnimState()
	: owner{nullptr}
	, nextState{nullptr}
	, condMap{}
{

}

AnimState::AnimState(Obj* obj_, std::unique_ptr<AnimState>&& nextState_, std::function<bool()> fn_)
	: owner{obj_}
	, nextState{std::move(nextState_)}
	, condMap{}
{
	condMap.clear();
	condMap.emplace(std::pair{ nextState->type, fn_ });

}


AnimState::AnimState(AnimState&& other_) noexcept
	: owner{other_.owner}
	, nextState{std::move(other_.nextState)}
	, condMap{}
{
	condMap.clear();
	for (auto& fnTmp : other_.condMap)
	{
		condMap.emplace(std::pair{ nextState->type, std::move(fnTmp) });
	
	}
}

AnimState& AnimState::operator=(AnimState&& other_) noexcept
{
	this->owner = other_.owner;
	std::shared_ptr<AnimState> tmpState = std::move(other_.nextState);


	this->condMap.clear();
	for (auto& fnTmp : other_.condMap)
	{
		this->condMap.emplace(std::pair{ nextState->type, std::move(fnTmp) });

	}

	return *this;
}

AnimState::~AnimState()
{

}

void AnimState::addPossible(anim::StateType type_, std::function<bool()> fn_)
{
	condMap.insert_or_assign(type_, fn_);
}

anim::StateType AnimState::getType()
{
	return type;
}
