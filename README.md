## Spaceship
Simple DirectX spaceship game

## Rules:
Spaceship is always located on the bottom of the screen and meteors will always spawn at the top of the screen.  
Meteros have random rotation, velocity and direction deviation.  
If either meteor or projectile goes off the screen it gets destroyed.  
Spaceship has its fire rate and it gives the initial velocity to projectiles.  
The more meteors player will destory the more will spawn (logarithmic growth).

If projectile hit meteor both get destroyed.  
If meteor hit spaceship the game restarts.

## Movement:
- A or Left moves spaceship left
- D or Right moves spaceship right
- Space fires projectile

## Development
This game was created in Visual Studio 2015 using DirectX 11 and [DirectXTK](https://github.com/Microsoft/DirectXTK).
