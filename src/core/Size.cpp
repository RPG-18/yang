#include "Size.h"

Size::Size(quint16 column, quint16 rows) noexcept
    : m_isNull(false),
      m_column(column),
      m_rows(rows)
{ }

Size::Size() noexcept
    : m_isNull(true),
      m_column(0),
      m_rows(0)
{

}
quint16 Size::column() const noexcept
{
    return m_column;
}
quint16 Size::rows() const noexcept
{
    return m_rows;
}
bool Size::isNull() const noexcept
{
    return m_isNull;
}
