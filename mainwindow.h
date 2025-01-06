#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include "_obj.h"
#include "solarsystem.h"
#include <QTextEdit>
#include <QGraphicsProxyWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void openFile();
    void saveFile();
    void showAboutDialog();
    void toggleFullScreen();
    void toggleWinScreen();
    void closeSimulationWindow();
    void startSimulation();
    void pauseSimulation();
    void continueSimulation();
    void stopSimulation();
    void setSimulationSpeed(double val);
    void addSun();
    void addPlanet();
private:
    Ui::MainWindow *ui;
    SolarSystem *system;
    std::vector<_obj> vect;
    QWidget *sceneWindow;

    QGraphicsScene *scene;
    QGraphicsView *view;
    double simulationSpeed;
    bool isFull = false;
};
#endif // MAINWINDOW_H
