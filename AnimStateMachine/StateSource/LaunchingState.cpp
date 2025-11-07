#include "../all_anim_states.h"

// never returns on its own, this is for transient state
// sequences that get popped off at the end of the sequence
// may not be needed
#include "../AnimLambdas.h"
#include "../../Animator.h"
#include "../../Obj.h"

LaunchingState::LaunchingState()
    : AnimState{}
{
}

LaunchingState::~LaunchingState()
{
}

LaunchingState::LaunchingState(Obj* obj_)
    : AnimState{ obj_, anim::StateType::Launching }
{
    addPossible(anim::CompoundStateType::Hit, lmb::wasHitCondition);
    addPossible(anim::CompoundStateType::Rising, [&](AnimState& state)->bool {
        bool facingRight = state.getOwner().core->animator->getMachine().getFacingRight();
        if (state.getOwner().core->animator->isOnLastFrame() && state.getOwner().core->animator->getCurrAnimName() == ((facingRight) ? "Launching_Right" : "Launching_Left"))
        {
           // state.getOwner().core->body->impulse({ 0.f,-6000.f });
            return true;
        }
        else
        {   
            return false;
        }
        });
}

LaunchingState::LaunchingState(LaunchingState&& other_) noexcept
    : AnimState{ static_cast<AnimState&&>(other_) }
{
}

LaunchingState& LaunchingState::operator=(LaunchingState&& other_) noexcept
{
    AnimState* aState;
    aState = std::move(&other_);
    return *(dynamic_cast<LaunchingState*>(aState));
}
