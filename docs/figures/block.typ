#import "@preview/cetz:0.4.2"
#import "@local/cetz-graph:0.1.0": ic, wire

#cetz.canvas(length: .6cm, {
  import cetz.draw: *
  set-style(
    stroke:(thickness:2pt)
  )
  ic((-7,0),pins: 10,label: "IMU", width: 3)
  line((-2,0),(-5,0), mark:(end:">", start:">", fill:black))
  ic((0,0),pins: 10,label: "ESP32", width: 3)
  line((2,0),(5,0), mark:(end:">", start:">", fill:black))
  ic((7,0),pins: 10,label: "DRV8316", width: 3)
  line((9,0),(12,0), mark:(end:">", start:">", fill:black))
  circle((14,0),radius:1.4)
  content((14,0),[MOTOR])

})
