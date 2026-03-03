#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "optiondialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleOptionsButton);
    ui->treeView->addAction(ui->actionItem_Options);

    connect(this, &MainWindow::statusUpdateMessage,
            ui->statusbar, &QStatusBar::showMessage);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);

    this->partList = new ModelPartList("PartsList");

    ui->treeView->setModel(this->partList);

    ModelPart* rootItem = this->partList->getRootItem();

    for (int i = 0; i < 3; i++) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        ModelPart* childItem = new ModelPart({ name, visible,255,255,255 });
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++) {
            QString subName = QString("Item %1,%2").arg(i).arg(j);
            ModelPart* childChildItem = new ModelPart({ subName, visible,255,255,255 });
            childItem->appendChild(childChildItem);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton() {
    emit statusUpdateMessage( QString("Add button was clicked") , 0 );
}

void MainWindow::handleTreeClicked() {
    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);
}

// Slot function added to MainWindow.cpp
void MainWindow::on_actionOpen_File_triggered() {
        // Add this line of code so you can see if the action is working
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)")
        );

        if (!fileName.isEmpty()) {
            QFileInfo fileInfo(fileName);
            QString onlyFileName = fileInfo.baseName();
            QModelIndex index = ui->treeView->currentIndex();

            if (index.isValid()) {
                ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
                selectedPart->set(0, onlyFileName);
                emit statusUpdateMessage(QString("Item renamed to: ") + onlyFileName, 0);
            } else {
                emit statusUpdateMessage(QString("File chosen, but no item selected!"), 0);
            }
        }

}

void MainWindow::handleOptionsButton() {
    QModelIndex index = ui->treeView->currentIndex();

    if (!index.isValid()) {
        emit statusUpdateMessage(QString("Please select an item first!"), 0);
        return;
    }

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    OptionDialog dialog(this);

    dialog.setInitialData(
        selectedPart->data(0).toString(),
        selectedPart->data(1).toBool(),
        selectedPart->data(2).toInt(),    // 红色
        selectedPart->data(3).toInt(),    // 绿色
        selectedPart->data(4).toInt()     // 蓝色
        );

    if (dialog.exec() == QDialog::Accepted) {
        QString newName = dialog.getName();
        bool newVisible = dialog.getIsVisible();

        selectedPart->set(0, newName);
        selectedPart->set(1, newVisible);
        selectedPart->set(2, dialog.getR());
        selectedPart->set(3, dialog.getG());
        selectedPart->set(4, dialog.getB());

        emit statusUpdateMessage(QString("Dialog accepted: Item updated"), 0);
    } else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }
}

void MainWindow:: on_actionItem_Options_triggered () {
    handleOptionsButton();
}
