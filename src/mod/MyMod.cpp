
#include "mod/MyMod.h"

#include <filesystem>

#include <pl/Mod.hpp>

namespace clange_me {

ClangeMeMod &ClangeMeMod::instance() {
    static ClangeMeMod instance;
    return instance;
}

ClangeMeMod::ClangeMeMod()
    : mSelf(*ll::mod::NativeMod::current()) {}

bool ClangeMeMod::load() {
    auto &self = getSelf();

    self.getLogger().debug("Loading...");

    std::error_code ec;

    std::filesystem::create_directories(self.getDataDir(), ec);
    if (ec) {
        self.getLogger().error(
            "Failed to create data directory {}: {}",
            self.getDataDir().string(),
            ec.message()
        );
        return false;
    }

    std::filesystem::create_directories(self.getConfigDir(), ec);
    if (ec) {
        self.getLogger().error(
            "Failed to create config directory {}: {}",
            self.getConfigDir().string(),
            ec.message()
        );
        return false;
    }

    mConfigFile.emplace();

    if (!mConfigFile->load()) {
        self.getLogger().warn("Failed to load typed config");
        return false;
    }

    mConfig = mConfigFile->value();

    self.getLogger().info(
        "Aim Trainer: {}",
        mConfig.aimTrainerEnabled ? "Enabled" : "Disabled"
    );

    self.getLogger().info(
        "Target Visualizer: {}",
        mConfig.targetVisualizerEnabled ? "Enabled" : "Disabled"
    );

    self.getLogger().info(
        "Visualizer Distance: {}",
        mConfig.visualizerDistance
    );

    self.getLogger().info(
        "Reaction Time Goal: {} ms",
        mConfig.reactionTimeGoal
    );

    self.getLogger().info(
        "Loaded {} from {}",
        self.getName(),
        self.getModDir().string()
    );

    return true;
}

bool ClangeMeMod::enable() {
    auto &self = getSelf();

    self.getLogger().debug("Enabling...");

    if (!mConfig.enabled) {
        self.getLogger().info("Clange Aim Assist is disabled by config");
        return true;
    }

    self.getLogger().info("Config message: {}", mConfig.message);

    return true;
}

bool ClangeMeMod::disable() {
    getSelf().getLogger().debug("Disabling...");
    return true;
}

bool ClangeMeMod::unload() {
    getSelf().getLogger().debug("Unloading...");
    mConfigFile.reset();
    return true;
}

} // namespace clange_me
