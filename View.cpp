#include "View.h"
#include "QThread"
#include "QDebug"
View::View() : QGraphicsView() , sec(0) , currentLevel(0)
{
    QCursor cursor(Qt::BlankCursor);
        setCursor(cursor);
    setMouseTracking(true);
    setFocus();
//create scene
scene = new QGraphicsScene();
scene->setSceneRect(0,0,1920,1080);
setScene(scene);

setWindowFlags(Qt::Window|Qt::FramelessWindowHint);

//set background
setBackgroundBrush(QBrush(QImage(":/ images/background.jpg")));



//set score board
scoreBoard=new QGraphicsPixmapItem();
scoreBoard->setPixmap(QPixmap(":/ images/scoreboard.png"));
scene->addItem(scoreBoard);
scoreBoard->setPos(2,2);


//set heart background
heartBack=new QGraphicsPixmapItem();
heartBack->setPixmap(QPixmap(":/ images/heartback.png"));
scene->addItem(heartBack);
heartBack->setPos(2,1030);


//set heart icon
heartIcon=new QGraphicsPixmapItem();
heartIcon->setPixmap(QPixmap(":/ images/heart.png"));
scene->addItem(heartIcon);
heartIcon->setPos(150,1035);


//fix size
setFixedSize(1920,1080);
setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//set score
vtimer = new QTimer();
connect(vtimer , SIGNAL(timeout()) , this , SLOT(schedule()));
vtimer->start(1000);

addSpaceShip();

scene->addItem(spaceship->lives);
spaceship->lives->setPos(110,1033);
//music
auto musicPlayer =new QMediaPlayer();
musicPlayer->setMedia(QUrl("qrc:/music/02-04. Main Theme (Remastered)"));
musicPlayer->play();


//score part
 score = new Score();
 scene->addItem(score);
 score->setPos(50 ,2);





}

View::~View()
{

}


void View::addChicken(int numberOfChickens)
{
   for(int i = 0 ; i < numberOfChickens ; i++){
       if(currentLevel < 3){
          chickens.push_back(new Chicken((i / col)));
       }
       else if (currentLevel < 5){
           if(i % 2 == 0)
          chickens.push_back(new Chicken((i / col)));
          else
          chickens.push_back(new Hen((i / col)));
       }else{
           if(i % 2 == 0)
          chickens.push_back(new Hen((i / col)));
          else
          chickens.push_back(new Superhen((i / col)));
       }

   scene->addItem(chickens.last());
   chickens.last()->setPos(pos_x + (i % col)*140 ,-90);
   }
}
void View::mouseMoveEvent(QMouseEvent * event)
{
 spaceship->setPos(event->x() -50,event->y()-50);
 spaceship->Collision();


}

void View::addSpaceShip()
{
    spaceship=new SpaceShip();
    scene->addItem(spaceship);
}

void View::keyPressEvent(QKeyEvent* click)
{
    if(click->key()==Qt::Key_Space)
    {if(isGifted == false){
            bullet=new Bullet();
            scene->addItem(bullet);
            bullet->setPos(spaceship->x()+36,spaceship->y()-36);
        }else if(isGifted==true)
        {
                bullet2=new Bullet();
                scene->addItem(bullet2);
                bullet2->setPos(spaceship->x()+66,spaceship->y());
                bullet=new Bullet();
                scene->addItem(bullet);
                bullet->setPos(spaceship->x(),spaceship->y());
    }
  }
}

void View::level_1()
{
    row = 4;
    col = 5;
    pos_x =960 - ((col/2) * 140 + 50);
    addChicken(row * col);
}

void View::level_2()
{
    row = 4;
    col = 9;
    pos_x =960 - ((col/2) * 140 + 50);
     addChicken(row * col);
}

void View::level_3()
{
    row = 3;
    col = 8;
    pos_x =960 - ((col/2 - 1) * 140 + 120);
    addChicken(row * col);
}

void View::level_4()
{
    row = 3;
    col = 10;
    pos_x =960 - ((col/2 - 1) * 140 + 120);
    addChicken(row * col);
}

void View::level_5()
{
    row = 3;
    col = 6;
    pos_x =960 - ((col/2 - 1) * 140 + 120);
    addChicken(row * col);
}

void View::level_6()
{
    row = 3;
    col = 9;
    pos_x =960 - ((col/2 - 1) * 140 + 120);
    addChicken(row * col);
}

void View::schedule()
{

    sec ++;
   if(sec == 4){
       level_1();
       currentLevel = 1;
//       meatIcon=new QGraphicsPixmapItem();
//       meatIcon->setPixmap(QPixmap(":/ images/meaticon.png"));
//       scene->addItem(meatIcon);
//       meatIcon->setPos(60 ,1035);
//       nom=new Score();
//       scene->addItem(nom);
//       nom->setPos(20 ,1032);
   }else if(currentLevel == 1 && chickens.size() == 0){
       currentLevel = 2;
       level_2();

   }else if(currentLevel == 2 && chickens.size() == 0){//from this stage we can have meat!
        currentLevel = 3;
        level_3();
        meatIcon=new QGraphicsPixmapItem();
        meatIcon->setPixmap(QPixmap(":/ images/meaticon.png"));
        scene->addItem(meatIcon);
        meatIcon->setPos(60 ,1035);
        nom=new Score();
        scene->addItem(nom);
        nom->setPos(20 ,1032);

   }else if(currentLevel == 3 && chickens.size() == 0){
        currentLevel = 4;
        level_4();
   }else if(currentLevel == 4 && chickens.size() == 0){
       currentLevel = 5;
       level_5();
       secsaver=sec;

  }
   else if(currentLevel == 5 && chickens.size() == 0){
          currentLevel = 6;
          level_6();
          isGifted=false;
     }

   if(sec % 5 == 0 &&currentLevel > 2)
       //random egg generation for 1/4 of hens
   for(int i =0;i<chickens.size()/8;i++){
           QRandomGenerator *gen6 = QRandomGenerator::system();
           rvalue=gen6->bounded(chickens.size()-1);
           //Even indexs are chickens - convert random value to Odd to generate egg for hens
           if(rvalue % 2 == 0) rvalue++;
           (chickens[rvalue]->generateEgg());

    }
   if(sec-secsaver==15 && currentLevel >4){
       //generation random pix.x() for the postion of the gift
        QRandomGenerator *gen5 = QRandomGenerator::system();
        int random=gen5->bounded(30,1900);
        gift=new Gift();
        scene->addItem(gift);
        gift->setPos(random,0);


   }
}
