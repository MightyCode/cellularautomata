# How to use our program :
First of all, it cover the seven first achievements. 
In order : 
        "Base version", "Multicoloritude", "Mouvements multiples", "Incomprésibilité", 
        "Généricité des règles", "Incomprésibilité fine", "Multicoloritude is back"

Our program work with multiple arguments when you build it, and when you lauch it.
Lauch arguments : 
-h --help : Display in the console the help of the program.
-m --frame number : Set the number of frame to simulate. Per default 3
-s --seed number : Set the seed of the random. Per default 2
-f --file file : Work only on SRULE=1, load a map based on a file.
-a --all : Work only on SRULE=1, load and display map after map, every map for a WIDTH and HEIGHT size.

Exemple of script line : ./src/project -m 200 -s 2
                         ./src/project -m 200 --file loop.txt
                         ./src/project -h

Build arguments :
WIDTH=number : Width of the map, number of columns. Per default 40.
HEIGHT=number : Height of the map, number of rows. Per default 30.
SRULE=number[0-2] : The set of rule you want to use.
- SRULE=0 game of life -> achiev 0, 1, 4
- SRULE=1 noita like the simulation -> achiev 2, 3, 4, 5, 6
- SRULE=2 compression rule shower -> achiev 3, 5

## Maps ##
A map can be created through the code but we prefer to load pregenerated map
Description of map:
- compression_test.txt(SRULE=2) show how conflits are handled and how cells around react to the resolution of the conflict.
- falling_sand.txt(SRULE=1) show of falling sand react after colliding with bunch of stones
- grid.txt (SRULE=1) ...
- loop.txt (SRULE=1) show how map full alternating sand and rough sand goes on. (Spoiler : It fall infinitly)
- sand_stone_blocks.txt(SRULE=1) ...
- sand_stone_water.txt (SRULE=1) show a sand, rough sand and water simulation