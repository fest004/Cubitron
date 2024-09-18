---
sidebar_position: 1
title: How it works
description: How a self balancing cube works
---

The moment of inertia tensor $\mathbf{I}$ is a second-order tensor that describes the distribution of mass in a rigid body with respect to its rotation.
For a rigid body consisting of $N$ particles, each with mass $m_i$ located at position $\mathbf{r}_i = (x_i, y_i, z_i)$ in a given coordinate system, the components of the inertia tensor are given by:

$$
I_{jk} = \sum_{i=1}^{N} m_i \left( \delta_{jk} \mathbf{r}_i^2 - r_{i,j} r_{i,k} \right)
$$

where $r_{i,j}$ and $r_{i,k}$ are the $j$th and $k$th components of the position vector $\mathbf{r}_i$ of the $i$th particle, $\delta_{jk}$ is the Kronecker delta, and $\mathbf{r}_i^2 = x_i^2 + y_i^2 + z_i^2$.

For a continuous mass distribution, this becomes an integral:

<!-- && -->
<!-- I_{jk} = \int_V \rho(\mathbf{r}) \left( \delta_{jk} \mathbf{r}^2 - r_j r_k \right) dV -->
<!-- && -->

where $\rho(\mathbf{r})$ is the mass density function and $V$ is the volume of the rigid body.

The diagonal elements of the inertia tensor represent the moments of inertia about the coordinate axes:

<!-- && -->
<!-- I_{xx} = \int_V \rho(\mathbf{r}) (y^2 + z^2) \, dV -->
<!-- && -->
<!-- && -->
<!-- I_{yy} = \int_V \rho(\mathbf{r}) (x^2 + z^2) \, dV -->
<!-- && -->
<!-- && -->
<!-- I_{zz} = \int_V \rho(\mathbf{r}) (x^2 + y^2) \, dV -->
<!-- && -->

<!-- The off-diagonal elements are the products of inertia: -->

<!-- && -->
<!-- I_{xy} = I_{yx} = -\int_V \rho(\mathbf{r}) x y \, dV -->
<!-- && -->
<!-- && -->
<!-- I_{xz} = I_{zx} = -\int_V \rho(\mathbf{r}) x z \, dV -->
<!-- && -->
<!-- && -->
<!-- I_{yz} = I_{zy} = -\int_V \rho(\mathbf{r}) y z \, dV -->
<!-- && -->

<!-- Thus, the inertia tensor $\mathbf{I}$ can be written in matrix form as: -->

<!-- && -->
<!-- \mathbf{I} = \begin{pmatrix} -->
<!-- I_{xx} & I_{xy} & I_{xz} \\ -->
<!-- I_{yx} & I_{yy} & I_{yz} \\ -->
<!-- I_{zx} & I_{zy} & I_{zz} -->
<!-- \end{pmatrix} -->
<!-- && -->
