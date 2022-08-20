from Palikat import Palikat
from MainMenu import MainMenu
import pygame, sys



maxRuudut = 32 # kuinka monta ruuta näkyy oikealle ja ylös. Esim jos maxRuudut on 10 niin 10*10 ruutua näytöllä. 18% 25?

pygame.init()
infoObject = pygame.display.Info()
width = infoObject.current_w
heigth = infoObject.current_h-60
win =  pygame.display.set_mode((infoObject.current_w, infoObject.current_h-60))

clock = pygame.time.Clock()

def Main_Menu(win):
    clock = pygame.time.Clock()
    menu = MainMenu(win,width,heigth)
    while menu.päällä: 
        clock.tick(60)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:  
                pygame.quit()
                sys.exit() 
            if event.type == pygame.MOUSEBUTTONDOWN:
                if pygame.mouse.get_pressed()[0]:
                    menu.click = True
                         


        win.fill((100,100,100)) 
        menu.run()
        pygame.display.update()
    Game_loop(win)
    
def Game_loop(win):
    päällä = True
    palikat = Palikat(maxRuudut,width,heigth)
 # mainloop
    clock = pygame.time.Clock()
    while päällä: 
        clock.tick(60)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:  
                päällä = False
               
            if event.type == pygame.MOUSEBUTTONDOWN:
                if pygame.mouse.get_pressed()[0]:
                    palikat.player.hyökkäys = not palikat.player.hyökkäys
                    print(clock)
                    print(palikat.kärpäs_group)
                elif pygame.mouse.get_pressed()[2]:
                    palikat.klikObejet(pygame.mouse.get_pos())
            
        
        if palikat.player.hp == 0:
            päällä = False
            pygame.mixer.music.fadeout(500)
            Main_Menu(win)
        win.fill((146,244,255)) 

        palikat.run()
        pygame.display.update()

    
Main_Menu(win)
#Game_loop(win)
    