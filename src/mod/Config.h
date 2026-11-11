
#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace clange_me {

struct ModConfig {
    int version = 1;

    bool enabled = true;
    std::string message = "Clange Aim Assist";

    bool aimTrainerEnabled = true;
    bool targetVisualizerEnabled = true;

    float visualizerDistance = 3.5f;
    int reactionTimeGoal = 500;
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace clange_me

template <>
struct pl::config::Schema<clange_me::ModConfig> {
    static constexpr std::string_view title = "Clange Aim Assist";
    static constexpr std::string_view description = {};

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};

        if (name == "enabled")
            return {.title = "Enabled"};

        if (name == "message")
            return {.title = "Message"};

        if (name == "aimTrainerEnabled")
            return {.title = "Aim Trainer"};

        if (name == "targetVisualizerEnabled")
            return {.title = "Target Visualizer"};

        if (name == "visualizerDistance")
            return {.title = "Visualizer Distance"};

        if (name == "reactionTimeGoal")
            return {.title = "Reaction Time Goal"};

        return {};
    }
};
