#include <algorithm>

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QVector>

#include "Gumbo.hpp"
#include "NonogramsParser.h"

#define RANGE(x) x->begin(), x->end()

using namespace EasyGumbo;

struct MonogramsParserImpl
{
    MonogramsParserImpl() noexcept;

    void fromBytes(const QByteArray& html);

    void parseCrossword();
    void extractColumn();
    void allocatedCulumns(size_t cnt);

    void extractRows();
    void allocatedRows(size_t cnt);

    std::shared_ptr<Gumbo> m_parser;
    size_t m_columnSize;
    QVector<QVector<quint8>> m_columns;

    size_t m_rowSize;
    QVector<QVector<quint8>> m_rows;
};

NonogramsParser::NonogramsParser() :
        m_impl(std::make_unique<MonogramsParserImpl>())
{
}

NonogramsParser::~NonogramsParser() = default;

void NonogramsParser::fromBytes(const QByteArray& html)
{
    m_impl->fromBytes(html);
}

const QVector<QVector<quint8>>& NonogramsParser::column() const noexcept
{
    return m_impl->m_columns;
}

const QVector<QVector<quint8>>& NonogramsParser::rows() const noexcept
{
    return m_impl->m_rows;
}

MonogramsParserImpl::MonogramsParserImpl() noexcept:
    m_columnSize(0),
    m_rowSize(0)
{
}

void MonogramsParserImpl::fromBytes(const QByteArray& html)
{
    m_parser = std::make_shared<Gumbo>(html);
    parseCrossword();
}

void MonogramsParserImpl::parseCrossword()
{
    extractColumn();
    extractRows();
}

void MonogramsParserImpl::extractColumn()
{
    auto iter = std::find_if(RANGE(m_parser), HasAttribute("class", "nmtt"));
    if (iter == m_parser->end())
    {
        return;
    }

    using Iterator = Gumbo::iterator;
    Iterator inTable(&*iter);

    auto trs = findAll(iter.fromCurrent(), m_parser->end(), Tag(GUMBO_TAG_TR));

    m_columnSize = trs.size();
    {
        const Element tr(*trs[0]);
        allocatedCulumns(tr.children().size());
    }

    for (size_t row = 0; row < trs.size(); ++row)
    {
        Iterator iter(trs[row]), end;
        size_t div = 0;
        while (iter != end)
        {
            if (iter->type == GUMBO_NODE_TEXT)
            {
                const auto column = div - 1;
                m_columns[column][row] = atoi(iter->v.text.text);
            }
            else if (iter->type == GUMBO_NODE_ELEMENT
                    && iter->v.element.tag == GUMBO_TAG_DIV)
            {
                ++div;
            }
            ++iter;
        }
    }
}

void MonogramsParserImpl::allocatedCulumns(size_t cnt)
{
    m_columns.resize(cnt);
    for (size_t i = 0; i < cnt; ++i)
    {
        m_columns[i] = QVector<quint8>(m_columnSize, 0);
    }
}

void MonogramsParserImpl::extractRows()
{
    auto iter = std::find_if(RANGE(m_parser), HasAttribute("class", "nmtl"));
    if (iter == m_parser->end())
    {
        return;
    }

    using Iterator = Gumbo::iterator;
    Iterator inTable(&*iter);
    auto trs = findAll(iter.fromCurrent(), m_parser->end(), Tag(GUMBO_TAG_TR));
    {
        const Element tr(*trs[0]);
        m_rowSize = tr.children().size();
    }

    allocatedRows(trs.size());
    for (size_t row = 0; row < trs.size(); ++row)
    {
        Iterator iter(trs[row]), end;
        size_t div = 0;
        while (iter != end)
        {
            if (iter->type == GUMBO_NODE_TEXT)
            {
                const auto column = div - 1;
                m_rows[row][column] = atoi(iter->v.text.text);
            }
            else if (iter->type == GUMBO_NODE_ELEMENT
                    && iter->v.element.tag == GUMBO_TAG_DIV)
            {
                ++div;
            }
            ++iter;
        }
    }
}

void MonogramsParserImpl::allocatedRows(size_t cnt)
{
    m_rows.resize(cnt);
    for (size_t i = 0; i < cnt; ++i)
    {
        m_rows[i] = QVector<quint8>(m_rowSize, 0);
    }
}
