import pygame
from random import randint
from os import path
from sys import exit
from time import time
from Player.Pelaaja import Pelaaja
from Visuals.Particle import Particle
from Visuals.Music import Music
from Utils.Laskut import Distance
from Dialogs.Dialogit import Dialog
from World.LoadWorld import LoadWorld
from Dialogs.DialogUtils import DialogUtils
pygame.mixer.pre_init(44100, -16, 2, 512)


def timer(func):
        def timed(*args,**kw):
            ts = time()
            result = func(*args,**kw)
            te = time()
            print ('func:%r took: %2.4f sec' % \
            (func.__name__,  te-ts))
            return result
        return timed


class GameHandler:
    __slots__ = "maxRuudut","display_surface","width","height","rightClick","level","music","taso_num","puhuminen","dialogit","offset","player","talk"
    def __init__(self, maxRuudut, widht, height):
        self.maxRuudut = maxRuudut
        self.display_surface = pygame.display.get_surface()
        self.width = widht
        self.height = height
        self.rightClick = False
        self.level = LoadWorld("level1", widht, height, maxRuudut)
        self.music = Music()
        self.taso_num = 1
        self.puhuminen = False
        self.offset = pygame.math.Vector2(0, 0)
        self.player = Pelaaja(
            (500, 86*int(self.height/self.maxRuudut)), [self.level.visible_sprites, self.level.active_sprites], self.level.collision_sprites,self.level.orb_group)
      
   # @timer
    def AddKärpänen(self):
        if randint(1, 5) != 1:
            return
        x, y = (randint(0, self.width), randint(0, self.height))
        r = randint(2, 4)
        f = Particle(x, y, r, [(205, 250, 80),
                     (160, 150, 50), (50, 50, 50)], 1)
        self.level.kärpäs_group.add(f)

    def update_kärpänen(self):
        self.level.kärpäs_group.update(self.display_surface)
        for tuli in self.level.kärpäs_group:
            if tuli.y <= 0:
                tuli.kill()
      
    #@timer
    def ObjectTypeChecker(self):
        for enemy in self.level.enemy_group:
            enemy.animate(self.offset)
            if enemy.type == 405:
                enemy.shoot((self.player.rect.x, self.player.rect.y))
                enemy.updateBullets(self.offset)
                self.player.checkHurting(enemy.rectBall)
            if enemy.type == 408:
                enemy.Moving()
            self.player.checkHurting(enemy.rect)
        self.checkTalking()

    def checkTalking(self):
        if not self.puhuminen:
            return
        self.talk.textPlace.update()
        self.talk.updatee(self.rightClick)
        self.rightClick = False
        if self.talk.StopTalking():
            self.puhuminen = False


    def klikObejet(self, mouspos):
        self.rightClick = True
        mouspos += self.offset
        for sprite in self.level.visible_sprites:
            if (
                sprite.type in [403, 225]
                and Distance(sprite.rect, self.player.rect) <= 100
                and not self.puhuminen
                and sprite.rect.collidepoint(mouspos)
                and sprite.updateObject 
            ):
                self.puhuminen = True
                self.talk = Dialog(self.display_surface, sprite, DialogUtils.getDialog(
                    sprite.id, sprite.type,self.taso_num), self.width, self.height)
      
   # @timer
    def updateAll(self):
        self.level.visible_sprites.custom_draw(self.player) #Piirtää kaikki spritet jotka kuuluu visible sprites grouppiin
    
   # @timer
    def updatePlayer(self):
        self.level.active_sprites.update() # Pelaaja. Tää kutsuu sen update functioo

    #@timer
    def playMusic(self):
        self.music.playMusic(self.player.playerInput.mute)

    def run(self):
        self.updatePlayer()
        self.updateAll()
        self.AddKärpänen()
        self.update_kärpänen()
        self.playMusic()
        self.ObjectTypeChecker()
        self.offset = self.level.visible_sprites.offset
        self.player.offSet = self.offset



    