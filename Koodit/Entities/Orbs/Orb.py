from random import randint
from World.Blocks.AnimatedSprites import AnimatedObj
from Visuals.Glow import Glow


class Orb(AnimatedObj):
    def __init__(self,pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type) -> None:
        super().__init__(pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type)
        self.glow = Glow(20,0.01,29,(0,0,0))
        self.inOrb = False
        self.useOrb = True # Pelaajan pitää mennä maahan jotta voi käyttää orbia uudelleen
        self.lockMovement = False
        self.drawPlayerOrbing = False

        


    
       
    