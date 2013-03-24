
Final Burn Alpha SDL for OpenDingux
-----------------------------------

FB Alpha is an arcade emulator supporting the following hardware platforms;

 - Capcom CPS-1
 - Capcom CPS-2
 - Cave
 - Neo Geo
 - Sega System 16 (and similar), System 18, X-Board, Y-Board
 - Toaplan
 - Taito Rainbow Islands/Operation Wolf/Rastan
 - Psikyo 68EC020 based hardware
 - misc stuff we like

Supported games
---------------

Refer to gamelist.txt for information


Versions
--------

FB Alpha SDL comes in two versions.

 - Legacy based on FBA 0.2.96.71 is intended for both Dingux/OpenDingux and
   can be run on Dingoo a320, Dingoo a380 and Ritmix rzx50. Screen size is
   detected automatically.
 - Current version based on FBA 0.2.97.24 is intended for GCW-Zero.


How to use FB Alpha
-------------------

FBA SDL is better be used in conjuction with fba-capex but it's not
obligatory. If you are using fba-capex make sure these files are present
in the same directory:

 ./roms       - put your roms here
 fbacapex.dge - frontend executable
 fbasdl.dge
 rominfo.fba
 zipname.fba

If you are using FBA SDL as standalone application then invoke it with
rom zip with full path as a parameter:

./fbasdl.dge ./roms/dino.zip

Full path and extension are obligatory.


Commandline interface
---------------------

FB Alpha can also be invoked with command line options. 
The options are as follows;

./fbasdl.dge <game> [<parameters>]

<game>                  - The game's romname with full path and extension.
--sound-sdl             - Use SDL for sound
--no-sound              - Just be silent
--samplerate=<Hz>       - Valid values are: 11025, 22050 and 44100
--sense=<value>         - (GCW-Zero) analog sensitivity: 0..100
--showfps               - Show frames per second while play
--68kcore=<value>       - (GCW-Zero) Choose Motorola 68000 emulation core.
                          0 - C68k, 1 - Musashi M68k
--z80core=<value>       - (Legacy) Choose Z80 emulation core.
                          0 - cz80, 1 - mame_z80
--use-swap              - (Legacy) Swap memory to file. Use only on legacy
                          Dinguxes and on Dingoo a380 and Ritmix rzx50
--frontend=<name>       - Frontend to run on exit, capex sets this parameter
                          to '--frontend=fbacapex.dge'

Example:

./fbasdl.dge ./roms/dino.zip --sound-sdl --samplerate=44100 --68kcore=0 --z80core=0


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


Usage/optimisation tips
-----------------------

If you are running on OpenDingux on Dingoo a320 you should do the following:

 - Overclock fba-capex/fbasdl to 408MHz (link properties)
 - Enable swap support:
   Create or edit the config file local/etc/swap.conf and add a line containing 
   SWAP_SD_SIZE_MB=megabytes. The path can be changed by adding a line
   containing SWAP_SD_FILE=path.

If you are running on legacy Dingux on Dingoo a320/a380 or Ritmix rzx50

 - Use '--use-swap' command switch


Thanks go to
------------

Slaanesh for not releasing FBA320 sources which gave me enough motivation to
replicate his work. :)


Source code
-----------

https://github.com/dmitrysmagin/fba-capex-a320
https://github.com/dmitrysmagin/fba-a320
https://github.com/dmitrysmagin/fba-sdl

Dmitry Smagin
exmortis [at] yandex [dot] ru

FB Alpha is written by FB Alpha Team
http://www.barryharris.me.uk/