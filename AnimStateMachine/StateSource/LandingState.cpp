#include "../all_anim_states.h"

// never returns on its own, this is for transient state
// sequences that get popped off at the end of the sequence
// may not be needed
#include "../AnimLambdas.h"
#include "../../Animator.h"
#include "../../Obj.h"

LandingState::LandingState()
    : AnimState{}
{
}

LandingState::~LandingState()
{
}

LandingState::LandingState(Obj* obj_)
    : AnimState{ obj_, anim::StateType::Landing }
{
    addPossible(anim::CompoundStateType::Hit, lmb::wasHitCondition);
   
    addPossible(anim::CompoundStateType::Running, [&](AnimState& state)->bool {
        
        bool facingRight = state.getOwner().core->animator->getMachine().getFacingRight();

        if (state.getOwner().core->animator->getCurrAnimName() == ((facingRight) ? "Landing_Right" : "Landing_Left") && state.getOwner().core->animator->isOnLastFrame() && (state.getOwner().core->body->grounded != true))
        {
            state.getOwner().core->body->grounded = true;
            if (state.getOwner().core->body->vel.x != 0.f)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
        return false;
        });
    addPossible(anim::CompoundStateType::Idle, [&](AnimState& state)->bool {
        bool facingRight = state.getOwner().core->animator->getMachine().getFacingRight();

        if (state.getOwner().core->animator->getCurrAnimName() == ((facingRight) ? "Landing_Right" : "Landing_Left") && state.getOwner().core->animator->isOnLastFrame() && (state.getOwner().core->body->grounded != true))
        {
            state.getOwner().core->body->grounded = true;
            if (state.getOwner().core->body->vel.x == 0.f)
            {

                return true;
            }
            else
            {
                return false;
            }

        }
        return false;
        });
}

LandingState::LandingState(LandingState&& other_) noexcept
    : AnimState{ static_cast<AnimState&&>(other_) }
{
}

LandingState& LandingState::operator=(LandingState&& other_) noexcept
{
    AnimState* aState;
    aState = std::move(&other_);
    return *(dynamic_cast<LandingState*>(aState));
}
