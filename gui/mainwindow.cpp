#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    this->debug = new debugWindow();

    this->settings = new Settings();

    this->debug->append(QString::fromUtf8("Created interfaces"));

    this->setupActions();

    this->network = NULL;

    this->prepareMap();
}

MainWindow::~MainWindow()
{
    if(this->debug) delete this->debug;

    if(this->settings) delete this->settings;

    delete ui;
}

void MainWindow::setupActions()
{
    connect(this->ui->actionDebug, SIGNAL(triggered()), this, SLOT(manageDebugWindow()));

    connect(this->ui->actionLoadGTFS, SIGNAL(triggered()), this, SLOT(loadGTFS()));
    connect(this->ui->actionLoadJSON, SIGNAL(triggered()), this, SLOT(loadJSON()));
    connect(this->ui->actionLoadMulJSON, SIGNAL(triggered()), this, SLOT(loadMulJSON()));
    connect(this->ui->actionLoadSavedDB, SIGNAL(triggered()), this, SLOT(loadSavedDB()));

    connect(this->ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(this->ui->actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(this->ui->search, SIGNAL(clicked()), this, SLOT(findRoute()));

    connect(this->ui->settingsButton, SIGNAL(clicked()), this->settings, SLOT(toggleVisibility()));
    this->debug->append(QString::fromUtf8("Actions assigned."));
}

void MainWindow::manageDebugWindow()
{
    if(this->debug != NULL)
    {
        this->debug->show();
    }
    else
    {
        this->debug = new debugWindow();
        this->debug->show();
    }
}

void MainWindow::loadFromFile(DataBase::LoadMethod method)
{
    if(this->network)
    {
        delete this->network;
        this->network = NULL;
    }

    QString filename;
    if(method == DataBase::LoadMethod::GTFS)
    {
        //filename = QFileDialog::getExistingDirectory(this, tr("test"), ".", QFileDialog::Sh | QFileDialog::DontResolveSymlinks);
        filename = QFileDialog::getOpenFileName(this, tr("Select .zip file containing GTFS database"), "ping");
    }
    else if(method == DataBase::LoadMethod::JSON)
    {
        filename = QFileDialog::getOpenFileName(this, tr("Select .json file containing database"), "ping");
    }
    else if(method == DataBase::LoadMethod::MULTJSON)
    {
        filename = QFileDialog::getExistingDirectory(this, tr("Select directory containing json files"), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    else if(method == DataBase::LoadMethod::SAVEDDB)
    {
        filename = QFileDialog::getOpenFileName(this, tr("Select .json file containing database"), "ping");
    }
    else
    {
        this->debug->append("Unsuspected behavior while loading database.");
    }

    this->debug->append(QString("Given path: ") + filename);
    DataBase db(method, filename.toStdString());

    if(!db.isValid())
    {
        this->debug->append("Database invalid!");
    }
    else
    {
        this->network = new Network(db);

        this->debug->append(QString("Database loaded successfully"));

        this->prepareGUI();
    }
}

void MainWindow::loadGTFS()
{
    this->loadFromFile(DataBase::LoadMethod::GTFS);
}

void MainWindow:: loadJSON()
{
    this->loadFromFile(DataBase::LoadMethod::JSON);
}

void MainWindow::loadMulJSON()
{
    this->loadFromFile(DataBase::LoadMethod::MULTJSON);
}

void MainWindow::loadSavedDB()
{
    this->loadFromFile(DataBase::LoadMethod::SAVEDDB);
}

void MainWindow::prepareGUI()
{
    if(!this->network)
        return;

    for(Node * n: this->network->getAllNodes())
    {
        this->ui->startNode->addItem(QString::fromStdString(n->getName()));
        this->ui->endNode->addItem(QString::fromStdString(n->getName()));
    }

    this->ui->routeTime->setTime(QTime::currentTime());
    this->ui->routeDate->setDate(QDate::currentDate());

    this->debug->append(QString("GUI repainted."));
}
void MainWindow::prepareMap()
{
    QFile apiFile("API_KEY");
    apiFile.open(QIODevice::ReadOnly);
    QTextStream stream(&apiFile);
    QString line = stream.readLine();
    if(line.length() == 0)
    {
        this->debug->append("No api key found");
    }
    else
    {
        this->debug->append("API key loaded.");
        this->apiKey = line;
    }

    this->ui->map->setHtml(QString("<center><iframe width=\"600\" height=\"450\" frameborder=\"0\" style=\"border:0\" \
                               src=\"https://www.google.com/maps/embed/v1/view?zoom=11&center=50.0647%2C19.9450&key=" + this->apiKey + "\"> \
                                </iframe></center>"));

    this->updateMap();

}

void MainWindow::updateMap()
{
    if(this->ui->map)
    {
        this->ui->map->update();
        this->debug->append("Map refreshed.");
    }
    else
    {
        this->debug->append("Map does not exists.");
    }
}

void MainWindow::showHelp()
{

}

void MainWindow::findRoute()
{
    if(!this->network)
    {
        this->debug->append(QString("findRoute method called but no network exists."));
        return;
    }

    Solver * s = this->settings->getCurrentSolver();
    if(s == NULL)
    {
        this->debug->append(QString("findRoute method called but no algorithm selected."));
        return;
    }
    else
    {
        this->debug->append(QString("findRoute method called with ") + QString::fromStdString(s->getName()) + QString( " alg."));
        this->network->setSolver(s);
    }



    QString startNodeName = this->ui->startNode->currentText();
    QString endNodeName = this->ui->endNode->currentText();


    this->debug->append(QString("findRoute method has been called."));
    this->debug->append(QString("Params:"));
    this->debug->append(QString(" * Time and date: ") + this->ui->routeTime->time().toString(QString("hh:mm")) + " " + this->ui->routeDate->date().toString("dd.M.yyyy"));
    this->debug->append(QString(" * Max switches ") + QString::number(this->ui->numSwitches->value()));
    this->debug->append(QString(" * Starting node is ") + QString::number(this->ui->startNode->currentIndex()) + ": " + startNodeName);
    this->debug->append(QString(" * Ending node is ") + QString::number(this->ui->endNode->currentIndex()) + ": " + endNodeName);

    this->debug->append(QString("Calling searching method."));

    Node * startNode = NULL;
    Node * endNode = NULL;
    std::list<Node *> nodes = this->network->getAllNodes();
    for(Node * n: nodes)
    {
        if(QString::fromStdString(n->getName()) == startNodeName)
            startNode = n;
        if(QString::fromStdString(n->getName()) == endNodeName)
            endNode = n;


        if(startNode && endNode)
            break;
    }
    if(!(startNode && endNode))
    {
        this->debug->append(QString("Start or end node not found, aborting."));
        return;
    }

    if(startNode == endNode)
    {
        this->debug->append(QString("Nodes are equal, no need for searching."));
        return;
    }

    Route * solution = this->network->findRouteBetween(startNode, endNode, this->ui->numSwitches->value(), Time(1000));

    if(solution && solution->getLength() != 0)
    {
        this->debug->append(QString("Found solution."));

        this->showRouteOnMap(solution);

        std::cout << *solution;
    }
    else
    {
        this->debug->append(QString("No solution has been found."));
    }
}
    delete ui;
}
    if(this->debug)
        delete this->debug;
    delete ui;
}

void MainWindow::setupActions()
{
    connect(this->ui->actionDebug, SIGNAL(triggered()), this, SLOT(manageDebugWindow()));
    connect(this->ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFromFile()));
    connect(this->ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(this->ui->actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(this->ui->search, SIGNAL(clicked()), this, SLOT(findRoute()));
    this->debug->append(QString::fromUtf8("Actions assigned."));
}


void MainWindow::manageDebugWindow()
{
    if(this->debug != NULL)
    {
        this->debug->show();
    }
    else
    {
        this->debug = new debugWindow();
        this->debug->show();
    }
}

void MainWindow::loadFromFile()
{
    if(this->network)
    {
        delete this->network;
        this->network = NULL;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("test"), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    this->debug->append(QString("Loading database from directory ") + filename);
    this->network = new Network();
    this->network->loadFromFile(filename.toStdString());
    this->debug->append(QString("Database loaded successfully"));

    this->prepareGUI();
}

void MainWindow::prepareGUI()
{
    if(!this->network)
        return;

    for(Node * n: this->network->getAllNodes())
    {
        this->ui->startNode->addItem(QString::fromStdString(n->getName()));
        this->ui->endNode->addItem(QString::fromStdString(n->getName()));
    }

    this->ui->routeTime->setTime(QTime::currentTime());
    this->ui->routeDate->setDate(QDate::currentDate());

    this->debug->append(QString("GUI repainted."));
}

void MainWindow::showHelp()
{

}

void MainWindow::findRoute()
{
    if(!this->network)
    {
        this->debug->append(QString("findRoute method called but no network exists."));
        return;
    }

    QString startNodeName = this->ui->startNode->currentText();
    QString endNodeName = this->ui->endNode->currentText();


    this->debug->append(QString("findRoute method has been called."));
    this->debug->append(QString("Params:"));
    this->debug->append(QString(" * Time and date: ") + this->ui->routeTime->time().toString(QString("hh:mm")) + " " + this->ui->routeDate->date().toString("dd.M.yyyy"));
    this->debug->append(QString(" * Max switches ") + QString::number(this->ui->numSwitches->value()));
    this->debug->append(QString(" * Starting node is ") + QString::number(this->ui->startNode->currentIndex()) + ": " + startNodeName);
    this->debug->append(QString(" * Ending node is ") + QString::number(this->ui->endNode->currentIndex()) + ": " + endNodeName);

    this->debug->append(QString("Calling searching method."));

    Node * startNode = NULL;
    Node * endNode = NULL;
    std::list<Node *> nodes = this->network->getAllNodes();
    for(Node * n: nodes)
    {
        if(QString::fromStdString(n->getName()) == startNodeName)
            startNode = n;
        if(QString::fromStdString(n->getName()) == endNodeName)
            endNode = n;


        if(startNode && endNode)
            break;
    }
    if(!(startNode && endNode))
    {
        this->debug->append(QString("Start or end node not found, aborting."));
        return;
    }

    if(startNode == endNode)
    {
        this->debug->append(QString("Nodes are equal, no need for searching."));
        return;
    }

    Route * solution = this->network->findRouteBetween(startNode, endNode);

    if(solution && solution->getLength() != 0)
    {
        this->debug->append(QString("Found solution."));
        //todo, do somethind;
    }
    else
    {
        this->debug->append(QString("No solution has been found."));

void MainWindow::showRouteOnMap(Route * r)
{
    this->debug->append("Showing route on map.");
    for(auto it = r->begin(); it != r->end(); it++)
    {
        this->debug->append("Adding points into map");
        double lon = (*it)->getStartNode()->getLongtitude();
        double lat = (*it)->getStartNode()->getLatitude();
        this->debug->append(QString("Coords: ") + QString::number(lat) + ' ' + QString::number(lon));
    }
}
