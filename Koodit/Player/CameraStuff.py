import pygame
from Visuals.Background import Background


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
                    if sprite.rect.colliderect(player.rect) and player.playerInput.jump_on_air and player.orbHandler.useOrb == True:
                        player.orbHandler.useOrb = False
                        player.orbHandler.getOrb(sprite.orbType)
                    sprite.AddParticle(self.offset)
                    sprite.Update_Particle(-self.offset[0], -self.offset[1])
                if player.hurtingTime == 0 and not player.hurting:
                    player.lopetaHurting = False
            if sprite.type in [223, 224, 402]:
                player.Check_hurting(sprite.rect)

