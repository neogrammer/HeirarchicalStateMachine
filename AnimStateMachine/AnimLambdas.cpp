#include "AnimLambdas.h"
#include "AnimState.h"
#include "../Obj.h"

std::function<bool(AnimState& state)> lmb::noCondition = [&](AnimState& state) ->bool {
    return false;
    };

std::function<bool(AnimState& state)> lmb::healthDepletedCondition = [&](AnimState& state)->bool {
    if (state.getOwner().getHealth() <= 0)
        return true;
    return false;
    };

std::function<bool(AnimState& state)> lmb::wasHitCondition = [&](AnimState& state)->bool {
    if (state.getOwner().tookAHit())
        return true;
    return false;
    };
