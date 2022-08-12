import pygame
from  Text import Text

class Dialog:
    def __init__(self,näyttö,sprite,text) -> None:
        self.näyttö = näyttö
        self.sprite = sprite
        self.text = text
        self.widht = 800
        self.height = 400
        self.kohta = 0

        self.GUI = pygame.Surface((self.widht,self.height), pygame.SRCALPHA)   # per-pixel alpha
        self.GUI.fill((0,0,0,128))
        pygame.draw.rect(self.GUI, (255, 255, 255, 200), (0, 0, self.widht, self.height), 1)                   
        self.näyttö.blit(self.GUI, (0,600))
        self.rect = self.GUI.get_rect(topleft = (self.widht,self.height))
        self.tekstikohta = Text(self.näyttö,(100,620),self.text[self.kohta],32,(255,255,255)) 
      
    def StopTalking(self):
        if self.kohta >= len(self.text):
            return True
        else:
            return False

    def updatee(self,click):
        if click:
            self.kohta += 1
        if self.StopTalking():
            return
        self.tekstikohta.text = self.text[self.kohta]
        self.näyttö.blit(self.GUI, (0,600))
        self.tekstikohta.update()