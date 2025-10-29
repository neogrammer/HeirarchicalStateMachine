#pragma once
#include "AnimState.h"

class HitState : public AnimState
{
public:
	HitState();
	~HitState() override final;

	HitState(Obj* obj_);
	HitState(HitState&& other_) noexcept;
	HitState& operator=(HitState&& other_) noexcept;
	HitState(const HitState& other_) = delete;
	HitState& operator=(const HitState& other_) = delete;

};

class DeadState : public AnimState
{
public:
	DeadState();
	~DeadState() override final;

	DeadState(Obj* obj_);
	DeadState(DeadState&& other_) noexcept;
	DeadState& operator=(DeadState&& other_) noexcept;
	DeadState(const DeadState& other_) = delete;
	DeadState& operator=(const DeadState& other_) = delete;

};

class IdleState : public AnimState
{
public:
	IdleState();
	~IdleState() override final;

	IdleState(Obj* obj_);
	IdleState(IdleState&& other_) noexcept;
	IdleState& operator=(IdleState&& other_) noexcept;
	IdleState(const IdleState& other_) = delete;
	IdleState& operator=(const IdleState& other_) = delete;

};


class RunningState : public AnimState
{
public:
	RunningState();
	~RunningState() override final;

	RunningState(Obj* obj_);
	RunningState(RunningState&& other_) noexcept;
	RunningState& operator=(RunningState&& other_) noexcept;
	RunningState(const RunningState& other_) = delete;
	RunningState& operator=(const RunningState& other_) = delete;


};