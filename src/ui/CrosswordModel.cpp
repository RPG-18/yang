#include <memory>

#include <QtCore/QDebug>
#include <QtCore/QTextCodec>

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

#include "CrosswordModel.h"
#include "NonogramsCrosswordGalleryParser.h"

CrosswordModel::CrosswordModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_count(0)
    , m_isFetchMore(false)
{
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &CrosswordModel::onLoadFinished);
}

void CrosswordModel::setSource(const QUrl &src)
{
    clearModel();

    m_source = src;
    load(m_source);
    emit sourceChanged();
}
const QUrl& CrosswordModel::source() const
{
    return m_source;
}

int CrosswordModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

bool CrosswordModel::canFetchMore(const QModelIndex &parent) const
{
    qDebug()<<"All:"<<m_count<<" cnt:"<<m_data.size();
    return m_count != m_data.size();
}
void CrosswordModel::fetchMore(const QModelIndex &parent)
{
    if(!m_isFetchMore && (m_prevPage != m_nextPage))
    {
        m_isFetchMore = true;

        m_prevPage = m_nextPage;
        load(m_nextPage);
    }
}

QHash<int, QByteArray> CrosswordModel::roleNames() const
{
    static QHash<int, QByteArray> roles =
    {
        {URL,   "url"},
        {DATE,  "date"},
        {SIZE,  "size"},
        {AUTHOR,"author"},
        {ICON,  "icon"},
        {NAME,  "nonogram"}
    };

    return roles;
}
QVariant CrosswordModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    Q_ASSERT( index.row() < m_data.size() );

    const auto row = index.row();
    switch (role)
    {
        case NAME:
            return m_data[row].name;
        case URL:
            return m_data[row].url;
        case DATE:
            return m_data[row].date.toString("dd/MM/yyyy");
        case SIZE:
            return m_data[row].size;
        case AUTHOR:
            return m_data[row].author;
        case ICON:
            return m_data[row].icon;
        default:
            return QVariant();
    }
}

void CrosswordModel::load(const QUrl& url)
{
    qDebug()<<"Load:"<<url;
    m_networkManager->get(QNetworkRequest(url));
}

void CrosswordModel::parse(const QByteArray& html)
{
    NonogramsCrosswordGalleryParser parser(html);
    m_nextPage = parser.nextPage();
    m_count    = parser.allTotal();

    const auto items = parser.nanograms();

    const size_t first = m_data.size();
    const size_t last  = first + items.size() - 1;
    beginInsertRows(QModelIndex(), first, last);
    for(const auto& item: items)
    {
        m_data.push_back(Crossword{
            item.page,
            item.name,
            item.date,
            item.size,
            item.author,
            item.icon
        });
    }
    endInsertRows();
}

void CrosswordModel::onLoadFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        const auto data = reply->readAll();
        auto codec = QTextCodec::codecForName("Windows-1251");
        const auto html = codec->toUnicode(data).toUtf8();
        parse(html);
        m_isFetchMore = false;
    }
    else
    {
        qWarning()<<"Error receiving data:"<<reply->errorString();
        qWarning()<<reply->readAll();
    }
    reply->deleteLater();
}
void CrosswordModel::clearModel()
{
    beginResetModel();
    m_count = 0;
    m_data.clear();
    m_prevPage = QUrl();
    m_nextPage = QUrl();
    endResetModel();
}



