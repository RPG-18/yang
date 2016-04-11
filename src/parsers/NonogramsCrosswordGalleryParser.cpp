#include <algorithm>

#include <QtCore/QDebug>
#include <QtCore/QDateTime>
#include <QtCore/QRegExp>
#include <QtCore/QString>
#include <gumbo.h>

#include "Gumbo.hpp"
#include "NonogramsCrosswordGalleryParser.h"

#define RANGE(x) x.begin(), x.end()


using namespace EasyGumbo;

NonogramsCrosswordGalleryParser::NonogramsCrosswordGalleryParser(const QByteArray &html)
    : m_allTotal(0)
{
    parse(html);
}

void NonogramsCrosswordGalleryParser::parse(const QByteArray &html)
{
    Gumbo gumbo(html.data());
    if (gumbo) {
        auto iter = std::find_if(RANGE(gumbo), And(Tag(GUMBO_TAG_DIV),
                                                   HasAttribute("class", "pager")));
        const Element pager(*iter);
        const Element pagerSpan(*pager.children()[1]);
        extractAllTotal(pagerSpan.children()[0]->v.text.text);

        const auto pages = findAll(iter.fromCurrent(), gumbo.end(), Tag(GUMBO_TAG_A));
        const Element pageA(*pages.back());
        m_nextPage = QUrl(pageA.attribute("href")->value);

        iter = std::find_if(iter, gumbo.end(), And(Tag(GUMBO_TAG_TABLE),
                                                   HasAttribute("class", "nonogram_list")));

        const auto tdImages = findAll(iter.fromCurrent(), gumbo.end(), And(Tag(GUMBO_TAG_TD),
                                                                           HasAttribute("class", "nonogram_img")));

        m_nanograms.reserve(tdImages.size());
        for (size_t i = 0; i < tdImages.size(); ++i) {
            extractCrossInfo(tdImages[i]->parent);
        }
    }
}

void NonogramsCrosswordGalleryParser::extractAllTotal(const char *data)
{

    QRegExp rx("(\\d+)");
    QString str(data);
    QStringList list;
    int pos = 0;

    rx.indexIn(str, 0);

    while ((pos = rx.indexIn(str, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }

    m_allTotal = list[2].toUInt();
}

void NonogramsCrosswordGalleryParser::extractCrossInfo(GumboNode *node)
{
    Info info;
    using Iterator = Gumbo::iterator;
    Iterator iter(node);
    const Iterator end;

    iter = std::find_if(iter, end, Tag(GUMBO_TAG_A));
    const Element aEl(*iter);
    info.page = QUrl(aEl.attribute("href")->value);
    ++iter;
    const Element iconEl(*iter);
    info.icon = QUrl(iconEl.attribute("src")->value);

    iter = std::find_if(iter, end, And(Tag(GUMBO_TAG_TD),
                                       HasAttribute("class", "nonogram_descr")));

    ++iter;
    ++iter;
    ++iter;
    info.name = QString::fromUtf8(iter->v.text.text);
    iter = std::find_if(iter, end, Tag(GUMBO_TAG_TBODY));
    auto tdTags = findAll(iter.fromCurrent(), end, Tag(GUMBO_TAG_TD));
    const Element tdDate(*tdTags[1]);
    info.date = QDate::fromString(tdDate.children()[0]->v.text.text,
                                  "dd.MM.yy");
    if (info.date.year() < 1990) {
        info.date = info.date.addYears(100);
    }
    const Element tdSize(*tdTags[3]);
    info.size = tdSize.children()[0]->v.text.text;

    if (tdTags.size() == 12) {
        const Element tdAuthor(*tdTags[5]);
        const Element aAuthor(*tdAuthor.children()[0]);

        info.author = QString::fromUtf8(aAuthor.children()[0]->v.text.text);
    }

    m_nanograms.push_back(info);
}