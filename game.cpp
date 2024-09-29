#include<game.h>


Game::Game(){
    game_begin=false;
};

void Game::FirstGame(){

    EnemyRoles.clear();
    OurRoles.clear();
    this->round=1;
    this->money=40;
    game_begin=true;
    enemy_timer.start(200000);
    enemy_timer.setSingleShot(true);
    this->batch=0;
    this->killed=0;
}
void Game::SecondGame(){

    EnemyRoles.clear();
    OurRoles.clear();
    this->round=2;
    this->money=40;
    this->killed=0;
    game_begin=true;
    this->batch=0;
    enemy_timer.start(200000);
    enemy_timer.setSingleShot(true);
}


MyRole*Game::GetRole(GridVec pos){
    {
            for(auto role:OurRoles){
                if(role->posi==pos.i&&role->posj==pos.j){
                    return role;
                }
            }
            return nullptr;
        }
    }

bool Game::IsValid(GridVec pos){
    for(auto role:OurRoles){
        if(role->posi==pos.i&&role->posj==pos.j)return false;
    }
    return true;
}

//todo 检测是否有东西，并从OurRoles列表移除
void Game::RemoveRole(GridVec pos){
    for(auto role:this->OurRoles){
        if(role->posi==pos.i&&role->posj==pos.j){
        this->OurRoles.removeOne(role);
        return;
        }
    }
    return;
}
