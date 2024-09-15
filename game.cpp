#include<game.h>


Game::Game(){
};

void Game::FirstGame(){

    /*
     * 这里要创建每一局的所有敌方
     */

    // 创建一个有4行的向量

    EnemyList[0] = {'H', 'I', 'H', 'I', 'G', 'G', 'H'};
    EnemyList[1] = {'H', 'H', 'I', 'I', 'H', 'H', 'G', 'H', 'H'};
    EnemyList[2]= {'H', 'I', 'J', 'H', 'H', 'G', 'G', 'H'};
    EnemyList[3] = {'J', 'J', 'H', 'H', 'J', 'J', 'H'};
    this->round=1;
    enemy_timer.start(300000);
}
void Game::SecondGame(){

    this->round=2;
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


//todo 检测是否有东西，并从OurRoles列表移除
void Game::RemoveRole(GridVec pos){

}
