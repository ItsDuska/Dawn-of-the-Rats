from Entities.Orbs.Orb import Orb

import pygame
from os import path

class DashOrb(Orb):
    def __init__(self, pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type) -> None:
        super().__init__(pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type)
        self.dashTime = 0
        self.MAX_DASH_TIME = 10
        self.color = [(250, 160, 240), (200, 130, 200), (50, 50, 50)]

    def Orb_Dash(self,direction):
        #if self.type != 407:
           # return
        self.inOrb = True
        print(self.dashTime)
        self.dashTime += 0.5
        if self.dashTime >= self.MAX_DASH_TIME:
            self.dashTime = 0
            self.inOrb = False
            direction = pygame.math.Vector2(0,0)
        self.continueDash(direction)
        self.dashSprite(direction)
        
    def continueDash(self,direction):
        if direction.x >= 1:
            direction.x = 5
            direction.x = 0
        elif direction.x <= -1:
            direction.x = -5
            direction.y = 0
        elif direction.y >= 1:
            direction.y = 10
        else:
            direction.y = -10

    def dashSprite(self,direction):
        if self.currentFrame >= 9:
            self.orbKuva("PlayerDash", "Dash9.png")
        else:
            self.orbKuva("PlayerDash", "Dash15.png")
        if direction.x < -1:
            self.image = pygame.transform.flip(self.image, True, False)

    def orbKuva(self,folder ,image):
        self.image = pygame.image.load(path.join("Kuvat", "Pelaaja", folder, image)).convert_alpha()

    def getInOrb(self):
        return self.inOrb

    def run(self,direction):
        self.Orb_Dash(direction)


     