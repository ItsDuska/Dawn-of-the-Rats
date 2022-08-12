import pygame
import os
class Palikka(pygame.sprite.Sprite):
    def __init__(self,pos,size,kuva,näyttö,maxRuudut,width,height,asia,kasvi,animate,col) -> None:
        super().__init__(asia)
        self.passable = kasvi
        self.orb = None
        self.animate = animate
        self.type = col
        
        self.image = pygame.image.load(os.path.join("Kuvat","Palikat","PalikkaKuvat",kuva)).convert_alpha() 
        self.image = pygame.transform.scale(self.image,(int(width/maxRuudut),int(height/maxRuudut)))
        näyttö.blit(self.image,(size,size))
        self.rect = self.image.get_rect(topleft = pos)
        if self.type in [36,37,38]:
            self.rect.h = 1
        elif self.type in [73,73]:
            self.rect.h = 10

