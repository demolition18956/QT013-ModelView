#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>

class QModelIndex;
class QDirModel;
class QItemSelectionModel;

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileDialog(QWidget *parent = nullptr);
    QStringList selectFiles();
    ~FileDialog();

protected slots:
    void switchToDir(const QModelIndex& index);
    void syncActive(const QModelIndex& index);
    void switchView();

private:
    Ui::FileDialog *ui;
    QItemSelectionModel *selModel;
    QDirModel* dirModel;
};

#endif // FILEDIALOG_H
