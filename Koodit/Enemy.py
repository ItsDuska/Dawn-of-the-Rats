import pygame
from os import path
import math
from Laskut import *


class Enemy(pygame.sprite.Sprite):
    def __init__(self, pos, maxRuudut, animate, col, kuva, width, height, display_surface, animationSpeed) -> None:
        __slots__ = "animationSpeed", "animate", "pos", "maxRuudut", "type", "kuva", "folder", "width", "height", "näyttö", "currentFrame", "orb", "image", "rect", "vasemmalle"
        super().__init__()
        self.animationSpeed = animationSpeed
        self.animate = animate
        self.pos = pos
        self.maxRuudut = maxRuudut
        self.type = col
        self.kuva = kuva[0]
        self.folder = kuva[1][0]
        self.width = width
        self.height = height
        self.näyttö = display_surface
        self.currentFrame = 0
        self.orb = None
        self.image = pygame.image.load(path.join(
            "Kuvat", "Enemies", self.folder, self.kuva[0])).convert_alpha()
        self.image = pygame.transform.scale(
            self.image, (int(self.width/maxRuudut), int(self.height/maxRuudut)))
        self.näyttö.blit(self.image, (self.maxRuudut, self.maxRuudut))
        self.rect = self.image.get_rect(topleft=pos)
        self.vasemmalle = False

    def Animoi(self, offset):
        self.currentFrame += self.animationSpeed
        if self.currentFrame >= len(self.kuva):
            self.currentFrame = 0
        self.image = pygame.image.load(path.join(
            "Kuvat", "Enemies", self.folder, self.kuva[int(self.currentFrame)])).convert_alpha()
        if self.type in [403, 405, 406]:
            self.image = pygame.transform.scale(self.image, (int(
                self.width/self.maxRuudut), 2*int(self.height/self.maxRuudut)+3))
            self.rect = self.image.get_rect(topleft=(self.rect.x, self.rect.y))
        else:
            self.image = pygame.transform.scale(
                self.image, (int(self.width/self.maxRuudut), int(self.height/self.maxRuudut)+2))

        self.CheckVasen()

        self.näyttö.blit(
            self.image, (self.rect.x-offset[0], self.rect.y-offset[1]))

    def CheckVasen(self):
        if self.vasemmalle:
            self.image = pygame.transform.flip(self.image, True, False)


class Snake(Enemy):
    __slots__ = "currentFrame1", "pelaajaXY", "korkeus", "pituus", "shooting", "ammuksenKesto", "fireball", "imageball", "rectball"

    def __init__(self, pos, maxRuudut, animate, col, kuva, width, height, display_surface) -> None:
        super().__init__(pos, maxRuudut, animate, col,
                         kuva, width, height, display_surface, 0.1)
        self.currentFrame1 = 0
        self.pelaajaXY = [0, 0]
        self.korkeus = 0
        self.pituus = 0
        self.shooting = False
        self.ammuksenKesto = 0  # kymppii loppuu
        self.fireball = ["FireBall1.png", "FireBall2.png",
                         "FireBall3.png", "FireBall4.png"]
        # self.ammusPos = [self.rect.x, self.rect.y]
        self.imageball = pygame.image.load(
            path.join(
                "Kuvat", "Enemies", self.folder, self.fireball[self.currentFrame1]
            )
        ).convert_alpha()
        self.rectball = self.imageball.get_rect(
            topleft=(self.rect.x, self.rect.y))

    def shoot(self, pelPos):
        if Distance(self.rect, pelPos) > 350 or self.shooting:
            return
        self.shooting = True
        self.pelaajaXY = pelPos
        distance = Distance(self.pelaajaXY, (self.rect.x, self.rect.y))
        self.korkeus = self.pelaajaXY[1] - self.rect.y
        self.pituus = math.sqrt((distance*distance-self.korkeus*self.korkeus))
        if self.pelaajaXY[0] < self.rect.x:
            self.pituus *= -1

    def updateAmmusPosAndBlit(self, offset):
        if not self.shooting:
            return
        self.AnimateAmmus()
        self.rectball.x += self.pituus / 50
        self.rectball.y += self.korkeus / 50
        self.näyttö.blit(self.imageball, (self.rectball.x,
                         self.rectball.y-offset[1]))
        self.ammuksenKesto += 0.1
        if self.ammuksenKesto >= 15:
            self.ammuksenKesto = 0
            self.shooting = False
            self.rectball.x = -offset[0]+self.rect.x
            self.rectball.y = self.rect.y

    def AnimateAmmus(self):
        self.currentFrame1 += 0.1
        if self.currentFrame1 >= len(self.fireball):
            self.currentFrame1 = 0
        self.imageball = pygame.image.load(path.join(
            "Kuvat", "Enemies", self.folder, self.fireball[int(self.currentFrame1)])).convert_alpha()
        self.imageball = pygame.transform.scale(self.imageball, (int(
            (self.width/self.maxRuudut)-10), int((self.height/self.maxRuudut)-2)))
        self.rectball = self.imageball.get_rect(
            topleft=(self.rectball.x, self.rectball.y))


class Bord(Enemy):
    __slots__ = "suunnat", "currentMovement", "movingSpeed", "movingSpeed", "kokopalikka", "startPos"

    def __init__(self, pos, maxRuudut, animate, col, kuva, width, height, display_surface, suunnat) -> None:
        super().__init__(pos, maxRuudut, animate, col,
                         kuva, width, height, display_surface, 0.2)
        self.suunnat = suunnat  # lista vector2 arvoja
        self.currentMovement = 0
        self.movingSpeed = 1
        self.kokopalikka = [(self.width/self.maxRuudut),
                            (self.height/self.maxRuudut)]
        self.startPos = self.rect.x, self.rect.y

    def Moving(self):
        if self.suunnat[self.currentMovement][0] < 0:
            self.rect.x -= self.movingSpeed
            self.vasemmalle = False
        elif self.suunnat[self.currentMovement][0] > 0:
            self.rect.x += self.movingSpeed
            self.vasemmalle = True

        if self.suunnat[self.currentMovement][1] < 0:
            self.rect.y -= self.movingSpeed
        elif self.suunnat[self.currentMovement][1] > 0:
            self.rect.y += self.movingSpeed

        if self.startPos[0] + (self.suunnat[self.currentMovement][0]*int(self.kokopalikka[0])) == self.rect.x and self.startPos[1] + (self.suunnat[self.currentMovement][1]*int(self.kokopalikka[1])) == self.rect.y:
            self.currentMovement += 1
            self.startPos = self.rect.x, self.rect.y
            if self.currentMovement == len(self.suunnat)-1:
                self.currentMovement = 0


class FallingRock(Enemy):
    def __init__(self, pos, maxRuudut, animate, col, kuva, width, height, display_surface, animationSpeed) -> None:
        super().__init__(pos, maxRuudut, animate, col, kuva,
                         width, height, display_surface, animationSpeed)
