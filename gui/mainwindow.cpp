#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->debug = new debugWindow();

    this->debug->append(QString::fromUtf8("Created interfaces"));

    this->setupActions();

    this->network = NULL;

    this->prepareMap();
}

MainWindow::~MainWindow()
{
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

    Route * solution = this->network->findRouteBetween(startNode, endNode, this->ui->numSwitches->value());

    if(solution && solution->getLength() != 0)
    {
        this->debug->append(QString("Found solution."));
        //todo, do somethind;
    }
    else
    {
        this->debug->append(QString("No solution has been found."));
    }
}
