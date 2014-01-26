Episode 9: Player Jump
======================

Problem:

  - Quote should Jump when z is pressed.
    - Corollary. Quote should fall.
  - Quote should not fall through the 'floor'.

Details:

  - Quick keypress == Short Jump (~1.5 tiles)
  - Long keypress == High Jump (~3 tiles)
  - When jump is pressed, initially velocity up
  - When jump is held, gravity has no effect
    - Corollary: When jump expires, or button is released, gravity is in effect.
  - Once in free-fall, jump has no effect
    - Corollary: If jump is pressed/released/pressed before expiration and
      before free-fall, gravity will not have effect

Solution:

  - Introduce a nested class: Jump
    - hides jump details from player class
    - keep track of

        1. active
        2. total amount of time remaining in jump

  - What do we need to know?
    - +y is down and -y is up (top-left corner is 0,0)
    - are we on the ground (true when we collide with floor, false otherwise)?
    - has our jump expired (velocity\_y &gt;= 0 or time\_remaining &lt;= 0)?
