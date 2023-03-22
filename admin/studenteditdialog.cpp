#include "studenteditdialog.h"
#include "ui_studenteditdialog.h"

StudentEditDialog::StudentEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentEditDialog)
{
    ui->setupUi(this);
}

StudentEditDialog::~StudentEditDialog()
{
    delete ui;
}

void StudentEditDialog::setReadOnly(bool r)
{
    if (r)
        ui->buttonBox->setStandardButtons(QDialogButtonBox::Close);
    else
        ui->buttonBox->setStandardButtons(QDialogButtonBox::Save|QDialogButtonBox::Cancel);
}

void StudentEditDialog::setPhotoDir(const QString &dir)
{
    m_photoDir = dir;
}
