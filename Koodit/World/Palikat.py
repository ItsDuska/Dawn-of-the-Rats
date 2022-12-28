import pygame
from random import randint
from os import listdir, path

from Player.Pelaaja import Pelaaja
from Visuals.TuliKärpänen import Kärpänen
from Visuals.Music import Music
from Utils.Laskut import Distance
from Entities.Dialogit import Dialog
from World.LoadWorld import LoadWorld
pygame.mixer.pre_init(44100, -16, 2, 512)


class Palikat:
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
    
    def AddKärpänen(self):
        if randint(1, 5) != 1:
            return
        x, y = (randint(0, self.width), randint(0, self.height))
        r = randint(2, 4)
        f = Kärpänen(x, y, r, [(205, 250, 80),
                     (160, 150, 50), (50, 50, 50)], 1)
        self.level.kärpäs_group.add(f)

    def update_kärpänen(self):
        self.level.kärpäs_group.update(self.display_surface)
        for tuli in self.level.kärpäs_group:
            if tuli.y <= 0:
                tuli.kill()

    def ObjectTypeChecker(self):
        for enemy in self.level.enemy_group:
            enemy.Animoi(self.offset)
            if enemy.type == 405:
                enemy.shoot((self.player.rect.x, self.player.rect.y))
                enemy.updateAmmusPosAndBlit(self.offset)
                self.player.Check_hurting(enemy.rectball)
            if enemy.type == 408:
                enemy.Moving()
            self.player.Check_hurting(enemy.rect)
        self.checkTalking()

    def checkTalking(self):
        if not self.puhuminen:
            return
        self.talk.tekstikohta.update()
        self.talk.updatee(self.rightClick)
        self.rightClick = False
        if self.talk.StopTalking():
            self.puhuminen = False

    def getDialog(self, id, type):
        lista = []
        with open(path.join("dialogit", self.getDialogPath(id, type)), "r") as f:
            lista.extend(line for line in f if "#" not in line)
        return lista

    def getDialogPath(self, id, type):
        tyyppi = "Fish" if type == 403 else "Sign"
        fname = f"L{str(self.taso_num)}{tyyppi}{str(id)}"
        for file in listdir(path.join('Dialogit')):
            if fname in file:
                return file

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
                self.talk = Dialog(self.display_surface, sprite, self.getDialog(
                    sprite.id, sprite.type), self.width, self.height)


    def run(self):
        self.level.active_sprites.update() # Pelaaja. Tää kutsuu sen update functioo
        self.level.visible_sprites.custom_draw(self.player) #Piirtää kaikki spritet jotka kuuluu visible sprites grouppiin
        self.AddKärpänen()
        self.update_kärpänen()
        self.music.Play_music(self.player.playerInput.mute)
        self.ObjectTypeChecker()
        self.offset = self.level.visible_sprites.offset
        self.player.offSet = self.offset
    