# fermions and antisymetric wave functions

>main difference between boson and fermion is antisymmetry. 
>This generally involves introducing a determinant somewhere.

## Quantum dots
    electrons, generally confined in 2-dim potential traps 
    often in semi-conductors

- fermions
- trapped in HO-like oscillator like potentials

###ex
N=6 HO system
1 particle

    E<sup>n<sup>x</sup>, n<sup>y</sup></sup> = \hbar\omega (n<sup>x</sup> + n<sup>y</sup> + )

HO potential -> convex function
    > figure on lecture notes

    Eventually, there's space for 2 fermions in a single-particle HO wf
    \psi<sup>i</sup> = \phi<sup>n<sup>x<sup>i</sup</sup>>, n<sup>y<sup>i</sup></sup></sup> \chi<sup>s<sup>i n<sup>s<sup>i
                    |                   |
                  HO wf              1/2 spinn

Further plot of a more complex system

    E<sup>20        E<sup>11        E<sup>02    |   3 \omega

        E<sup>10            E<sup>01        |   2 \omega

                E<sup>00                |     \omega
eg.

> Quantum dots reffered to as artificial atoms. 
> you can transfer a lot of atomic behaviour to 
> quantum dots


## N=2
    E<sup>0 = 2\omega

###\psi<sup>T

\psi<sup>1(\vec{r<sup>i})  = \phi<sup>{00} \chi<sup>{1/2, 1/2}(s<sup>i)
r = \sqrt( x<sup>i^2 + y<sup>i^2 ); \vec{r<sup>i} = x<sup>i\vec{e<sup>x} + y<sup>i\vec{e<sup>y}
\psi<sup>2(\vec{r<sup>i}, s<sup>i) = \phi<sup>{00}(r<sup>i) x<sup>{1/2, -1/2}(s<sup>i)
\psi(\vec{r}, \vec{r<sup>e 


> Slater determinant

build up many body system based on several one-body systems

With N particles, we need to solve an NxN determinant
:
:
:
\psi<sup>{00} \proportional \exp( - (1/2) \alpha^2 (x<sup>i^2 + y<sup>i^2) ) 
Hermite polynomial  H<sup>u<sup>x<sup>i(x<sup>i) H<sup>u<sup>y<sup>i(y<sup>i) 
    - the 0th polynomial is always set = to 1  
    H<sup>0(i) = 1

    - Spatial part symmetric ( \phi<sup>{00}(1)\phi<sup>{00}(2) )
    - Spin part is anti-symmetric, S=0, M<sup>s = m<sup>s<sup>1 0 m<sup>s<sup>2 = 0

    Hamiltonian is spin-independent => the spin cannot change. 
    <psi'|H|psi> = 0
s' =/= S
H = H<sup>0 + H<sup>1
H<sup>0 \sum<sup>{i=1}^2 (-(1/2) \del<sup>i^2 + (1/2)\omega^2r<sup>i^2 ).... I missed something. 

...possibly solving the <||> expression above? 

##How to deal with a determinant efficiently in our vmc code? 

\psi<sup>T = \psi<sup>D X \psi<sup>J
D = anti-symmetry
J = Jastrow correlation


determinant
            | d<sup>11 d<sup>12 ... d<sup>1N |
            | d<sup>21 .         .   |
D   =       |   .    .       .   |
            |   .      .     .   |
            | d<sup>N1 ...      d<sup>NN |

D \element real numbers dim NxN
obtain determinant O(N^3) FLOPS - mounting N-particles
 ~ o(N^4) FLOPS

###Metropolis ratio

    |\psi<sup>D(r^{new})\psi<sup>j8(r^{new})|^2 / |\psi<sup>D(r^{old})\psi<sup>J(r^{old})|^2

use linalg and moving 1 particle at a time to simplify problem. so we use less than O(N^4) FLOPS

*Slater determinant == SD*
SD(\vec{r<sup>1}, \vec{r<sup>2}, ..., \vec{r<sup>N}, s<sup>1, s<sup>2, ..., s<sup>N )

                    |\psi<sup>1(1) ...  \psi<sup>1(N) |
=   (1/\sqrt(N!))   |\psi<sup>2(1)                |
                    |   ..                    |
                    |\psi<sup>N(1) ...  \psi<sup>N(N) |

collumns are for a given particle, rows refer to specific quantum numbers <- at least one of them for each

3x3 determinant example in lecture for 26/3-2020

rewrite this to



det(3x3) = \sum<sup>{i=1}^n d<sup>{ij}\cdot C<sup>{ij} 

C<sup>{ij} = (-1)^{i+j}M<sup>{ij}


##Metropolis test

R = \psi<sup>{SD}(r^{new}) / \psi<sup>{SD}(r^{old}) = \sum<sup>{i=1}^n d<sup>ij (r^{new}C<sup>ij(r^{new}) / \sum<sup>{i=1}^n d<sup>ij(r^{old})C<sup>ij(r^{old})

> moving particle j from r<sup>j^{old} to r<sup>j^{new} leaves C<sup>ij(r^{old}) = C<sup>ij(r^{new})

> C<sup>ij/|D| = d<sup>ji^{-1}

R = \sum<sup>{j=1}^n d<sup>ij(r^{new}) d<sup>ji^{-1}(r^{new}) / [\sum<sup>{j=1}^n d<sup>ij(r^{old})d<sup>ij^{-1}(r^{old})=\kroenickerdelta<sup>ij ]
    = \sum<sup>{j=1}^n d<sup>ij(r^{new})d<sup>ji^{-1}(r^{old})


# 1st simplification
> Essentially, calculate a determinant and it's inverse once at start. Then reuse through program 
# 2nd simplification

\del<sup>i |\psi<sup>SD| / |\psi<sup>SD| = \sum<sup>{j=i}^N \del<sup>i \psi<sup>j(r<sup>i) \cdot d<sup>ji^{-1}(r<sup>i) | r<sup>i == \vec{r<sup>i}










