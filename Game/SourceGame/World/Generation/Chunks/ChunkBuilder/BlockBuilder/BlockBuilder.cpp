#include "BlockBuilder.h"

sf::Vector2f BlockBuilder::getTexCoord(bool* blocks)
{
    int index = 0;

    for (int i = 0; i < this->TEX_COORD_TABLE_SIZE; i++)
    {
        bool isSame = false;

        for (int bit = 0; bit < 8; bit++)
        {
            if (blocks[bit] != this->possiblities[i][bit])
            {
                isSame = false;
                break;
            }

            isSame = true;
        }
        
        if (isSame) 
        {
            index = i; 
            break;
        }
    }

    sf::Vector2f texPos(this->texCoordTable[index], 0);

    return texPos;
}

sf::Vector2f BlockBuilder::getGrassTexCoord(bool* blocks)
{
    /*
    
    Koska meidän tarvitsee katsoa vain neljä kohtaa niin funktio on erilaine.

    Katsomme siis x:n paikat:

    -   x   -
    x   -   x
    -   x   -
    
    */
    int index = 0;

    for (int i = 0; i < this->GRASS_TEX_COORD_TABLE_SIZE; i++)
    {
        bool isSame = false;

        for (int bit = 0; bit < 4; bit++)
        {
            if (blocks[bit] != this->possibilitiesGrass[i][bit])
            {
                isSame = false;
                break;
            }

            isSame = true;
        }

        if (isSame)
        {
            index = i;
            break;
        }
    }

    sf::Vector2f texPos(this->grassTexCoordTable[index], 1);

    return texPos;
}

BlockBuilder::BlockBuilder()
    : texCoordTable
        {
            0,0,0,0,
            1,1,1,1,
            2,2,2,2,
            3,3,3,3,
            4,4,4,4,
            7,7,7,7,
            9,9,9,9,
            11,11,11,11,
            12,14,15,16,
            17,26,25,24,
            23,22,21,20,
            19,
            26
    }, grassTexCoordTable{
            0,
            4,
            9,
            11,
            14,
            15,
            16,
            17,
            18,
            19,
        
    }
{  
}
