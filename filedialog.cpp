#include "filedialog.h"
#include "ui_filedialog.h"
#include <QDirModel>
#include <QItemSelectionModel>

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);

    dirModel = new QDirModel;
    selModel = new QItemSelectionModel(dirModel);

    ui->listView->setModel(dirModel);
    ui->treeView->setModel(dirModel);
    ui->iconView->setModel(dirModel);

    ui->listView->setSelectionModel(selModel);
    ui->treeView->setSelectionModel(selModel);
    ui->iconView->setSelectionModel(selModel);

    QModelIndex cwdIndex = dirModel->index(QDir::rootPath());
    ui->listView->setRootIndex(cwdIndex);
    ui->treeView->setRootIndex(cwdIndex);
    ui->iconView->setRootIndex(cwdIndex);

    for (int r = 0; r < dirModel->rowCount(QModelIndex()); ++r)
    {
        QModelIndex index = dirModel->index(r,0,QModelIndex());
        if (index.isValid())
            ui->comboBox->addItem(dirModel->fileIcon(index),dirModel->filePath(index));
    }

    connect(ui->listView, SIGNAL(activated(const QModelIndex&)), this, SLOT(switchToDir(const QModelIndex&)));
    connect(ui->treeView, SIGNAL(activated(const QModelIndex&)), this, SLOT(switchToDir(const QModelIndex&)));
    connect(ui->iconView, SIGNAL(activated(const QModelIndex&)), this, SLOT(switchToDir(const QModelIndex&)));

    connect(ui->listView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(syncActive(const QModelIndex&)));
    connect(ui->treeView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(syncActive(const QModelIndex&)));
    connect(ui->iconView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(syncActive(const QModelIndex&)));

    connect(ui->switchButton, SIGNAL(clicked()), this, SLOT(switchView()));
}

QStringList FileDialog::selectFiles()
{
    QStringList fileNames;
    QModelIndexList indexes = selModel->selectedIndexes();

    foreach (QModelIndex index, indexes)
    {
        fileNames.append(dirModel->filePath(index));
    }
    return fileNames;
}

FileDialog::~FileDialog()
{
    delete ui;
}

void FileDialog::switchToDir(const QModelIndex& index)
{
    if (dirModel->isDir(index))
    {
        ui->listView->setRootIndex(index);
        ui->iconView->setRootIndex(index);
        ui->treeView->setExpanded(index,true);

    }
}

void FileDialog::syncActive(const QModelIndex& index)
{
    ui->listView->setCurrentIndex(index);
    ui->treeView->setCurrentIndex(index);
    ui->iconView->setCurrentIndex(index);
}

void FileDialog::switchView()
{
    ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex()+1) % ui->stackedWidget->count());
}
