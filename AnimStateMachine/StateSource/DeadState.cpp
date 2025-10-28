#include "../all_anim_states.h"
#include "../../all_object_types.h"
#include "../anim_machine_helpers.h"
#include "../../Obj.h"

// never returns on its own, this is for transient state
// sequences that get popped off at the end of the sequence
// may not be needed
#include "../AnimLambdas.h"


DeadState::DeadState()
{
}

DeadState::~DeadState()
{
}

DeadState::DeadState(Obj* obj_)
    : AnimState{ obj_, anim::StateType::Dead }
{
}


DeadState::DeadState(DeadState&& other_) noexcept
    : AnimState{ static_cast<AnimState&&>(other_) }
{
}

DeadState& DeadState::operator=(DeadState&& other_) noexcept
{
    AnimState* aState;
    aState = std::move(&other_);
    return *(dynamic_cast<DeadState*>(aState));
}
