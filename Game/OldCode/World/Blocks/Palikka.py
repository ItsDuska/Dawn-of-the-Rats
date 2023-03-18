import pygame
from os import path


class Palikka(pygame.sprite.Sprite):
    __slots__ = "passable","animate","type","id","updateObject","image","rect"
    def __init__(self, pos, size, image, screen, maxTiles, width, height, spriteGroups, isPassable, animate, col, num=0) -> None:
        super().__init__(spriteGroups)
        self.passable = isPassable
        self.animate = animate
        self.type = col
        self.id = num  # kylttei varte. 0 = ei kylttiä olemassa
        self.updateObject = True
        self.image = pygame.image.load(path.join(
            "Kuvat", "Palikat", "PalikkaKuvat", image)).convert_alpha()
        self.image = pygame.transform.scale(
            self.image, (int(width/maxTiles), int(height/maxTiles)))
        screen.blit(self.image, (size, size))  # size,size vanha
        self.rect = self.image.get_rect(topleft=pos)
        if self.type in [36, 37, 38]:
            self.rect.h = 1
        elif self.type in [223, 223]:
            self.rect.h = 10
