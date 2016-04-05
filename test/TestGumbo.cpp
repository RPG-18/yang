#include <algorithm>
#include <iostream>

#include <gtest/gtest.h>
#include <config.h>

#include "Gumbo.h"
#include "Algorithm.h"

#include <QtCore/QDir>

QByteArray getData(const QString& fileName)
{
    QDir dir(TEST_SOURCE_DIR);
    dir.cd("data");

    QFile file(dir.absoluteFilePath("6309.html"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    return file.readAll();
}

TEST(Gumbo, parser)
{
    auto data = getData("6309.html");
    ASSERT_TRUE(!data.isEmpty());

    Gumbo parser(data);
    ASSERT_TRUE(parser);
}

TEST(Gumbo, iterator)
{
    auto data = getData("6309.html");
    ASSERT_TRUE(!data.isEmpty());

    Gumbo parser(data);

    int count = 0;
    int lastLine = 0;
    GumboTag lastTag = GUMBO_TAG_UNKNOWN;
    for(auto iter(parser.begin()), end(parser.end());
        end != iter;
        ++iter)
    {
        if(iter->type == GUMBO_NODE_ELEMENT )
        {
            lastTag  = iter->v.element.tag;
            lastLine = iter->v.element.start_pos.line;
            ++count;
        }
    }

    ASSERT_EQ(1658,count);
    ASSERT_EQ(295, lastLine);
    ASSERT_EQ(GUMBO_TAG_SPAN,lastTag);
}

TEST(Gumbo, hasAttribute)
{
    auto data = getData("6309.html");
    ASSERT_TRUE(!data.isEmpty());

    Gumbo parser(data);
    auto iter = std::find_if(parser.begin(),
                             parser.end(),
                             HasAttribute("id", "nonogram_table"));

    ASSERT_NE(parser.end(), iter);
    ASSERT_EQ(size_t(91),  iter->v.element.start_pos.line);
    ASSERT_EQ(size_t(217), iter->v.element.start_pos.column);
}

TEST(Gumbo, findTag)
{
    auto data = getData("6309.html");
    ASSERT_TRUE(!data.isEmpty());

    Gumbo parser(data);
    auto iter = std::find_if(parser.begin(),
                             parser.end(),
                             Tag(GUMBO_TAG_INPUT));
    ASSERT_NE(parser.end(), iter);
    ASSERT_EQ(size_t(91),   iter->v.element.start_pos.line);
    ASSERT_EQ(size_t(49442),iter->v.element.start_pos.column);
}

TEST(Gumbo, findAll)
{
    auto data = getData("6309.html");
     ASSERT_TRUE(!data.isEmpty());

     Gumbo parser(data);
     auto iter = std::find_if(parser.begin(),
                              parser.end(),
                              HasAttribute("class", "nmtt"));
     auto trs = findAll(iter.fromCurrent(),
             Gumbo::iterator(), Tag(GUMBO_TAG_TR));
     ASSERT_EQ(size_t(3), trs.size());
}
