#ifndef FRAMEDIALOG_H
#define FRAMEDIALOG_H

#include <QDialog>

namespace Ui {
class FrameDialog;
}

class FrameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FrameDialog(QWidget *parent = 0);
    ~FrameDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FrameDialog *ui;
};

#endif // FRAMEDIALOG_H
