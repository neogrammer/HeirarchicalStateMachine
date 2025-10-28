#pragma once

#include <stack>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include "anim_machine_helpers.h"
class Obj;
class AnimState
{
	using uniq = std::unique_ptr<AnimState>;

	anim::StateType type{ anim::StateType::None };

	Obj* owner{ nullptr };

	uniq nextState{ nullptr };

	bool isTransient{ false };

	std::unordered_map<anim::StateType, std::function<bool()>> condMap;
	std::function<bool()>* getCondFn(anim::StateType type_);
	bool checkCondition();

public:
	AnimState();
	AnimState(Obj* obj_, std::unique_ptr<AnimState>&& nextState_ = nullptr, std::function<bool()> fn_);
	AnimState(AnimState&& other_) noexcept;
	AnimState& operator=(AnimState&& other_) noexcept;
	AnimState(const AnimState& other_) = delete;
	AnimState& operator=(AnimState&& other_) = delete;
	virtual ~AnimState() = 0;
	void addPossible(anim::StateType type_, std::function<bool()> fn_);
	anim::StateType getType();
};

