#include "../all_anim_states.h"
#include "../../all_object_types.h"
#include "../anim_machine_helpers.h"
#include "../../Obj.h"

// never returns on its own, this is for transient state
// sequences that get popped off at the end of the sequence
// may not be needed
#include "../AnimLambdas.h"

RunningState::RunningState()
{
}

RunningState::~RunningState()
{
}

RunningState::RunningState(Obj* obj_)
    : AnimState{ obj_, anim::StateType::Running }
{
    addPossible(anim::CompoundStateType::Hit, lmb::wasHitCondition);
    addPossible(anim::CompoundStateType::Idle, [&](AnimState& state)->bool {
        return (std::fabsf(state.getOwner().core->body->vel.x) == 0.f);
    });

}

RunningState::RunningState(RunningState&& other_) noexcept
    : AnimState{ static_cast<AnimState&&>(other_) }
{
}

RunningState& RunningState::operator=(RunningState&& other_) noexcept
{
    AnimState* aState;
    aState = std::move(&other_);
    return *(dynamic_cast<RunningState*>(aState));
}
