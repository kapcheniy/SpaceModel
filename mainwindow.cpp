#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *fileMenu = menuBar()->addMenu("Файл");

    QAction *openAction = new QAction("Открыть", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction("Сохранить", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    fileMenu->addAction(saveAction);

    QMenu *viewMenu = menuBar()->addMenu("Вид");
    QAction *fullscreenAction = viewMenu->addAction("Полноэкранный режим");
    connect(fullscreenAction, &QAction::triggered, this, &MainWindow::toggleFullScreen);
    QAction *inWinscreenAction = viewMenu->addAction("Оконный режим");
    connect(inWinscreenAction, &QAction::triggered, this, &MainWindow::toggleWinScreen);

    QMenu *simulationMenu = menuBar()->addMenu("Симуляция");
    QAction *start = simulationMenu->addAction("Построить модель");
    connect(start, &QAction::triggered, this, &MainWindow::startSimulation);
    QAction *pause = simulationMenu->addAction("Пауза");
    connect(pause, &QAction::triggered, this, &MainWindow::pauseSimulation);
    QAction *con = simulationMenu->addAction("Продолжить");
    connect(con, &QAction::triggered, this, &MainWindow::continueSimulation);
    QAction *stop = simulationMenu->addAction("Сбросить модель");
    connect(stop, &QAction::triggered, this, &MainWindow::stopSimulation);

    QMenu *add = menuBar()->addMenu("Добавить");
    QAction *sun = add->addAction("Звезду");
    connect(sun, &QAction::triggered, this, &MainWindow::addSun);
    QAction *planet = add->addAction("Планету");
    connect(planet, &QAction::triggered, this, &MainWindow::addPlanet);

    QMenu *speedMenu = menuBar()->addMenu("Скорость симуляции");
    QAction *speed025 = speedMenu->addAction("0.25x");
    connect(speed025, &QAction::triggered, [this]() { setSimulationSpeed(8); });
    QAction *speed05 = speedMenu->addAction("0.5x");
    connect(speed05, &QAction::triggered, this, [this]() { setSimulationSpeed(4); });
    QAction *speed1 = speedMenu->addAction("1x");
    connect(speed1, &QAction::triggered, this, [this]() { setSimulationSpeed(2.0); });
    QAction *speed15 = speedMenu->addAction("1.5x");
    connect(speed15, &QAction::triggered, this, [this]() { setSimulationSpeed(1.33); });
    QAction *speed2 = speedMenu->addAction("2x");
    connect(speed2, &QAction::triggered, this, [this]() { setSimulationSpeed(1); });

    QMenu *helpMenu = menuBar()->addMenu("Справка");
    QAction *aboutAction = helpMenu->addAction("О программе");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){

}

void MainWindow::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            vect.clear();
            QTextStream in(&file);
            QString str;
            while(!in.atEnd()){
                _obj t;
                str = in.readLine();
                t.name =  str;
                str = in.readLine();
                t.x =  str;
                str = in.readLine();
                t.y =  str;
                vect.push_back(t);
            }
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        }
    }
}

void MainWindow::saveFile() {
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for(size_t i=0;i<vect.size();i++){
                out<<vect[i].name<<"\n";
                out<<vect[i].x<<"\n";
                out<<vect[i].y<<"\n";
            }
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        }
    }
}

void MainWindow::showAboutDialog(){
    QWidget *helpWindow = new QWidget(this);
    helpWindow->setWindowTitle("Справка");
    helpWindow->resize(400, 300);

    if(isFull){
        QPoint centerPos = this->geometry().center() - QPoint(helpWindow->width() / 2, helpWindow->height() / 2);
        helpWindow->move(centerPos);
    }else{
        helpWindow->move(220,220);
    }
    QVBoxLayout *layout = new QVBoxLayout(helpWindow);

    QTextEdit *helpText = new QTextEdit(helpWindow);
    helpText->setReadOnly(true);
    helpText->setText(
        "Справка для проекта 'Модель космической системы'\n\n"
        "Этот проект моделирует движение объектов в космической системе, таких как планеты и звёзды.\n\n"
        "Основные возможности:\n"
        "1. Визуализация: Реализация планетарной системы с использованием QGraphicsScene и QGraphicsView.\n"
        "2. Динамика: Объекты движутся под воздействием гравитационных сил.\n"
        "3. Настройка: Возможность изменения скорости симуляции.\n\n"
        "Управление:\n"
        "- Вы можете менять скорость симуляции через соответствующее меню.\n"
        "- Объекты добавляются и обрабатываются через вектор параметров vect."
        );
    layout->addWidget(helpText);

    QPushButton *closeButton = new QPushButton("Закрыть", helpWindow);
    connect(closeButton, &QPushButton::clicked, helpWindow, &QWidget::close);
    layout->addWidget(closeButton);

    helpWindow->show();
}
void MainWindow::toggleFullScreen(){
    if(!this->isFullScreen()) {
        this->showFullScreen();
        isFull = true;
    }
}
void MainWindow::toggleWinScreen(){
    if(this->isFullScreen())  {
        this->showNormal();
        isFull = false;
    }

}
void MainWindow::closeSimulationWindow(){
    sceneWindow->close();
}
void MainWindow::startSimulation(){
    // sceneWindow = new QWidget;
    // sceneWindow->setWindowTitle("Солнечная система");

    // QGraphicsScene *scene = new QGraphicsScene;

    // scene->setSceneRect(-400, -400, 800, 800);

    // system = new SolarSystem(scene,vect);
    // QGraphicsView *view = new QGraphicsView(scene);
    // view->setRenderHint(QPainter::Antialiasing);

    // QVBoxLayout *layout = new QVBoxLayout;
    // layout->addWidget(view);
    // sceneWindow->setLayout(layout);

    // sceneWindow->setWindowModality(Qt::WindowModal);
    // sceneWindow->setAttribute(Qt::WA_DeleteOnClose);

    // sceneWindow->setGeometry(100, 100, 800, 800);

    // sceneWindow->showFullScreen();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-400, -400, 800, 800);
    simulationSpeed = 2;
    system = new SolarSystem(scene,vect, simulationSpeed);

    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(view);
    pauseSimulation();
}
void MainWindow::pauseSimulation(){
    system->updateSimulationSpeed(100000000);
}
void MainWindow::continueSimulation(){
    system->updateSimulationSpeed(2);
}
void MainWindow::stopSimulation(){
    view->close();
    vect.clear();
}

void MainWindow::setSimulationSpeed(double val){
    if (val > 0) {
        simulationSpeed = val;  // Обновляем значение скорости
        system->updateSimulationSpeed(simulationSpeed);  // Сообщаем SolarSystem о новой скорости
    }
}
void MainWindow::addSun(){
    _obj t;
    t.name = "sun";
    t.x =  0;
    t.y =  0;
    vect.push_back(t);
    view->close();
    startSimulation();
}
void MainWindow::addPlanet(){
    _obj t;
    t.name = "planet";
    t.x =  0;
    t.y =  0;
    vect.push_back(t);
    view->close();
    startSimulation();
}
