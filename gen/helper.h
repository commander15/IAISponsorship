#ifndef HELPER_H
#define HELPER_H

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>

#include <QtSql/qsqltablemodel.h>

class Helper : public QObject
{
    Q_OBJECT

public:
    explicit Helper(const QSqlDatabase &db, QObject *parent = nullptr);
    ~Helper();

    Q_INVOKABLE bool hasNextStudentId(int level);
    Q_INVOKABLE int nextStudentId(int level);

    Q_INVOKABLE int randomStudentId(int level);

    Q_INVOKABLE QUrl studentPhotoUrl(int id, int level) const;
    Q_INVOKABLE QString studentFirstName(int id, int level) const;
    Q_INVOKABLE QString studentLastName(int id, int level) const;

    QString studentPhoto(int id, int level) const;
    QString studentName(int id, int level) const;
    QSqlRecord studentRecord(int id, int level) const;

    Q_INVOKABLE bool saveSponsorship(int sponsorId, int sponsoredId);

private:
    void setupModel(QSqlTableModel *model, int level);

    static int random(int min, int max, const QList<int> &excepts);

    QSqlTableModel m_level1;
    QList<int> m_level1Indexes;

    QSqlTableModel m_level2;
    int m_level2Index;
    bool m_random;
};

#endif // HELPER_H
