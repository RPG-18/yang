#include <QtQml/QQmlContext>
#include <QtQml/QQmlApplicationEngine>

#include "Crossword.h"
#include "CrosswordModel.h"
#include "Application.h"

Application::Application():
    m_crossword(nullptr),
    m_crossModel(nullptr),
    m_engine(std::make_shared<QQmlApplicationEngine>())
{
    m_crossword = new Crossword(m_engine.get());
    m_engine->rootContext()
            ->setContextProperty("crossword", m_crossword);

    m_crossModel = new CrosswordModel(m_engine.get());
    m_engine->rootContext()
        ->setContextProperty("crosswords", m_crossModel);

    m_engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
}
