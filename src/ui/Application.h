#pragma once

#include <memory>

class Crossword;
class QQmlApplicationEngine;

class Application
{
public:

    Application();

private:

    Crossword* m_crossword;
    std::shared_ptr<QQmlApplicationEngine> m_engine;
};

