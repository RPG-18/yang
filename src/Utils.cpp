#include <QtCore/QTimer>
#include <QtCore/QEventLoop>
#include <QtWebEngineWidgets/QWebEnginePage>

#include "Utils.h"

QString getHtml(const QUrl& url)
{
    QWebEnginePage page;

    QEventLoop loop;
    QObject::connect(&page, &QWebEnginePage::loadFinished,
                     &loop, &QEventLoop::quit);
    page.load(url);
    loop.exec();

    QTimer::singleShot(1000, &loop, &QEventLoop::quit);
    QString html;

    page.toHtml([&html, &loop](const QString& data){
        html = data;
        loop.quit();
    });

    loop.exec();

    return html;
}
