import pygame
import random
import os
from Palikka import Palikka, AnimatedObj
from Pelaaja import Pelaaja
from TuliKärpänen import Kärpänen
from Music import Music
from Laskut import *
from Dialogit import Dialog
from Enemy import Enemy, Snake, Bord
from PalikkaKuvat import blockit, Läpi_palikat

pygame.mixer.pre_init(44100, -16, 2, 512)


class Palikat:
    def __init__(self, maxRuudut, widht, height):
        self.maxRuudut = maxRuudut
        self.display_surface = pygame.display.get_surface()
        self.width = widht
        self.height = height
        self.currentFrame = 0
        self.rightClick = False
        self.tasoDir = os.path.join("Tasot", "level1")
        self.music = Music()
        self.taso_num = 1
        self.puhuminen = False
        self.dilogit = []
        self.Palikat = blockit
        self.Läpi_palikat = Läpi_palikat
        self.enemies = [405, 408]
        self.num = 0  # kylttien id
        self.offset = pygame.math.Vector2(0, 0)

        self.enemy_group = pygame.sprite.Group()
        self.kärpäs_group = pygame.sprite.Group()
        self.visible_sprites = CameraGroup(self.width, self.height)
        self.active_sprites = pygame.sprite.Group()
        self.collision_sprites = pygame.sprite.Group()

        self.setup_level(self.Lataa())

    def Lataa(self):
        with open(self.tasoDir, "r") as file:
            return [[int(digit) for digit in line.split()] for line in file]

    def setup_level(self, tasoData,):
        animated_objects = {401: [["Orb1.png", "Orb2.png", "Orb3.png", "Orb4.png", "Orb5.png", "Orb6.png", "Orb7.png", "Orb8.png", "Orb9.png", "Orb10.png"],
                                  ["Orb"], 2], 402: [["Plant1.png", "Plant2.png", "Plant3.png", "Plant4.png", "Plant5.png", "Plant6.png", "Plant7.png", "Plant8.png", "Plant9.png", "Plant10.png"], ["Venus_Trap"]
                                                     ], 403: [["FishBoi1.png", "FishBoi1.png", "FishBoi1.png", "FishBoi2.png", "FishBoi2.png", "FishBoi2.png", "FishBoi3.png", "FishBoi3.png", "FishBoi3.png", "FishBoi3.png"], ["FishBoi"]],
                            404: [["SlimeBoi1.png", "SlimeBoi1.png", "SlimeBoi1.png", "SlimeBoi2.png", "SlimeBoi2.png", "SlimeBoi2.png", "SlimeBoi3.png", "SlimeBoi3.png", "SlimeBoi3.png", "SlimeBoi3.png", ], ["SlimeBoi"]],
                            405: [["Snakee1.png", "Snakee2.png", "Snakee3.png", "Snakee4.png", "Snakee5.png", "Snakee6.png", "Snakee7.png", "Snakee8.png", "Snakee9.png", "Snakee9.png", ], ["Snake"]],
                            406: [["ZombiNPC1.png", "ZombiNPC1.png", "ZombiNPC2.png", "ZombiNPC2.png", "ZombiNPC2.png", "ZombiNPC3.png", "ZombiNPC3.png", "ZombiNPC3.png", "ZombiNPC4.png", "ZombiNPC4.png"], ["ZombiNPC"]],
                            407: [["Dash1.png", "Dash2.png", "Dash3.png", "Dash4.png", "Dash5.png", "Dash6.png", "Dash7.png", "Dash8.png", "Dash9.png", "Dash10.png", "Dash11.png", "Dash12.png"],
                                  ["Orb"], 1], 408: [["Bord1.png", "Bord2.png", "Bord3.png", "Bord3.png", "Bord4.png", "Bord5.png", "Bord6.png", "Bord7.png", "Bord8.png"], ["Bord"]],
                            }
        # 1-200 ei ole läpi päästävii. 201-400 on läpi päästäviä. 401-600 on animoituja

        self.generation_loop(tasoData, self.Palikat)

        self.generation_loop(tasoData, self.Läpi_palikat)

        self.generation_loop(tasoData, animated_objects)

        self.player = Pelaaja(
            (500, 2300), [self.visible_sprites, self.active_sprites], self.collision_sprites)

    def generation_loop(self, tasoData, kuva):
        for row_index, row in enumerate(tasoData):
            for col_index, col in enumerate(row):
                x = col_index * int(self.width/self.maxRuudut)
                y = row_index * int(self.height/self.maxRuudut)
                if col in kuva:
                    if col >= 201 and col <= 400:
                        self.lisää_kuva(
                            x, y, kuva[col], self.display_surface, False, False, col)
                    elif col <= 200:
                        self.lisää_kuva(
                            x, y, kuva[col], self.display_surface, True, False, col)
                    elif col >= 401:
                        if col in self.enemies:
                            if col == 405:
                                sus = Snake((x, y), self.maxRuudut, True, col,
                                            kuva[col], self.width, self.height, self.display_surface)
                            elif col == 408:
                                sus = Bord((x, y), self.maxRuudut, True, col, kuva[col], self.width, self.height, self.display_surface, [
                                           [4, 0], [0, 4], [-4, 0], [0, -4], [0, -4]])
                            else:
                                sus = Enemy((x, y), self.maxRuudut, True, col,
                                            kuva[col], self.width, self.height, self.display_surface, 0.1)
                            self.enemy_group.add(sus)
                        else:
                            self.anim_obj = AnimatedObj(
                                (x, y), self.maxRuudut, kuva[col], self.display_surface, self.width, self.height, False, True, col,)
                            self.visible_sprites.add(self.anim_obj)

    def lisää_kuva(self, a, b, kuva, näyttö, passable, animate, col):
        if col == 225:
            self.num += 1
            Palikka((a, b), self.maxRuudut, kuva, näyttö, self.maxRuudut, self.width, self.height, [
                    self.visible_sprites, self.collision_sprites], passable, animate, col, self.num)
        else:
            Palikka((a, b), self.maxRuudut, kuva, näyttö, self.maxRuudut, self.width, self.height, [
                    self.visible_sprites, self.collision_sprites], passable, animate, col)

    def AddKärpänen(self):
        if random.randint(1, 5) != 1:
            return
        x, y = (random.randint(0, self.width), random.randint(0, self.height))
        r = random.randint(2, 4)
        f = Kärpänen(x, y, r, [(205, 250, 80),
                     (160, 150, 50), (50, 50, 50)], 1)
        self.kärpäs_group.add(f)

    def update_kärpänen(self):
        self.kärpäs_group.update(self.display_surface)
        for tuli in self.kärpäs_group:
            if tuli.y <= 0:
                tuli.kill()

    def ObjectTypeChecker(self):
        for enemy in self.enemy_group:
            enemy.Animoi(self.offset)
            if enemy.type == 405:
                enemy.shoot((self.player.rect.x, self.player.rect.y))
                enemy.updateAmmusPosAndBlit(self.offset)
                self.player.Check_hurting(enemy.rectball)

            if enemy.type == 408:
                enemy.Moving()

            self.player.Check_hurting(enemy.rect)

        if self.puhuminen:
            self.talk.tekstikohta.update()
            self.talk.updatee(self.rightClick)
            self.rightClick = False
            if self.talk.StopTalking():
                self.puhuminen = False

    def getDialog(self, id, type):
        lista = []
        f = open(os.path.join("dialogit", self.getDialogPath(id, type)), "r")
        for line in f:
            if not "#" in line:
                lista.append(line)
        f.close()
        return lista

    def getDialogPath(self, id, type):
        if type == 403:
            tyyppi = "Fish"
        else:
            tyyppi = "Sign"
        fname = "L" + str(self.taso_num)+tyyppi+str(id)
        for file in os.listdir(os.path.join('Dialogit')):
            if fname in file:
                return file

    def klikObejet(self, mouspos):
        self.rightClick = True
        mouspos += self.offset
        for sprite in self.visible_sprites:
            if sprite.type in [403, 225]:
                if Distance(sprite.rect, self.player.rect) <= 100 and not self.puhuminen and sprite.rect.collidepoint(mouspos):
                    self.puhuminen = True
                    self.talk = Dialog(self.display_surface, sprite, self.getDialog(
                        sprite.id, sprite.type), self.width, self.height)

    def run(self):
        self.active_sprites.update()
        self.visible_sprites.custom_draw(self.player)
        self.AddKärpänen()
        self.update_kärpänen()
        if not self.player.mute:
            self.music.Play_music()
        self.ObjectTypeChecker()
        self.offset = self.visible_sprites.offset


class CameraGroup(pygame.sprite.Group):
    def __init__(self, w, h):
        super().__init__()
        self.scroll = 0
        self.CAMERA_BORDERS = {'left': 100,
                               'right': 200, 'top': 100, 'bottom': 150}
        self.display_surface = pygame.display.get_surface()
        self.offset = pygame.math.Vector2(100, 300)
        self.tausta = Background(self.display_surface, self.scroll, w, h)

        self.sparkles = pygame.sprite.Group()
        # camera
        cam_left = self.CAMERA_BORDERS['left']
        cam_top = self.CAMERA_BORDERS['top']
        cam_width = self.display_surface.get_size(
        )[0] - (cam_left + self.CAMERA_BORDERS['right'])
        cam_height = self.display_surface.get_size(
        )[1] - (cam_top + self.CAMERA_BORDERS['bottom'])

        self.camera_rect = pygame.Rect(
            cam_left, cam_top, cam_width, cam_height)

    def custom_draw(self, player):
        # camera pos
        if player.rect.left < self.camera_rect.left:
            self.tausta.scroll -= 1
            self.camera_rect.left = player.rect.left
        if player.rect.right > self.camera_rect.right:
            self.tausta.scroll += 1
            self.camera_rect.right = player.rect.right
        if player.rect.top < self.camera_rect.top:
            self.camera_rect.top = player.rect.top
        if player.rect.bottom > self.camera_rect.bottom:
            self.camera_rect.bottom = player.rect.bottom

        self.tausta.draw_bg()
        # camera offsetti kai jotain emt
        self.offset = pygame.math.Vector2(
            self.camera_rect.left - self.CAMERA_BORDERS['left'],
            self.camera_rect.top - self.CAMERA_BORDERS['top'])

        for sprite in self.sprites():
            offset_pos = sprite.rect.topleft - self.offset
            self.display_surface.blit(sprite.image, offset_pos)
            if sprite.animate:
                sprite.Animoi()
                if sprite.orb:
                    if sprite.rect.colliderect(player.rect) and player.jump_on_air and player.orbattu == False:
                        player.orbissa = True
                        player.OrbCheck(sprite.orbType)
                    sprite.AddParticle(self.offset)
                    sprite.Update_Particle(-self.offset[0], -self.offset[1])
                if player.hurtingTime == 0 and not player.hurting:
                    player.lopetaHurting = False
            if sprite.type in [223, 224, 402]:
                player.Check_hurting(sprite.rect)

    def animate_all(self):
        for sprite in self.visible_sprites:
            if sprite.animate:
                sprite.Animoi()


class Background:
    def __init__(self, screen, scroll, w, h):
        self.width = w
        self.height = h
        self.screen = screen
        self.scroll = scroll

        self.bg_images = []
        for i in range(1, 5):
            self.bg_image = pygame.image.load(os.path.join(
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
