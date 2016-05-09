## CSE 5337 Asteroids Project
A semi-finished Asteroids Games using C++ and openGL.

## Features
### Completed
- Ship Movement
    - The ship is able to move about the screen using the arrow keys.
- Ship Wrapping
    - Once the ship leaves the screen, frustrum calculation and culling happens so the ship appears on the other side of the screen.
- Asteroid Movement
    - Same as the ship.
### Sort of Completed
- Collision: Ship vs Asteroid
    - Collision detection? Check.  Collision Response? Nope.
    - Basically if there is a collision between the ship and an asteroid, nothing happens.
- Collision: Missile vs Asteroid
    - Same as ship vs asteroid.
    - Also, the missile never disappears after it leaves the screen or hits an asteroid.  A new missile never appears either.