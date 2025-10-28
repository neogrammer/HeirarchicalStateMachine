#include "../all_anim_states.h"
#include "../../all_object_types.h"
#include "../anim_machine_helpers.h"
#include "../../Obj.h"

// never returns on its own, this is for transient state
// sequences that get popped off at the end of the sequence
// may not be needed
#include "../AnimLambdas.h"

HitState::HitState()
    : AnimState{}
{
}

HitState::~HitState()
{
}

HitState::HitState(Obj* obj_)
    : AnimState{ obj_, anim::StateType::Hit }
{
    addPossible(anim::CompoundStateType::Idle, lmb::noCondition);
    addPossible(anim::CompoundStateType::Falling, lmb::noCondition);
    addPossible(anim::CompoundStateType::Dead, lmb::healthDepletedCondition);
}

HitState::HitState(HitState&& other_) noexcept
    : AnimState{ static_cast<AnimState&&>(other_) }
{

}

HitState& HitState::operator=(HitState&& other_) noexcept
{
    AnimState* aState;
    aState = std::move(&other_);
    return *(dynamic_cast<HitState*>(aState));
}
