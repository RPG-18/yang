#pragma once

#include <QtCore/QUrl>
#include <QtCore/QDate>
#include <QtCore/QVector>
#include <QtCore/QByteArray>

#include "Gumbo.hpp"

class NonogramsCrosswordGalleryParser
{
public:

    struct Info
    {
        QUrl page;
        QUrl icon;
        QString name;
        QDate date;
        QString size;
        QString author;
    };

    typedef QVector<Info> NanogramInfo;

    NonogramsCrosswordGalleryParser(const QByteArray& html);

    quint32 allTotal() const noexcept
    {
        return m_allTotal;
    }

    const QUrl& nextPage() const noexcept
    {
        return m_nextPage;
    }

    const NanogramInfo& nanograms() const noexcept
    {
        return m_nanograms;

    }
private:

    void parse(const QByteArray& html);
    void extractAllTotal(const char* str);
    void extractCrossInfo( GumboNode* node);

private:

    quint32 m_allTotal;

    QUrl m_nextPage;
    NanogramInfo m_nanograms;
};
