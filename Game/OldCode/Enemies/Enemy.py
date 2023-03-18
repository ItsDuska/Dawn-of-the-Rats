import pygame
from os import path


class Enemy(pygame.sprite.Sprite):
    def __init__(self, pos, maxTiles, animate, col, images, width, height, display_surface, animationSpeed) -> None:
        __slots__ = "animationSpeed", "animate", "pos", "maxTiles", "type", "images", "folder", "width", "height", "screen", "currentFrame", "image", "rect", "facingLeft"
        super().__init__()
        self.animationSpeed = animationSpeed
        self.animated = animate
        self.pos = pos
        self.maxTiles = maxTiles
        self.type = col
        self.images = images[0]
        self.folder = images[1][0]
        self.width = width
        self.height = height
        self.screen = display_surface
        self.currentFrame = 0
        self.image = pygame.image.load(path.join(
            "Kuvat", "Enemies", self.folder, self.images[0])).convert_alpha()
        self.image = pygame.transform.scale(
            self.image, (int(self.width/maxTiles), int(self.height/maxTiles)))
        self.screen.blit(self.image, (self.maxTiles, self.maxTiles))
        self.rect = self.image.get_rect(topleft=pos)
        self.facingLeft = False

    def animate(self, offset):
        self.currentFrame += self.animationSpeed
        if self.currentFrame >= len(self.images):
            self.currentFrame = 0
        self.image = pygame.image.load(path.join(
            "Kuvat", "Enemies", self.folder, self.images[int(self.currentFrame)])).convert_alpha()
        if self.type in [403, 405, 406]:
            self.image = pygame.transform.scale(self.image, (int(
                self.width/self.maxTiles), 2*int(self.height/self.maxTiles)+3))
            self.rect = self.image.get_rect(topleft=(self.rect.x, self.rect.y))
        else:
            self.image = pygame.transform.scale(
                self.image, (int(self.width/self.maxTiles), int(self.height/self.maxTiles)+2))

        self.checkRight()

        self.screen.blit(
            self.image, (self.rect.x-offset[0], self.rect.y-offset[1]))

    def checkRight(self):
        if self.facingLeft:
            self.image = pygame.transform.flip(self.image, True, False)






class FallingRock(Enemy):
    def __init__(self, pos, maxTiles, animate, col, images, width, height, display_surface, animationSpeed) -> None:
        super().__init__(pos, maxTiles, animate, col, images,
                         width, height, display_surface, animationSpeed)
