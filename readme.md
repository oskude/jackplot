# jackplot

plot [jack](https://jackaudio.org/) audio data in real-time. for fun and _"science"_...

**WARNING: as this is c - _and i dont really know what im doing_ - use at your own risk!**

<img src="docu/jackplot.apng" style="background:black" title="you gotta see it live! snappy, crisp and minimal cpu usage!"/>

> **SORRY** about the cpu usage of above apng, should play only once!

## todo

- [ ] learn c, jack, glfw and opengl :dizzy:
- [ ] document development
- [x] window resize
- [ ] data resize?
- [ ] point/"pixel" resize? (relative to window size?)
- [x] ~~fullscreen~~ : use your window manager
- [ ] more input channels
- [ ] channel plot color

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
