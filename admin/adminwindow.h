#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qactiongroup.h>

#include <QtSql/qsqlquerymodel.h>

#include "studenteditdialog.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

    bool event(QEvent *e) override;

private:
    Q_SLOT void changeButtonStates(int index);

    Q_SLOT void showStudent(const QModelIndex &index);
    Q_SLOT void addStudent();
    Q_SLOT void editStudent();
    Q_SLOT void deleteStudent();

    Q_SLOT void showSponsorship(const QModelIndex &index);

    void setupViews();
    void setupModels();

    void refreshStudentModel();
    void refreshSponsorshipModel();

    void translate();

    Ui::AdminWindow *ui;
    QActionGroup m_actions;

    StudentEditDialog m_studentDialog;

    QSqlQueryModel m_studentModel;
    QSqlQueryModel m_sponsorshipModel;
};

#endif // ADMINWINDOW_H
