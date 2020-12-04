#ifndef EFFECT_H
#define EFFECT_H

#include "shockwave.h"
#include "boom.h"
#include "gunbullet.h"
#include "swirl.h"
#include <list>

using std::list;

class GameEngine;
/* Base class : Effect
 * ******************* */
class Effect
{
public:
    Effect(GameEngine* parent = nullptr);
    virtual ~Effect();
    virtual void operation() = 0;
    virtual bool to_be_destroyed() const = 0;
protected:
    GameEngine* parent;
};

/* INVINCE:
 * ******************* */
class Invince_Effect: public Effect{
public:
    Invince_Effect(GameEngine* parent = nullptr);
    ~Invince_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    double time_duration = 0;
};

/* FREEZE:
 * ******************* */
class Freeze_Effect: public Effect{
public:
    Freeze_Effect(GameEngine* parent = nullptr);
    ~Freeze_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    double time_duration = 0;
};

/* Shoot_Effect :
 * ******************* */
class Shoot_Effect: public Effect{
public:
    Shoot_Effect(GameEngine* parent = nullptr);
    ~Shoot_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    int remain_bullet = 0;
    list<Gunbullet> gunbullets;
};

/* Explosion_Effect :
 * ****************** */
class Explosion_Effect: public Effect{
public:
    Explosion_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    ~Explosion_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    int remain_bullet = 0;
    list<Gunbullet> gunbullets;
};

/* Swirl_Effect:
 * ***************** */
class Swirl_Effect: public Effect{
public:
    Swirl_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    ~Swirl_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    Swirl swirl;
    double time_duration = 0;
    static int excisting_effects;
};
/*
class ShockWave_Effect: public Effect{
public:
    ShockWave_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    ~ShockWave_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    ShockWave item;
};

class ShockWave_Effect: public Effect{
public:
    ShockWave_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    ~ShockWave_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    ShockWave item;
};

class ShockWave_Effect: public Effect{
public:
    ShockWave_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    ~ShockWave_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    ShockWave item;
};

class ShockWave_Effect: public Effect{
public:
    ShockWave_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    ~ShockWave_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    ShockWave item;
};

class ShockWave_Effect: public Effect{
public:
    ShockWave_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    ~ShockWave_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    ShockWave item;
};
*/

/* ShockWave:
 * ******************* */
class ShockWave_Effect: public Effect{
public:
    ShockWave_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    ~ShockWave_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    ShockWave item;
};


/* Boom Effect
 *  ******************** */
class Boom_Effect: public Effect
{
public:
    Boom_Effect(const double &x, const double &y, GameEngine* parent = nullptr);
    Boom_Effect(const Vector &v, GameEngine* parent = nullptr);
    ~Boom_Effect() override;
    void operation() override;
    bool to_be_destroyed() const override;
private:
    list<Boom> items;
    const Vector center;
};

#endif // EFFECT_H
