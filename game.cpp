#include<game.h>


Game::Game(){
};

void Game::FirstGame(){

    /*
     * 这里要创建每一局的所有敌方
     */


    this->round=1;

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
