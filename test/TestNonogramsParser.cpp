#include <algorithm>
#include <iostream>

#include <gtest/gtest.h>
#include <config.h>

#include <QtCore/QDir>

#include "NonogramsParser.h"

QByteArray getData(const QString& fileName)
{
    QDir dir(TEST_SOURCE_DIR);
    dir.cd("data");

    QFile file(dir.absoluteFilePath("6309.html"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    return file.readAll();
}

TEST(NonogramsParser, parseFromBytes)
{
    NonogramsParser parser;

    parser.fromBytes(getData("6309.html"));

    ASSERT_EQ(20, parser.column().size());
    ASSERT_EQ(19, parser.rows().size());
}
