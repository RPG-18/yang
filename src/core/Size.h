#pragma once

#include <QtCore/QObject>

class Size
{
    Q_GADGET

public:

    Size() noexcept;

    Size(quint16 column, quint16 rows) noexcept;

    Q_INVOKABLE quint16 rows() const noexcept;
    Q_INVOKABLE quint16 column() const noexcept;
    Q_INVOKABLE bool isNull() const noexcept;

private:

    bool m_isNull;
    quint16 m_column;
    quint16 m_rows;
};

Q_DECLARE_METATYPE(Size)
