---
title: Testing
sidebar_position: 1
description: Testing details
---


# Single Plane Testing

Testing with one side of the cube in a 2D plane with 1 DOF will provide a surprising amount of feedback and hints on what to do next. This makes it the first major milestone of this project.

The test will include primitive versions of several integral components of the final product.

## Cube-Face

The face of the cube itself will need options for connecting the other components. Iterating on the cube-face will be important, as this is one of the components we plan to fabricate in aluminum for the final project. To avoid ordering it more than once, 3D-printed prototypes will help keep the project within both budget and time constraints.

The cube-face will need the following:

 -   Fastening for the motor-holder
 -   Fastening for the flywheel
 -   Mechanism for attaching to an anchor point
 -   Ability to withstand forces from the flywheel/motor

## Braking Mechanism

Testing the braking mechanism is arguably the most important aspect of this prototype, as we are currently deciding between two different approaches.

### Bicycle Mechanism

A bicycle brakes by applying pressure to the side of the wheel, holding it in place and stopping it. This idea inspires the first mechanism: a small servo will push a cylinder made of material with high friction against the flywheel.

### Collision Mechanism

Another approach is to have small protrusions on the edge of the flywheel, which we can intentionally block, causing it to stop instantly. To absorb the impact, a small bendable piece of metal will be attached to the servo, preventing the servo from being damaged by continuously absorbing large forces. While the servo still pushes an object to stop the wheel, this solution differs significantly from the bicycle mechanism.

Regardless of the mechanism chosen, it will need to meet the following requirements:

 -   Stop the wheel fast enough to transfer enough energy
 -   Provide consistent performance
 -   Require infrequent maintenance or be easy to replace (ideally both)
 -   Be fastened to the cube
 -   Maintain optimal weight distribution

## Motor

For the first prototype, we’ve already ordered a set of inexpensive motors. Fast acceleration of the flywheel will be less critical at this stage, as it becomes more important when multiple motors are working together across several planes. These motors will serve as a benchmark, helping us estimate the specifications for the final project. Still, they will need to generate enough kinetic energy to rotate the cube-face 90 degrees in one go, with enough acceleration to change direction when balancing.

## Balancing

Having only one plane to worry about will make mathematical model prototyping much easier. We want a super stable cube, as that’s what will create the "magical" effect. Any wobbling will detract from the desired appearance. Much of this will depend on the algorithm we choose for balancing, as well as our placement and usage of our sensor.


