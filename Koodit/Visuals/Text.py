import pygame
from os import path
pygame.font.init()


class Text:
    __slots__ = "font", "screen", "width", "height", "text", "pos_x", "pos_y", "color"

    def __init__(self, screen, pos, text, size, color, width, height) -> None:
        self.font = pygame.font.Font(path.join("yoster.ttf"), size)
        self.screen = screen
        self.width = width
        self.height = height
        self.text = text
        self.pos_x = pos[0]
        self.pos_y = pos[1]
        self.color = color
        self.blit_text(self.text, (pos[0], pos[1]), self.font, self.color)

    def update(self):
        self.blit_text(self.text, (self.pos_x, self.pos_y),
                       self.font, self.color)

    def moveEndCredits(self):
        self.pos_y += 0.7  # 0.4

    def blit_text(self, text, pos, font, color=pygame.Color('black')):
        words = [word.split(' ') for word in text.splitlines()]
        space = font.size(' ')[0]
        max_width = self.width-50
        x, y = pos
        for line in words:
            for word in line:
                word_surface = font.render(word, 0, color)
                word_width, word_height = word_surface.get_size()
                if x + word_width >= max_width:
                    x = pos[0]
                    y += word_height
                self.screen.blit(word_surface, (x, y))
                x += word_width + space
            x = pos[0]
            y += word_height
