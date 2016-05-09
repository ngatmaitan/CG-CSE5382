//
//  SimpleGame.cpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include <vector>
#include <iostream>

using namespace std;

#include "AsteroidsGame.h"
#include "Mesh.h"
#include "Material.h"
#include "Files.h"

#include <cmath>

Vector3 AsteroidsGame::cross(const Vector3 &A, const Vector3 &B)
{
    float Cx = A.Y * B.Z - A.Z * B.Y;
    float Cy = A.Z * B.X - A.X * B.Z;
    float Cz = A.X * B.Y - A.Y * B.X;
    
    return Vector3(Cx, Cy, Cz);
}

float AsteroidsGame::dot(const Vector3 &A, const Vector3 &B)
{
    float Cx = A.X * B.X;
    float Cy = A.Y * B.Y;
    float Cz = A.Z * B.Z;
    float dotProduct = Cx + Cy + Cz;
    
    return dotProduct;
}

bool AsteroidsGame::collide(float aRadius, float bRadius, const Vector3 &objA, const Vector3 &objB)
{
    float centerDistance = sqrt(pow(objA.X-objB.X, 2) + pow(objA.Y-objB.Y, 2) + pow(objA.Z-objB.Z, 2));

    float radiusDistance = aRadius + bRadius;

    if (centerDistance < radiusDistance){
        return true;
    }
    else {
        return false;
    }
    
}

bool AsteroidsGame::OnCreateScene()
{
    ship=&CreateShip();
    missile=&CreateMissile();
    
    for(int i = 0; i < 4; i ++)
    {
        asteroids.push_back(&CreateAsteroid());
    }
    
//    for(int i = 0; i < 10; i++)
//    {
//        missiles.push_back(&CreateMissile());
//    }
    
    auto& cam = Game::Camera;
    
    cam.Transform.Translation.Z = 5;
    
    return true;
    
}

void AsteroidsGame::OnUpdate(const GameTime& time)
{
    //get aspect
    int w, h;
    
    Game::GetFramebufferSize(&w, &h);
    
    float zNear = Game::Camera.ZNear;
    float fov = Game::Camera.FieldOfView;
    float aspect = w * 1.f / h;
    
    float hh = tan(fov/2) * zNear;
    float hw = hh * aspect;
    
    //viewpoint corners at Z=1
    Vector3 nw = Vector3(-hw, hh, 1);
    Vector3 ne = Vector3(hw, hh, 1);
    Vector3 se = Vector3(hw, -hh, 1);
    Vector3 sw = Vector3(-hw, -hh, 1);
    
    //plane normals
    Vector3 top = cross(nw, ne).normalize();
    Vector3 right = cross(ne, se).normalize();
    Vector3 bottom = cross(se, sw).normalize();
    Vector3 left = cross(sw, nw).normalize();
    
    Vector3 shipPos = ship->Transform.Translation;
    Vector3 missilePos = missile->Transform.Translation;
    
    //multiply camera view matrix by ship's translation to get position of ship relative to camera
    Vector3 shipRelCamera = Matrix::Multiply(Game::Camera.GetViewMatrix(), shipPos);
    Vector3 missileRelCamera = Matrix::Multiply(Game::Camera.GetViewMatrix(), missilePos);

    if (dot(shipRelCamera, top) < 0 || dot(shipRelCamera, bottom) < 0 ){
        shipPos.Y *= -0.98f;
    }
    else if (dot(shipRelCamera, left) < 0 || dot(shipRelCamera, right) < 0){
        shipPos.X *= -0.98f;
    }
    
    if (((dot(missileRelCamera, top) < 0 || dot(missileRelCamera, bottom) < 0) && missile->missileFire == false)){
        missilePos.Y *= -0.98f;
    }
    else if (((dot(missileRelCamera, left) < 0 || dot(missileRelCamera, right) < 0 ) && missile->missileFire == false)){
        missilePos.X *= -0.98f;
    }
    
    ship->move(shipPos);
    missile->move(missilePos);
    
    Vector3 pointOnShip(ship->Radius, 0, 0);
    pointOnShip = Matrix::Multiply(ship->Transform.GetMatrix(), pointOnShip);
    float shipRadius = sqrt(pow(shipPos.X-pointOnShip.X, 2) + pow(shipPos.Y-pointOnShip.Y, 2) + pow(shipPos.Z-pointOnShip.Z, 2));
    
    Vector3 pointOnMissile(missile->Radius, 0, 0);
    pointOnMissile = Matrix::Multiply(ship->Transform.GetMatrix(), pointOnMissile);
    float missileRadius = sqrt(pow(missilePos.X-pointOnMissile.X, 2) + pow(missilePos.Y-pointOnMissile.Y, 2) + pow(missilePos.Z-pointOnMissile.Z, 2));
    
    // asteroid things
    for (int i = 0; i < asteroids.size(); i++){
        auto& asteroid = *asteroids[i];
        
        auto astPos = asteroid.Transform.Translation;
        Vector3 pointOnAst(asteroid.Radius, 0, 0);
        
        // distance pointOnSphere - astPos;
        pointOnAst = Matrix::Multiply(asteroid.Transform.GetMatrix(), pointOnAst);
        float astRadius = sqrt(pow(astPos.X-pointOnAst.X, 2) + pow(astPos.Y-pointOnAst.Y, 2) + pow(astPos.Z-pointOnAst.Z, 2));
        
        Vector3 astRelCamera = Matrix::Multiply(Game::Camera.GetViewMatrix(), astPos);
        
        if (dot(astRelCamera, top) < -4 || dot(astRelCamera, bottom) < -4 ){
            astPos.Y *= -0.98f;
        }
        else if (dot(astRelCamera, left) < -6 || dot(astRelCamera, right) < -6){
            astPos.X *= -0.98f;
        }
        
        asteroids[i]->move(astPos);
        
        if (collide(shipRadius, astRadius, astPos, shipPos) == true){
            cout << "collision between ship and asteroid \n";
        }
        else {
            cout << "no collision detected \n";
        }
        if ((collide(missileRadius, astRadius, astPos, missilePos) == true) && missile->missileFire == true){
            cout << "collision between missile and asteroid \n";
        }
        else {
            cout << "no collision detected \n";
        }
    }
}

Ship& AsteroidsGame::CreateShip()
{
    auto& ship = Create<Ship>("ship");
    
    return ship;
}

Asteroid& AsteroidsGame::CreateAsteroid()
{
    asteroid = &Create<Asteroid>("asteroid");
    asteroid->Initialize();
    
    return *asteroid;
}

Missile& AsteroidsGame::CreateMissile()
{
    missile = &Create<Missile>("missile");
    missile->Initialize();
    
    return *missile;
}

