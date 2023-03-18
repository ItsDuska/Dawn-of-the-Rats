import pygame
from os import path
from random import randint
from Visuals.Particle import Particle



"""
func:'updateAll' took: 0.0124 sec
func:'updateAll' took: 0.0125 sec
func:'updateAll' took: 0.0125 sec
func:'updateAll' took: 0.0130 sec
func:'updateAll' took: 0.0140 sec
func:'updateAll' took: 0.0140 sec
func:'updateAll' took: 0.0109 sec
func:'updateAll' took: 0.0145 sec
func:'updateAll' took: 0.0125 sec
func:'updateAll' took: 0.0150 sec
func:'updateAll' took: 0.0136 sec
func:'updateAll' took: 0.0135 sec
func:'updateAll' took: 0.0138 sec
func:'updateAll' took: 0.0131 sec
func:'updateAll' took: 0.0125 sec
func:'updateAll' took: 0.0135 sec

KeskiArvo = 0,01408666666666666667



func:'updateAll' took: 0.0115 sec
func:'updateAll' took: 0.0125 sec
func:'updateAll' took: 0.0115 sec
func:'updateAll' took: 0.0120 sec
func:'updateAll' took: 0.0131 sec
func:'updateAll' took: 0.0147 sec
func:'updateAll' took: 0.0120 sec
func:'updateAll' took: 0.0125 sec
func:'updateAll' took: 0.0115 sec
func:'updateAll' took: 0.0120 sec
func:'updateAll' took: 0.0090 sec
func:'updateAll' took: 0.0115 sec
func:'updateAll' took: 0.0105 sec
func:'updateAll' took: 0.0115 sec
func:'updateAll' took: 0.0120 sec

0,01268666666666666667 keskiarvo


"""





class AnimatedObj(pygame.sprite.Sprite):
    __slots__ = "passable","screen","animated","type","id","sheet","currentFrame","folder","size","frameCount","spark","color","updateObject","image","rect","scale"
    def __init__(self, pos, image, screen, kasvi, animate, type,scale) -> None:
        super().__init__()
        self.passable = kasvi
        self.screen = screen
        self.animated = animate
        self.type = type
        self.id = 0
        self.scale = scale
        self.frameCount = image[1]
        self.size = image[2]
        self.sheet = pygame.image.load(path.join(*image[0]))
        self.currentFrame = 0
        self.spark = pygame.sprite.Group()
        self.color = None
        self.updateObject = True
        
        #self.image = pygame.image.load(path.join(
           # "Kuvat", "Palikat", "Animoidut_palikat", self.folder, self.images[0])).convert_alpha()
        self.animationList = self.makeAnimationList()
        self.image = self.animationList[0]
        self.rect = self.image.get_rect(topleft=pos)

    def get_image(self, frame: int):
        image = pygame.Surface((self.size), pygame.SRCALPHA).convert_alpha()
        image.blit(self.sheet, (0, 0),
                   ((frame*self.size[0]), 0, self.size[0], self.size[1]))

        if self.type in [103, 105, 106]:
            image = pygame.transform.scale(image, (self.scale[0], 2*self.scale[1]+3))
        else:
            image = pygame.transform.scale(
                image,self.scale)
        #image.set_colorkey((0, 0, 0))
        return image

    def makeAnimationList(self):
        return [self.get_image(_) for _ in range(self.frameCount)]


    def animate(self):
        self.currentFrame += 0.1
        if self.currentFrame >= self.frameCount:
            self.currentFrame = 0
        self.image = self.animationList[int(self.currentFrame)]


#Ongelmana on se että me vain lisätään uutta ja uutta ympyrää imageen ja se image ei tyhjenny
    

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

