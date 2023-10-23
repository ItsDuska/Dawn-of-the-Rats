#include "BlockTextureMapper.h"

sf::Vector2f BlockTextureMapper::getTexCoord(bool* blocks)
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
    
    int texturePosX = this->texCoordTable[index];

    if (texturePosX >= 4 && texturePosX <= 12)
    {
        texturePosX += rand() % 2;
    }

    sf::Vector2f texPos(texturePosX, 0);


    return texPos;
}

sf::Vector2f BlockTextureMapper::getGrassTexCoord(bool* blocks)
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

    
    //Random texture
    if (texPos.x <= 12.f)
    {
       texPos.x += rand() % 4;
    }
   

    return texPos;
}

BlockTextureMapper::BlockTextureMapper()
    : texCoordTable
        {
            0,0,0,0,
            1,1,1,1,
            2,2,2,2,
            3,3,3,3,
            4,4,4,4,
            6,6,6,6,
            8,8,8,8,
            10,10,10,10,
            12,14,15,16,
            17,26,25,24,
            23,22,21,20,
            19,
            26
    }, grassTexCoordTable{
            0,
            4,
            8,
            12,
            16,
            17,
            18,
            19,
            20,
            21,
        
    }
{  
}
