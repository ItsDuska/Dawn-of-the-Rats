import pygame
from random import randint


class Particle(pygame.sprite.Sprite):
    __slots__ = "x", "y", "radius", "yvel", "burn_rate", "layers", "glow", "colors", "Yminus", "Xminus", "surf"

    def __init__(self, x, y, radius, colors, yvel):
        super(Particle, self).__init__()
        self.x = x
        self.y = y
        self.radius = radius
        self.yvel = yvel
        self.burn_rate = 0.01
        self.layers = 2
        self.glow = 1
        self.colors = colors
        self.Yminus = 0
        self.Xminus = 0

        surf_size = 2 * self.radius * self.layers * self.layers * self.glow
        self.surf = pygame.Surface((surf_size, surf_size), pygame.SRCALPHA)

    def update(self, win, x=0, y=0):
        xvel = randint(-1, 1)

        self.x += xvel
        self.y -= self.yvel

        self.radius -= self.burn_rate
        if self.radius <= 0:
            self.radius = 0.01
        surf_size = 2 * self.radius * self.layers * self.layers * self.glow
        self.surf = pygame.Surface((surf_size, surf_size), pygame.SRCALPHA)
        for i in range(self.layers, -1, -1):
            alpha = 255 - i * (255 // self.layers - 5)
            if alpha <= 0:
                alpha = 0.01
            radius = int(self.radius * self.glow * i * i)
            color = self.colors[0] if self.radius > 3.5 else self.colors[1]
            color = (*color, alpha)
            pygame.draw.circle(self.surf, color, (self.surf.get_width(
            ) // 2, self.surf.get_height() // 2), radius)

        win.blit(self.surf, self.surf.get_rect(center=(self.x, self.y)))
