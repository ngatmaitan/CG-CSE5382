//
//  Missile.cpp
//  GameEngine
//
//  Created by Nicole on 4/25/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Common.h"
#include "Missile.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

bool Missile::OnInitialize()
{
    auto& mesh = Create<Mesh>("missile-mesh");
    
    vector<float> vertices =
    {
        0.005f, -0.24f, 0
    };
    
    vector<GLushort> indices = {0,1,2};
    
    float max = 0;
    for (int i = 0; i<vertices.size(); i++)
    {
        float num = abs(vertices[i]);
        if ( num > max)
        {
            max = num;
        }
    }
    
    Radius = sqrt(pow(max-0, 2) + pow(max-0, 2) + pow(max-0, 2));
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    
    auto& material = Create<class Material>("missile-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    
    return material.Build("Shaders/primitive");
}

void Missile::OnUpdate(const GameTime& time)
{
    Vector3 up = Transform.Up();
    float drag = .15f;
    Vector3 velocity;

    velocity = Transform.Translation - previousTranslation;
    previousTranslation = Transform.Translation;
    
    if (glfwGetKey(Game::Instance().Window(), GLFW_KEY_SPACE)){
        velocity += up * 0.2f;
        missileFire = true;
    }
    if (glfwGetKey(Game::Instance().Window(), GLFW_KEY_UP)){
        velocity += up * 0.05f;
    }
    if (glfwGetKey(Game::Instance().Window(), GLFW_KEY_LEFT)){
        Transform.Rotation.Z -= 0.05f;
    }
    if (glfwGetKey(Game::Instance().Window(), GLFW_KEY_RIGHT)){
        Transform.Rotation.Z += 0.05f;
    }
    
    Transform.Translation += velocity * (1.f - drag);
}

void Missile::move(const Vector3& newPos)
{
    Vector3 velocity;
    
    velocity = Transform.Translation - previousTranslation;
    
    Transform.Translation = newPos;
    
    previousTranslation = newPos - velocity;
    
}

void Missile::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}


