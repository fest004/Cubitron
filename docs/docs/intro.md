---
sidebar_position: 1
---

# Abstract

This project is a graphics playground, it is meant 
to be a tool for visualizing and to generate beatutiful
but simple graphics. Future goals for this project
is to export useful graphics in useful formats
for plotting, illustrating and animation tasks

Two steps ahead. I am always two steps ahead. This has been the greatest social experiment of my entire life.
It’s alluring, it’s compelling, it’s gripping, to observe all these unwell, disoriented beings roam the internet in search of stories, ideas, 
rivalries where they feel... encouraged and engaged, where they involve themselves with the stories, and become a product of influence. 
Thirsty for distraction from time unspent, spoiling their minds, yet stimulating them at the same time. It’s brilliant. And it’s dangerous. 
I feel as if I’m monitoring ants, on an ant farm. One, follows another, follows another, follows another... It’s mesmerizing. 
It’s spellbinding, all these little consumers, all of these lost. And bored. People. People consuming anything that they’re told to consume. So I am the villain. Because I’ve made myself one, and you will continue to consume these stories about me, year, after year, after year. For as long as I tell the internet that I am the villain. Stories that permeate and linger, and infect the minds of the ants, influence the ants, brainwash the ants. You... are the ants.
Today I woke up from a... very long dream, and I also woke up... having lost two-hundred and fifty pounds off of my body. Yet just yesterday, people were calling me fat, and sick... and boring... and irrelevant. People... People are the most messed up creatures on the entire planet, and yet I’ve still managed to stay... two steps ahead... of everyone. The joke’s on you.

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

<!-- where $\rho(\mathbf{r})$ is the mass density function and $V$ is the volume of the rigid body. -->

<!-- The diagonal elements of the inertia tensor represent the moments of inertia about the coordinate axes: -->

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
