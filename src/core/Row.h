#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QMetaType>

class Row
{
    Q_GADGET
    Q_PROPERTY(int rsize READ size)

public:

    Row() = default;
    explicit Row(const QVector<quint8>& row);

    Q_INVOKABLE quint8 value(int index) const noexcept;
    int size() const noexcept;

private:
    QVector<quint8> m_row;
};

using RowList = QVector<Row>;
