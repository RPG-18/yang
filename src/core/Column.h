#pragma once

#include <QtCore/QVector>
#include <QtCore/QMetaType>

class Column
{
    Q_GADGET

public:

    Column() = default;
    Column(const QVector<quint8>& column);

    Q_INVOKABLE quint8 value(int index) const noexcept;
    Q_INVOKABLE int size() const noexcept;

private:

    QVector<quint8> m_column;
};


using ColumnList = QVector<Column>;

Q_DECLARE_METATYPE(Column)
Q_DECLARE_METATYPE(ColumnList)
