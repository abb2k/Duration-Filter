#include "../utils/Saved.hpp"

float Saved::getDurationFiltered(){
    return Mod::get()->getSavedValue<float>("DurationFiltered", 0);
}

void Saved::setDurationFiltered(float duration){
    Mod::get()->setSavedValue<float>("DurationFiltered", duration);
}

std::string Saved::getDurationOperator(){
    return Mod::get()->getSavedValue<std::string>("DurationOperator", "=");
}

void Saved::setDurationOperator(std::string durationOperator){
    Mod::get()->setSavedValue<std::string>("DurationOperator", durationOperator);
}


bool Saved::getDurationFilterEnabled(){
    return Mod::get()->getSavedValue<bool>("DurationFilterEnabled", false);
}

void Saved::setDurationFilterEnabled(bool enabled){
    Mod::get()->setSavedValue<bool>("DurationFilterEnabled", enabled);
}
