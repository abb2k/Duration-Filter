#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class DUrationFilterPopup : public Popup, public TextInputDelegate {
    private:
        bool init(CCLabelBMFont* label);

        TextInput* DurationTextInput;
        CCMenuItemToggler* EnabledToggle;
        ButtonSprite* buttonS;

        CCLabelBMFont* outerLabel;

        void OnOperatorChanged(CCObject*);
        void OnToggledEnabled(CCObject*);
        void textChanged(CCTextInputNode* input) override;

        void onClose(cocos2d::CCObject*) override;

    public:
        static DUrationFilterPopup* create(CCLabelBMFont* label);

        void show() override;
};