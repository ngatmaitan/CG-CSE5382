//
//  Asteroid.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROID_H
#define ASTEROID_H

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"

class Asteroid : public WorldEntity
{
public:
    
    Asteroid()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    
    Vector3 previousTranslation;
    
    void move(const Vector3& newPos);
    
private:
    Mesh* m_mesh;
    Material* m_material;
};

#endif /* Asteroid_hpp */
