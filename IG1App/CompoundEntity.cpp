#include "CompoundEntity.h"

CompoundEntity::CompoundEntity() {

}

CompoundEntity::~CompoundEntity() {
	for (Abs_Entity* obj : gObjects) delete obj;
}

void CompoundEntity::update() {
	for (Abs_Entity* obj : gObjects) obj->update();
}

void CompoundEntity::load() {
	for (Abs_Entity* obj : gObjects) obj->load();
}

void CompoundEntity::unload() {
	for (Abs_Entity* obj : gObjects) obj->unload();
}

void CompoundEntity::render(const glm::mat4& modelViewMat) const {
	for (Abs_Entity* obj : gObjects) obj->render(modelViewMat);

}

void CompoundEntity::addEntity(Abs_Entity* ae) {
	gObjects.push_back(ae);
}
