#import "@preview/cetz:0.4.2"
#import "@local/cetz-graph:0.1.0": ic, wire

#cetz.canvas(length: .5cm, {
  import cetz.draw: *
  set-style(
    stroke:(thickness:2pt)
  )
  ic((-6,0),pins: 10,label: "IMU", width: 3)
  line((-2,0),(-4,0), mark:(end:">", start:">", fill:black))
  ic((0,0),pins: 10,label: "ESP32", width: 3)
  line((2,-1),(4,-3), mark:(end:">", start:">", fill:black))
  line((2,0),(4,0), mark:(end:">", start:">", fill:black))
  line((2,1),(4,3), mark:(end:">", start:">", fill:black))
  ic((6,-4),pins: 10,label: "STM32", width: 3)
  ic((6,0),pins: 10,label: "STM32", width: 3)
  ic((6,4),pins: 10,label: "STM32", width: 3)
  line((8,-4),(10,-4), mark:(end:">", start:">", fill:black))
  line((8,0),(10,0), mark:(end:">", start:">", fill:black))
  line((8,4),(10,4), mark:(end:">", start:">", fill:black))
  ic((12.5,-4),pins: 10,label: "DRV8316", width: 4)
  ic((12.5,0),pins: 10,label: "DRV8316", width: 4)
  ic((12.5,4),pins: 10,label: "DRV8316", width: 4)
  line((15,-4),(17,-4), mark:(end:">", start:">", fill:black))
  line((15,0),(17,0), mark:(end:">", start:">", fill:black))
  line((15,4),(17,4), mark:(end:">", start:">", fill:black))
  circle((19,-4),radius:1.5)
  circle((19,0),radius:1.5)
  circle((19,4),radius:1.5)
  content((19,-4),[MOTOR])
  content((19,0),[MOTOR])
  content((19,4),[MOTOR])

})
