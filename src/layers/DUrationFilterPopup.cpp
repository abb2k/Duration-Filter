#include "../layers/DUrationFilterPopup.hpp"
#include "../utils/Saved.hpp"

DUrationFilterPopup* DUrationFilterPopup::create(CCLabelBMFont* label) {
    auto ret = new DUrationFilterPopup();
    if (ret && ret->init(220, 150, label, "GJ_square01.png", {0.f, 0.f, 80.f, 80.f})) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void DUrationFilterPopup::show(){
    auto scene = CCScene::get();

    this->setZOrder(105);

    scene->addChild(this);
}

bool DUrationFilterPopup::setup(CCLabelBMFont* label) {

    this->setTitle("Duration Filter");

    outerLabel = label;

    auto tInputDu = TextInput::create(80, "Duration");
    tInputDu->setString("Duration");
    tInputDu->setPosition({-58, 23});
    tInputDu->getInputNode()->setTouchEnabled(false);
    this->m_buttonMenu->addChild(tInputDu);

    DurationTextInput = TextInput::create(80, "Filter");

    float num = Saved::getDurationFiltered();
    if (roundf(num) == num)
        DurationTextInput->setString(std::to_string(static_cast<int>(num)));
    else    
        DurationTextInput->setString(std::to_string(num));
    
    DurationTextInput->setCommonFilter(CommonFilter::Float);
    DurationTextInput->setDelegate(this);
    DurationTextInput->setPosition({58, 23});
    this->m_buttonMenu->addChild(DurationTextInput);
    
    buttonS = ButtonSprite::create("0", "bigFont.fnt", "GJ_button_01.png", 1);
    buttonS->setScale(0.65f);
	auto duOperatorButton = CCMenuItemSpriteExtra::create(
		buttonS,
		nullptr,
		this,
		menu_selector(DUrationFilterPopup::OnOperatorChanged)
	);
    duOperatorButton->setPositionY(23);
    this->m_buttonMenu->addChild(duOperatorButton);
    buttonS->m_label->setString(Saved::getDurationOperator().c_str());

    auto checkOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    checkOn->setScale(0.85f);
    auto checkOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    checkOff->setScale(0.85f);
    EnabledToggle = CCMenuItemToggler::create(
        checkOff,
        checkOn,
        this,
        menu_selector(DUrationFilterPopup::OnToggledEnabled)
    );
    EnabledToggle->setPosition({-56, -15});
    EnabledToggle->toggle(Saved::getDurationFilterEnabled());
    this->m_buttonMenu->addChild(EnabledToggle);

    auto EnabledToggleToggle = CCLabelBMFont::create("Filter Enabled", "bigFont.fnt");
    EnabledToggleToggle->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
    EnabledToggleToggle->setPosition({22, -15});
    EnabledToggleToggle->setScale(0.45f);
    this->m_buttonMenu->addChild(EnabledToggleToggle);

    auto okButtonS = ButtonSprite::create("Ok", "goldFont.fnt", "GJ_button_01.png", 1);
	auto okButton = CCMenuItemSpriteExtra::create(
		okButtonS,
		nullptr,
		this,
		menu_selector(DUrationFilterPopup::onClose)
	);
    okButton->setPositionY(-52);
    this->m_buttonMenu->addChild(okButton);

    return true;
}

void DUrationFilterPopup::OnOperatorChanged(CCObject*){
    std::string current = buttonS->m_label->getString();

    if (current == "="){
        buttonS->m_label->setString(">");
        Saved::setDurationOperator(">");
    }
    else if (current == ">"){
        buttonS->m_label->setString("<");
        Saved::setDurationOperator("<");
    }
    else if (current == "<"){
        buttonS->m_label->setString("=");
        Saved::setDurationOperator("=");
    }
}

void DUrationFilterPopup::OnToggledEnabled(CCObject*){
    Saved::setDurationFilterEnabled(!EnabledToggle->isOn());
}

void DUrationFilterPopup::textChanged(CCTextInputNode* input){
    if (input == DurationTextInput->getInputNode()){
        auto val = geode::utils::numFromString<float>(input->getString());

        if (val.isOk()){
            float realVal = val.value();
            if (realVal < 0){
                realVal = 0;
                DurationTextInput->setString("0");
            }
            Saved::setDurationFiltered(realVal);
        }
        else{
            Saved::setDurationFiltered(0);
        }
    }
}

void DUrationFilterPopup::onClose(cocos2d::CCObject* sender){
    if (outerLabel)
        outerLabel->setString(fmt::format("{}{}", Saved::getDurationOperator(), static_cast<int>(Saved::getDurationFiltered())).c_str());
        
    Popup<CCLabelBMFont*>::onClose(sender);
}