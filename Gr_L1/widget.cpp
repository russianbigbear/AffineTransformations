#include "widget.h"

/*конструктор виджета*/
Widget::Widget(QWidget *parent) : QGraphicsView(parent)
{   
    tmr = new QTimer(); //запоминаем текущее время
    tmr->setSingleShot(false);
    //соединяем сигнал timeout tmr со слотом to_zero
    connect(tmr, SIGNAL(timeout()), this, SLOT(to_zero()));

    shn = new QTimer();
    shn->setSingleShot(false);
    connect(shn, SIGNAL(timeout()), this, SLOT(sunshine()));

    tms = new QTimer();
    tms->setSingleShot(false);
    connect(tms, SIGNAL(timeout()), this, SLOT(to_max()));

    this->setMinimumSize(800,600);          //минимальный размер окна
    this->scene = new QGraphicsScene();     //класс графики
    this->setScene(scene);
    this->setSceneRect(0,0,1, 1);           //создание прямоугольной сцены

    coordinats.resize(36);                  //кол.стр. матрица coordinats
    relations.resize(62);                   //кол.стр. матрица relations
    generate_Figure();                      //создание фигуры

    //присваевыем созданное
    Figure = coordinats;
    F_rel = relations;

    //очищаем матрицы
    coordinats.clear();
    relations.clear();

    //переопределяем размеры
    coordinats.resize(24);
    relations.resize(36);
    generate_D();

    //присваевыем созданное
    D = coordinats;
    D_rel = relations;

    //generate_all_M();
}

//пуш точки
 void Widget::push_XYZ(int cor, int x, int y, int z)
 {
     coordinats[cor].push_back(x);
     coordinats[cor].push_back(y);
     coordinats[cor].push_back(z);
 }

QVector<QVector <qreal>> Widget::affD(QVector<QVector <qreal>> a){

    QVector<QVector <qreal>> D;
    D.resize(4);

    D[0].push_back(dX);
    D[0].push_back(0);
    D[0].push_back(0);
    D[0].push_back(0);

    D[1].push_back(0);
    D[1].push_back(dY);
    D[1].push_back(0);
    D[1].push_back(0);

    D[2].push_back(0);
    D[2].push_back(0);
    D[2].push_back(dZ);
    D[2].push_back(0);

    D[3].push_back(0);
    D[3].push_back(0);
    D[3].push_back(0);
    D[3].push_back(0);

    return multi_matrixs(a,D);
}
QVector<QVector <qreal>> Widget::affRx(QVector<QVector <qreal>> a)
{
    QVector<QVector <qreal>> Rx;
    Rx.resize(4);
    Rx[0].push_back(1);
    Rx[0].push_back(0);
    Rx[0].push_back(0);
    Rx[0].push_back(0);

    Rx[1].push_back(0);
    Rx[1].push_back(qCos(angX));
    Rx[1].push_back(-qSin(angX));
    Rx[1].push_back(0);

    Rx[2].push_back(0);
    Rx[2].push_back(qSin(angX));
    Rx[2].push_back(qCos(angX));
    Rx[2].push_back(0);

    Rx[3].push_back(0);
    Rx[3].push_back(0);
    Rx[3].push_back(0);
    Rx[3].push_back(1);

    return multi_matrixs(a, Rx);
}

QVector<QVector <qreal>> Widget::affRy(QVector<QVector <qreal>> a){
    QVector<QVector <qreal>> Ry;
    Ry.resize(4);
    Ry[0].push_back(qCos(angY));
    Ry[0].push_back(0);
    Ry[0].push_back(qSin(angY));
    Ry[0].push_back(0);

    Ry[1].push_back(0);
    Ry[1].push_back(1);
    Ry[1].push_back(0);
    Ry[1].push_back(0);

    Ry[2].push_back(-qSin(angY));
    Ry[2].push_back(0);
    Ry[2].push_back(qCos(angY));
    Ry[2].push_back(0);

    Ry[3].push_back(0);
    Ry[3].push_back(0);
    Ry[3].push_back(0);
    Ry[3].push_back(1);

    return multi_matrixs(a, Ry);
}

QVector<QVector <qreal>> Widget::affRz(QVector<QVector <qreal>> a){
    QVector<QVector <qreal>> Rz;
    Rz.resize(4);
    Rz[0].push_back(qCos(angZ));
    Rz[0].push_back(-qSin(angZ));
    Rz[0].push_back(0);
    Rz[0].push_back(0);

    Rz[1].push_back(qSin(angZ));
    Rz[1].push_back(qCos(angZ));
    Rz[1].push_back(0);
    Rz[1].push_back(0);

    Rz[2].push_back(0);
    Rz[2].push_back(0);
    Rz[2].push_back(1);
    Rz[2].push_back(0);

    Rz[3].push_back(0);
    Rz[3].push_back(0);
    Rz[3].push_back(0);
    Rz[3].push_back(1);

    return multi_matrixs(a, Rz);
}

/*генерация матриц координат*/
void Widget::generate_all_M(){
    //Mx
    {
        Mx.resize(4);
        Mx[0].push_back(-1);
        Mx[0].push_back(0);
        Mx[0].push_back(0);
        Mx[0].push_back(0);

        Mx[1].push_back(0);
        Mx[1].push_back(1);
        Mx[1].push_back(0);
        Mx[1].push_back(0);

        Mx[2].push_back(0);
        Mx[2].push_back(0);
        Mx[2].push_back(1);
        Mx[2].push_back(0);

        Mx[3].push_back(0);
        Mx[3].push_back(0);
        Mx[3].push_back(0);
        Mx[3].push_back(1);
    }
    //My
    {
        My.resize(4);
        My[0].push_back(1);
        My[0].push_back(0);
        My[0].push_back(0);
        My[0].push_back(0);

        My[1].push_back(0);
        My[1].push_back(-1);
        My[1].push_back(0);
        My[1].push_back(0);

        My[2].push_back(0);
        My[2].push_back(0);
        My[2].push_back(1);
        My[2].push_back(0);

        My[3].push_back(0);
        My[3].push_back(0);
        My[3].push_back(0);
        My[3].push_back(1);
    }
    //Mz
    {
        Mz.resize(4);
        Mz[0].push_back(1);
        Mz[0].push_back(0);
        Mz[0].push_back(0);
        Mz[0].push_back(0);

        Mz[1].push_back(0);
        Mz[1].push_back(1);
        Mz[1].push_back(0);
        Mz[1].push_back(0);

        Mz[2].push_back(0);
        Mz[2].push_back(0);
        Mz[2].push_back(-1);
        Mz[2].push_back(0);

        Mz[3].push_back(0);
        Mz[3].push_back(0);
        Mz[3].push_back(0);
        Mz[3].push_back(1);
    }
    // T
    {
        T.resize(4);
        T[0].push_back(1);
        T[0].push_back(0);
        T[0].push_back(0);
        T[0].push_back(0);

        T[1].push_back(0);
        T[1].push_back(1);
        T[1].push_back(0);
        T[1].push_back(0);

        T[2].push_back(0);
        T[2].push_back(0);
        T[2].push_back(0);
        T[2].push_back(0);

        T[3].push_back(0);
        T[3].push_back(0);
        T[3].push_back(0);
        T[3].push_back(1);
    }

}

/*генерация буквы D*/
void Widget::generate_D(){
    //(x,y,z)

    //лицевая сторона
    push_XYZ(0, 0, 0, 10);          relations[0].push_back(1);
    push_XYZ(1, 120, -40, 10);      relations[0].push_back(5);
    push_XYZ(2, 160, -80, 10);      relations[1].push_back(2);
    push_XYZ(3, 160, -240, 10);     relations[2].push_back(3);
    push_XYZ(4, 120, -320, 10);     relations[3].push_back(4);
    push_XYZ(5, 0, -360, 10);       relations[4].push_back(5);

    push_XYZ(6, 40, -40, 10);       relations[6].push_back(7);
    push_XYZ(7, 80, -60, 10);       relations[6].push_back(11);
    push_XYZ(8, 120, -120, 10);     relations[7].push_back(8);
    push_XYZ(9, 120, -200, 10);     relations[8].push_back(9);
    push_XYZ(10, 80, -300, 10);     relations[9].push_back(10);
    push_XYZ(11, 40, -320, 10);     relations[10].push_back(11);

    //обратная сторона
    push_XYZ(12, 0, 0, 80);         relations[12].push_back(13);
    push_XYZ(13, 120, -40, 80);     relations[12].push_back(17);
    push_XYZ(14, 160, -80, 80);     relations[13].push_back(14);
    push_XYZ(15, 160, -240, 80);    relations[14].push_back(15);
    push_XYZ(16, 120, -320, 80);    relations[15].push_back(16);
    push_XYZ(17, 0, -360, 80);      relations[16].push_back(17);

    push_XYZ(18, 40, -40, 80);      relations[18].push_back(19);
    push_XYZ(19, 80, -60, 80);      relations[18].push_back(23);
    push_XYZ(20, 120, -120, 80);    relations[19].push_back(20);
    push_XYZ(21, 120, -200, 80);    relations[20].push_back(21);
    push_XYZ(22, 80, -300, 80);     relations[21].push_back(22);
    push_XYZ(23, 40, -320, 80);     relations[22].push_back(23);

    //связь 2ух сторон
    for(int i = 0; i < 12; i++)
       relations[i].push_back(i + 12);

}

QVector<QVector <qreal>> Widget::multi_matrixs(QVector<QVector <qreal>> a, QVector<QVector <qreal>> b){
    for(int i=0; i<a.size(); i++) // проходимся по всем точкам
    {
        // i-очередная точка
        a[i].push_back(1);// преобразование к виду (x,y,z,1)
        QVector<qreal> sup = a[i];
        qreal supp;

        for(int j=0; j<4; j++) // по координатам
        {
            supp = 0;
            for(int k=0; k<4; k++) // умножение на строку
            {
                supp += a[i][k]*b[j][k];
            }
            sup[j] =supp;
        }
        for(int j=0; j<4; j++)
            a[i][j] = sup[j];
        a[i].pop_back();
    }
    return a;
}

/*отрисовка*/
void Widget::draw(QVector<QVector <qreal>> a)
{
    scene->clear();
    scene->setBackgroundBrush(Qt::black);
    scene->addLine(-200,0,200,0,QPen(QColor(78, 70, 81)));
    scene->addLine(0,-200,0,200,QPen(QColor(215, 215, 215)));
    scene->addLine(-150,-150,150,150,QPen(QColor(160,195, 195)));

    a = affRx(a);
    a = affRy(a);
    a = affRz(a);
    a = affD(a);

    for(int i=0; i<a.size(); i++)
    {
        for(int j=0; j < relations[i].size(); j++)
        {

            if(persp)
            {
                if(sun)
                    scene->addLine((a[i][0]/(1-a[i][2]/point_persp)),
                            (a[i][1]/(1-a[i][2]/point_persp)),
                            (a[relations[i][j]][0]/(1 - a[relations[i][j]][2]/point_persp)),
                            (a[relations[i][j]][1]/(1 - a[relations[i][j]][2]/point_persp)),
                            QPen(QColor(255, 255, 100)));
                else
                    scene->addLine((a[i][0]/(1-a[i][2]/point_persp)),
                            (a[i][1]/(1-a[i][2]/point_persp)),
                            (a[relations[i][j]][0]/(1 - a[relations[i][j]][2]/point_persp)),
                            (a[relations[i][j]][1]/(1 - a[relations[i][j]][2]/point_persp)),
                            QPen(QColor(255, 229, 180)));
            }
            else
            {
                if(sun)
                    scene->addLine(a[i][0], a[i][1], a[relations[i][j]][0], a[relations[i][j]][1], QPen(QColor(255, 255, 100)));
                else
                    scene->addLine(a[i][0], a[i][1], a[relations[i][j]][0], a[relations[i][j]][1], QPen(QColor(255, 229, 180)));
            }
        }
    }
}

/*Нажатие клавиш*/
void Widget::keyPressEvent(QKeyEvent *e)
{
    //нажата стрелка_вниз
    if(e->key() == Qt::Key_Down)
        angX-= M_PI/18;
    //нажата стрелка_вправо
    if(e->key() == Qt::Key_Right)
        angY += M_PI/18;
    //нажата стрелка_вверх
    if(e->key() == Qt::Key_Up)
        angX += M_PI/18;
    //нажата стрелка_влево
    if(e->key() == Qt::Key_Left)
        angY -= M_PI/18;

    //нажат +
    if(e->key()==Qt::Key_Plus)
        angZ +=M_PI/18;
    //нажат -
    if(e->key()==Qt::Key_Minus)
        angZ -= M_PI/18;
    //нажата 4
    if(e->key() == Qt::Key_4)
        tmr->start(100);
    //нажата 5
    if(e->key() == Qt::Key_5)
        tms->start(100);

    //нажата 1
    if(e->key() == Qt::Key_1)
        if(dX > 0.2 && dY>0.2 && dZ>0.2)
        {
            dX -= 0.1;
            dY -= 0.1;
            dZ -= 0.1;
        }
    //нажата 2
    if(e->key() == Qt::Key_2)
    {
        dX += 0.1;
        dY += 0.1;
        dZ += 0.1;
    }

    //нажата D
    if(e->key() == Qt::Key_D)
        for(int i=0; i<coordinats.size(); i++)
            coordinats[i][0] += 10;
    //нажата A
    if(e->key() == Qt::Key_A)
        for(int i = 0; i < coordinats.size(); i++)
            coordinats[i][0] -= 10;
    //нажата W
    if(e->key() == Qt::Key_W)
        for(int i=0; i<coordinats.size(); i++)
            coordinats[i][1] -= 10;
    //нажата S
    if(e->key() == Qt::Key_S)
        for(int i = 0; i < coordinats.size(); i++)
            coordinats[i][1] += 10;

    //нажата P
    if(e->key() == Qt::Key_P)
        persp = !persp;

    //нажата R
    if(e->key() == Qt::Key_R)
    {
        coordinats.clear();
        relations.clear();
        coordinats = D;
        relations = D_rel;
        sun = false;
        shn->stop();
    }

    //нажата Y
    if(e->key() == Qt::Key_Y)
    {
        coordinats.clear();
        relations.clear();
        coordinats = Figure;
        relations = F_rel;
        sun = true;
        shn->start(200);

    }

    //нажата U
    if(e->key() == Qt::Key_U)
        shining = !shining;

    draw(coordinats);
}

void Widget::sunshine(){
    if(shining){
        QVector<QVector <qreal>> sup = coordinats;
        for(int i=24; i<coordinats.size(); i++)
        {
            for(int j=0; j<coordinats[i].size(); j++)
            {

                coordinats[i][j] = coordinats[i][j] + rand()%50-25;

            }
        }
        draw(coordinats);
        coordinats = sup;
    }
}

/*масштабирование проволочной фигуры*/
void Widget::to_zero(){

    if(dX > 0.2 && dY > 0.2 && dZ > 0.2)
    {
        qDebug()<<"<";
        dX -= 0.05;
        dY -= 0.05;
        dZ -= 0.05;
        draw(coordinats); // отрисовка
    }
    else
    {
        qDebug() << "End <";
        tmr->stop();
    }
}

void Widget::to_max()
{
    if(dX < 1.4 && dY < 1.4 && dZ < 1.4)
    {
        qDebug()<<">";
        dX += 0.05;
        dY += 0.05;
        dZ += 0.05;
        draw(coordinats); // отрисовка
    }
    else
    {
        qDebug() << "End >";
        tms->stop();
    }
}

/*создание проволочной фигуры "Солнышко"*/
void Widget::generate_Figure()
{
    coordinats[0].push_back(0);         relations[0].push_back(1);
    coordinats[0].push_back(0);         relations[0].push_back(24);
    coordinats[0].push_back(0);         relations[0].push_back(25);
                                        relations[0].push_back(11);

    coordinats[1].push_back(40);        relations[1].push_back(25);
    coordinats[1].push_back(-80);       relations[1].push_back(2);
    coordinats[1].push_back(0);         relations[1].push_back(26);

    coordinats[2].push_back(120);       relations[2].push_back(26);
    coordinats[2].push_back(-120);      relations[2].push_back(3);
    coordinats[2].push_back(0);         relations[2].push_back(27);

    coordinats[3].push_back(200);       relations[3].push_back(27);
    coordinats[3].push_back(-120);      relations[3].push_back(4);
    coordinats[3].push_back(0);         relations[3].push_back(28);

    coordinats[4].push_back(280);       relations[4].push_back(28);
    coordinats[4].push_back(-80);       relations[4].push_back(5);
    coordinats[4].push_back(0);         relations[4].push_back(29);

    coordinats[5].push_back(320);       relations[5].push_back(29);
    coordinats[5].push_back(0);         relations[5].push_back(6);
    coordinats[5].push_back(0);         relations[5].push_back(30);

    coordinats[6].push_back(320);       relations[6].push_back(30);
    coordinats[6].push_back(60);        relations[6].push_back(7);
    coordinats[6].push_back(0);         relations[6].push_back(31);

    coordinats[7].push_back(280);       relations[7].push_back(31);
    coordinats[7].push_back(140);       relations[7].push_back(8);
    coordinats[7].push_back(0);         relations[7].push_back(32);

    coordinats[8].push_back(200);       relations[8].push_back(32);
    coordinats[8].push_back(180);       relations[8].push_back(9);
    coordinats[8].push_back(0);         relations[8].push_back(33);

    coordinats[9].push_back(120);       relations[9].push_back(33);
    coordinats[9].push_back(180);       relations[9].push_back(10);
    coordinats[9].push_back(0);         relations[9].push_back(34);

    coordinats[10].push_back(40);       relations[10].push_back(34);
    coordinats[10].push_back(140);      relations[10].push_back(11);
    coordinats[10].push_back(0);        relations[10].push_back(35);

    coordinats[11].push_back(0);        relations[11].push_back(24);
    coordinats[11].push_back(60);       relations[11].push_back(35);
    coordinats[11].push_back(0);

    coordinats[12].push_back(0);        relations[12].push_back(24);
    coordinats[12].push_back(0);        relations[12].push_back(25);
    coordinats[12].push_back(40);       relations[12].push_back(23);
    relations[12].push_back(13);

    coordinats[13].push_back(40);       relations[13].push_back(25);
    coordinats[13].push_back(-80);      relations[13].push_back(14);
    coordinats[13].push_back(40);       relations[13].push_back(26);

    coordinats[14].push_back(120);      relations[14].push_back(26);
    coordinats[14].push_back(-120);     relations[14].push_back(15);
    coordinats[14].push_back(40);       relations[14].push_back(27);

    coordinats[15].push_back(200);      relations[15].push_back(27);
    coordinats[15].push_back(-120);     relations[15].push_back(16);
    coordinats[15].push_back(40);       relations[15].push_back(28);

    coordinats[16].push_back(280);      relations[16].push_back(28);
    coordinats[16].push_back(-80);      relations[16].push_back(17);
    coordinats[16].push_back(40);       relations[16].push_back(29);

    coordinats[17].push_back(320);      relations[17].push_back(29);
    coordinats[17].push_back(0);        relations[17].push_back(18);
    coordinats[17].push_back(40);       relations[17].push_back(30);

    coordinats[18].push_back(320);      relations[18].push_back(30);
    coordinats[18].push_back(60);       relations[18].push_back(19);
    coordinats[18].push_back(40);       relations[18].push_back(31);

    coordinats[19].push_back(280);      relations[19].push_back(31);
    coordinats[19].push_back(140);      relations[19].push_back(20);
    coordinats[19].push_back(40);       relations[19].push_back(32);

    coordinats[20].push_back(200);      relations[20].push_back(32);
    coordinats[20].push_back(180);      relations[20].push_back(21);
    coordinats[20].push_back(40);       relations[20].push_back(33);

    coordinats[21].push_back(120);      relations[21].push_back(33);
    coordinats[21].push_back(180);      relations[21].push_back(22);
    coordinats[21].push_back(40);       relations[21].push_back(34);

    coordinats[22].push_back(40);       relations[22].push_back(34);
    coordinats[22].push_back(140);      relations[22].push_back(23);
    coordinats[22].push_back(40);       relations[22].push_back(35);

    coordinats[23].push_back(0);        relations[23].push_back(24);
    coordinats[23].push_back(60);       relations[23].push_back(35);
    coordinats[23].push_back(40);

    coordinats[24].push_back(-60);
    coordinats[24].push_back(30);
    coordinats[24].push_back(20);

    coordinats[25].push_back(-20);
    coordinats[25].push_back(-80);
    coordinats[25].push_back(20);

    coordinats[26].push_back(60);
    coordinats[26].push_back(-160);
    coordinats[26].push_back(20);

    coordinats[27].push_back(160);
    coordinats[27].push_back(-180);
    coordinats[27].push_back(20);

    coordinats[28].push_back(260);
    coordinats[28].push_back(-160);
    coordinats[28].push_back(20);

    coordinats[29].push_back(340);
    coordinats[29].push_back(-80);
    coordinats[29].push_back(20);

    coordinats[30].push_back(380);
    coordinats[30].push_back(30);
    coordinats[30].push_back(20);

    coordinats[31].push_back(340);
    coordinats[31].push_back(140);
    coordinats[31].push_back(20);

    coordinats[32].push_back(260);
    coordinats[32].push_back(220);
    coordinats[32].push_back(20);

    coordinats[33].push_back(160);
    coordinats[33].push_back(240);
    coordinats[33].push_back(20);

    coordinats[34].push_back(60);
    coordinats[34].push_back(220);
    coordinats[34].push_back(20);

    coordinats[35].push_back(-20);
    coordinats[35].push_back(140);
    coordinats[35].push_back(20);
}


void Widget::keyReleaseEvent(QKeyEvent *e)
{

}

Widget::~Widget()
{

}
