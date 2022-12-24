import pygame
from os import path
from random import randint

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
        self.folder = kuva[1][0]
        self.colors = [[(130, 160, 250), (90, 120, 200), (50, 50, 50)], [(250, 160, 240), (200, 130, 200), (50, 50, 50)]
                       ]

        self.orb = self.folder == "Orb"

        self.orbType = kuva[2] if self.folder == "Orb" else None

        self.spark = pygame.sprite.Group()
        self.image = pygame.image.load(path.join(
            "Kuvat", "Palikat", "Animoidut_palikat", self.folder, self.kuva[0])).convert_alpha()
        self.image = pygame.transform.scale(
            self.image, (int(width/maxRuudut), int(height/maxRuudut)))
        self.näyttö.blit(self.image, (maxRuudut, maxRuudut))
        self.rect = self.image.get_rect(topleft=pos)

    def Animoi(self):
        self.currentFrame += 0.1
        if self.currentFrame >= len(self.kuva):
            self.currentFrame = 0
        self.image = pygame.image.load(path.join(
            "Kuvat", "Palikat", "Animoidut_palikat", self.folder, self.kuva[int(self.currentFrame)])).convert_alpha()
        if self.type in [103, 105, 106]:
            self.image = pygame.transform.scale(self.image, (int(
                self.width/self.maxRuudut), 2*int(self.height/self.maxRuudut)+3))
        else:
            self.image = pygame.transform.scale(
                self.image, (int(self.width/self.maxRuudut), int(self.height/self.maxRuudut)+2))

    def AddParticle(self, sus):
        if randint(1, 35) != 1:
            return
        x, y = (randint(-sus[0]+self.rect.x, -sus[0]+self.rect.x+30),
                randint(-sus[1]+self.rect.y+20, -sus[1]+self.rect.y+30))
        r = randint(3, 4)
        f = Kärpänen(x, y, r, self.colors[self.orbType-1], 0.5)
        self.spark.add(f)

    def Update_Particle(self, x, y):
        self.spark.update(self.näyttö, x, y)
        for tuli in self.spark:
            if tuli.y <= 0:
                tuli.kill()