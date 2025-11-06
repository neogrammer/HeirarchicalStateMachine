#include "../all_anim_states.h"

// never returns on its own, this is for transient state
// sequences that get popped off at the end of the sequence
// may not be needed
#include "../AnimLambdas.h"

#include "../../Obj.h"

RisingState::RisingState()
    : AnimState{}
{
}

RisingState::~RisingState()
{
}

RisingState::RisingState(Obj* obj_)
    : AnimState{ obj_, anim::StateType::Rising }
{
    addPossible(anim::CompoundStateType::Hit, lmb::wasHitCondition);
    addPossible(anim::CompoundStateType::Falling, [&](AnimState& state)->bool {
        if (state.getOwner().core->body->vel.y >= 0.f)
        {
            return true;
        }
        else
        {
            return false;
        }
        });
}

RisingState::RisingState(RisingState&& other_) noexcept
    : AnimState{ static_cast<AnimState&&>(other_) }
{
}

RisingState& RisingState::operator=(RisingState&& other_) noexcept
{
    AnimState* aState;
    aState = std::move(&other_);
    return *(dynamic_cast<RisingState*>(aState));
}
