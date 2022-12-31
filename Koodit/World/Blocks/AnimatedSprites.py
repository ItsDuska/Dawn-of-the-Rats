import pygame
from os import path
from random import randint
from Visuals.Particle import Particle

class AnimatedObj(pygame.sprite.Sprite):
    __slots__ = "passable","screen","width","height","animated","type","id","images","maxTiles","currentFrame","folder","spark","color","updateObject","image","rect"
    def __init__(self, pos, maxTiles, image, screen, width, height, kasvi, animate, type) -> None:
        super().__init__()
        self.passable = kasvi
        self.screen = screen
        self.width = width
        self.height = height
        self.animated = animate
        self.type = type
        self.id = 0
        self.images = image[0]
        self.maxTiles = maxTiles
        self.currentFrame = 0
        self.folder = image[1][0]
        self.spark = pygame.sprite.Group()
        self.color = None
        self.updateObject = True
        
        self.image = pygame.image.load(path.join(
            "Kuvat", "Palikat", "Animoidut_palikat", self.folder, self.images[0])).convert_alpha()
        self.image = pygame.transform.scale(
            self.image, (int(width/maxTiles), int(height/maxTiles)))
        self.screen.blit(self.image, (maxTiles, maxTiles))
        self.rect = self.image.get_rect(topleft=pos)

    def animate(self):
        self.currentFrame += 0.1
        if self.currentFrame >= len(self.images):
            self.currentFrame = 0
        self.image = pygame.image.load(path.join(
            "Kuvat", "Palikat", "Animoidut_palikat", self.folder, self.images[int(self.currentFrame)])).convert_alpha()
        if self.type in [103, 105, 106]:
            self.image = pygame.transform.scale(self.image, (int(
                self.width/self.maxTiles), 2*int(self.height/self.maxTiles)+3))
        else:
            self.image = pygame.transform.scale(
                self.image, (int(self.width/self.maxTiles), int(self.height/self.maxTiles)+2))

    def AddParticle(self, sus):
        if randint(1, 35) != 1:
            return
        x, y = (randint(self.rect.x, self.rect.x+30),randint(self.rect.y+20, self.rect.y+30))
        #x, y = (randint(-sus[0]+self.rect.x, -sus[0]+self.rect.x+30),randint(-sus[1]+self.rect.y+20, -sus[1]+self.rect.y+30))
        r = randint(3, 4)
        f = Particle(x, y, r, self.color, 0.5)
        self.spark.add(f)
        #print(self.rect.x,self.rect.y)
       # print(f.x,f.y)

    def Update_Particle(self, x, y):
        self.spark.update(self.screen, self.rect.x, self.rect.y)
        for particle in self.spark:
            if particle.y <= 0:
                particle.kill()

