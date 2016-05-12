#include <iostream>
#include <QtCore/QDebug>
#include "Utils.h"
#include "Crossword.h"
#include "NonogramsParser.h"

Crossword::Crossword(QObject* parent) :
        QObject(parent)
{
}

Size Crossword::size() const noexcept
{
    return m_size;
}

quint16 Crossword::rowSize() const noexcept
{
    return m_rows[0].size();
}

int Crossword::rowValue(int row, int indx) const noexcept
{
    Q_ASSERT(row < m_size.rows());

    return m_rows[row].value(indx);
}


quint16 Crossword::columnSize() const noexcept
{
    return m_column[0].size();
}

int Crossword::columnValue(int col, int indx) const noexcept
{
    Q_ASSERT(col < m_size.column());
    return m_column[col].value(indx);
}

void Crossword::formNanogramsOrg(const QUrl& url)
{
    auto html = getHtml(url);
    formNanogramsOrg(html.toUtf8());
    emit loaded();
}

void Crossword::formNanogramsOrg(const QByteArray& data)
{
    NonogramsParser parser;
    parser.fromBytes(data);

	m_column.clear();
    m_column.reserve(parser.column().size());

    using size_type = QVector<QVector<quint8>>::size_type;
    for (size_type c = 0; c < parser.column().size(); ++c)
    {
        m_column.push_back(Column(parser.column()[c]));
    }

	m_rows.clear();
    m_rows.reserve(parser.rows().size());
    for (size_type r = 0; r < parser.rows().size(); ++r)
    {
        m_rows.push_back(Row(parser.rows()[r]));
    }

    m_size = Size(parser.column().size(), parser.rows().size());
}
