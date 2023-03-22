²#include <QtWidgets/qapplication.h>

#include <QtSql/qsqldatabase.h>

#include "adminwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(app.applicationDirPath() + "/../data/database.db");
    db.open();

    AdminWindow w;
    w.show();

    return app.exec();
}
