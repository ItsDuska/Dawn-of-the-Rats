class Collisions:
    def __init__(self) -> None:
        pass

    def horizontal_collisions(self):
        for sprite in self.collision_sprites.sprites():
            if (sprite.passable and sprite.rect.colliderect(self.rect) and sprite.type not in [36, 37, 38]):
                if self.direction.x < 0:
                    self.rect.left = sprite.rect.right
                elif self.direction.x > 0:
                    self.rect.right = sprite.rect.left

    def vertical_collisions(self):
        for sprite in self.collision_sprites.sprites():
            if sprite.passable and sprite.rect.colliderect(self.rect):
                if self.direction.y > 0 and (sprite.type not in [36, 37, 38] or not self.alas):
                    self.rect.bottom = sprite.rect.top
                    self.direction.y = 0
                    self.on_floor = True
                    self.orbattu = False

                if self.direction.y < 0 and sprite.type not in [36, 37, 38]:
                    self.rect.top = sprite.rect.bottom
                    self.direction.y = 0

        if self.on_floor and self.direction.y != 0:
            self.on_floor = False
            self.alas = False