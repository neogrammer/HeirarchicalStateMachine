#include "../all_anim_states.h"
#include "../../all_object_types.h"
#include "../anim_machine_helpers.h"
#include "../../Obj.h"

// never returns on its own, this is for transient state
// sequences that get popped off at the end of the sequence
// may not be needed
#include "../AnimLambdas.h"

IdleState::IdleState()
    : AnimState{}
{
}

IdleState::~IdleState()
{
}

IdleState::IdleState(Obj* obj_)
    : AnimState{ obj_, anim::StateType::Idle }
{
    addPossible(anim::CompoundStateType::Hit, lmb::wasHitCondition);
    addPossible(anim::CompoundStateType::Running, [&](AnimState& state)->bool {
        if (state.getOwner().core->body->vel.x != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    });
}

IdleState::IdleState(IdleState&& other_) noexcept
    : AnimState{static_cast<AnimState&&>(other_)}
{
}

IdleState& IdleState::operator=(IdleState&& other_) noexcept
{
    AnimState* aState;
    aState = std::move(&other_);
    return *(dynamic_cast<IdleState*>(aState));
}
