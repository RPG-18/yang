#pragma once

#include <QtCore/QUrl>
#include <QtCore/QDate>
#include <QtCore/QVector>
#include <QtCore/QAbstractListModel>

class QNetworkReply;
class QNetworkAccessManager;

class CrosswordModel: public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)

public:


    enum Roles
    {
        URL,
        DATE,
        SIZE,
        AUTHOR,
        ICON,
        NAME
    };

    CrosswordModel(QObject *parent = nullptr);

    void setSource(const QUrl& src);
    const QUrl& source() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:

    void sourceChanged();

private slots:

    void onLoadFinished(QNetworkReply *reply);

private:

    struct Crossword
    {
        QUrl url;
        QString name;
        QDate date;
        QString size;
        QString author;
        QUrl icon;
    };

    void load(const QUrl& url);
    void parse(const QByteArray& html);
    void clearModel();

private:

    QNetworkAccessManager* m_networkManager;

    QUrl m_source;
    int m_count;
    QVector<Crossword> m_data;
    QUrl m_prevPage;
    QUrl m_nextPage;
    bool m_isFetchMore;
};
