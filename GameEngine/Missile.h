//
//  Missile.h
//  GameEngine
//
//  Created by Nicole on 4/25/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef MISSILE_H
#define MISSILE_H

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"

class Missile : public WorldEntity
{
public:
    
    Missile()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    
    Vector3 previousTranslation;
    
    void move(const Vector3& newPos);
    
    bool missileFire = false;
    
private:
    Mesh* m_mesh;
    Material* m_material;
};

#endif /* Missile_h */

