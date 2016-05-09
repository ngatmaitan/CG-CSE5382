//
//  SimpleGame.hpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Missile.h"

class AsteroidsGame : public Game
{
public:
	AsteroidsGame() : ShaderFolder("Shaders/")
    {
    }
    
    bool OnCreateScene() override;
    
    void OnUpdate(const GameTime& time) override;
    
    bool collide(float aRadius, float bRadius, const Vector3 &objA, const Vector3 &objB);

    /// location of shaders in the file system.
	std::string ShaderFolder;
    
    Ship& CreateShip();
    Asteroid& CreateAsteroid();
    Missile& CreateMissile();
    
    static Vector3 cross(const Vector3 &A, const Vector3 &B);
    static float dot(const Vector3 &A, const Vector3 &B);
    
private:
    Ship* ship;
    Asteroid* asteroid;
    Missile* missile;
    
    vector<Asteroid*> asteroids = {};
    vector<Missile*> missiles = {};
};


#endif /* SimpleGame_hpp */
