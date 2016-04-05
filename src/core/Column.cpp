#include "Column.h"

Column::Column(const QVector<quint8> &column):
    m_column(column)
{

}

quint8 Column::value(int index) const noexcept
{
    Q_ASSERT(index<m_column.size());
    return m_column[index];
}

int Column::size() const noexcept
{
    return m_column.size();
}

