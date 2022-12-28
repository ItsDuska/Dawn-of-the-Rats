import pygame
from os import path
from random import randint
from Visuals.TuliKärpänen import Kärpänen

class AnimatedObj(pygame.sprite.Sprite):
    __slots__ = "passable","näyttö","width","height","animate","type","id","kuva","maxRuudut","currentFrame","folder","spark","color","updateObject","image","rect"
    def __init__(self, pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type) -> None:
        super().__init__()
        self.passable = kasvi
        self.näyttö = näyttö
        self.width = width
        self.height = height
        self.animate = animate
        self.type = type
        self.id = 0
        self.kuva = kuva[0]
        self.maxRuudut = maxRuudut
        self.currentFrame = 0
        self.folder = kuva[1][0]
        self.spark = pygame.sprite.Group()
        self.color = None
        self.updateObject = True
        
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
        x, y = (randint(self.rect.x, self.rect.x+30),randint(self.rect.y+20, self.rect.y+30))
        #x, y = (randint(-sus[0]+self.rect.x, -sus[0]+self.rect.x+30),randint(-sus[1]+self.rect.y+20, -sus[1]+self.rect.y+30))
        r = randint(3, 4)
        f = Kärpänen(x, y, r, self.color, 0.5)
        self.spark.add(f)
        #print(self.rect.x,self.rect.y)
       # print(f.x,f.y)

    def Update_Particle(self, x, y):
        self.spark.update(self.näyttö, self.rect.x, self.rect.y)
        for tuli in self.spark:
            if tuli.y <= 0:
                tuli.kill()
