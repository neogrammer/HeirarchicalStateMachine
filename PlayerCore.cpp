#include "PlayerCore.h"
#include "Cfg.h"

#include "Obj.h"
#include "AnimStateMachine/all_anim_states.h"

PlayerCore::PlayerCore(Obj* owner_)
{
	animator = std::make_unique<Animator>(owner_);
	AssignAnimations(Cfg::textures.get(Cfg::Textures::PlayerAtlas));
	input = std::make_unique<Input>(input::SourceType::Controlled);
	body = std::make_unique<Body>(sf::Vector2f{ 800.f,450.f }, sf::Vector2f{ 130.f,160.f }, sf::Vector2i{ 0,0 }, false);
}

PlayerCore::~PlayerCore() {}

void PlayerCore::AssignAnimations(sf::Texture& tex_)
{
	// Teleport in and teleport land
	animator->addAnimation(tex_, "TeleportIn_Right", 1, { 130,160 }, { 130 * 0,160 * 0 }, 0.07f, true );
	animator->addAnimation(tex_, "TeleportIn_Left", 1, { 130,160 }, { 130 * 0,160 * 13 }, 0.07f, true );
	animator->addAnimation(tex_, "TeleportLand_Right", 16, { 130,160 }, { 130 * 1,160 * 0 }, 0.07f, false, 1.f, "Idle_Right");
	animator->addAnimation(tex_, "TeleportLand_Left", 16, { 130,160 }, { 130 * 1,160 * 13 }, 0.07f, false, 1.f, "Idle_Left");

	// Idle and Blink
	animator->addAnimation(tex_, "Idle_Right", 3, { 130,160 }, { 0,160 }, .6f, true, 2.f);
	animator->addAnimation(tex_, "Idle_Left", 3, { 130,160 }, { 0,14*160 }, .6f, true, 2.f);
	animator->addAnimation(tex_, "Blink_Right", 3, { 130,160 }, { 130 * 4,160 * 1 }, 0.07f, false, 0.4f, "Idle_Right");
	animator->addAnimation(tex_, "Blink_Left", 3, { 130,160 }, { 130 * 4,160 * 15 }, 0.07f, false, 0.4f, "Idle_Left" );

	// ReadyShot and Shoot
	animator->addAnimation(tex_, "ReadyShot_Right", 2, { 130,160 }, { 130 * 8,160 * 1 }, 0.07f, false, 0.f, "Shooting_Right");
	animator->addAnimation(tex_, "ReadyShot_Left", 2, { 130,160 }, { 130 * 8,160 * 14 }, 0.07f, false, 0.f, "Shooting_Left");
	animator->addAnimation(tex_, "Shooting_Right", 1, { 130,160 }, { 130 * 12,160 * 1 }, 0.07f, true );
	animator->addAnimation(tex_, "Shooting_Left", 1, { 130,160 }, { 130 * 12,160 * 14 }, 0.07f, true );

	// StartRun and Running, StartRunAndShooting and RunningAndShooting,  StartRunAndCharging and RunningAndCharging
	animator->addAnimation(tex_, "StartingRun_Right", 2, { 130,160 }, { 130 * 0,160 * 2 }, 0.07f, false, 0.f, "Running_Right");
	animator->addAnimation(tex_, "StartingRun_Left", 2, { 130,160 }, { 130 * 0,160 * 15 }, 0.07f, false, 0.f, "Running_Left");
	animator->addAnimation(tex_, "Running_Right", 10, { 130,160 }, { 130 * 2,160 * 2 }, 0.07f, true);
	animator->addAnimation(tex_, "Running_Left", 10, { 130,160 }, { 130 * 2,160 * 15 }, 0.07f, true);
	animator->addAnimation(tex_, "StartingRunAndShooting_Right", 2, { 130,160 }, { 130 * 0,160 * 3 }, 0.07f,false, 0.f, "RunningAndShooting_Right");
	animator->addAnimation(tex_, "StartingRunAndShooting_Left", 2, { 130,160 }, { 130 * 0,160 * 16 }, 0.07f,false, 0.f, "RunningAndShooting_Left");
	animator->addAnimation(tex_, "RunningAndShooting_Right", 10, { 130,160 }, { 130 * 2,160 * 3 }, 0.07f, true );
	animator->addAnimation(tex_, "RunningAndShooting_Left", 10, { 130,160 }, { 130 * 2,160 * 16 }, 0.07f, true );
	animator->addAnimation(tex_, "StartingRunAndCharging_Right", 2, { 130,160 }, { 130 * 0,160 * 4 }, 0.07f, false, 0.f, "RunningAndCharging_Right");
	animator->addAnimation(tex_, "StartingRunAndCharging_Left", 2, { 130,160 }, { 130 * 0,160 * 17 }, 0.07f, false, 0.f, "RunningAndChargine_Left");
	animator->addAnimation(tex_, "RunningAndCharging_Right", 10, { 130,160 }, { 130 * 2,160 * 4 }, 0.07f, true);
	animator->addAnimation(tex_, "RunningAndCharging_Left", 10, { 130,160 }, { 130 * 2,160 * 17 }, 0.07f, true);

	// Crouch, CrouchAndShooting, CrouchAndCharging
	animator->addAnimation(tex_, "Crouching_Right", 1, { 130,160 }, { 130 * 15,160 * 2 }, 0.07f, true );
	animator->addAnimation(tex_, "Crouching_Left", 1, { 130,160 }, { 130 * 15,160 * 15 }, 0.07f, true);
	animator->addAnimation(tex_, "CrouchingAndShooting_Right", 1, { 130,160 }, { 130 * 15,160 * 3 }, 0.07f, true);
	animator->addAnimation(tex_, "CrouchingAndShooting_Left", 1, { 130,160 }, { 130 * 15,160 * 16 }, 0.07f, true);
	animator->addAnimation(tex_, "CrouchingAndCharging_Right", 1, { 130,160 }, { 130 * 15,160 * 4 }, 0.07f, true);
	animator->addAnimation(tex_, "CrouchingAndCharging_Left", 1, { 130,160 }, { 130 * 15,160 * 17 }, 0.07f, true);

	// LiftingOff, NearingPeak, LeavingPeak, Falling, and Landing
	animator->addAnimation(tex_, "LiftingOff_Right", 4, { 130,160 }, { 130 * 0,160 * 5 }, 0.07f, false, 0.f );
	animator->addAnimation(tex_, "LiftingOff_Left", 4, { 130,160 }, { 130 * 0,160 * 18 }, 0.07f, false);
	animator->addAnimation(tex_, "NearingPeak_Right", 1, { 130,160 }, { 130 * 4,160 * 5 }, 0.07f );
	animator->addAnimation(tex_, "NearingPeak_Left", 1, { 130,160 }, { 130 * 4,160 * 18 }, 0.07f );
	animator->addAnimation(tex_, "LeavingPeak_Right", 1, { 130,160 }, { 130 * 5,160 * 5 }, 0.07f );
	animator->addAnimation(tex_, "LeavingPeak_Left", 1, { 130,160 }, { 130 * 5,160 * 18 }, 0.07f );
	animator->addAnimation(tex_, "Falling_Right", 2, { 130,160 }, { 130 * 6,160 * 5 }, 0.07f );
	animator->addAnimation(tex_, "Falling_Left", 2, { 130,160 }, { 130 * 6,160 * 18 }, 0.07f );
	animator->addAnimation(tex_, "Landing_Right", 3, { 130,160 }, { 130 * 8,160 * 5 }, 0.07f, false, 0.f, "Idle_Right");
	animator->addAnimation(tex_, "Landing_Left", 3, { 130,160 }, { 130 * 8,160 * 18 }, 0.07f, false, 0.f, "Idle_Left");

	// LiftingOffAndShooting, NearingPeakAndShooting, LeavingPeakAndShooting, FallingAndShooting, and LandingAndShooting
	animator->addAnimation(tex_, "LiftingOffAndShooting_Right", 4, { 130,160 }, { 130 * 0,160 * 6 }, 0.07f );
	animator->addAnimation(tex_, "LiftingOffAndShooting_Left", 4, { 130,160 }, { 130 * 0,160 * 19 }, 0.07f );
	animator->addAnimation(tex_, "NearingPeakAndShooting_Right", 1, { 130,160 }, { 130 * 4,160 * 6 }, 0.07f );
	animator->addAnimation(tex_, "NearingPeakAndShooting_Left", 1, { 130,160 }, { 130 * 4,160 * 19 }, 0.07f );
	animator->addAnimation(tex_, "LeavingPeakAndShooting_Right", 1, { 130,160 }, { 130 * 5,160 * 6 }, 0.07f );
	animator->addAnimation(tex_, "LeavingPeakAndShooting_Left", 1, { 130,160 }, { 130 * 5,160 * 19 }, 0.07f );
	animator->addAnimation(tex_, "FallingAndShooting_Right", 2, { 130,160 }, { 130 * 6,160 * 6 }, 0.07f );
	animator->addAnimation(tex_, "FallingAndShooting_Left", 2, { 130,160 }, { 130 * 6,160 * 19 }, 0.07f );
	animator->addAnimation(tex_, "LandingAndShooting_Right", 3, { 130,160 }, { 130 * 8,160 * 6 }, 0.07f, false, 0.f, "Shooting_Right");
	animator->addAnimation(tex_, "LandingAndShooting_Left", 3, { 130,160 }, { 130 * 8,160 * 19 }, 0.07f, false, 0.f, "Shooting_Left");

	// LiftingOffAndCharging, NearingPeakAndCharging, LeavingPeakAndCharging, FallingAndCharging, and LandingAndCharging
	animator->addAnimation(tex_, "LiftingOffAndCharging_Right", 4, { 130,160 }, { 130 * 0,160 * 7 }, 0.07f );
	animator->addAnimation(tex_, "LiftingOffAndCharging_Left", 4, { 130,160 }, { 130 * 0,160 * 20 }, 0.07f );
	animator->addAnimation(tex_, "NearingPeakAndCharging_Right", 1, { 130,160 }, { 130 * 0,160 * 7 }, 0.07f );
	animator->addAnimation(tex_, "NearingPeakAndCharging_Left", 1, { 130,160 }, { 130 * 0,160 * 20 }, 0.07f );
	animator->addAnimation(tex_, "LeavingPeakAndCharging_Right", 1, { 130,160 }, { 130 * 0,160 * 7 }, 0.07f );
	animator->addAnimation(tex_, "LeavingPeakAndCharging_Left", 1, { 130,160 }, { 130 * 0,160 * 20 }, 0.07f );
	animator->addAnimation(tex_, "FallingAndCharging_Right", 2, { 130,160 }, { 130 * 0,160 * 7 }, 0.07f );
	animator->addAnimation(tex_, "FallingAndCharging_Left", 2, { 130,160 }, { 130 * 0,160 * 20 }, 0.07f );
	animator->addAnimation(tex_, "LandingAndCharging_Right", 3, { 130,160 }, { 130 * 0,160 * 7 }, 0.07f, false, 0.f, "Shooting_Right");
	animator->addAnimation(tex_, "LandingAndCharging_Left", 3, { 130,160 }, { 130 * 0,160 * 20 }, 0.07f, false, 0.f, "Shooting_Left");

	// ChargeShot and SuperChargeShot
	animator->addAnimation(tex_, "ChargeShot_Right", 6, { 130,160 }, { 130 * 0,160 * 8 }, 0.07f,false, 0.3f,"Idle_Right");
	animator->addAnimation(tex_, "ChargeShot_Left", 6, { 130,160 }, { 130 * 0,160 * 21 }, 0.07f, false, 0.3f, "Idle_Left");
	animator->addAnimation(tex_, "SuperChargeShot_Right", 10, { 130,160 }, { 130 * 0,160 * 9 }, 0.07f, false, 0.3f, "Idle_Right");
	animator->addAnimation(tex_, "SuperChargeShot_Left", 10, { 130,160 }, { 130 * 0,160 * 22 }, 0.07f, false, 0.3f, "Idle_Left");

	// TakeHit and Die
	animator->addAnimation(tex_, "TakeHit_Right", 7, { 130,160 }, { 130 * 10,160 * 10 }, 0.07f, true);
	animator->addAnimation(tex_, "TakeHit_Left", 7, { 130,160 }, { 130 * 10,160 * 23 }, 0.07f, true );
	animator->addAnimation(tex_, "Die_Right", 5, { 130,160 }, { 130 * 10,160 * 11 }, 0.07f, false, 1.3f);
	animator->addAnimation(tex_, "Die_Left", 5, { 130,160 }, { 130 * 10,160 * 24 }, 0.07f, false, 1.3f);

	// SlideWall, SlideWallAndShooting, SlideWallAndCharging
	animator->addAnimation(tex_, "SlideWall_Right", 2, { 130,160 }, { 130 * 0,160 * 12 }, 0.07f, true);
	animator->addAnimation(tex_, "SlideWall_Left", 2, { 130,160 }, { 130 * 0,160 * 25 }, 0.07f,true );
	animator->addAnimation(tex_, "SlideWallAndShooting_Right", 2, { 130,160 }, { 130 * 0,160 * 13 }, 0.07f,true );
	animator->addAnimation(tex_, "SlideWallAndShooting_Left", 2, { 130,160 }, { 130 * 0,160 * 26 }, 0.07f,true );
	animator->addAnimation(tex_, "SlideWallAndCharging_Right", 2, { 130,160 }, { 130 * 0,160 * 14 }, 0.07f,true );
	animator->addAnimation(tex_, "SlideWallAndCharging_Left", 2, { 130,160 }, { 130 * 0,160 * 27 }, 0.07f,true );

	//RidingZip, RidingZipAndShooting, RidingZipAndCharging
	animator->addAnimation(tex_, "RidingZip_Right", 1, { 130,160 }, { 130 * 3,160 * 12 }, 0.07f, true);
	animator->addAnimation(tex_, "RidingZip_Left", 1, { 130,160 }, { 130 * 3,160 * 25 }, 0.07f, true);
	animator->addAnimation(tex_, "RidingZipAndShooting_Right", 1, { 130,160 }, { 130 * 3,160 * 13 }, 0.07f, true);
	animator->addAnimation(tex_, "RidingZipAndShooting_Left", 1, { 130,160 }, { 130 * 3,160 * 26 }, 0.07f, true);
	animator->addAnimation(tex_, "RidingZipAndCharging_Right", 1, { 130,160 }, { 130 * 3,160 * 14 }, 0.07f, true);
	animator->addAnimation(tex_, "RidingZipAndCharging_Left", 1, { 130,160 }, { 130 * 3,160 * 27 }, 0.07f, true);

	// KickWall, KickWallAndShooting, KickWallAndCharging
	animator->addAnimation(tex_, "KickWall_Right", 1, { 130,160 }, { 130 * 5,160 * 12 }, 0.07f, false, 0.3f, "NearingPeak_Right");
	animator->addAnimation(tex_, "KickWall_Left", 1, { 130,160 }, { 130 * 5,160 * 25 }, 0.07f, false, 0.3f, "NearingPeak_Left");
	animator->addAnimation(tex_, "KickWallAndShooting_Right", 1, { 130,160 }, { 130 * 5,160 * 13 }, 0.07f, false, 0.3f, "NearingPeakAndShooting_Right");
	animator->addAnimation(tex_, "KickWallAndShooting_Left", 1, { 130,160 }, { 130 * 5,160 * 26 }, 0.07f, false, 0.3f, "NearingPeakAndShooting_Left");
	animator->addAnimation(tex_, "KickWallAndCharging_Right", 1, { 130,160 }, { 130 * 5,160 * 14 }, 0.07f, false, 0.3f, "NearingPeakAndCharging_Right");
	animator->addAnimation(tex_, "KickWallAndCharging_Left", 1, { 130,160 }, { 130 * 5,160 * 27 }, 0.07f, false, 0.3f, "NearingPeakAndCharging_Left");



	animator->setAnimation("Idle_Right");
}
