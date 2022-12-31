from World.GameHandler import GameHandler
from MainMenu.MainMenu import MainMenu
from os import path
#from time import time
import pygame



#15.541315079 millisekunttia main loop

class DawnOfTheRats: 
    __slots__ = "maxRuudut", "width", "heigth", "profile", "window", "clock"

    def __init__(self) -> None:
        pygame.init()
        pygame.event.set_allowed(
            pygame.QUIT | pygame.KEYDOWN | pygame.MOUSEBUTTONDOWN)
        infoObject = pygame.display.Info()
        self.maxRuudut = 25  # kuinka monta ruuta näkyy oikealle ja ylös. Esim jos maxRuudut on 10 niin 10*10 ruutua näytöllä. 18% 25?
        self.width = infoObject.current_h
        self.heigth =  infoObject.current_h-60
        self.profile = False        #48
        icon = pygame.image.load(path.join("kuvat", "MainMenuStuff","Rat","rat-spinning1.png"))#.convert_alpha()
        self.window = pygame.display.set_mode((self.width, self.heigth), 0, 16)
        pygame.display.set_icon(icon)
        self.clock = pygame.time.Clock()
        self.Main_Menu()

    def Main_Menu(self):
        menu = MainMenu(self.window, self.width, self.heigth)
        while menu.isWindowOn:
            self.clock.tick(60)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    exit()
                if (
                    event.type == pygame.MOUSEBUTTONDOWN
                    and pygame.mouse.get_pressed()[0]
                ):
                    menu.click = True
            self.run(100, 100, 100, menu)
        if self.profile:
            self.profiling()
        else:
            self.Game_loop()

    def Game_loop(self):           
        gameHandler = GameHandler(self.maxRuudut, self.width, self.heigth)
        while gameHandler.player.hp > 0:
            #start = time()
            self.clock.tick(60)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    gameHandler.player.hp = 0
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if pygame.mouse.get_pressed()[0]:
                        gameHandler.player.attacking = not gameHandler.player.attacking
                    elif pygame.mouse.get_pressed()[2]:
                        gameHandler.klikObejet(pygame.mouse.get_pos())
                if event.type == pygame.KEYUP and event.key == pygame.K_m:
                    gameHandler.player.playerInput.mute = not gameHandler.player.playerInput.mute

            pygame.display.set_caption(str(int(self.clock.get_fps())))   
            self.run(146, 244, 255, gameHandler)
           # end = time()
            #print(end-start)
        pygame.mixer.music.fadeout(500)
        self.Main_Menu()
        

    def run(self, arg0, arg1, arg2, arg3):
        self.window.fill((arg0, arg1, arg2))
        arg3.run()
        pygame.display.update()

    def profiling(self):
        if not self.profile:
            return

        import cProfile
        import pstats

        with cProfile.Profile() as pr:
            self.Game_loop()

        stats = pstats.Stats(pr)
        stats.sort_stats(pstats.SortKey.TIME)
        stats.dump_stats(filename="ProfilingJuttu.prof")
        #   snakeviz ./ProfilingJuttu.prof kun haluu profilaa


dawnOfTheRats = DawnOfTheRats()
