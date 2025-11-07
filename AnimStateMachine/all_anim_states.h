#pragma once
#include "AnimState.h"
class Animator;
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

class LaunchingState : public AnimState
{
public:
	LaunchingState();
	~LaunchingState() override final;

	LaunchingState(Obj* obj_);
	LaunchingState(LaunchingState&& other_) noexcept;
	LaunchingState& operator=(LaunchingState&& other_) noexcept;
	LaunchingState(const LaunchingState& other_) = delete;
	LaunchingState& operator=(const LaunchingState& other_) = delete;


};


class RisingState : public AnimState
{
public:
	RisingState();
	~RisingState() override final;

	RisingState(Obj* obj_);
	RisingState(RisingState&& other_) noexcept;
	RisingState& operator=(RisingState&& other_) noexcept;
	RisingState(const RisingState& other_) = delete;
	RisingState& operator=(const RisingState& other_) = delete;


};

class FallingState : public AnimState
{
public:
	FallingState();
	~FallingState() override final;

	FallingState(Obj* obj_);
	FallingState(FallingState&& other_) noexcept;
	FallingState& operator=(FallingState&& other_) noexcept;
	FallingState(const FallingState& other_) = delete;
	FallingState& operator=(const FallingState& other_) = delete;


};

class LandingState : public AnimState
{
public:
	LandingState();
	~LandingState() override final;

	LandingState(Obj* obj_);
	LandingState(LandingState&& other_) noexcept;
	LandingState& operator=(LandingState&& other_) noexcept;
	LandingState(const LandingState& other_) = delete;
	LandingState& operator=(const LandingState& other_) = delete;


};