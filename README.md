# Modelling and Particles in OpenGL

This cooperative project, carried out along with [@git-akispa](https://github.com/git-akispa), involves the implementation of advanced topics Computer Graphics such as hierarchical 3D modelling and particle/physics systems using C and FreeGLUT for rendering and interaction.

* [Hierarchical Modelling](#hierarchical-modelling)
* [Particle Physics](#particle-physics)
* [Setup (Windows)](#setup-windows)

<br/>

### Hierarchical Modelling

<p align="center">
  <img src="./media/cg2_exhibition_1.gif" alt="Test Run Exhibition" width="675" height="486">
  <br>
  <i> Preview of the first part of the project on Hierarchical Modelling. </i>
</p>

* Rendering of a **hierarchical (tree) 3D model of a dog**, comprised of `GLUquadricObj`s. 
* Features a **GUI (drop-menu) for interacting with the rendered model**, which can perform different actions such as "jump", "give paw", "nod", etc. 
* Virtual dog is initially located on the origin.
* The camera performs a **low-res motion along the surface of a sphere** centered at the origin, always **oriented to face the origin** directly.
* **Camera position** is modified **using the arrow keys**. 
* **Sphere radius** is increased/decreased **using the PgUp/PgDn buttons**.
* Implemented by [@git-akispa](https://github.com/git-akispa).

<br/>

### Particle Physics

<p align="center">
  <img src="./media/cg2_exhibition_2.gif" alt="Test Run Exhibition" width="680" height="498">
  <br>
  <i> Preview of the second part of the project on Particle Physics. </i>
</p>

* Simulation of a **3D particle system** using classical (newtonian) dynamics and collisions. 
* Features a **GUI (drop-menu) for interacting with the world**, which can render different surfaces. 
* **Air drag** is turned on or off by pressing the **'A' key** (toggle mode) and increased/decreased using the **Up/Down arrow keys**.
* Main platform is a rectangle with its centre on the origin.
* The camera performs a **high-res motion along the surface of a sphere** centered at the origin, always **oriented to face the origin** directly.
* **Camera position** is modified by **moving the mouse while holding down left mouse button**. 
* **Sphere radius** is increased/decreased by **scrolling the wheel Up/Down**.
* Utilises a custom linked list implementation and the threading API of `<Windows.h>` to generate and keep track of the particles.
* Implemented by [@Dimyfantidis](https://github.com/DimYfantidis).

<br/>

### Setup (Windows)

*Project is platform-specific for MS Windows architectures as it uses the `<Windows.h>` API and precombiled binaries of FreeGLUT for Windows.*

1. Clone the project:
    ```
    git clone https://github.com/DimYfantidis/Modelling_and_Particles_OpenGL.git
    ```
2. Navigate to the `build` directory:
    ```
    cd ./build
    ```
3. Compile using CMake for 🟣 Visual Studio (MSVC):
    ```
    cmake ..
    ```
4. Open the main solution, `./build/modelling_and_particles.sln`, using Visual Studio.
5. Set the `modelling_and_particles` project as startup project.
6. Run the program (Ctrl + F5).
