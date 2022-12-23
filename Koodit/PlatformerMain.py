from Palikat import Palikat
from MainMenu import MainMenu
import pygame
import sys


"""

    GAME LOOP() 23.12.2022 klo 12.00 | Kesto 28.5 SEC

"""


class DawnOfTheRats:
    __slots__ = "maxRuudut", "width", "heigth", "profile", "window", "clock"

    def __init__(self) -> None:
        pygame.init()
        pygame.event.set_allowed(
            pygame.QUIT | pygame.KEYDOWN | pygame.MOUSEBUTTONDOWN)
        infoObject = pygame.display.Info()
        self.maxRuudut = 25  # kuinka monta ruuta näkyy oikealle ja ylös. Esim jos maxRuudut on 10 niin 10*10 ruutua näytöllä. 18% 25?
        self.width = infoObject.current_h
        self.heigth = infoObject.current_h-60
        self.profile = False
        self.window = pygame.display.set_mode((self.width, self.heigth), 0, 16)
        self.clock = pygame.time.Clock()
        self.Main_Menu()

    def Main_Menu(self):
        menu = MainMenu(self.window, self.width, self.heigth)
        while menu.päällä:
            self.clock.tick(60)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if (
                    event.type == pygame.MOUSEBUTTONDOWN
                    and pygame.mouse.get_pressed()[0]
                ):
                    menu.click = True
            self.window.fill((100, 100, 100))
            menu.run()
            pygame.display.update()

        self.Game_loop()

    def Game_loop(self):
        päällä = True
        palikat = Palikat(self.maxRuudut, self.width, self.heigth)
        while päällä:
            self.clock.tick(60)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    päällä = False
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if pygame.mouse.get_pressed()[0]:
                        palikat.player.hyökkäys = not palikat.player.hyökkäys
                    elif pygame.mouse.get_pressed()[2]:
                        palikat.klikObejet(pygame.mouse.get_pos())

            if palikat.player.hp == 0:
                päällä = False
                pygame.mixer.music.fadeout(500)
                self.Main_Menu()

            pygame.display.set_caption(str(int(self.clock.get_fps())))
            self.window.fill((146, 244, 255))
            palikat.run()
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
        #    ./ProfilingJuttu.prof kun haluu profilaa


dawnOfTheRats = DawnOfTheRats()
