
Final Burn Alpha SDL for GCW-Zero
---------------------------------

FB Alpha is an arcade emulator supporting the following hardware platforms;

 - Capcom CPS-1 
 - Capcom CPS-2 
 - Capcom CPS-3 
 - Cave 
 - Data East DEC-0, DEC-8 and DECO IC16 based games 
 - Galaxian based hardware 
 - Irem M62, M63, M72, M90 and M92 hardware 
 - Kaneko 16 
 - Konami 
 - Neo-Geo 
 - Pacman based hardware 
 - PGM 
 - Psikyo 68EC020 and SH-2 based hardware 
 - Sega System 1, System 16 (and similar), System 18, X-Board and Y-Board 
 - Toaplan 1 
 - Toaplan 2 
 - Taito F2, X, Z and others 
 - Miscellaneous drivers for lots of other hardware 


Supported games
---------------

Refer to gamelist.txt for the list of supported roms


Version
-------

FBA SDL for GCW-Zero is based on FBA 0.2.97.35.

Romset is synchronized with MAME 0.159


How to use FB Alpha
-------------------

FBA SDL is now merged with the frontend based on Capex in one application. Just
run it, press START and choose Rom Show mode: all, available or non-available.
If needed, supplementary rom paths could be set.

FBA SDL could be used as a standalone application when invoked with
rom zip with full path as a parameter:

./fbasdl.dge ./roms/dino.zip

Full path and extension are obligatory.


Commandline interface
---------------------

FBA SDL can also be invoked with command line options. 
The options are as follows;

./fbasdl.dge <game> [<parameters>]

<game>                  - The game's romname with full path and extension.
--no-sound              - Just be silent
--sound-sdl             - Use SDL for sound (mutex syncro)
--sound-sdl-old         - Use SDL for sound
--sound-ao              - Use libao for sound
--samplerate=<Hz>       - Valid values are: 11025, 16000, 22050, 32000 and 44100
--sense=<value>         - Analog sensitivity: 0..100
--showfps               - Show frames per second while play
--vsync                 - Syncronize video refresh on 60Hz
--68kcore=<value>       - Choose Motorola 68000 emulation core.
                          0 - C68k, 1 - Musashi M68k, 2 - A68k

Example:

./fbasdl.dge ./roms/dino.zip --sound-sdl --samplerate=44100 --68kcore=0


Controls and hotkeys
--------------------

Standard keymapping:
D-PAD        - D-PAD
SELECT       - Coin1
START        - Start1
SELECT+START - Start2
A            - Fire1
B            - Fire2
X            - Fire3
Y            - Fire4
L            - Fire5
R            - Fire6

L+R+Y        - Show/hide fps
L+R+A        - Quick state load
L+R+B        - Quick state save
L+R+SELECT   - Service menu
L+R+START    - FBA menu (key config and load/save states)

All fire keys could be redefined in the menu.


Thanks go to
------------

Slaanesh for not releasing FBA320 sources which gave me enough motivation to
replicate his work. :)


Source code
-----------

https://github.com/dmitrysmagin/fba-a320
https://github.com/dmitrysmagin/fba-sdl

Dmitry Smagin
exmortis [at] yandex [dot] ru

FB Alpha is written by FB Alpha Team
http://fbalpha.com/
