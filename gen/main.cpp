#include <QtGui/qguiapplication.h>

#include <QtQml/qqmlapplicationengine.h>
#include <QtQml/qqmlcontext.h>

#include <QtSql/qsqldatabase.h>

#include "helper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(app.applicationDirPath() + "/../data/database.db");
    db.open();

    Helper helper(db);
    qmlRegisterSingletonInstance("Sponsorship", 1, 0, "Sponsorship", &helper);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("roundImages", qEnvironmentVariable("IAI_SPONSORSHIP_ROUNDED", "1").toInt() == 1);
    engine.load("qrc:/qml/main.qml");

    return app.exec();
}
