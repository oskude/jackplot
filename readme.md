# jackplot

plot jack audio data in real-time. for fun and _"science"_...

**WARNING: as this is c - _and i dont really know what im doing_ - use at your own risk!**

<img src="jackplot.apng" style="background:black" title="you gotta see it live! snappy, crisp and minimal cpu usage!" />

> **SORRY** about the cpu usage of above apng, should play only once!

## help

- if you're a noob (like me) don't hesitate to ask "stupid" questions.
- if you're a pro don't hesitate to (rage AND) lend a hand.

## todo

0. learn c, jack, glfw and opengl :dizzy:
1. document development
1. window resize
1. point/"pixel" resize? (relative to window size?)
1. fullscreen (optional video mode?)
1. more input channels
1. channel plot color

## ideas

- midi input
- do not plot 0.0 values? (optional)
  - when multiple channels, i doubt we want to see all the 0.0 lines

## hmmm

- can jackplot set the port color in qjackctl graph?
  - and/or can jackplot get that from qjacktl graph?
- how do jack clients automagically connect to system ports?
  - is that them or jack server doing it?
- i need an audio player that doesnt create a new jack port on next track...
- _"sync to tempo"?_
