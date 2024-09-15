#include "role.h"

Item::Item(QObject *parent)
    : QObject{parent}
{}
Item::Item(QString name,int x,int y){
    this->name=name;
    this->posx=x;
    this->posy=y;
    this->celli=x/Cell_Size;
    this->cellj=y/Cell_Size;
}
