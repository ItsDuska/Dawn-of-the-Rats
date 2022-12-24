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
        self.stopOrbing

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
        if self.suunta[0] == -5:
            self.image = pygame.transform.flip(self.image, True, False)

    def Orb_Dash(self):
        if self.orbType != 1:
            return

        self.continueDash()
        self.dashTime += 0.4
        if self.dashTime >= self.MAX_DASH_TIME:
            self.dashTime = 0
            self.inOrb = False
            self.direction = [0,0]
            self.lopetaOrb = False

        self.rect.x += self.direction[0]
        self.direction.y = self.direction[1]
        self.dashSprite()
        

    def continueDash(self):
        if self.lopetaOrb:
            return

        self.lopetaOrb = True
        if self.oikea:
            self.suunta[0] = -5
            self.suunta[1] = 0
        elif self.vasen:
            self.suunta[0] = 5
            self.suunta[1] = 0
        elif self.alas:
            self.suunta[1] = 10
        else:
            self.suunta[1] = -10

    def Orbs(self):
        if not self.inOrb:
            return
        self.Orb_Jump()
        self.Orb_Dash()

    def orbKuva(self,folder ,image):
        self.image = pygame.image.load(path.join("Kuvat", "Pelaaja", folder, image)).convert_alpha()
