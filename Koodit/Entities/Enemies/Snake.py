from Entities.Enemies.Enemy import Enemy
from Utils.Laskut import Distance
from os import path
import pygame
import math

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
