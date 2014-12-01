#include "debugwindow.h"
#include "ui_debugwindow.h"

debugWindow::debugWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::debugWindow)
{
    ui->setupUi(this);

    this->file = NULL;
    this->stream = NULL;

    this->ui->log->setReadOnly(true);
    this->ui->fileName->setText(QTime::currentTime().toString() + QString(".log"));
}

debugWindow::~debugWindow()
{
    delete ui;
}

void debugWindow::append(const QString &str)
{
    QString msg = this->getCurrentTime() + str;
    this->ui->log->append(msg);
    if(this->stream)
    {
        (*this->stream) << msg << endl;
    }

}

void debugWindow::on_logIntoFile_pressed()
{

    if(!this->ui->logIntoFile->isChecked()) //unknown behavior as it should work without "!"
    {
        if(this->ui->fileName->text().isEmpty())
        {
            this->append(QString("No filename specified for logging."));
            this->ui->logIntoFile->toggle();
        }
        else
        {
            this->append(QString("Saving into file ") + this->ui->fileName->text());
            this->file = new QFile(this->ui->fileName->text());
            this->file->open(QIODevice::WriteOnly);
            this->stream = new QTextStream(this->file);

            //copy all lines from log into file
            (*this->stream) << this->ui->log->toPlainText() << endl;
        }
    }
    else
    {
        this->append(QString("Saving into file aborted."));
        //destroy file handle.
        if(this->stream)
        {
            delete this->stream;
            this->stream = NULL;
        }
        if(this->file)
        {
            delete this->file;
            this->file = NULL;
        }
    }
}

void debugWindow::on_clear_pressed()
{
    if(this->ui->logIntoFile->isChecked())
        this->ui->logIntoFile->click();//emulate toogle of log button to get rid of file logging
    this->ui->log->setText(QString());
    this->ui->fileName->setText(QTime::currentTime().toString() + QString(".log"));
    this->append(QString("Log cleared"));
}

QString debugWindow::getCurrentTime()
{
    return QTime::currentTime().toString(QString("hh:mm:ss.zzz: "));
}


