#include "Tank.hpp"

Tank* Tank::create(const bool isR,
                   const TANK_TYPE type) {
    Tank *tank = new Tank();
    if (!tank) {
        return NULL;
    }
    tank->isAmeetBase = false;
	tank->lowBlood = false;
	tank->isAmeetWall = false;
	tank->isAmeet = false;
    tank->isR = isR;
    tank->type = type;
    tank->bindImage();
    tank->initAttributes();
    tank->setState(TANK_STATE::NORMAL);
    
    return tank;
}

void Tank::bindImage() {
    string filename = "pictures/";
    if (isR) filename += "R-";
    else filename += "B-";
    switch (type) {
        case TANK_TYPE::ASSASSIN:
            filename += "assassin.png";
            break;
        case TANK_TYPE::FIGHTER:
            filename += "fighter.png";
            break;
        case TANK_TYPE::SHOOTER:
            filename += "shooter.png";
            break;
        default:
            return;
    }
    initWithFile(filename);
}

void Tank::initAttributes() {
    bullet_speed = 500;
    CD = 0;  // 每隔1秒才能射一发子弹
    switch(type) {
        case TANK_TYPE::ASSASSIN:
            health_value  = health_value_max = 800;
            attack_value  = 200;
            defense_value = 150;
            attack_range  = 120;
            moving_speed  = 50;
            break;
        case TANK_TYPE::FIGHTER:
            health_value  = health_value_max  = 1000;
            attack_value  = 150;
            defense_value = 200;
            attack_range  = 160;
            moving_speed  = 40;
            break;
        case TANK_TYPE::SHOOTER:
            health_value  = health_value_max  = 600;
            attack_value  = 100;
            defense_value = 100;
            attack_range  = 200;
            moving_speed  = 30;
            break;
        default:
            return;
    }
}

TANK_TYPE Tank::getType() const {
    return type;
}

bool Tank::getIsR() const {
    return isR;
}

int Tank::getAttackRange() const {
    return attack_range;
}

int Tank::getMovingSpeed() const {
    return moving_speed;
}

int Tank::getBulletSpeed() const {
    return bullet_speed;
}

int Tank::getCD() const {
    return CD;
}

TANK_STATE Tank::getState() const {
    return state;
}

void Tank::setIsR(bool isr) {
    this->isR = isr;
}

void Tank::setType(TANK_TYPE type) {
    this->type = type;
}

void Tank::setState(TANK_STATE s) {
    state = s;
}

void Tank::setCD(const int CD) {
    this->CD = CD;
}

void Tank::avoidWall(bool side, const Wall * wall) {
	double length = 5;
	if (side) { length = -5; }
	if ((wall->getBoundingBox().containsPoint(getPosition())) &&
		(getPosition().y >= wall->getBoundingBox().getMinY() ||
		getPosition().y <= wall->getBoundingBox().getMaxY())) {
		MoveBy* moveAction = MoveBy::create(0.1f, Vec2(length, 0));
		runAction(moveAction);
	}
}

void Tank::move(const bool forward, const Wall *wall, Label *label, const Tower *tower) {
    Vec2 nextPos;
    if (forward) {
        nextPos = Vec2(
            getPositionX() + 10 * sin(CC_DEGREES_TO_RADIANS(getRotation())),
            getPositionY() + 10 * cos(CC_DEGREES_TO_RADIANS(getRotation())));
    } else {
        nextPos = Vec2(
            getPositionX() - 10 * sin(CC_DEGREES_TO_RADIANS(getRotation())),
            getPositionY() - 10 * cos(CC_DEGREES_TO_RADIANS(getRotation())));
    }
    if (!wall->getBoundingBox().containsPoint(nextPos) &&
        !tower->getBoundingBox().containsPoint(nextPos)) {
        auto moveToAction = MoveTo::create(0.1f, nextPos);
        runAction(moveToAction);
        auto labelNextPos = nextPos + Vec2(0.0f, 40.0f);
        auto labelMoveToAction = MoveTo::create(0.1f, labelNextPos);
        label->runAction(labelMoveToAction);
	}
}

void Tank::turn(const bool leftward) {
    if (leftward) {
        auto rotateAction = RotateBy::create(0.1f, -10);
        runAction(rotateAction);
    } else {
        auto rotateAction = RotateBy::create(0.1f, 10);
        runAction(rotateAction);
    }
}

void Tank::playDestroyAnimation() {
    string animationName;
    if (isR) animationName = "R-";
    else     animationName = "B-";
    switch (type) {
        case TANK_TYPE::ASSASSIN:
            animationName += "assassin-destroy";
            break;
        case TANK_TYPE::FIGHTER:
            animationName += "fighter-destroy";
            break;
        case TANK_TYPE::SHOOTER:
            animationName += "shooter-destroy";
            break;
        default:
            return;
    }
    auto aimation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
    runAction(aimation);
}

bool Tank::withinAttackRange(const Attackable *target) {
    return getPosition().getDistance(target->getPosition()) < getAttackRange() - 30;
}
