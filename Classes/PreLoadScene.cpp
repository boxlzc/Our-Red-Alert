#include "PreLoadScene.h"
#include "StartMenuScene.h"
#include <string>
#include <cstring>
using std::string;


USING_NS_CC;

bool PreLoad::hasPlayedBgm = false;

Scene* PreLoad::createScene() {
	auto scene = Scene::create();
	auto layer = PreLoad::create();

	scene->addChild(layer);
	return scene;
}

bool PreLoad::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* 设置背景图片 */
	auto back_ground = Sprite::create("background3.png");
	back_ground->setPosition(origin + visibleSize / 2);
	back_ground->setScaleX(visibleSize.width / back_ground->getContentSize().width);
	back_ground->setScaleY(visibleSize.height / back_ground->getContentSize().height);
	addChild(back_ground, -5);

	auto bar_sprite = Sprite::create("slider2.png");
	auto bar_back_ground_sprite = Sprite::create("slider1.png");
	bar_back_ground_sprite->setScale(2);
	bar_back_ground_sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.15));
	this->addChild(bar_back_ground_sprite);

	/*设置_progress的各项参数*/
	_progress = ProgressTimer::create(bar_sprite);
	_progress->setPercentage(0.0f);
	_progress->setScale(2);
	_progress->setMidpoint(Point(0.0f, 0.5f));
	_progress->setBarChangeRate(Point(1.0f, 0.f));
	_progress->setType(ProgressTimer::Type::BAR);
	_progress->setPosition(visibleSize.width / 2, visibleSize.height * 0.15);
	this->addChild(_progress);

	/* 添加标签 */
	Label *label = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 45);
	Size size = Director::getInstance()->getVisibleSize();
	label->setPosition(Vec2(size.width / 2, size.height * 0.23));
	this->addChild(label);

	return true;
}

void PreLoad::onEnterTransitionDidFinish() {
	//读取preloadResources文件中的游戏资源名称列表
	ValueMap map = FileUtils::getInstance()->getValueMapFromFile("preloadResources.plist");
	ValueVector spriteSheets = map.at("SpriteSheets").asValueVector();
	ValueVector effects = map.at("Sounds").asValueVector();
	ValueVector musics = map.at("Musics").asValueVector();
	ValueVector animation = map.at("Animotions").asValueVector();

	_sourceCount = spriteSheets.size() + effects.size() + musics.size() + animation.size();
	// 设置进度条更新间隔=100/需要加载的资源数量
	_progressInterval = 100 / _sourceCount;

	loadMusic(musics);
	loadEffect(effects);
	loadSpriteSheets(spriteSheets);
	loadAnimations(animation);
}

void PreLoad::loadMusic(ValueVector musicFiles) {
	for (Value &v: musicFiles) {
		string str = v.asString();
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(str.c_str());
		progressUpdate();
	}
}

void PreLoad::loadEffect(ValueVector effectFiles) {
	for (Value &v : effectFiles) {
		string str = v.asString();
		SimpleAudioEngine::getInstance()->preloadEffect(str.c_str());
		progressUpdate();
	}
}

void PreLoad::loadSpriteSheets(ValueVector spriteSheets) {
	auto a = SpriteFrameCache::getInstance();
	for (Value &v : spriteSheets) {
		string str = v.asString();		
		a->addSpriteFramesWithFile(str);
		progressUpdate();
	}
}

void PreLoad::loadAnimations(ValueVector animations) {
	for (Value &v : animations) {
		int frame = 0;
		string str = v.asString();
		if (str == "Base.plist")
		{
			frame = 26;
			auto animation = Animation::create();
			for (int i = 1; i <= frame; i++)
			{
				std::string name = StringUtils::format("Picture/animation/Base/Base_1 (%d).png", i);
				auto spriteFrame = SpriteFrame::create(name, Rect(0,0,141,89));
				animation->addSpriteFrame(spriteFrame);
			}
			animation->setDelayPerUnit(3.0f / (float)frame);
			animation->setRestoreOriginalFrame(true);
			AnimationCache::getInstance()->addAnimation(animation, "BaseCreate");
		}
	
		else if (str == "PowerPlant.plist")
		{
			frame = 25;
			auto animation = Animation::create();
			for (int i = 1; i <= frame; i++)
			{
				std::string name = StringUtils::format("Picture/animation/PowerPlant/PowerPlant_1 (%d).png", i);
				auto spriteFrame = SpriteFrame::create(name, Rect(0, 0, 135, 121));
				animation->addSpriteFrame(spriteFrame);
			}
			animation->setDelayPerUnit(3.0f / (float)frame);
			AnimationCache::getInstance()->addAnimation(animation, "PowerPlantCreate");
		}
		else if (str == "Mine.plist")
		{
			frame = 24;
			auto SpriteFrameCacheInstance = SpriteFrameCache::getInstance();
			SpriteFrameCacheInstance->addSpriteFramesWithFile(str);
			auto animation = Animation::create();
			for (int i = 1; i <= frame; i++)
			{
				std::string name = StringUtils::format("Picture/animation/Mine/Mine_1 (%d).png", i);
				auto spriteFrame = SpriteFrame::create(name, Rect(0, 0, 134, 95));
				animation->addSpriteFrame(spriteFrame);				
			}
			animation->setDelayPerUnit(3.0f / (float)frame);
			AnimationCache::getInstance()->addAnimation(animation, "MineCreate");
		}	
		else if (str == "TankFactory.plist")
		{
			frame = 24;
			auto SpriteFrameCacheInstance = SpriteFrameCache::getInstance();
			SpriteFrameCacheInstance->addSpriteFramesWithFile(str.c_str());
			auto animation = Animation::create();
			for (int i = 1; i <= frame; i++)
			{
				std::string name = StringUtils::format("Picture/animation/TankFactory/TankFactory_1 (%d).png", i);
				auto spriteFrame = SpriteFrame::create(name, Rect(0, 0, 140, 110));
				animation->addSpriteFrame(spriteFrame);
			}
			animation->setDelayPerUnit(3.0f / (float)frame);
			AnimationCache::getInstance()->addAnimation(animation, "TankFactoryCreate");
		}
		else if (str == "MilitaryCamp.plist")
		{
			frame = 24;
			auto SpriteFrameCacheInstance = SpriteFrameCache::getInstance();
			SpriteFrameCacheInstance->addSpriteFramesWithFile(str);
			auto animation = Animation::create();
			for (int i = 1; i <= frame; i++)
			{
				std::string name = StringUtils::format("Picture/animation/MilitaryCamp/MilitaryCamp_1 (%d).png", i);
				auto spriteFrame = SpriteFrame::create(name, Rect(0, 0, 70, 127));
				animation->addSpriteFrame(spriteFrame);
			}
			animation->setDelayPerUnit(3.0f / (float)frame);
			AnimationCache::getInstance()->addAnimation(animation, "MilitaryCampCreate");
		}
		progressUpdate();
	}
}

void PreLoad::progressUpdate() {
	if (--_sourceCount) {
		_progress->setPercentage(100.0f - (_progressInterval * _sourceCount));
	}
	else {
		// 以渐进的方式显示图片,每次动作持续0.5s
		auto display_action = ProgressFromTo::create(0.5f, _progress->getPercentage(), 100);
		auto call_function = CallFunc::create([=] {
			// 当加载资源完成，延迟1秒跳转到游戏主场景
			auto delay = DelayTime::create(1.0f);
			auto call_function = CallFunc::create([] {
				Director::getInstance()->replaceScene(GameMenu::createScene());
			});
			auto action = Sequence::create(delay, call_function, NULL);
			this->runAction(action);
		});
		auto action = Sequence::create(display_action, call_function, NULL);

		_progress->runAction(action);
	}
}

