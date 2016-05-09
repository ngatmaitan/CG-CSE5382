//
//  Asteroid.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Asteroid.h"
#include "Common.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"
#include "GeometryProvider.h"

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

bool Asteroid::OnInitialize()
{
    auto& mesh = Create<Mesh>("asteroid-mesh");
    
    vector<Vector3> vertices = {};
    
    vector<GLushort> indices = {};
    
    GeometryProvider::Icosahedron(vertices, indices);
    
    /// loop through vertices and calculate radius = length(farthest point from 0,0,0)
    float radiusMax = 0;
    for (int i = 0; i < vertices.size(); i++){
        float Radius = sqrt(pow(vertices[i].X-0, 2) + pow(vertices[i].Y-0, 2) + pow(vertices[i].Z-0, 2));
        
        if (Radius > radiusMax){
            radiusMax = Radius;
        }
    }
    Radius = radiusMax/2;
    
    Transform.Scale = .4;
    
    mesh.Initialize(vertices, indices);
    
    float x = rand() % 6 + -3;
    float y = rand() % 6 + -3;
    
    Vector3 newPos = {x*0.02f, y*0.02f, 0};
    
    Transform.Translation = newPos;
    
    m_mesh = &mesh;
    
    auto& material = Create<class Material>("asteroid-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    
    return material.Build("Shaders/primitive");
}

void Asteroid::OnUpdate(const GameTime& time)
{
    float drag = 0;
    Vector3 velocity;

    velocity = Transform.Translation - previousTranslation;
    previousTranslation = Transform.Translation;

    Transform.Rotation.X += 0.01f;
    Transform.Rotation.Y -= 0.01f;
    
    Transform.Translation += velocity * (1.f - drag);
}

void Asteroid::move(const Vector3& newPos)
{
    Vector3 velocity;
    
    velocity = Transform.Translation - previousTranslation;
    
    Transform.Translation = newPos;
    
    previousTranslation = newPos - velocity;
}

void Asteroid::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}


