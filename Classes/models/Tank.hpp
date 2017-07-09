#ifndef TANK
#define TANK

#include "cocos2d.h"
#include "enums.hpp"
#include "Attackable.hpp"
#include "Bullet.hpp"
#include <string>
USING_NS_CC;
using namespace std;

class Tank: public Attackable {
public:
    static Tank* create(const bool isR = true,
                        const TANK_TYPE type = TANK_TYPE::FIGHTER);
    
    void bindImage();
    
	void initAttributes();
    
    TANK_TYPE getType() const;
    
    int getAttackRange() const;
    
    int getMovingSpeed() const;
    
    int getBulletSpeed() const;
    
    TANK_STATE getTankState() const;
    
    void setIsR(bool isr);
    
    void setType(TANK_TYPE type);
    
    void setState(TANK_STATE s);
    
    void move(const bool forward);
    
    void turn(const bool leftward);
    
    void hurt(const int hurt);
    
    void destroy();
    
    void changeDirection(const int delda);
    
protected:
    bool isR;        // 坦克时R方还是B方
    TANK_TYPE type;  // 坦克的类型
    TANK_STATE state; // 坦克的状态

    int attack_range;    // 射程
    int moving_speed;    // 移动速度
    int bullet_speed;    // 子弹速度
};

#endif
