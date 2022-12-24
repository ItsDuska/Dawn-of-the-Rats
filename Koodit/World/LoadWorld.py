import pygame
from os import path
from Palikka import Palikka, AnimatedObj
from PalikkaKuvat import blockit, Läpi_palikat
from Enemy import Enemy, Snake, Bord
from CameraStuff import CameraGroup


class LoadWorld:
    def __init__(self, level, width, height, maxRuudut) -> None:
        self.display_surface = pygame.display.get_surface()
        self.width = width
        self.height = height
        self.maxRuudut = maxRuudut
        self.tasoDir = path.join("Tasot", level)
        self.num = 0
        self.enemies = [405, 408, 409]
        self.initGroups()
        self.setup_level(self.Lataa())

    def initGroups(self):
        self.enemy_group = pygame.sprite.Group()
        self.kärpäs_group = pygame.sprite.Group()
        self.visible_sprites = CameraGroup(self.width, self.height)
        self.active_sprites = pygame.sprite.Group()
        self.collision_sprites = pygame.sprite.Group()

    def Lataa(self):
        with open(self.tasoDir, "r") as file:
            return [[int(digit) for digit in line.split()] for line in file]

    def setup_level(self, tasoData):
        # 1-200 ei ole läpi päästävii. 201-400 on läpi päästäviä. 401-600 on animoituja
        animated_objects = {401: [["Orb1.png", "Orb2.png", "Orb3.png", "Orb4.png", "Orb5.png", "Orb6.png", "Orb7.png", "Orb8.png", "Orb9.png", "Orb10.png"],
                                  ["Orb"], 2], 402: [["Plant1.png", "Plant2.png", "Plant3.png", "Plant4.png", "Plant5.png", "Plant6.png", "Plant7.png", "Plant8.png", "Plant9.png", "Plant10.png"], ["Venus_Trap"]
                                                     ], 403: [["FishBoi1.png", "FishBoi1.png", "FishBoi1.png", "FishBoi2.png", "FishBoi2.png", "FishBoi2.png", "FishBoi3.png", "FishBoi3.png", "FishBoi3.png", "FishBoi3.png"], ["FishBoi"]],
                            404: [["SlimeBoi1.png", "SlimeBoi1.png", "SlimeBoi1.png", "SlimeBoi2.png", "SlimeBoi2.png", "SlimeBoi2.png", "SlimeBoi3.png", "SlimeBoi3.png", "SlimeBoi3.png", "SlimeBoi3.png", ], ["SlimeBoi"]],
                            405: [["Snakee1.png", "Snakee2.png", "Snakee3.png", "Snakee4.png", "Snakee5.png", "Snakee6.png", "Snakee7.png", "Snakee8.png", "Snakee9.png", "Snakee9.png", ], ["Snake"]],
                            406: [["ZombiNPC1.png", "ZombiNPC1.png", "ZombiNPC2.png", "ZombiNPC2.png", "ZombiNPC2.png", "ZombiNPC3.png", "ZombiNPC3.png", "ZombiNPC3.png", "ZombiNPC4.png", "ZombiNPC4.png"], ["ZombiNPC"]],
                            407: [["Dash1.png", "Dash2.png", "Dash3.png", "Dash4.png", "Dash5.png", "Dash6.png", "Dash7.png", "Dash8.png", "Dash9.png", "Dash10.png", "Dash11.png", "Dash12.png"],
                                  ["Orb"], 1], 408: [["Bord1.png", "Bord2.png", "Bord3.png", "Bord3.png", "Bord4.png", "Bord5.png", "Bord6.png", "Bord7.png", "Bord8.png"], ["Bord"]], 409: [["FallingRock1.png"], ["FallingRock"]]
                            }
        self.generation_loop(tasoData, blockit)
        self.generation_loop(tasoData, Läpi_palikat)
        self.generation_loop(tasoData, animated_objects)

    def generation_loop(self, tasoData, kuvat):
        for row_index, row in enumerate(tasoData):
            for col_index, col in enumerate(row):
                x = col_index * int(self.width/self.maxRuudut)
                y = row_index * int(self.height/self.maxRuudut)
                if col not in kuvat:
                    continue
                if col >= 201 and col <= 400:
                    self.lisää_kuva(
                        x, y, kuvat[col], self.display_surface, False, False, col)
                elif col <= 200:
                    self.lisää_kuva(
                        x, y, kuvat[col], self.display_surface, True, False, col)
                elif col >= 401:
                    self.enemyOrAnimatedObject(col, x, y, kuvat)

    def enemyOrAnimatedObject(self, col, x, y, kuva):
        if col in self.enemies:
            self.addEnemy(col, x, y, kuva)
        else:
            anim_obj = AnimatedObj(
                (x, y), self.maxRuudut, kuva[col], self.display_surface, self.width, self.height, True, True, col)
            self.visible_sprites.add(anim_obj)

    def addEnemy(self, col, x, y, kuva):
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

    def lisää_kuva(self, a, b, kuva, näyttö, passable, animate, col):
        if col == 225:
            self.num += 1
            Palikka((a, b), self.maxRuudut, kuva, näyttö, self.maxRuudut, self.width, self.height, [
                    self.visible_sprites, self.collision_sprites], passable, animate, col, self.num)
        else:
            Palikka((a, b), self.maxRuudut, kuva, näyttö, self.maxRuudut, self.width, self.height, [
                    self.visible_sprites, self.collision_sprites], passable, animate, col)
