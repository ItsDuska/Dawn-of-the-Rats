import pygame
from Visuals.Background import Background


class CameraGroup(pygame.sprite.Group):
    __slots__ = "scroll","CAMERA_BORDERS","display_surface","offset","background","WINDOW_SIZE","camera_rect",
    def __init__(self, w, h):
        super().__init__()
        self.scroll = 0
        self.CAMERA_BORDERS = {'left': 100,
                               'right': 200, 'top': 100, 'bottom': 150}
        self.display_surface = pygame.display.get_surface()
        self.offset = pygame.math.Vector2(100, 300)
        self.background = Background(self.display_surface, self.scroll, w, h)
        self.WINDOW_SIZE = pygame.display.get_window_size()
        
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
            self.background.scroll -= 1
            self.camera_rect.left = player.rect.left
        if player.rect.right > self.camera_rect.right:
            self.background.scroll += 1
            self.camera_rect.right = player.rect.right
        if player.rect.top < self.camera_rect.top:
            self.camera_rect.top = player.rect.top
        if player.rect.bottom > self.camera_rect.bottom:
            self.camera_rect.bottom = player.rect.bottom

        self.background.draw_bg()
        # camera offsetti kai jotain emt
        self.offset = pygame.math.Vector2(
            self.camera_rect.left - self.CAMERA_BORDERS['left'],
            self.camera_rect.top - self.CAMERA_BORDERS['top'])

        for sprite in self.sprites():
            offset_pos = sprite.rect.topleft - self.offset
            if not self.isInScreen(offset_pos):
                sprite.updateObject = False
                continue
            sprite.updateObject = True
            self.display_surface.blit(sprite.image, offset_pos)
            if sprite.animate:
                sprite.animate()
                #if player.hurtingTime == 0 and not player.hurting:
                   # player.lopetaHurting = False
            if sprite.type in [223, 224, 402]:
                player.checkHurting(sprite.rect)


    def isInScreen(self,pos):
        # 50 luku on sitä varten ettei kulmissa näy tyhjää
        return (
            pos[0] >= -50
            and pos[0] <= self.WINDOW_SIZE[0]+50
            and pos[1] >= -50
            and pos[1] <= self.WINDOW_SIZE[1]+50
        )

