#include "Character.h"

void Character::Initialize(KamataEngine::Model* model,const KamataEngine::Vector3& position) {
	model_ = model;

	worldTransform_.translation_ = position;
	worldTransform_.Initialize();
}

void Character::Draw(KamataEngine::Camera& camera) {
	model_->Draw(worldTransform_, camera);
}

void Character::Hit(int damage) {
	life_ -= damage;

	if (life_ <= 0.0f) {
		life_ = 0.0f;
		isDead_ = true;
	}
}