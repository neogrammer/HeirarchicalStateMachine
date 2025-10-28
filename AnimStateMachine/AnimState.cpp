#include "AnimState.h"
#include <stdexcept>
#include "../Obj.h"
#include "all_anim_states.h"

auto noCondition = [&](AnimState& state) ->bool {
	return false;
	};


std::function<bool(AnimState&)>* AnimState::getCondFn(anim::CompoundStateType type_)
{
	if (condMap.find(type_) == condMap.end())
	{
		throw std::runtime_error("Whoa, anim::stateType does not exist in the condMap!  Bye Felecia!");
	}
	return &condMap.at(type_);
}

bool AnimState::checkCondition()
{
	return false;
}

AnimState::AnimState()
	: type{ anim::StateType::None }
	, owner{ nullptr }
, nextState{ anim::CompoundStateType::None }
	, isTransient{false}
	, isLastInSequence{true}
	, readyToTransition{false}
	, popOffOnCleanup{false}
	, possibleStates{}
	, condMap{}
{

}

AnimState::AnimState(Obj* obj_, anim::StateType type_, anim::StateType type_2)
	: type{type_}
	, type2{type_2}
	, owner{obj_}
	, nextState{ anim::CompoundStateType::None }
	, isTransient{false}
	, isLastInSequence{true}
	, readyToTransition{ false }
	, popOffOnCleanup{ false }
	, possibleStates{}
	, condMap{}
{
	condMap.clear();
	possibleStates.clear();
}


AnimState::AnimState(AnimState&& other_) noexcept
	: type{ other_.type }
	, type2{ other_.type2 }
	, owner{ other_.owner }
	, nextState{other_.nextState }
	, isTransient{ other_.isTransient }
	, isLastInSequence{ other_.isLastInSequence }
	, readyToTransition{ other_.readyToTransition }
	, popOffOnCleanup{ other_.popOffOnCleanup }
	, possibleStates{}
	, condMap{}
{
	possibleStates.clear();


	condMap.clear();
	for (auto& fnTmp : other_.condMap)
	{
		possibleStates.emplace(fnTmp.first);
		condMap.emplace(std::pair{ fnTmp.first, std::move(fnTmp.second) });
	
	}
}

AnimState& AnimState::operator=(AnimState&& other_) noexcept
{
	this->type= other_.type ;
	this->type2= other_.type2 ;
	this->owner= other_.owner ;
	this->nextState=other_.nextState ;
	this->isTransient= other_.isTransient ;
	this->isLastInSequence= other_.isLastInSequence ;
	this->readyToTransition= other_.readyToTransition ;
	this->popOffOnCleanup= other_.popOffOnCleanup ;
	this->possibleStates.clear();
	this->condMap.clear();

	for (auto& fnTmp : other_.condMap)
	{
		this->possibleStates.emplace(fnTmp.first);
		this->condMap.emplace(std::pair{ fnTmp.first, std::move(fnTmp.second) });

	}

	return *this;
}

Obj& AnimState::getOwner()
{
	// if owner does not exist, throw the fuck out this program
	if (owner == nullptr)
	{
		throw std::runtime_error("Whoa nelly!  An anim state has no owner");
	}
	else
	{
		return *owner;
	}
}

AnimState::~AnimState()
{
	owner = nullptr;
	this->possibleStates.clear();
	this->condMap.clear();
}

void AnimState::addPossible(anim::CompoundStateType type_, std::function<bool(AnimState& state)> fn_)
{
	condMap.insert_or_assign(type_, fn_);
	possibleStates.emplace(type_);
}

anim::CompoundStateType AnimState::buildCompoundType(anim::StateType type_, anim::StateType type2_)
{
	using c = anim::CompoundStateType;
	using t = anim::StateType;

	anim::CompoundStateType tmp{ anim::CompoundStateType::Idle };
	
	if (type2_ == anim::StateType::None)
	{

		switch (type_)
		{
		case t::Idle: { tmp = c::Idle; break; }
		case t::Running: { tmp = c::Running; break; }
		case t::Hit: { tmp = c::Hit; break; }
		case t::Dead: { tmp = c::Dead; break; }
		default:break;
		}

	}
	else
	{
		//  if (type_ == t::Running && type2_ == t::Shooting) tmp = c::RunningAndshooting;
	}


	return tmp;
}

void AnimState::transition(anim::StateType type_, anim::StateType type2_)
{
	if (owner == nullptr)
	{
		throw std::runtime_error("Whoa nelly!  An anim state has no owner");
	}

	//top priority
	if ((possibleStates.find(anim::CompoundStateType::Hit) != possibleStates.end()) && (type_ == anim::StateType::Hit))
	{
		nextState = anim::CompoundStateType::Hit;
		readyToTransition = true;
		if (isTransient) popOffOnCleanup = true;
		return;
	}
	if ((possibleStates.find(anim::CompoundStateType::Dead) != possibleStates.end()) && (type_ == anim::StateType::Dead))
	{ 
		nextState = anim::CompoundStateType::Dead;
		readyToTransition = true;
		if (isTransient) popOffOnCleanup = true;
		return;
	}

	nextState = buildCompoundType(type_, type2_);
}

anim::CompoundStateType AnimState::getCompoundType()
{
	return buildCompoundType(type, type2);
}

anim::StateType AnimState::getType()
{
	return type;
}

anim::StateType AnimState::getType2()
{
	return type2;
}

anim::StateType AnimState::getTypeFromCompound(anim::CompoundStateType cType)
{
	using t = anim::StateType;
	using c = anim::CompoundStateType;

	switch (cType)
	{
	case c::Idle: { return t::Idle; break; }
	case c::Running: { return t::Running; break; }
	case c::Hit: { return t::Hit; break; }
	case c::Dead: { return t::Dead; break; }
	default: { return t::None; break; }
	}
}

anim::StateType AnimState::getType2FromCompound(anim::CompoundStateType cType)
{
	using t = anim::StateType;
	using c = anim::CompoundStateType;

	return t::None;

	/*switch (cType)
	{
	default: { return t::None; break; }
	}*/
}



void AnimState::update(float dt_)
{
	if (!owner)
	{
		throw std::runtime_error("No animState owner");
	}

	for (auto possible : possibleStates)
	{
		if (condMap.at(possible)(*this) == true)
		{
			transition(getTypeFromCompound(possible), getType2FromCompound(possible));
		}
	}
}