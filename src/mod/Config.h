
#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace clange_me {

struct ModConfig {
    int version = 1;

    bool enabled = true;
    std::string message = "Hello from clange_me";

    bool reachVisualizerEnabled = true;
    float visualizerDistance = 3.5f;
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace clange_me

template <>
struct pl::config::Schema<clange_me::ModConfig> {
    static constexpr std::string_view title = "Clange Me Config";
    static constexpr std::string_view description = {};

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};

        if (name == "enabled")
            return {.title = "Enabled"};

        if (name == "message")
            return {.title = "Message"};

        if (name == "reachVisualizerEnabled")
            return {.title = "Reach Visualizer"};

        if (name == "visualizerDistance")
            return {.title = "Visualizer Distance"};

        return {};
    }
};
