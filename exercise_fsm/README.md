# Excercise 1: Design Finite State Machine for button behavior
## Requirements: 
This excercise focus on designing Finite State Machine for button based on these below behaviors:
- Button recognize one single click and print "1 click"
- Button accept double clicks and print "2 click"
- Button detect long click (user hold button) and print "hold"
- Button release only after hold and print "release"
Some other requirements:
- Button should debounce if it appear signal noise while interraction
- System should export only one message corresponding to user action for each state
## General diagram for button behavior
### Noisy pulse
![Pulse diagram for noise detection](https://github.com/PDucMinh/CCpp-Advance/assets/98310838/7d16d1aa-f577-44a2-b479-1672e97bc12c)

### One click button
![Pulse diagram for single click](https://github.com/PDucMinh/CCpp-Advance/assets/98310838/ee96d639-ef4a-4632-a1dd-8a5683bc497f)

### Double click button
![Pulse diagram for double click](https://github.com/PDucMinh/CCpp-Advance/assets/98310838/2661f53e-c8b6-44dc-bba4-38004cb79f05)


### Hold button then release

## General FSM design
![Finite state machine for button detection](https://www.plantuml.com/plantuml/png/XPB1ReGm34Jl_WfhpqK2LxrK5Lgff_v3BmWYWHe28icXVz-rWpU8fjtRQDuOUu2h3zqMucnXd0Q3Pbx3Dmx6zzkqXcbn0BT0C7Zv6AovOEUHnTrqKn2JXPeDzdRglyH_PzKeeKHyHgHeNEmWDWirDsDDvzFQNIloux85Z4uUY8r4V6pAc7PC07mzLd6jMXJvYlNkjLBYPZG0egf3HfqSma-70T_mkPvzfgblvctYa7o9-CYyrlcNcWDthWiqqFuEy1lI3SN0-GXT0ZuU0iI1fzH1i59joApDx7ZyFsDr7jFUj8_I7xtfKMzwr9jEjKwzUP8J-XFnccpgS_dzb3RbebJ-nfcNYYeijqmKz33zv-1gt11d-mC0)


# Excercise 2: Design Finite State Machine detect "10110"