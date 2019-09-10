#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVector>
#include <QtMath>
#include <QTimer>
#include <QThread>

class Widget : public QGraphicsView
{
    Q_OBJECT
public slots:
    void to_zero();
    void to_max();
    void sunshine();
public:
    ///таймеры
    QTimer *tmr;
    QTimer *tms;
    QTimer *shn;

    bool shining = false;
    bool sun = false;
    bool persp = false;

    qreal point_persp = 500;

    QVector<QVector <qreal>> Mx; //матрица X'ов
    QVector<QVector <qreal>> My; //матрица Y'ов
    QVector<QVector <qreal>> Mz; //матрица Z'ов

    QVector<QVector <qreal>> T;

    QVector<QVector <qreal>> Figure;        //матрица фигуры
    QVector<QVector <int>> F_rel;           //матрица связей фигуры

    QVector<QVector<qreal>> D;              //матрица буквы D
    QVector<QVector <int>> D_rel;           //матрицы связи D

    QVector<QVector <qreal>> coordinats;    //координаты
    QVector<QVector <int>> relations;       //связи координат

    QGraphicsScene *scene;                  //класс 2D графики

    qreal angX=0;                           //начальный угол x
    qreal angY=0;                           //начальный угол y
    qreal angZ=0;                           //начальный угол z

    qreal dX = 0.8;                         //начальный размер x
    qreal dY = 0.8;                         //начальный размер y
    qreal dZ = 0.8;                         //начальный размер z

    double timerF = 0.05;
    double timerS = 0;

    void draw(QVector<QVector <qreal>>);    //отрисовка фигуры
    void generate_D();                      //генерация D
    void generate_Figure();                 //создание проволочной фигуры
    void generate_all_M();
    void push_XYZ(int cor, int x, int y, int z);     //пуш xyz

    /// Умножение координатных матриц
    QVector<QVector <qreal>> multi_matrixs(QVector<QVector <qreal>> a, QVector<QVector <qreal>> b);

    QVector<QVector <qreal>> affRx(QVector<QVector <qreal>> a);
    QVector<QVector <qreal>> affRy(QVector<QVector <qreal>> a);
    QVector<QVector <qreal>> affRz(QVector<QVector <qreal>> a);
    QVector<QVector <qreal>> affD(QVector<QVector <qreal>> a);

    /// Отслеживание нажатия/отпускания клавиш
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

     /// Конструктор/деконструктор
     Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
