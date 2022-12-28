from Entities.Orbs.Orb import Orb

import pygame
from os import path

class DashOrb(Orb):
    def __init__(self, pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type) -> None:
        super().__init__(pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type)
        self.dashTime = 0
        self.MAX_DASH_TIME = 10
        self.color = [(130, 160, 250), (90, 120, 200), (50, 50, 50)]
        self.glow.color = [90, 120, 200,20]
        

    def Orb_Dash(self,direction):
        if not self.inOrb:
            return
        self.drawPlayerOrbing = True
        self.lockMovement = True
        self.dashTime += 0.5
        if self.dashTime >= self.MAX_DASH_TIME:
            self.dashTime = 0
            self.drawPlayerOrbing = False
            self.inOrb = False
            self.lockMovement = False
            direction = pygame.math.Vector2(0,0)
        self.continueDash(direction)
        
    def continueDash(self,direction):
        if direction.x >= 1:
            direction.x = 3
            direction.y = 0
        elif direction.x <= -1:
            direction.x = -3
            direction.y = 0
        elif direction.y >= 1:
            direction.x = 0
            direction.y = 15
        else:
            direction.x = 0
            direction.y = -15

    def dashSprite(self,direction,currentFrame):
        if currentFrame >= 9:
            image = self.orbKuva("PlayerDash", "Dash9.png")
        else:
            image = self.orbKuva("PlayerDash", "Dash15.png")
        if direction < -1:
            image = pygame.transform.flip(image, True, False)
        return image

    def orbKuva(self,folder ,image):
        return pygame.image.load(path.join("Kuvat", "Pelaaja", folder, image)).convert_alpha()


    def run(self,direction):
        self.Orb_Dash(direction)
        self.glow.update(self.image)


     