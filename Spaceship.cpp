#include "Spaceship.h"

SpaceShip::SpaceShip()
{ lives=3;
   setPixmap(QPixmap(":/ images/spaceshipp.png"));
setPos(910,800);
//timer =new QTimer();
//connect(timer , SIGNAL(timeout()) , this , SLOT(Collision()));
//timer->start(10);
}

void SpaceShip::Collision()
{
    QList<QGraphicsItem *> collidingitems= collidingItems();
for(int i=0;i<collidingitems.size();i++){
    if(typeid (*(collidingitems[i]))==typeid (Chicken))
   {     delete collidingitems[i];
                    lives--;
    }
if(lives==0)
   exit(1);//TO DO
}
}



