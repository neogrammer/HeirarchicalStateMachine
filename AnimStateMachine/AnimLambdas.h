#pragma once
#include <functional>
class AnimState;
namespace lmb {
    extern std::function<bool(AnimState& state)> noCondition;
    extern std::function<bool(AnimState& state)> healthDepletedCondition;
    extern std::function<bool(AnimState& state)> wasHitCondition;
    extern std::function<bool(AnimState& state)> isGroundedCondition;
    extern std::function<bool(AnimState& state)> isRisingCondition;
    extern std::function<bool(AnimState& state)> isFallingCondition;



}