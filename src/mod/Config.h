
#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace clange_me {

struct ModConfig {
    int version = 1;
    bool enabled = true;
    std::string message = "Hello from clange_me";

    bool showReachVisualizer = true;
    float visualizerDistance = 3.0f;
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace clange_me

template <> struct pl::config::Schema<clange_me::ModConfig> {
    static constexpr std::string_view title = "Clange Me Config";
    static constexpr std::string_view description = {};

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};

        if (name == "enabled")
            return {.title = "Enabled", .description = "Turns clange_me behavior on or off."};

        if (name == "message")
            return {.title = "Message", .description = "Message written when the mod is enabled."};

        if (name == "showReachVisualizer")
            return {.title = "Show Reach Visualizer", .description = "Enables the visual reach indicator."};

        if (name == "visualizerDistance")
            return {.title = "Visualizer Distance", .description = "Distance displayed by the visualizer."};

        return {};
    }
};
