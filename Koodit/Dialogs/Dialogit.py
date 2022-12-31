import pygame
from Visuals.Text import Text


class Dialog:
    def __init__(self,window, sprite, text, w, h) -> None:
        __slots__ = "window", "sprite", "text", "widht", "height", "DialogsPart", "GUI", "rect", "textPlace"
        self.window =window
        self.sprite = sprite
        self.text = text
        self.widht = w
        self.height = h
        self.DialogsPart = 0
        self.GUI = pygame.Surface(
            (self.widht, self.height), pygame.SRCALPHA)   # per-pixel alpha
        self.GUI.fill((0, 0, 0, 128))
        pygame.draw.rect(self.GUI, (255, 255, 255, 200),
                         (0, 0, self.widht, self.height), 1)
        self.window.blit(self.GUI, (0, self.height/3))
        self.rect = self.GUI.get_rect(topleft=(self.widht, self.height))
        self.textPlace = Text(self.window, (self.widht/4, self.height-self.height/3),
                                self.text[self.DialogsPart], 32, (255, 255, 255), self.widht, self.height)

    def StopTalking(self):
        return self.DialogsPart >= len(self.text)

    def updatee(self, click):
        if click:
            self.DialogsPart += 1
        if self.StopTalking():
            return
        self.textPlace.text = self.text[self.DialogsPart]
        self.window.blit(self.GUI, (0, 600))
        self.textPlace.update()
