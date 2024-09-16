#include<game.h>


Game::Game(){
};

void Game::FirstGame(){

    /*
     * 这里要创建每一局的所有敌方
     */

    // 创建一个有4行的向量

    // EnemyList[0]
    EnemyList[0][0] = 'H';
    EnemyList[0][1] = 'I';
    EnemyList[0][2] = 'H';
    EnemyList[0][3] = 'I';
    EnemyList[0][4] = 'G';
    EnemyList[0][5] = 'G';
    EnemyList[0][6] = 'H';
    EnemyList[0][7] = 0;  // 填充 0
    EnemyList[0][8] = 0;  // 填充 0
    EnemyList[0][9] = 0;  // 填充 0

    // EnemyList[1]
    EnemyList[1][0] = 'H';
    EnemyList[1][1] = 'H';
    EnemyList[1][2] = 'I';
    EnemyList[1][3] = 'I';
    EnemyList[1][4] = 'H';
    EnemyList[1][5] = 'H';
    EnemyList[1][6] = 'G';
    EnemyList[1][7] = 'H';
    EnemyList[1][8] = 'H';
    EnemyList[1][9] = 0;  // 填充 0

    // EnemyList[2]
    EnemyList[2][0] = 'H';
    EnemyList[2][1] = 'I';
    EnemyList[2][2] = 'J';
    EnemyList[2][3] = 'H';
    EnemyList[2][4] = 'H';
    EnemyList[2][5] = 'G';
    EnemyList[2][6] = 'G';
    EnemyList[2][7] = 'H';
    EnemyList[2][8] = 0;  // 填充 0
    EnemyList[2][9] = 0;  // 填充 0

    // EnemyList[3]
    EnemyList[3][0] = 'J';
    EnemyList[3][1] = 'J';
    EnemyList[3][2] = 'H';
    EnemyList[3][3] = 'H';
    EnemyList[3][4] = 'J';
    EnemyList[3][5] = 'J';
    EnemyList[3][6] = 'H';
    EnemyList[3][7] = 0;  // 填充 0
    EnemyList[3][8] = 0;  // 填充 0
    EnemyList[3][9] = 0;  // 填充 0
    this->batch=0;
    this->round=1;
    this->money=999;
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

bool Game::IsValid(GridVec pos){
    for(auto role:OurRoles){
        if(role->posi==pos.i&&role->posj==pos.j)return false;
    }
    return true;
}

//todo 检测是否有东西，并从OurRoles列表移除
void Game::RemoveRole(GridVec pos){

}
