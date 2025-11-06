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
        
        if (state.getOwner().core->body->grounded && state.getOwner().core->animator->isOnLastFrame())
        {
            if (state.getOwner().core->body->vel.x != 0.f)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
        });
    addPossible(anim::CompoundStateType::Idle, [&](AnimState& state)->bool {

        if (state.getOwner().core->body->grounded && state.getOwner().core->animator->isOnLastFrame())
        {
            if (state.getOwner().core->body->vel.x == 0.f)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
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
