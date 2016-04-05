#include "Row.h"

Row::Row(const QVector<quint8>& row):
    m_row(row)
{

}
quint8 Row::value(int index) const noexcept
{
    Q_ASSERT(index<m_row.size());
    return m_row[index];
}

int Row::size() const noexcept
{
    return m_row.size();
}
