#include "../hooks/EditorUIHook.hpp"
#include "../layers/DUrationFilterPopup.hpp"
#include "../utils/Saved.hpp"

bool MyEditorUI::init(LevelEditorLayer* editorLayer){
	if (!EditorUI::init(editorLayer)) return false;

	if (auto delCat = getChildByID("delete-category-menu"))
		if (auto delMenu = delCat->getChildByID("delete-filter-menu")){

			m_fields->fButtonSprite = ButtonSprite::create("0", "bigFont.fnt", "GJ_button_04.png", 1);
			auto duFilterButton = CCMenuItemSpriteExtra::create(
				m_fields->fButtonSprite,
				nullptr,
				this,
				menu_selector(MyEditorUI::OnDuFilterButtonClicked)
			);

			delMenu->addChild(duFilterButton);
			duFilterButton->setID("delete-filter-duration");
			delMenu->updateLayout();

			m_fields->fButtonSprite->m_label->setScale(0.6f);
			m_fields->fButtonSprite->m_label->setString(fmt::format("{}{}", Saved::getDurationOperator(), static_cast<int>(Saved::getDurationFiltered())).c_str());
		}

	return true;
}

void MyEditorUI::OnDuFilterButtonClicked(CCObject*){
	DUrationFilterPopup::create(m_fields->fButtonSprite->m_label)->show();
}

void MyEditorUI::selectObject(GameObject* p0, bool p1){

	if (!isGameObjectSelectValid(p0)) return;

	EditorUI::selectObject(p0, p1);
}

void MyEditorUI::selectObjects(cocos2d::CCArray* p0, bool p1){

	CCObject* child;

	std::vector<GameObject*> toRemove{};

	CCARRAY_FOREACH(p0, child){
		if (auto objec = typeinfo_cast<GameObject*>(child)){
			if (!isGameObjectSelectValid(objec)) toRemove.push_back(objec);
		}
	}

	for (int i = 0; i < toRemove.size(); i++)
	{
		if (p0->containsObject(toRemove[i])){
			p0->removeObject(toRemove[i]);
		}
	}

	EditorUI::selectObjects(p0, p1);
}

bool MyEditorUI::isGameObjectSelectValid(GameObject* objec){
	if (!Saved::getDurationFilterEnabled() || objec == nullptr){
		return true;
	}

	if (auto trigger = typeinfo_cast<EnhancedTriggerObject*>(objec)){
		if (Saved::getDurationOperator() == "="){
			if (trigger->m_duration != Saved::getDurationFiltered()){
				return false;
			}
		}
		else if (Saved::getDurationOperator() == ">"){
			if (trigger->m_duration <= Saved::getDurationFiltered()){
				return false;
			}
		}
		else if (Saved::getDurationOperator() == "<"){
			if (trigger->m_duration >= Saved::getDurationFiltered()){
				return false;
			}
		}
	}
	else if (auto trigger = typeinfo_cast<TriggerControlGameObject*>(objec)){

		if (Saved::getDurationOperator() == "="){
			if (trigger->m_duration != Saved::getDurationFiltered()){
				return false;
			}
		}
		else if (Saved::getDurationOperator() == ">"){
			if (trigger->m_duration <= Saved::getDurationFiltered()){
				return false;
			}
		}
		else if (Saved::getDurationOperator() == "<"){
			if (trigger->m_duration >= Saved::getDurationFiltered()){
				return false;
			}
		}
	}
	else
		return false;

	return true;
}