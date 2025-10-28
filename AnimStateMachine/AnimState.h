#pragma once

#include <stack>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include "anim_machine_helpers.h"
#include <set>

class Obj;
class AnimState
{
	using uniq = std::unique_ptr<AnimState>;

	anim::StateType type{ anim::StateType::None };
	anim::StateType type2{ anim::StateType::None };


	Obj* owner{ nullptr };

	anim::CompoundStateType nextState{ anim::CompoundStateType::None };
	float runTime{ 0.f };
	bool isTransient{ false };
	bool isLastInSequence{ true };
	bool readyToTransition{ false };
	bool popOffOnCleanup{ false };
	std::set<anim::CompoundStateType> possibleStates;
	std::unordered_map<anim::CompoundStateType, std::function<bool(AnimState& state)>> condMap;
	anim::CompoundStateType buildCompoundType(anim::StateType type_, anim::StateType type2_ = anim::StateType::None);
protected:
	std::function<bool(AnimState&)>* getCondFn(anim::CompoundStateType type_);
	bool checkCondition();
	void addPossible(anim::CompoundStateType type_, std::function<bool(AnimState& state)> fn_);
	void transition(anim::StateType type_, anim::StateType type2_ = anim::StateType::None);
public:
	AnimState();
	virtual ~AnimState() = 0;
	AnimState(Obj* obj_, anim::StateType type_, anim::StateType type2_ = anim::StateType::None);
	AnimState(AnimState&& other_) noexcept;
	AnimState& operator=(AnimState&& other_) noexcept;
	AnimState(const AnimState& other_) = delete;
	AnimState& operator=(const AnimState& other_) = delete;

	Obj& getOwner();

	anim::CompoundStateType getCompoundType();
	anim::StateType getType();
	anim::StateType getType2();

	anim::StateType getTypeFromCompound(anim::CompoundStateType cType);
	anim::StateType getType2FromCompound(anim::CompoundStateType cType);

	void update(float dt_);
};

