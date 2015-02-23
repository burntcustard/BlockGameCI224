CI224 University Gamesdev Semester 2 Assessment
List of team members & objectives:
Reece Cunningham, Owen Alister-Hooke, John Evans

Essential objectives:

1) Create a cubeworld with at least 10 different cubes, or OpenGL shapes.

2) All cubes to be at least different colours and size. Textured cubes if possible and time permits.

3) A firstperson camera that can move around the cubeworld.

4) Collision detection between objects.

5) Gun that shoots cubes.

6) Makefile and build system.

7) Supported on different platforms (Linux and Windows), android as well but not essential as windows and Linux.

8) Thorough testing and supporting documentation such as doxygen.

Objectives extended:

1) Jump on cubes.

2) Enemies.

3) Add up score for amount of cubes shot.

4) timer on screen.

Project pitch
We intend for the game to be a first person shooter cubeworld game, where there are a set of randomly generated OpenGL cubes or shapes, which are all different sizes and colours (or textures), and there is a first person camera with a gun model showing. The aim of the game is to shoot all the cubes within the cubeworld in the quickest time possible, whilst avoiding the enemies trying to prevent you from doing this. All of the things we would like to implement within the game can be found within the objectives list, such as adding the ability to jump on top of the cubes to make the game have greater playability for the user.

Project plan
To meet the objectives of our assessment we will use our current semester 1 code and extend on this by adding more cubes and OpenGL shapes. Then further extending the code by implementing the objectives needed for the game as stated above. In order to ensure we have a working game done properly, we will list the objectives from most important to least important and separate the objectives into essential objectives and extended objectives. Then after creating the objectives list, we will create small goals or sub-objectives for each main objective, and the goals can be spread across the group to complete. Alternatively whole small features (objectives) can be assigned to each group member. To ensure as many objectives as possible are met, for each essential objective a deadline will be set i.e. feature 1 needs to be complete within a fortnight at the latest. Work done by each group member can be done forking the main repository for the project and once complete creating a pull request.

Proposed technology
1) C++11

2) SDL2

3) SDL2_IMAGE

4) OPENGL

5) GLEW

6) Automated build tools

7) Testing tools

Marking scheme
25% working playable game level

Cubeworld (set of 3D cubes)
First person camera
Collision detection
Shoot projectiles and cubes removed when hit
25% Using standard tools such as git, makefile etc.

Continuous integration
Doxygen for commenting code
Build system
Testing
25% Code quality

Structured well and thoroughly commented
Build and run successfully on at least two platforms
25% enhancements to game

Add up and display player score
Enemies attacking, reducing score and/or creating a failure state (i.e. player dies)
Ability for player and/or enemies to jump on cubes
Differentiation of cubes (e.g. higher point values for smaller cubes)
Messages for player i.e. game over, highscore
