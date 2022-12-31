from Entities.Enemies.Enemy import Enemy
from Utils.Laskut import Distance
from os import path
import pygame
import math

class Snake(Enemy):
    __slots__ = "currentFrame1", "playerXY", "heightInWorld", "widht", "shooting", "bulletsTime", "fireball", "imageBullet", "rectBall"

    def __init__(self, pos, maxTiles, animate, col, images, width, height, display_surface) -> None:
        super().__init__(pos, maxTiles, animate, col,
                         images, width, height, display_surface, 0.1)
        self.currentFrame1 = 0
        self.playerXY = [0, 0]
        self.heightInWorld = 0
        self.widht = 0
        self.shooting = False
        self.bulletsTime = 0  # kymppii loppuu
        self.fireball = ["FireBall1.png", "FireBall2.png",
                         "FireBall3.png", "FireBall4.png"]
        # self.ammusPos = [self.rect.x, self.rect.y]
        self.imageBullet = pygame.image.load(
            path.join(
                "Kuvat", "Enemies", self.folder, self.fireball[self.currentFrame1]
            )
        ).convert_alpha()
        self.rectBall = self.imageBullet.get_rect(
            topleft=(self.rect.x, self.rect.y))

    def shoot(self, pelPos):
        if Distance(self.rect, pelPos) > 350 or self.shooting:
            return
        self.shooting = True
        self.playerXY = pelPos
        distance = Distance(self.playerXY, (self.rect.x, self.rect.y))
        self.heightInWorld = self.playerXY[1] - self.rect.y
        self.widht = math.sqrt((distance*distance-self.heightInWorld*self.heightInWorld))
        if self.playerXY[0] < self.rect.x:
            self.widht *= -1

    def updateBullets(self, offset):
        if not self.shooting:
            return
        self.animateBullet()
        self.rectBall.x += self.widht / 50
        self.rectBall.y += self.heightInWorld / 50
        self.screen.blit(self.imageBullet, (self.rectBall.x,
                         self.rectBall.y-offset[1]))
        self.bulletsTime += 0.1
        if self.bulletsTime >= 15:
            self.bulletsTime = 0
            self.shooting = False
            self.rectBall.x = -offset[0]+self.rect.x
            self.rectBall.y = self.rect.y

    def animateBullet(self):
        self.currentFrame1 += 0.1
        if self.currentFrame1 >= len(self.fireball):
            self.currentFrame1 = 0
        self.imageBullet = pygame.image.load(path.join(
            "Kuvat", "Enemies", self.folder, self.fireball[int(self.currentFrame1)])).convert_alpha()
        self.imageBullet = pygame.transform.scale(self.imageBullet, (int((self.width/self.maxTiles)), int((self.height/self.maxTiles))))
        self.rectBall = self.imageBullet.get_rect(
            topleft=(self.rectBall.x, self.rectBall.y))
