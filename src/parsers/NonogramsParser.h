#ifndef YAJC_NONOGRAMSPARSER_H
#define YAJC_NONOGRAMSPARSER_H

#include <memory>

#include <QtCore/QVector>
#include <QtCore/QByteArray>

struct MonogramsParserImpl;
class NonogramsParser
{
public:

    NonogramsParser();
    ~NonogramsParser();

    void fromBytes(const QByteArray& html);

    const QVector<QVector<quint8>>& column() const noexcept;
    const QVector<QVector<quint8>>& rows() const noexcept;

private:

    std::unique_ptr<MonogramsParserImpl> m_impl;
};


#endif //YAJC_NONOGRAMSPARSER_H
