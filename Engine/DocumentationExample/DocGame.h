//
// Created by Oddball on 29/01/2023.
//
#pragma once
#include <engine/Game.h>

using gl3::engine::Game;
using gl3::engine::ecs::Entity;
using gl3::engine::sceneGraph::Transform;

class DocGame : public Game {

public:
    DocGame(int width, int height, const std::string &title) : Game(width, height, title) {
    }

private:

    void start() override {}

    void update(GLFWwindow *window) override {};

    void draw() override {};

    void drawUI() override {};
};