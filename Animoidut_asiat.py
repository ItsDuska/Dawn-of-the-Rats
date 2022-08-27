import pygame
import os
import random
from TuliKärpänen import Kärpänen


class AnimatedObj(pygame.sprite.Sprite):
    def __init__(self, pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type) -> None:
        super().__init__()
        self.passable = kasvi
        self.näyttö = näyttö
        self.width = width
        self.height = height
        self.animate = animate
        self.type = type
        self.kuva = kuva[0]
        self.maxRuudut = maxRuudut
        self.currentFrame = 0
        self.id = 0
        self.folder = kuva[1][0]
        self.colors = [[(130, 160, 250), (90, 120, 200), (50, 50, 50)], [(250, 160, 240), (200, 130, 200), (50, 50, 50)]
                       ]

        self.orb = True if self.folder == "Orb" else False
        self.orbType = kuva[2] if self.folder == "Orb" else None

        self.spark = pygame.sprite.Group()
        self.image = pygame.image.load(os.path.join(
            "Kuvat", "Palikat", "Animoidut_palikat", self.folder, self.kuva[0])).convert_alpha()
        self.image = pygame.transform.scale(
            self.image, (int(width/maxRuudut), int(height/maxRuudut)))
        self.näyttö.blit(self.image, (maxRuudut, maxRuudut))
        self.rect = self.image.get_rect(topleft=pos)
        if self.type == 403:
            self.rect.h *= 2
            self.rect.w *= 2

    def Animoi(self):
        self.currentFrame += 0.1
        if self.currentFrame >= len(self.kuva):
            self.currentFrame = 0
        self.image = pygame.image.load(os.path.join(
            "Kuvat", "Palikat", "Animoidut_palikat", self.folder, self.kuva[int(self.currentFrame)])).convert_alpha()
        if self.type in [403, 405, 406]:
            self.image = pygame.transform.scale(self.image, (int(
                self.width/self.maxRuudut), 2*int(self.height/self.maxRuudut)+3))
        else:
            self.image = pygame.transform.scale(
                self.image, (int(self.width/self.maxRuudut), int(self.height/self.maxRuudut)+2))

    def AddParticle(self, sus):
        if random.randint(1, 35) != 1:
            return
        x, y = (random.randint(-sus[0]+self.rect.x, -sus[0]+self.rect.x+30),
                random.randint(-sus[1]+self.rect.y+20, -sus[1]+self.rect.y+30))
        r = random.randint(3, 4)
        f = Kärpänen(x, y, r, self.colors[self.orbType-1], 0.5)
        self.spark.add(f)

    def Update_Particle(self, x, y):
        self.spark.update(self.näyttö, x, y)
        for tuli in self.spark:
            if tuli.y <= 0:
                tuli.kill()
