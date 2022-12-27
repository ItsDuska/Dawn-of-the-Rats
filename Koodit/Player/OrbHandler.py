import pygame
from os import path

class OrbHandler:
    def __init__(self) -> None:
        self.orbType = 0
        self.inOrb = False
        self.useOrb = True # Pelaajan pitää mennä maahan jotta voi käyttää orbia uudelleen
        self.dashTime = 0
        self.MAX_DASH_TIME = 10
        self.direction = [0,0]
        self.stopOrbing = False
        self.image = None
        self.currentFrame = 0

    def getOrb(self, type):
        self.orbType = type

    def Orb_Jump(self,dir):
        if self.inOrb:
            return
        if self.orbType != 2:
            return
        self.dir = -12
        #self.inOrb = False
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
            self.stopOrbing = True
        self.dashSprite()
        
    def continueDash(self,oikea,vasen,alas):
        if self.stopOrbing:
            return

        self.stopOrbing = False
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

    def update(self,currentFrame,oikea,vasen,alas,dir):
        self.currentFrame = currentFrame
        if self.inOrb:
            return
        self.Orb_Jump(dir)
        self.Orb_Dash(oikea,vasen,alas)

    def orbKuva(self,folder ,image):
        self.image = pygame.image.load(path.join("Kuvat", "Pelaaja", folder, image)).convert_alpha()

    def getDirectionX(self):
        return 0 if self.direction[0] is None else self.direction[0]

    def getDirectionY(self):
        return 0 if self.direction[1] is None else self.direction[1]