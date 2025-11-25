#import "@preview/cetz:0.4.2": canvas, draw

#canvas(length: 2cm, {
  import draw: *

  ortho(
    x: 30deg, 
    y: 30deg, 
    {
      let c = 1 
      
      // ============================================
      // 1. DRAW THE CUBE (The Background)
      // ============================================
      
      // Hidden Edges (Back) - Drawn first so they are behind everything
      set-style(stroke: (dash: "dashed", paint: gray))
      line((-c, -c, -c), (-c, c, -c))
      line((-c, -c, -c), (c, -c, -c))
      line((-c, -c, -c), (-c, -c, c))

      // Visible Edges (Front)
      set-style(stroke: (dash: "solid", paint: black, thickness: 2pt))
      // Top Rim
      line((-c, -c, c), (c, -c, c), (c, c, c), (-c, c, c), close: true)
      // Bottom/Side Rims
      line((c, -c, -c), (c, c, -c), (-c, c, -c)) 
      line((c, -c, -c), (c, -c, c))
      line((c, c, -c), (c, c, c))
      line((-c, c, -c), (-c, c, c))

      // Define styles for consistency
      let surf-style = (fill: luma(240), stroke: 2pt)
      let vec-width = 2pt

      // ============================================
      // 2. DRAW FACES & CURVED ARROWS
      // ============================================
      // We group the white circle and the curved arrow together 
      // so they share the same rotation.

      // --- TOP FACE (Blue) ---
      group({
        translate((0, 0, c)) // Move to top face
        
        // A. The White Mask
        circle((0,0), radius: 0.6, ..surf-style)
        
        // B. The Curved Torque Arrow
        // 'mode: "OPEN"' ensures it doesn't try to close the shape
        arc((0,0), start: 45deg, stop: 315deg, radius: 0.35, 
            stroke: (paint: blue, thickness: vec-width), 
            mark: (start: "stealth", end: "stealth", fill: blue))
      })

      // --- RIGHT FACE (Red) ---
      group({
        translate((c, 0, 0)) // Move to right face
        rotate(y: 90deg)     // Rotate to face right
        
        // A. The White Mask
        circle((0,0), radius: 0.6, ..surf-style)
        
        // B. The Curved Torque Arrow
        arc((0,0), start: 45deg, stop: 315deg, radius: 0.35, 
            stroke: (paint: red, thickness: vec-width), 
            mark: (start: "stealth", end: "stealth", fill: red))
      })

      // --- FRONT-LEFT FACE (Green) ---
      group({
        translate((0, -c, 0)) // Move to front-left face
        rotate(x: 90deg)      // Rotate to face forward
        
        // A. The White Mask
        circle((0,0), radius: 0.6, ..surf-style)
        
        // B. The Curved Torque Arrow
        arc((0,0), start: 45deg, stop: 315deg, radius: 0.35, 
            stroke: (paint: green, thickness: vec-width), 
            mark: (start: "stealth", end: "stealth", fill: green))
      })

      // ============================================
      // 3. DRAW STRAIGHT VECTORS
      // ============================================
      // Drawn last to stick out on top of everything
      
      set-style(stroke: (thickness: vec-width), mark: (end: "stealth"))

      // Blue Arrow (Up)
      line((0,0,c), (0,0,c + 1.5), stroke: blue, mark: (fill: blue))

      // Red Arrow (Right)
      line((c,0,0), (c + 1.5,0,0), stroke: red, mark: (fill: red))

      // Green Arrow (Out/Left)
      line((0,-c,0), (0, -c - 1.5, 0), stroke: green, mark: (fill: green))
    }
  )
})
