import pygame
from os import path

class OrbHandler:
    def __init__(self) -> None:
        self.orbType = None
        self.inOrb = False
        self.useOrb = True # Pelaajan pitää mennä maahan jotta voi käyttää orbia uudelleen
        self.dashTime = 0
        self.MAX_DASH_TIME = 10
        self.direction = [0,0]
        self.stopOrbing = False
        self.image = None
        self.currentFrame = None

    def getOrb(self, type):
        self.orbType = type

    def Orb_Jump(self):
        if not self.inOrb:
            return
        if self.orbType != 2:
            return
        self.direction.y = -12
        self.inOrb = False
        self.useOrb = False

    def dashSprite(self):
        if self.currentFrame >= 9:
            self.orbKuva("PlayerDash", "Dash9.png")
        else:
            self.orbKuva("PlayerDash", "Dash15.png")
        if self.direction[0] == -5:
            self.image = pygame.transform.flip(self.image, True, False)

    def Orb_Dash(self,oikea,vasen,alas):
        if self.orbType != 1:
            return

        self.continueDash(oikea,vasen,alas)
        self.dashTime += 0.4
        if self.dashTime >= self.MAX_DASH_TIME:
            self.dashTime = 0
            self.inOrb = False
            self.direction = [0,0]
            self.stopOrbing = False
        self.dashSprite()
        
    def continueDash(self,oikea,vasen,alas):
        if self.stopOrbing:
            return

        self.stopOrbing = True
        if oikea:
            self.direction[0] = -5
            self.direction[1] = 0
        elif vasen:
            self.direction[0] = 5
            self.direction[1] = 0
        elif alas:
            self.direction[1] = 10
        else:
            self.direction[1] = -10

    def update(self,currentFrame,oikea,vasen,alas):
        self.currentFrame = currentFrame
        if not self.inOrb:
            return
        self.Orb_Jump()
        self.Orb_Dash(oikea,vasen,alas)

    def orbKuva(self,folder ,image):
        self.image = pygame.image.load(path.join("Kuvat", "Pelaaja", folder, image)).convert_alpha()

    def getDirection(self):
        return [0,0] if self.direction is None else self.direction