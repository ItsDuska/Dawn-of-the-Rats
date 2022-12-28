import pygame
from pygame.locals import BLEND_RGB_ADD
from math import sin, pi

class Glow:
    def __init__(self,amplitude,frequency,radius,color) -> None:
        self.amplitude = amplitude
        self.frequency = frequency
        self.x = 0
        self.radius = radius
        self.color = list(color)
        self.surface = pygame.surface.Surface((radius*2,radius*2), pygame.SRCALPHA)
       
    def getFlickeringValue(self):
        value = int(self.amplitude * sin(2*pi*self.frequency*self.x))
        return (self.color[0]+value-self.amplitude,self.color[1]+value-self.amplitude,self.color[2]+value-self.amplitude,self.color[3])
            
    def update(self,screen):
        self.getFlickeringValue()
        pygame.draw.circle(self.surface, self.getFlickeringValue(), (self.radius,self.radius), self.radius)
        screen.blit(self.surface,(-4,-4), special_flags=BLEND_RGB_ADD)
        if self.x > 100:
            self.x = 0
        self.x += 1