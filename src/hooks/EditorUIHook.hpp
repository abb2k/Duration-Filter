#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
class $modify(MyEditorUI, EditorUI) {
	struct Fields{
		ButtonSprite* fButtonSprite;
	};

	bool init(LevelEditorLayer* editorLayer);
	
	void OnDuFilterButtonClicked(CCObject*);

	void selectObject(GameObject* p0, bool p1);

	void selectObjects(cocos2d::CCArray* p0, bool p1);

	bool isGameObjectSelectValid(GameObject* objec);
};