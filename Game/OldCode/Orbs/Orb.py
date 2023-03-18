from random import randint
from World.Blocks.AnimatedSprites import AnimatedObj
from Visuals.Glow import Glow


class Orb(AnimatedObj):
    __slots__ = "glow","inOrb","useOrb","lockMovement","drawPlayerOrbing"
    def __init__(self, pos, image, screen, isPassable, animate, type,scale) -> None:
        super().__init__(pos, image, screen, isPassable, animate, type,scale)
        self.glow = Glow(20,0.01,20,(0,0,0))
        self.inOrb = False
        self.useOrb = True # Pelaajan pitää mennä maahan jotta voi käyttää orbia uudelleen
        self.lockMovement = False
        self.drawPlayerOrbing = False

        


    
       
    