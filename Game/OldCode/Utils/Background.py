import pygame
from os import path


class Background:
    __slots__ = "screen", "scroll", "width", "height", "bg_images", "bg_image", "bg_width"

    def __init__(self, screen, scroll, width, height):
        self.screen = screen
        self.scroll = scroll
        self.width = width
        self.height = height
        self.bg_images = []

        for i in range(1, 5):
            self.bg_image = pygame.image.load(path.join(
                "Kuvat", "BackGround", f"Bg{i}.png")).convert_alpha()
            self.bg_image = pygame.transform.scale(
                self.bg_image, (self.width, self.height))
            self.bg_images.append(self.bg_image)
        self.bg_width = self.bg_images[0].get_width()

    def draw_bg(self):
        for x in range(6):
            speed = 1
            for i in self.bg_images:
                self.screen.blit(
                    i, ((x * self.bg_width-300) - self.scroll * speed, 0))
                speed += 0.2
