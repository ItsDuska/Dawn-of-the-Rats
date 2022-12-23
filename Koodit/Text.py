import pygame
import os
pygame.font.init()


class Text:
    __slots__ = "fontti", "näyttö", "width", "height", "text", "pos_x", "pos_y", "color"

    def __init__(self, näyttö, pos, text, koko, color, w, h) -> None:
        self.fontti = pygame.font.Font(os.path.join("yoster.ttf"), koko)
        self.näyttö = näyttö
        self.width = w
        self.height = h
        self.text = text
        self.pos_x = pos[0]
        self.pos_y = pos[1]
        self.color = color
        self.blit_text(self.text, (pos[0], pos[1]), self.fontti, self.color)

    def update(self):
        self.blit_text(self.text, (self.pos_x, self.pos_y),
                       self.fontti, self.color)

    def liiku(self):
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
                self.näyttö.blit(word_surface, (x, y))
                x += word_width + space
            x = pos[0]
            y += word_height
