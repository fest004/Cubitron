#set text(font: "TeX Gyre Schola")
#show math.equation : set text(font:"TeX Gyre Schola Math")
#show heading : it => {
  set block(below: 1em, above: 3em)
  set text(weight: "bold",  font:"TeX Gyre Bonum" )
  smallcaps(it)
}
#text(font:"TeX Gyre Bonum",weight: "black", size: 35pt,
smallcaps("CUBITRON")
)
#set par(justify: true)
#text(font: "TeX Gyre Bonum", weight: "bold",
  [Felix Strand #h(1.2cm) Brage Wiseth]
)
= Introduction
In this project, we aim to design and build a self-balancing cube using reaction wheels, a type
of control mechanism commonly used in spacecraft for attitude control. The goal is to create a compact,
dynamically stable system capable of maintaining its equilibrium in three-dimensional space without external support.
The cube, with its simple geometric structure, presents unique challenges in terms of balance and orientation control,
making it an excellent platform for exploring the principles of feedback control systems and mechanical design.

Reaction wheels, which function by spinning at varying speeds to produce torques that counteract disturbances,
will serve as the core actuators for balancing the cube. By carefully coordinating the speeds of these wheels,
the system will be able to counteract any rotational forces, allowing the cube to maintain stability in any orientation.

This project will involve multiple stages, including the design and fabrication of the cube, the selection and
integration of reaction wheels, the development of sensors to track its orientation, and the implementation of a
control algorithm that adjusts the wheel speeds in real-time to correct any deviations. The project not only
challenges our understanding of dynamic systems and control theory but also has the potential to inform future
applications in robotics, aerospace, and precision engineering, where balance and stability are crucial.

Ultimately, the self-balancing cube will serve as a proof-of-concept for demonstrating the potential of
reaction wheels in balancing and controlling small-scale systems, offering a hands-on opportunity to delve
into the fascinating intersection of mechanical engineering, robotics, and control theory.


= First Principles
How can we balance with just a set of spinning wheels that don't even touch the ground? Well the same way
you and I would balance on a slack line or on a fence post, We pivot our arms around our torso kinda like how
a plane would turn its wings when banking. How this makes us balance is not at all obvoius, but it has something
to do with angular momentum and torques, considering that we are rotating our body. Another hint is that
by extending our arms further out or even using a rod to artifitially extend our arms we can greatly
enhance our ability to balance. By doing so we create torque, we can use this exact theqnique with flywheels only
instead of it beeing two arms we essentially have infinite arms stacked in a circle.
