#ifndef PLAYERANIMFSM_H__
#define PLAYERANIMFSM_H__
#include <optional>
#include <type_traits>
#include <variant>
#include <iostream>
#include <FSM/Events.h>
#include <FSM/FSM.h>


class FSM_Player : public FSM<FSM_Player, PlayerAnimVar>
{
public:
	FSM_Player() { state_ = IdleState{}; }

	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedMoving& e) { std::cout << "StartedMoving" << std::endl; return StartedMovingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventStartedShooting& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventJumped& e) { std::cout << "Jumping" << std::endl; return JumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventTransEnd& e) { std::cout << "Moving" << std::endl; return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventStartedShooting& e) { std::cout << "StartedMovingAndShooting" << std::endl; return StartedMovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }

	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStoppedMoving& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventJumped& e) { std::cout << "Jumping" << std::endl; return JumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingState& s, const EventStartedShooting& e) { std::cout << "MovingAndShooting" << std::endl; return MovingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "StartedMoving" << std::endl; return StartedMovingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventJumped& e) { std::cout << "JumpingAndShooting" << std::endl; return JumpingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(StartedMovingAndShootingState& s, const EventStartedShooting& e) { std::cout << "FallingAndShooting" << std::endl; return MovingAndShootingState{}; }


	//4
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStoppedMoving& e) { std::cout << "Shooting" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Moving" << std::endl; return MovingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventJumped& e) { std::cout << "JumpingAndShooting" << std::endl; return JumpingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(MovingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(JumpingState& s, const EventFell& e) { std::cout << "Falling" << std::endl; return FallingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingState& s, const EventStartedShooting& e) { std::cout << "JumpingAndShooting" << std::endl; return JumpingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventLanded& e) { std::cout << "Landing" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingState& s, const EventStartedShooting& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventStartedShooting& e) { std::cout << "LandingAndShooting" << std::endl; return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventTransEnd& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingState& s, const EventStartedMoving& e) { std::cout << "Moving" << std::endl; return MovingState{}; }

	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStoppedShooting& e) { std::cout << "Idle" << std::endl; return IdleState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventStartedMoving& e) { std::cout << "MovingAndShooting" << std::endl; return MovingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(ShootingState& s, const EventJumped& e) { std::cout << "JumpingAndShooting" << std::endl; return JumpingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(JumpingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingAndShootingState& s, const EventStoppedShooting & e) { std::cout << "Jumping" << std::endl; return JumpingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingAndShootingState& s, const EventFell& e) { std::cout << "FallingAndShooting" << std::endl; return FallingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(JumpingAndShootingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	//10
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventLanded& e) { std::cout << "LandingAndShooting" << std::endl; return LandingAndShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(FallingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Jumping" << std::endl; return FallingState{}; }



	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventHit& e) { std::cout << "Hit" << std::endl; return HitState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventDied& e) { std::cout << "Dying" << std::endl; return DyingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventTransEnd& e) { std::cout << "Idle" << std::endl; return ShootingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventStoppedShooting& e) { std::cout << "Landing" << std::endl; return LandingState{}; }
	std::optional<PlayerAnimVar> On_Event(LandingAndShootingState& s, const EventStartedMoving& e) { std::cout << "MovingAndShooting" << std::endl; return MovingAndShootingState{}; }

	std::optional<PlayerAnimVar> On_Event(HitState& s, const EventRecovered& e) { std::cout << "Idle" << std::endl; return IdleState{}; }

	std::optional<PlayerAnimVar> On_Event(DyingState& s, const EventTransEnd& e) { std::cout << "Dead" << std::endl; return DeadState{}; }


	template<typename State, typename Event>
	std::optional<PlayerAnimVar> On_Event(State&, const Event&)
	{
		return std::nullopt;     // ignore
	}

};
#endif