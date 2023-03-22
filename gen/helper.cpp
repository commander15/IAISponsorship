#include "helper.h"

#include <QtSql/qsqlrecord.h>
#include <QtSql/qsqlquery.h>

#include <QtCore/qcoreapplication.h>
#include <QtCore/qfile.h>
#include <QtCore/qrandom.h>

Helper::Helper(const QSqlDatabase &db, QObject *parent) :
    QObject(parent),
    m_level1(this, db),
    m_level2(this, db),
    m_level2Index(-1),
    m_random(false)
{
    setupModel(&m_level1, 1);
    setupModel(&m_level2, 2);
}

Helper::~Helper()
{
}

bool Helper::hasNextStudentId(int level)
{
    switch (level) {
    case 1:
        return m_level1Indexes.size() < m_level1.rowCount();

    case 2:
        return true;

    default:
        return false;
    }
}

int Helper::nextStudentId(int level)
{
    if (!hasNextStudentId(level))
        return -1;

    QSqlTableModel *model;
    int index;

    switch (level) {
    case 1:
        model = &m_level1;
        index = random(0, m_level1.rowCount() - 1, m_level1Indexes);
        m_level1Indexes.append(index);
        break;

    case 2:
        model = &m_level2;
        if (!m_random) {
            index = m_level2Index + 1;
            m_level2Index = index;

            qDebug("Going to %d", index);

            if (index >= model->rowCount() - 1) {
                m_random = true;
                qDebug("Radom mode activated, row %d", index);
            }
        } else {
            index = random(0, model->rowCount() - 1, {m_level2Index});
            m_level2Index = index;
        }
        break;

    default:
        return -1;
    }

    return model->record(index).value("studentId").toInt();
}

int Helper::randomStudentId(int level)
{
    QSqlQueryModel *model = (level == 1 ? &m_level1 : &m_level2);
    int r = random(0, model->rowCount() - 1, {});
    return model->record(r).value("studentId").toInt();
}

QUrl Helper::studentPhotoUrl(int id, int level) const
{
    QString photo = studentPhoto(id, level);
    return (!photo.isEmpty() ? QUrl::fromLocalFile(photo) : QUrl());
}

QString Helper::studentFirstName(int id, int level) const
{
    QString name = studentName(id, level);

    if (!name.isEmpty() && name.contains(' ')) {
        name = name.section(' ', 0, 0).toLower();
        name[0] = name.at(0).toUpper();
    }

    return name;
}

QString Helper::studentLastName(int id, int level) const
{
    QString name = studentName(id, level);
    name = name.section(' ', -1, -1, QString::SectionFlag::SectionSkipEmpty);
    name.remove(studentFirstName(id, level));

    if (!name.isEmpty()) {
        name = name.toLower();
        name[0] = name.at(0).toUpper();
    }
    return name;
}

QString Helper::studentPhoto(int id, int level) const
{
    QString photo = studentRecord(id, level).value("studentPhoto").toString();
    if (!photo.isEmpty()) {
        const QString path = qApp->applicationDirPath() + QStringLiteral("/../data/Level%1/photos").arg(level);
        return (QFile::exists(path + '/' + photo) ? path + '/' + photo : studentPhoto(-1, -1));
    } else
        return QString();
}

QString Helper::studentName(int id, int level) const
{
    return studentRecord(id, level).value("studentName").toString();
}

QSqlRecord Helper::studentRecord(int id, int level) const
{
    const QSqlTableModel *model = (level == 1 ? &m_level1 : &m_level2);

    for (int i(0); i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);

        if (record.value("studentId").toInt() == id)
            return record;
    }

    return QSqlRecord();
}

bool Helper::saveSponsorship(int sponsorId, int sponsoredId)
{
    qDebug("%d sponsors %d", sponsorId, sponsoredId);
    QSqlQuery query(m_level1.database());
    query.prepare("INSERT INTO Sponsorships(sponsorId, sponsoredId) VALUES(?, ?)");
    query.bindValue(0, sponsorId);
    query.bindValue(1, sponsoredId);
    return query.exec();
}

void Helper::setupModel(QSqlTableModel *model, int level)
{
    model->setTable("Students");
    model->setFilter("studentLevel = " + QString::number(level));
    //model->sort(0, Qt::DescendingOrder);
    model->select();

    qDebug("%s", model->query().lastQuery().toStdString().c_str());

    qDebug("%d students on level %d", model->rowCount(), level);
}

int Helper::random(int min, int max, const QList<int> &excepts)
{
    int r;
    do r = QRandomGenerator::global()->bounded(min, max + 1);
    while (excepts.contains(r));
    return r;
}
