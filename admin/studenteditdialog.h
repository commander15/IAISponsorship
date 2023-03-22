#ifndef STUDENTEDITDIALOG_H
#define STUDENTEDITDIALOG_H

#include <QDialog>

namespace Ui {
class StudentEditDialog;
}

class StudentEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentEditDialog(QWidget *parent = nullptr);
    ~StudentEditDialog();

    void setReadOnly(bool r);

    void setPhotoDir(const QString &dir);

private:
    Ui::StudentEditDialog *ui;

    QString m_photoDir;
};

#endif // STUDENTEDITDIALOG_H
