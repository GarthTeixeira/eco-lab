import pygame
pygame.init()

W, H = 640, 480
screen = pygame.display.set_mode((W, H))
pygame.display.set_caption("Teste Pygame")
clock = pygame.time.Clock()

x, y = 50, 50
vx, vy = 3, 2

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # pinta o fundo (cinza)
    screen.fill((40, 40, 40))

    # desenha um retângulo (verde) se movendo
    pygame.draw.rect(screen, (0, 200, 0), (x, y, 60, 40))

    # movimentação simples + bounce
    x += vx; y += vy
    if x < 0 or x+60 > W: vx *= -1
    if y < 0 or y+40 > H: vy *= -1

    pygame.display.flip()   # ou pygame.display.update()
    clock.tick(60)          # limita a 60 FPS

pygame.quit()
