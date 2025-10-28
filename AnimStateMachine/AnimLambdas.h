#pragma once
#include <functional>
class AnimState;
namespace lmb {
    extern std::function<bool(AnimState& state)> noCondition;
    extern std::function<bool(AnimState& state)> healthDepletedCondition;
    extern std::function<bool(AnimState& state)> wasHitCondition;
}