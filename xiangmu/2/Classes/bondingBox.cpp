#include "bondingBox.h"
#include "SelectRole.h"
#include "Bullets.h"
#include "GameAttackScene.h"
#include "AttackLayer.h"
#include "GameSceneOver.h"

bool bondingBox::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->schedule(schedule_selector(bondingBox::Enemy_To_RoleBonding));
	this->schedule(schedule_selector(bondingBox::Role_To_EnemyBonding));
	this->schedule(schedule_selector(bondingBox::RoleBullets_To_Enemy));
	this->schedule(schedule_selector(bondingBox::EnemyBullets_To_Role));
	this->schedule(schedule_selector(bondingBox::Enemy_And_Role));
	return true;
}
void bondingBox::Enemy_To_RoleBonding(float t){
 	auto enemys = SelectRole::getInstence()->getEnemyArmatures();
 	auto roles = SelectRole::getInstence()->getRoleArmatures();
 		for(int i = 0; i < enemys.size();i++){
 			auto enemy = enemys.at(i);
 			for(int j = 0; j < roles.size();j++){
 				auto role = roles.at(j);
 				if(enemy->getKindRole() == "long"){
 					if(enemy->getPositionX()-role->getPositionX() <= role->getAttackRange() && enemy->getPositionX() - role->getPositionX() >= 0){
 						enemy->setArmaturestatic(attackStatic);
 						break;
 					}
 				}else
 				{
 					if(enemy->getPositionX() - role->getPositionX() <= enemy->getContentSize().width && enemy->getPositionX()-role->getPositionX() >=0){
 						enemy->setArmaturestatic(attackStatic);
 						break;
 					}
 				}
				enemy->setArmaturestatic(moveStatic);
 			}
 		}
}
void bondingBox::Role_To_EnemyBonding(float t){
	auto enemys = SelectRole::getInstence()->getEnemyArmatures();
	auto roles = SelectRole::getInstence()->getRoleArmatures();
	for(int i = 0; i < roles.size();i++){
		auto role = roles.at(i);
		if(role->getArmaturestatic() == skillStatic){
			break;
		}
		if(role->getArmaturestatic() == noStatic){
			break;
		}
		for(int j = 0; j < enemys.size();j++){
			auto enemy = enemys.at(j);
			if(role->getKindRole() == "long"){
				if(enemy->getPositionX()-role->getPositionX() <= role->getAttackRange() && enemy->getPositionX() - role->getPositionX() >= 0){
					role->setArmaturestatic(attackStatic);
					break;
				}
			}else
			{
				if(enemy->getPositionX() - role->getPositionX() <= enemy->getContentSize().width && enemy->getPositionX()-role->getPositionX() >=0){
					role->setArmaturestatic(attackStatic);
					break;
				}
			}
			role->setArmaturestatic(moveStatic);
		}
	}
}
void bondingBox::RoleBullets_To_Enemy(float t){
	auto bullets = Bullets::getInstence()->getRoleBullets();
	auto enemys = SelectRole::getInstence()->getEnemyArmatures();
	for(int i = 0; i < bullets.size();i++){
		auto bullet = bullets.at(i);
		for(int j = 0; j < enemys.size();j++){
			auto enemy = enemys.at(j);
			if(bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
				bullet->setIsDie();
				enemy->setHp(bullet->getAttack());
				break;
			}
		}
	}
	Bullets::getInstence()->deleteRoleBullets();
	SelectRole::getInstence()->deleteEnemyArmature();
}
void bondingBox::EnemyBullets_To_Role(float t){
	auto bullets = Bullets::getInstence()->getEnemyBullets();
	auto roles = SelectRole::getInstence()->getRoleArmatures();
	for(int i = 0; i < bullets.size();i++){
		auto bullet = bullets.at(i);
		for(int j = 0;j < roles.size();j++){
			auto role = roles.at(j);
			if(role->getArmaturestatic() == skillStatic){
				break;
			}
			if(bullet->getBoundingBox().intersectsRect(role->getBoundingBox())){
				bullet->setIsDie();
				role->setHp(bullet->getAttack());
				break;
			}
		}
	}
	Bullets::getInstence()->deleteEnemyBullets();
	SelectRole::getInstence()->deleteRoleArmature();
}
void bondingBox::Enemy_And_Role(float t){
	auto enemys = SelectRole::getInstence()->getEnemyArmatures();
	auto roles = SelectRole::getInstence()->getRoleArmatures();
	if(enemys.size() <= 0){
		for(int i = 0;i < roles.size();i++){
			roles.at(i)->setArmaturestatic(moveStatic);
			setAttackLayerVisible();
		}
		return;
	}else if(roles.size() <= 0){
		for(int j = 0; j < enemys.size();j++){
			enemys.at(j)->setArmaturestatic(moveStatic);
			auto delay = DelayTime::create(2);
			auto replaceScene = CallFunc::create([](){
				auto scene = GameOverScene::create();
				Director::getInstance()->replaceScene(scene);
			});
			auto seq = Sequence::create(delay,replaceScene,NULL);
			this->runAction(seq);
		}
		
		return;
	}
}
void bondingBox::setAttackLayerVisible(){
	GameAttackScene *scene = dynamic_cast<GameAttackScene *>(Director::getInstance()->getRunningScene());
	AttackLayer *layer = dynamic_cast<AttackLayer *>(scene->getAttackLayer());
	layer->setNextMapVisable(true);
}