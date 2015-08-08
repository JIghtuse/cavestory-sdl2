Reconstructing Cave Story
=========================
with C++11 and SDL 2.0
----------------------
[![Build status](https://travis-ci.org/JIghtuse/cavestory-sdl2.png?branch=master)](https://travis-ci.org/JIghtuse/cavestory-sdl2)

This project based on Christopher Herbert's ["Reconstructing Cave Story"](https://www.youtube.com/redirect?q=https%3A%2F%2Fwww.youtube.com%2Fplaylist%3Flist%3DPL006xsVEsbKjSKBmLu1clo85yLrwjY67X&session_token=1f8IgNHMWKHO6UV96j9zL0OKMK58MTM5MDI5MTY1M0AxMzkwMjA1MjUz).

I decided to make the same with SDL 2.0 and C++11.

Note on media content
---------------------
Original content from the game was taken from the [CaveStory tribute
site](http://www.cavestory.org/downloads_game.php). It is located at `content/original_graphics`.

You can buy CaveStory+ on [Steam](http://store.steampowered.com/app/200900/),
[Desura](http://www.desura.com/games/cave-story) or [Ubuntu Software
Centre](https://apps.ubuntu.com/cat/applications/cave-story-plus/) and add 
bitmaps with higher resolution to `content` directory. Next you need to change
line 6 of `src/config.cpp` to `return GraphicsQuality::HIGH;` and recompile the
game. Game settings will be improved someday (to change it in game itself).

For example, if you take the game from the Humble Indie Bundle 7, you can copy
bitmaps like that:

    cp <game_root>/data/base/{Arms,Bullet,bkBlue,Caret,MyChar,TextBox,Npc/NpcCemet,Stage/PrtCave}.bmp content

Where &lt;game\_root&gt; is path where you install the game (e.g. ~/.steam/steam/steamapps/common/Cave\ Story+).
You can also use import\_steam\_bitmaps.sh script for your needs.

Keys to play
------------
* &larr; go left
* &rarr; go right
* &darr; look down / interact
* &uarr; look up
* Z jump
* X fire
* Q quit

Used materials
--------------
* [Lesson 5: Clipping Sprite Sheets](http://twinklebear.github.io/sdl2%20tutorials/2013/08/27/lesson-5-clipping-sprite-sheets/) by [Twinklebear](http://twinklebear.github.io/)
* [SDL 1.2 to 2.0 Migration Guide](http://wiki.libsdl.org/MigrationGuide)

Resources
---------
* [Reconstructing Cave Story Playlist](https://www.youtube.com/redirect?q=https%3A%2F%2Fwww.youtube.com%2Fplaylist%3Flist%3DPL006xsVEsbKjSKBmLu1clo85yLrwjY67X&session_token=_R790HVt2Rq01ukIB2AOonlxcnt8MTM5MTk0NTQyMEAxMzkxODU5MDIw)
* [Reconstructing Cave Story (original)](https://github.com/chebert/cavestory-screencast)
* [/r/reconstructcavestory](http://www.reddit.com/r/reconstructcavestory)
* [PyGame translation](https://github.com/ilogik/cavestory-python)
* [LÖVE and MoonScript translation](https://github.com/Kingdaro/cavestory-love2d)
* [Rust translation](https://github.com/drbawb/rust-story)
