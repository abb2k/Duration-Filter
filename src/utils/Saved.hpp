#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class Saved{
    public:
        static float getDurationFiltered();
        static void setDurationFiltered(float duration);

        static std::string getDurationOperator();
        static void setDurationOperator(std::string durationOperator);

        static bool getDurationFilterEnabled();
        static void setDurationFilterEnabled(bool enabled);
};