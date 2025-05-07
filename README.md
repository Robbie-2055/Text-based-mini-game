# Oreopolis: Text-Based Mining Adventure
Oreopolis is a C++ text-based grid exploration game where you play as a miner navigating a 12x12 map. 
Your goal is to mine hidden gems and ores, avoid obstacles, and sell your loot at the shop. Once you earn $100 or more, you win the game!

Features
* Randomized map generation for replayability.
* Inventory system to track mined resources.
* Shop interaction system.
* Basic movement and collision handling.

## Game play
* You control a miner starting at position (0,0).
* Use W, A, S, D keys to move:
W = Up, A = Left, S = Down, D = Right
* Press I to check your inventory.
* Mine gems (G) worth $10 and ores (O) worth $5.
* Avoid obstacles (X)—they block your path!
* Visit the shop (S) to sell mined minerals.
* Reach $100 or more to win.

## Symbols on the Grid
| Symbol | Meaning     |
| ------ | ----------- |
| `P`    | Player      |
| `G`    | Gem         |
| `O`    | Ore         |
| `S`    | Shop        |
| `X`    | Obstacle    |
| `.`    | Empty Space |
