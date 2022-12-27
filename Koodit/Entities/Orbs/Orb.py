from random import randint
from Visuals.TuliKärpänen import Kärpänen
from World.Blocks.AnimatedSprites import AnimatedObj
import pygame


class Orb(AnimatedObj):
    def __init__(self,pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type) -> None:
        super().__init__(pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type)
        self.inOrb = False
        self.useOrb = True # Pelaajan pitää mennä maahan jotta voi käyttää orbia uudelleen
        #[[(130, 160, 250), (90, 120, 200), (50, 50, 50)], [(250, 160, 240), (200, 130, 200), (50, 50, 50)]]


    
       
    