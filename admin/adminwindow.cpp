#include "adminwindow.h"
#include "ui_adminwindow.h"

#include <QtSql/qsqlrecord.h>

#include <QtCore/qstandardpaths.h>
#include <QtCore/qdir.h>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow),
    m_actions(this)
{
    ui->setupUi(this);

    ui->actionStudents->trigger();
    connect(ui->actionStudents, &QAction::triggered, this, [=] {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->actionSponsorships, &QAction::triggered, this, [=] {
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->actionSettings, &QAction::triggered, this, [=] {
        ui->stackedWidget->setCurrentIndex(2);
    });

    ui->studentView->setModel(&m_studentModel);
    connect(ui->studentView, &QAbstractItemView::doubleClicked, this, &AdminWindow::showStudent);

    ui->sponsorshipView->setModel(&m_sponsorshipModel);
    connect(ui->sponsorshipView, &QAbstractItemView::doubleClicked, this, &AdminWindow::showSponsorship);

    changeButtonStates(0);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &AdminWindow::changeButtonStates);

    QString photoDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/IAI/Sponsorship";
    ui->dirInput->setText(QDir::toNativeSeparators(photoDir));

    m_actions.setExclusive(true);
    m_actions.addAction(ui->actionStudents);
    m_actions.addAction(ui->actionSponsorships);
    m_actions.addAction(ui->actionSettings);

    m_studentDialog.setPhotoDir(photoDir);

    setupModels();
    setupViews();
    translate();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

bool AdminWindow::event(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        translate();
        return true;
    } else
        return QMainWindow::event(e);
}

void AdminWindow::changeButtonStates(int index)
{
    bool edit;
    bool print;
    bool deleteData;

    switch (index) {
    case 0:
        edit = true;
        deleteData = true;
        print = false;
        break;

    case 1:
        edit = false;
        deleteData = true;
        print = true;
        break;

    default:
        edit = false;
        deleteData = false;
        print = false;
        break;
    }

    ui->editButton->setEnabled(edit);
    ui->deleteButton->setEnabled(deleteData);
    ui->printButton->setEnabled(print);

    ui->buttonsWidget->setVisible(index >= 0 && index <= 1);
}

void AdminWindow::showStudent(const QModelIndex &index)
{
    QSqlRecord rec = m_studentModel.record(index.row());

    m_studentDialog.setReadOnly(true);
    m_studentDialog.exec();
}

void AdminWindow::addStudent()
{
    //
    m_studentDialog.setReadOnly(false);
    if (m_studentDialog.exec()) {
        //
    }
}

void AdminWindow::editStudent()
{
    //
    m_studentDialog.setReadOnly(false);
    if (m_studentDialog.exec())
        ;
}

void AdminWindow::deleteStudent()
{
    //
}

void AdminWindow::showSponsorship(const QModelIndex &index)
{
    //
}

void AdminWindow::setupViews()
{
    QHeaderView *view;

    view = ui->studentView->horizontalHeader();
    view->setSectionResizeMode(0, QHeaderView::Stretch);
    view->setSectionResizeMode(1, QHeaderView::Fixed);

    view = ui->sponsorshipView->horizontalHeader();
    view->setSectionResizeMode(0, QHeaderView::Stretch);
    view->setSectionResizeMode(1, QHeaderView::Stretch);
}

void AdminWindow::setupModels()
{
    refreshStudentModel();
    refreshSponsorshipModel();
}

void AdminWindow::refreshStudentModel()
{
    QString query = "SELECT studentName, studentLevel FROM Students";
    m_studentModel.setQuery(query);
}

void AdminWindow::refreshSponsorshipModel()
{
    QString query = "SELECT Sponsors.studentName, Sponsoreds.studentName "
             "FROM Sponsorships "
             "LEFT JOIN Students AS Sponsors   ON Sponsors.studentId = Sponsorships.sponsorId "
             "LEFT JOIN Students AS Sponsoreds ON Sponsoreds.studentId = Sponsorships.sponsoredId "
             "ORDER BY 1";
     m_sponsorshipModel.setQuery(query);
}

void AdminWindow::translate()
{
    m_studentModel.setHeaderData(0, Qt::Horizontal, tr("Name"));
    m_studentModel.setHeaderData(1, Qt::Horizontal, tr("Level"));

    m_sponsorshipModel.setHeaderData(0, Qt::Horizontal, tr("Sponsor"));
    m_sponsorshipModel.setHeaderData(1, Qt::Horizontal, tr("Sponsored"));
}
