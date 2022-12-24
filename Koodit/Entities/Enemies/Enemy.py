import pygame
from os import path


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






class FallingRock(Enemy):
    def __init__(self, pos, maxRuudut, animate, col, kuva, width, height, display_surface, animationSpeed) -> None:
        super().__init__(pos, maxRuudut, animate, col, kuva,
                         width, height, display_surface, animationSpeed)
