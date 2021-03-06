//
// Created by vecr on 26/05/18.
//

#include "Map.h"

Map::Map() {
    int j=0,cellNumber=0, nEffects=Effects::numberOfEffects(), distanceBtwnEffects=8, distanceBtwnDrawCard=6; //TODO Decidere ogni quante celle avere un effetto
    int min=40,max=80;
    dimensions=Util::random(min,max);

    for (auto &i : mapMatrix) { //Creating and setting where to draw a card or where the cell has a effect
        while(j<10&&cellNumber<=dimensions){
            i[j]=cellNumber;

            if(cellNumber%distanceBtwnEffects!=0){
                cellEffect[cellNumber][1]=0;

            }
            else{
                cellEffect[cellNumber][1]=Util::randomFrom1(nEffects);
            }

            if(cellNumber%distanceBtwnDrawCard!=0){
                drawACard[cellNumber][1]=0;
            }
            else{
                drawACard[cellNumber][1]=1;
            }
            cellNumber++;
            j++;
        }
        j=0;
    }
}

void Map::displayMap(Player p) {//Prints the map with all the players and the effects or cards simbols under the cell number
    int cellNumber=0,j=0,remainingCellsToFill=0;
    Colors c;
    //Used to display the cells and the players in them
    std::cout<<constructCellString(0,110)<<std::endl;
    for (auto &i : mapMatrix) {
        while(j<10&&cellNumber<=dimensions){
            if(j==0)
                std::cout<<constructCellString(2,i[j])<<std::endl;
            if(j==0)
                std::cout<<"║";
            if(cellNumber>9&&cellNumber<=dimensions){
                if(j!=9){
                    std::cout<<" "<< i[j]<<" ";
                    checkForPlayers(i[j],p);
                    std::cout<<" │";
                }
                else{
                    std::cout<<" "<< i[j]<<" ";
                    checkForPlayers(i[j],p);
                    std::cout<<" ";
                }
            }else{
                if(cellNumber!=0){
                    if(j!=9){
                        std::cout<<" 0"<< i[j]<<" ";
                        checkForPlayers(i[j],p);
                        std::cout<<" │";
                    }
                    else{
                        std::cout<<" 0"<< i[j]<<" ";
                        checkForPlayers(i[j],p);
                        std::cout<<" ";
                    }
                }else{
                    std::cout<<" GO ";
                    checkForPlayers(i[j],p);
                    std::cout<<" │";
                }

            }

            if(j==9&&cellNumber<=dimensions)
            {
                std::cout<<"║"<<std::endl;
            }else if(cellNumber>=dimensions){
                remainingCellsToFill=10-(dimensions%10)-2;
                for (int k = 0; k <remainingCellsToFill ; ++k) {
                    std::cout<<"         │";
                }
                std::cout<<"         ║";
                std::cout<<std::endl;
            }

            if(j==9&&cellNumber!=dimensions){
                std::cout<<"║ ";
                for (int k = 0; k < 10; ++k) {
                    if(drawACard[i[k]][1]==0){
                        std::cout<<" ";
                    }else{
                        std::cout<<c.kGreen<<"♣"<<c.kStop;
                    }
                    if(cellEffect[i[k]][1]==0){
                        std::cout<<" ";
                    }else{
                        std::cout<<c.kRed<<"♥"<<c.kStop;
                    }
                    if(k<9)
                        std::cout<<"      │ ";
                    else{
                        std::cout<<"      ";
                    }
                }
                std::cout<<"║"<<std::endl;
                std::cout<<constructCellString(3,i[j])<<std::endl;
            }
            cellNumber++;
            j++;
        }
        j=0;
    }
    std::cout<<constructCellString(2,110)<<std::endl;
    std::cout<<constructCellString(1,110)<<std::endl;
    std::cout<<c.kGreen<<"♣"<<c.kStop<<" = pesca una carta;"<<std::endl;
    std::cout<<c.kRed<<"♥"<<c.kStop<<" = effetto su casella;"<<std::endl;
}



std::string Map::constructCellString(int resource, int cellNumber){ //Used to build the different strings needed
    std::string complete, stringResources[]={
            "╔═════════╤═════════╤═════════╤═════════╤═════════╤═════════╤═════════╤═════════╤═════════╤═════════╗",//0

            "╚═════════╧═════════╧═════════╧═════════╧═════════╧═════════╧═════════╧═════════╧═════════╧═════════╝",//1

            "║         │         │         │         │         │         │         │         │         │         ║",//2

            "╟─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────╢"//3

    };

    if(drawACard[cellNumber][1]==1){
        complete.append("║         │         │         │         │         │         │         │         │         │         ║");
    }

    if(resource<10){
        return stringResources[resource];
    }

};

void Map::checkForPlayers(int cellNumber, Player p) {
    std::cout<< p.drawPlayersForMap(cellNumber);
}

int Map::getMapDimensions() {
    return dimensions;
}

int Map::getCellEffect(int cellNumber) {
    return cellEffect[cellNumber][1];
}

int Map::getDrawACard(int cellNumber) {
    return drawACard[cellNumber][1];
}

