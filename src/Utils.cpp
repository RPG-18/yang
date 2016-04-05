#include <QtCore/QTimer>
#include <QtCore/QEventLoop>
#include <QtWebEngineWidgets/QWebEngineView>

#include "Utils.h"

QString getHtml(const QUrl& url)
{
    QWebEngineView view;

    QEventLoop loop;
    QObject::connect(&view, &QWebEngineView::loadFinished,
                     &loop, &QEventLoop::quit);
    view.load(url);
    loop.exec();

    QTimer::singleShot(1000, &loop, &QEventLoop::quit);
    QString html;

    view.page()->toHtml([&html, &loop](const QString& data){
        html = data;
        loop.quit();
    });

    loop.exec();

    return html;
}
