#pragma once

#include <QtCore/QObject>
#include <QtQml/QQmlListProperty>

#include "Row.h"
#include "Size.h"
#include "Column.h"

class Crossword: public QObject
{
    Q_OBJECT
    Q_PROPERTY(Size size READ size)

public:

    Crossword(QObject* parent = nullptr);

    Size size() const noexcept;
    void formNanogramsOrg(const QByteArray& data);

    Q_INVOKABLE void formNanogramsOrg(const QUrl& url);
    Q_SIGNAL void loaded() const;


    Q_INVOKABLE quint16 rowSize() const noexcept;
    Q_INVOKABLE int rowValue(int row, int indx) const noexcept;

    Q_INVOKABLE quint16 columnSize() const noexcept;
    Q_INVOKABLE int columnValue(int col, int indx) const noexcept;

private:

    Size m_size;
    RowList m_rows;
    ColumnList m_column;
};
