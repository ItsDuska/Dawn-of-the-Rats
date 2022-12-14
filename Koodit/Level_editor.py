import itertools
from genericpath import exists
import pygame
import numpy
import os
from time import time

from World.PalikkaKuvat import blockit, Läpi_palikat


pygame.init()
win = pygame.display.set_mode((800, 800))
koko = (800, 800)
clock = pygame.time.Clock()
päällä = True
tausta = pygame.image.load(os.path.join(
    "Kuvat", "Taustakuva.png")).convert_alpha()
tausta = pygame.transform.scale(tausta, (800, 800))

taso = input("anna taso\n")


class Render:
    def __init__(self, maxRuudut, näyttö, taso):
        self.maxRuudut = maxRuudut
        # self.levelit = Levelit()
        self.display_surface = näyttö
        self.width = 800
        self.height = 800
        self.currentFrame = 1
        self.world_shift_x = 0
        self.world_shift_y = 0
        self.world_shift_xx = 0  # muistiin
        self.world_shift_yy = 0  # muistiin
        self.maailma_x = 0  # max on
        self.maailma_y = 0
        self.offset_x = 0
        self.offset_y = 0
        self.alotus = 0
        self.holdingShift = False
        self.HoldPos = (0, 0)
        self.clicked = False
        self.mousePos = [0,0]
        self.matrixPos = [0,0]
        self.delete = False
        self.Palikat = blockit

        self.Läpi_palikat = Läpi_palikat

        self.animated_objects = {401: [["Orb1.png"], ["Orb"]], 402: [["Plant1.png"], ["Venus_Trap"]], 403: [["FishBoi1.png"], ["FishBoi"]], 404: [["SlimeBoi1.png"], ["SlimeBoi"]],
                                 405: [["Snakee1.png"], ["Snake"]], 406: [["ZombiNPC1.png"], ["ZombiNPC"]], 407: [["Dash1.png"], ["Orb"]], 408: [["Bord1.png"], ["Bord"]], 409: [["FallingRock1.png"], ["FallingRock"]],
                                 410:[["Water_Waves1.png"],["Water_Waves"]]
                                 }

        ##########################
        self.enemies = [405, 408, 409]
        ##########################

        self.tasoDir = os.path.join("Tasot", taso)

        self.Luo()

        self.tyyppi = self.Palikat

        self.drawnTiles = pygame.sprite.Group()
        self.tiles = pygame.sprite.Group()
        self.setup_level(self.level)

    def setup_level(self, tasoData):
        self.generation_loop(tasoData, self.Palikat)
        self.generation_loop(tasoData, self.Läpi_palikat)
        self.generation_loop(tasoData, self.animated_objects)

    def generation_loop(self, tasoData, kuva):
        for row_index, row in enumerate(tasoData):
            for col_index, col in enumerate(row):
                x = col_index * int(self.width/self.maxRuudut)
                y = row_index * int(self.width/self.maxRuudut)
                if col in kuva:
                    if col >= 201 and col <= 400:
                        self.lisää_kuva(
                            x, y, kuva[col], self.display_surface, "PalikkaKuvat", False, False)
                    elif col <= 200:
                        self.lisää_kuva(
                            x, y, kuva[col], self.display_surface, "PalikkaKuvat", False, False)
                    elif col >= 401 and col not in self.enemies:  # vika on enemies
                        self.lisää_kuva(
                            x, y, kuva[col][0][0], self.display_surface, kuva[col][1][0], True, False)
                    elif col in self.enemies:  # enemies
                        self.lisää_kuva(
                            x, y, kuva[col][0][0], self.display_surface, kuva[col][1][0], True, True)

    def lisää_kuva(self, a, b, kuva, näyttö, kansio, kansio2, enemy):
        tile = Palikka((a+self.world_shift_xx, b+self.world_shift_yy), self.maxRuudut,
                            kuva, näyttö, self.maxRuudut, self.width, self.height, kansio, kansio2, enemy)
        self.tiles.add(tile)

    def lisää_kuva2(self, a, b, kuva, näyttö, kansio, kansio2, enemy):
        tile = Palikka((a * int(self.width/self.maxRuudut), b * int(self.width/self.maxRuudut)), self.maxRuudut,
                            kuva, näyttö, self.maxRuudut, self.width, self.height, kansio, kansio2, enemy)
        self.tiles.add(tile)


    def changeImage(self,col,tile):
        kuvat = [self.Palikat,self.Läpi_palikat,self.animated_objects]
        for kuva in kuvat:
            if col not in kuva:
                continue


            if col >= 201 and col <= 400:
               # self.lisää_kuva(x,y, kuva[col], self.display_surface, "PalikkaKuvat", False, False)
                tile.setImage("PalikkaKuvat",False,False,kuva[col])
            elif col <= 200:
                #self.lisää_kuva(x, y, kuva[col], self.display_surface, "PalikkaKuvat", False, False)
                tile.setImage("PalikkaKuvat",False,False,kuva[col])

            elif col >= 401 and col not in self.enemies:  # vika on enemies
                #self.lisää_kuva(x, y, kuva[col][0][0], self.display_surface, kuva[col][1][0], True, False)
                tile.setImage(kuva[col][1][0],True,False,kuva[col][0][0])
            elif col in self.enemies:  # enemies
                #self.lisää_kuva(x, y, kuva[col][0][0], self.display_surface, kuva[col][1][0], True, True)
                tile.setImage(kuva[col][1][0],True,True,kuva[col][0][0])

    def addNewBlockToGrid(self,col):
            kuvat = [self.Palikat,self.Läpi_palikat,self.animated_objects]
            for kuva in kuvat:
                if col not in kuva:
                    continue

                if col >= 201 and col <= 400:
                    self.lisää_kuva2(
                        self.matrixPos[0],self.matrixPos[1], kuva[col], self.display_surface, "PalikkaKuvat", False, False)
                    
                elif col <= 200:
                    self.lisää_kuva2(
                        self.matrixPos[0],self.matrixPos[1] , kuva[col], self.display_surface, "PalikkaKuvat", False, False)
                elif col >= 401 and col not in self.enemies:  # vika on enemies
                    self.lisää_kuva2(
                            self.matrixPos[0],self.matrixPos[1], kuva[col][0][0], self.display_surface, kuva[col][1][0], True, False)
                elif col in self.enemies:  # enemies
                    self.lisää_kuva2(
                            self.matrixPos[0],self.matrixPos[1], kuva[col][0][0], self.display_surface, kuva[col][1][0], True, True)
                


    def move(self):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_a] and self.offset_x >= 1:
            self.world_shift_x = int(self.width/self.maxRuudut)
            self.world_shift_xx += int(self.width/self.maxRuudut)
            self.offset_x += -1
        elif keys[pygame.K_d] and self.offset_x <= 500-self.maxRuudut:
            self.world_shift_x = -int(self.width/self.maxRuudut)
            self.world_shift_xx += -int(self.width/self.maxRuudut)
            self.offset_x += 1
        else:
            self.world_shift_x = 0
        if keys[pygame.K_w] and self.offset_y >= 1:
            self.world_shift_y = int(self.width/self.maxRuudut)
            self.world_shift_yy += int(self.width/self.maxRuudut)
            self.offset_y += -1
        elif keys[pygame.K_s] and self.offset_y <= 100-self.maxRuudut:
            self.world_shift_y = -int(self.width/self.maxRuudut)
            self.world_shift_yy += -int(self.width/self.maxRuudut)
            self.offset_y += 1
        else:
            self.world_shift_y = 0
        if keys[pygame.K_r]:
            self.Reset()
        elif keys[pygame.K_e]:
            self.Tallennus()

        self.holdingShift = bool(keys[pygame.K_LSHIFT])
        if keys[pygame.K_1]:
            self.tyyppi = self.Palikat
            self.currentFrame = 1
            self.alotus = 0
        elif keys[pygame.K_2]:
            self.tyyppi = self.Läpi_palikat
            self.currentFrame = 1
            self.alotus = 200
        elif keys[pygame.K_3]:
            self.tyyppi = self.animated_objects
            self.currentFrame = 1
            self.alotus = 400

    def drawGrid(self):
        # Set the size of the grid block
        blockSize = int(self.width/self.maxRuudut)
        for x, y in itertools.product(range(0, 800, blockSize), range(0, 800, blockSize)):
            rect = pygame.Rect(x, y, blockSize, blockSize)
            pygame.draw.rect(self.display_surface,
                             (100, 100, 100), rect, 1)

    def FillArea(self, x, y, delete):
        for Y, X in itertools.product(range(self.HoldPos[1], y), range(self.HoldPos[0], x)):
            if delete:
                self.clicked = True
                self.level[Y][X] = 0
            elif self.level[Y][X] != self.currentFrame + self.alotus:
                self.level[Y][X] = self.currentFrame + self.alotus
            self.addNewBlockToGrid(self.currentFrame + self.alotus)
        #self.tiles.empty()
        #self.setup_level(self.level)

    def click(self, x, y, delete):
        self.delete = delete
        self.mousePos = [x,y]
        grid_x, grid_y = x//int(self.width /
                                self.maxRuudut), y//int(self.width/self.maxRuudut)

        grid_x += self.offset_x
        grid_y += self.offset_y

        self.matrixPos = [grid_x,grid_y]

        if self.holdingShift:
            self.FillArea(grid_x, grid_y, delete)
            self.tiles.empty()
            self.setup_level(self.level)
            return
        else:
            self.HoldPos = (grid_x, grid_y)

        if delete:
            self.clicked = True
            self.level[grid_y][grid_x] = 0
        elif self.level[grid_y][grid_x] == self.currentFrame + self.alotus:
            return
        else:
            self.level[grid_y][grid_x] = self.currentFrame + self.alotus
            self.addNewBlockToGrid(self.level[grid_y][grid_x])
        #self.tiles.empty()
        #self.setup_level(self.level)

    def Tallennus(self):
        arr = numpy.array(self.level)
        numpy.savetxt(self.tasoDir, arr, fmt="%d")

    def Lataa(self):
        with open(self.tasoDir, "r") as file:
            return [[int(digit) for digit in line.split()] for line in file]

    def Luo(self):
        if exists(self.tasoDir):
            self.level = self.Lataa()
            return self.Lataa()
        f = open(self.tasoDir, "x")
        f.close()
        self.level = [[0 for _ in range(500)] for _ in range(100)]

    def Reset(self):
        f = open(self.tasoDir, "w").close()
        self.tiles.empty()
        self.level = [[0 for _ in range(500)] for _ in range(100)]
        self.setup_level(self.level)

    def DrawGUI(self):
        if self.currentFrame+self.alotus <= 0 or (self.currentFrame+self.alotus <= 200 and self.tyyppi == self.Läpi_palikat) or (self.currentFrame+self.alotus <= 400 and self.tyyppi == self.animated_objects):
            self.currentFrame = len(self.tyyppi)
        elif self.currentFrame >= 1+len(self.tyyppi):
            self.currentFrame = 1

        if self.tyyppi == self.animated_objects:
            if self.currentFrame+self.alotus in self.enemies:
                self.kuvaa = pygame.image.load(os.path.join(
                    "Kuvat", "Enemies", self.animated_objects[self.currentFrame+self.alotus][1][0], self.animated_objects[self.currentFrame+self.alotus][0][0])).convert_alpha()
            else:
                self.kuvaa = pygame.image.load(os.path.join("Kuvat", "Palikat", "Animoidut_palikat", self.animated_objects[
                    self.currentFrame+self.alotus][1][0], self.animated_objects[self.currentFrame+self.alotus][0][0])).convert_alpha()
        else:

            self.kuvaa = pygame.image.load(os.path.join(
                "Kuvat", "Palikat", "PalikkaKuvat", self.tyyppi[self.currentFrame+self.alotus])).convert_alpha()

        self.kuvaa = pygame.transform.scale(self.kuvaa, (64, 64))
        self.display_surface.blit(self.kuvaa, (0, 736))

    def run(self):
        self.renderOnlyOnScreen()
        self.tiles.update(self.world_shift_x, self.world_shift_y)
        self.move()
        self.drawGrid()
        self.DrawGUI()

    """
    Ennen:
    0.003535747528076172
    0.0020220279693603516
    0.0025217533111572266
    
    Nyt:


    """

    def addNewBlock(self,tile):
        if not self.click:
            return
        
        
        if tile.rect.collidepoint(self.mousePos[0], self.mousePos[1]):
            if self.delete:
                self.tiles.remove(tile)
            else:    
                self.changeImage(self.level[self.matrixPos[1]][self.matrixPos[0]],tile)

        self.clicked = False
        


    def renderOnlyOnScreen(self):
        #a = time()
        for tile in self.tiles:
            self.addNewBlock(tile)
            if not self.isInScreen((tile.rect.x,tile.rect.y)):
                continue
        
            
            self.display_surface.blit(tile.image,(tile.rect.x,tile.rect.y))
        #b = time()
        #print(b-a)


    def isInScreen(self,pos):
            # 50 luku on sitä varten ettei kulmissa näy tyhjää
            return (
                pos[0] >= -50
                and pos[0] <= self.width+50
                and pos[1] >= -50
                and pos[1] <= self.height+50
        )


class Palikka(pygame.sprite.Sprite):
    def __init__(self, pos, size, kuva, näyttö, maxRuudut, width, height, kansio, kansio2, enemy) -> None:
        super().__init__()
        self.maxRuudut = maxRuudut
        self.width = width
        self.height = height
        self.setImage(kansio,kansio2,enemy,kuva)
        näyttö.blit(self.image, (size, size))
        self.rect = self.image.get_rect(topleft=pos)

    def setImage(self,kansio,kansio2,enemy,kuva):
        if kansio2:
            if enemy:
                self.image = pygame.image.load(os.path.join(
                    "Kuvat", "Enemies", kansio, kuva)).convert_alpha()
            else:
                self.image = pygame.image.load(os.path.join(
                    "Kuvat", "Palikat", "Animoidut_palikat", kansio, kuva)).convert_alpha()
        else:
            self.image = pygame.image.load(os.path.join(
                "Kuvat", "Palikat", kansio, kuva)).convert_alpha()
        self.image = pygame.transform.scale(
            self.image, (int(self.width/self.maxRuudut), int(self.height/self.maxRuudut)))
        
        
    def update(self, x_shift, y_shift):
        self.rect.x += x_shift
        self.rect.y += y_shift


render = Render(30, win, taso)

while päällä:
    clock.tick(25)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            päällä = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 5:
                # alas scrolli
                render.currentFrame += 1
            elif event.button == 4:
                # ylös scrolli
                render.currentFrame -= 1
        if pygame.mouse.get_pressed()[0]:
            pos = pygame.mouse.get_pos()
            render.click(pos[0], pos[1], False)
        if pygame.mouse.get_pressed()[2]:
            pos = pygame.mouse.get_pos()
            render.click(pos[0], pos[1], True)

    win.fill((0, 0, 0))
    win.blit(tausta, (0, 0))
    render.run()
    pygame.display.update()


render.Tallennus()
