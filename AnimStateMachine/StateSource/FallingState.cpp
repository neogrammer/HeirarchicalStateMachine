#include "../all_anim_states.h"

// never returns on its own, this is for transient state
// sequences that get popped off at the end of the sequence
// may not be needed
#include "../AnimLambdas.h"
#include "../../Animator.h"
#include "../../Obj.h"

FallingState::FallingState()
    : AnimState{}
{
}

FallingState::~FallingState()
{
}

FallingState::FallingState(Obj* obj_)
    : AnimState{ obj_, anim::StateType::Falling }
{
    addPossible(anim::CompoundStateType::Hit, lmb::wasHitCondition);
    addPossible(anim::CompoundStateType::Landing, [&](AnimState& state)->bool {
        bool facingRight = state.getOwner().core->animator->getMachine().getFacingRight();
        if (state.getOwner().core->body->landing && state.getOwner().core->animator->getCurrAnimName() == ((facingRight) ? "Falling_Right" : "Falling_Left"))
        {
            state.getOwner().core->body->landing = false;
            state.getOwner().core->body->grounded = true;

            return true;
        }
        return false;
        });
}

FallingState::FallingState(FallingState&& other_) noexcept
    : AnimState{ static_cast<AnimState&&>(other_) }
{
}

FallingState& FallingState::operator=(FallingState&& other_) noexcept
{
    AnimState* aState;
    aState = std::move(&other_);
    return *(dynamic_cast<FallingState*>(aState));
}
