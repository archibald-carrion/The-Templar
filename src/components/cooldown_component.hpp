//
// Created by joe on 12/3/24.
//

#ifndef COOLDOWN_COMPONENT_HPP
#define COOLDOWN_COMPONENT_HPP

#include <map>
#include <string>
#include <optional>

/**
 * @brief Represents a timing tracer
 *
 */
struct TimingTracer {
    double Counter = 0;
    double TimeLimit = 0;
};

/**
 * @brief Component for managing cooldowns
 *
 */
struct CooldownsComponent {
    TimingTracer Global;
    std::map<std::string, TimingTracer> PlayerActions;
    std::string LastPerformed;

    std::optional<TimingTracer> GlobalBuffer;

    void PerformAction(const std::string& actionName) {
        Global.Counter = 0;

        LastPerformed = actionName;

        if (actionName.empty() || !PlayerActions.contains(actionName)) {
            return;
        }

        auto&[Counter, TimeLimit] = PlayerActions.at(actionName);
        Counter = 0;
    }

    [[nodiscard]] bool CanPerformAction(const std::string& actionName) const {
        const bool globalCan = Global.Counter < 0 || Global.Counter > Global.TimeLimit;

        if (actionName.empty()) {
            return globalCan;
        }

        if (!PlayerActions.contains(actionName) && !actionName.empty()) {
            return false;
        }

        if (actionName.empty()) {
            return globalCan;
        }

        return  globalCan && (PlayerActions.at(actionName).Counter < 0
                          || PlayerActions.at(actionName).Counter > PlayerActions.at(actionName).TimeLimit);
    }
};

#endif //COOLDOWN_COMPONENT_HPP
