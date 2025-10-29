#pragma once

#include <vector>
#include <stack>
#include <memory>
#include <utility>
#include "anim_machine_helpers.h"

#include "AnimState.h"
class Obj;

class AnimMachine
{
	
	using stateUP = std::unique_ptr<AnimState>;

	std::stack<stateUP> stateStack{};

	anim::CompoundStateType toState{ anim::CompoundStateType::None };

	std::unique_ptr<AnimState> buildState(anim::CompoundStateType stateType_);
	bool facingRight{ true };

	std::string stateToString();

public:
	AnimMachine() = delete;
	AnimMachine(Obj* owner_);
	~AnimMachine();
	void setFacingRight(bool cond_);
	bool getFacingRight();
	std::string getCurrAnim();
	void update(float dt_);
	
};