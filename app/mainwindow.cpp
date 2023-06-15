#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButtonRun_clicked()
{
    ui->graph->clearGraphs();
    const double a = ui->lineEditA->text().toDouble();
    const double b = ui->lineEditB->text().toDouble();
    const double c = ui->lineEditC->text().toDouble();
    const double d = ui->lineEditD->text().toDouble();
    const double leftBound = ui->lineEditLeftBound->text().toDouble();
    const double rightBound = ui->lineEditRightBound->text().toDouble();
    const double eps = ui->lineEditEps->text().toDouble();
    const double maxIter = ui->lineEditNmax->text().toDouble();
    std::function<double(double)> f = [&a, &b, &c, &d](double x){ return a*sin(b*x)+c*cos(d*x); };

    QVector<double> x;
    QVector<double> y;
    double xi = leftBound;
    double h = 0.01;
    while (xi < rightBound) {
        x.append(xi);
        y.append(f(xi));
        xi += h;
    }
    x.append(rightBound);
    y.append(f(rightBound));
    ui->graph->addGraph();
    ui->graph->graph(0)->addData(x, y);


    Problem problem(f, leftBound, rightBound);
    StopCondition stop(eps, maxIter);
    Algorithm *alg = nullptr;
    if (ui->radioButtonEnum->isChecked())
        alg = new Enumeration(problem, stop);
    else if (ui->radioButtonPiavski->isChecked()) {
        const double m = ui->lineEditM->text().toDouble();
        alg = new Piyavsky(problem, stop, m);
    }
    else if (ui->radioButtonStrongin->isChecked()) {
        const double r = ui->lineEditR->text().toDouble();
        alg = new Strongin(problem, stop, r);
    }
    alg->run();

    const double &iterCount = alg->solution().iterationCount;
    const double &fmin = alg->solution().optimum.z;
    const double &xmin = alg->solution().optimum.x;
    const std::vector<Point> &trials = alg->solution().trials;
    ui->lineEditXmin->setText(QString::number(xmin));
    ui->lineEditFmin->setText(QString::number(fmin));
    ui->lineEditN->setText(QString::number(iterCount));

    QVector<double> xtrial;
    QVector<double> ytrial(trials.size(), 0.0);
    for (const Point& point : trials) {
        xtrial.append(point.x);
    }
    ui->graph->addGraph();
    ui->graph->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->graph->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->graph->graph(1)->setPen(QPen(Qt::green));
    ui->graph->graph(1)->addData(xtrial, ytrial);

    ui->graph->addGraph();
    ui->graph->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->graph->graph(2)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->graph->graph(2)->setPen(QPen(QBrush(Qt::red), 2));
    ui->graph->graph(2)->addData(xmin, fmin);

    ui->graph->rescaleAxes();
    QCPRange yr = ui->graph->yAxis->range();
    yr.lower -= 0.15;
    yr.upper += 0.15;
    ui->graph->yAxis->setRange(yr);
    ui->graph->replot();
}
