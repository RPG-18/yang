#pragma once

#include <memory>

class Crossword;
class CrosswordModel;
class QQmlApplicationEngine;

class Application
{
public:

    Application();

private:

    Crossword* m_crossword;
    CrosswordModel* m_crossModel;
    std::shared_ptr<QQmlApplicationEngine> m_engine;
};

